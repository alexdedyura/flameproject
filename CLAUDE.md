# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

> For a detailed architecture and systems reference, see `sources/ARCHITECTURE.md`.

## What this is

Flame Project is an RPG gamemode for **open.mp** (open multiplayer) written in **Pawn**. The whole gamemode compiles to a single `.amx` from one entry point: `sources/flame.pwn`. The legacy SA-MP server has been fully retired; the gamemode runs SA-MP-style code through open.mp's compatibility layer (`#define SAMP_COMPAT` + `#include <open.mp>` at the top of `flame.pwn`).

## Build

```bat
compile.bat
```

This invokes the open.mp toolchain `qawno\pawncc.exe` on `sources\flame.pwn` and moves the resulting `flame.amx` into `gamemodes\`. There is no separate lint or unit-test step — "passing" means the Pawn compiler produces `flame.amx` without new errors/warnings. After changing Pawn code, run the build and confirm it still compiles; if you cannot run it, say so explicitly and describe what you checked instead.

To run the server: `omp-server.exe` (Windows) reads `config.json`, which lists the main script (`pawn.main_scripts: ["flame"]`), the legacy plugins, and all open.mp settings. (`config.json` replaces the old `server.cfg`; `qawno` replaces the old `pawno`.)

## Architecture

`sources/flame.pwn` includes a small set of **aggregating `.inc` files**, each of which pulls in its own submodules. Load order in `flame.pwn` matters and encodes real dependencies (e.g. `player/phone.inc` is included *after* `vehicles/vehicles.inc` because the phone's vehicle-call feature needs both player inventory and vehicle enums).

The top-level modules and their aggregators:

- `sources/core/core.inc` — engine-level helpers: MySQL wrappers, colors, dialogs, macros, zones, timers, string/date utils. Start here for shared helpers.
- `sources/textdraws/textdraws.inc` — all textdraw UI (speedometer, inventory, iPhone, loading screen, etc.).
- `sources/player/player.inc` — auth, account/inventory load & save, documents, licenses, bank, quests, RP rating, spawn, death.
- `sources/vehicles/vehicles.inc` — vehicle core, ownership, keys, sharing/carsharing, shop, fuel, tax, speedometer.
- `sources/player/phone.inc` — smartphone subsystem (see notes below).
- `sources/player/admin/admin.inc` — admin tools, spectate.
- `sources/objects/object.inc` — static map objects / interiors per location.
- `sources/systems/systems.inc` — bus stops, pickups, weather.
- `sources/commands/commands.inc` — all chat commands, grouped by theme (main, world, chat, mapping, anim, fraction).

### Conventions

- **Callbacks**: extend callbacks via `YSI\y_hooks` (`hook OnX()`) where neighboring code already does. `flame.pwn` itself dispatches some callbacks manually to per-module functions like `Vehicles_OnPlayerStateChange(...)` — follow whichever pattern the surrounding module uses.
- **Commands**: add via `izcmd` as `CMD:name(playerid, params[])`, matching nearby commands. Parse args with `sscanf2`.
- **MySQL**: use the existing helpers in `sources/core/mysql.inc` (`UpdateBaseInt/Str/Float`, `mysql_format` + `mysql_function_query` with callback patterns). DB name is `flame`; schema/dump is `database/flame.sql`.
- **New submodule**: include it through the nearest aggregating `.inc`, not directly from `flame.pwn`.
- `forward` before `public` for timer/MySQL callback functions when the compiler requires it and neighbors do so.
- **open.mp compat**: keep the `SAMP_COMPAT` shim happy — use `true`/`false` for bools, `foreach (new i : Vehicle)`-style iterators, and hoist `mysql_format` literals into temps where the compat headers need it.

### Dependencies

Two layers, both bundled in the repo (treat as read-only — see "Do not touch"):

**Legacy Pawn plugins** (`plugins/*.dll`, loaded via `pawn.legacy_plugins` in `config.json`):

| Plugin | Version | Purpose |
| --- | --- | --- |
| `crashdetect` | — | AMX crash/error backtraces during development |
| `jit` | — | Pawn JIT compiler for runtime speed |
| `streamer` | v2.9.6 (Incognito) | streams objects/pickups/labels/zones beyond native limits |
| `sscanf` | 2.13.8 | string/argument parsing (`sscanf2`) for commands |
| `mysql` | — | MySQL DB access (`a_mysql`); talks cp1251 |
| `pawn-memory` | — | low-level heap/memory helpers |
| `rustext` | — | server-side Russian text rendering (`SetDefaultRussifierType`, set in `OnGameModeInit`) |

`pawnraknet` and `CRP` from the old SA-MP setup are no longer loaded (a stale `plugins/pawnraknet.cfg` may remain).

**open.mp components** (`components/*.dll` — Actors, Vehicles, Objects, TextDraws, Pickups, Dialogs, etc.): the engine's native subsystems, shipped with the server. Don't edit; just rely on their natives.

Compile-time includes live in `qawno/include` (`open.mp`, `YSI`, `izcmd`, `sscanf2`, `streamer`, `a_mysql`, `rustext`). Keep changes compatible with all of the above.

## Encoding (important)

Source/README files containing Russian text **must be saved in legacy Windows-1251 (cp1251)**, and MySQL is configured to talk cp1251 (see `mysql.inc`). Russian text will often appear as mojibake in tools — that is expected, not corruption. If a file with Cyrillic is saved as UTF-8 (or any non-cp1251 encoding), the in-game text breaks into "кракозябры" — e.g. mangled smartphone dialogs and on-screen strings instead of readable Russian.

Practical rules:

- **Do not** auto-recode whole files or change a file's encoding for a small edit. When editing an existing file, preserve its current encoding.
- **Never use the `Edit`/`Write` tools (or any tool that rewrites the whole file as UTF-8) on a cp1251 file that contains Cyrillic — not even for an ASCII-only change.** These tools re-encode the *entire* file on save, so a cp1251 file is read as UTF-8: every Cyrillic byte that isn't valid UTF-8 becomes U+FFFD (`EF BF BD`), which is **unrecoverable** — the original letters are gone. This is the #1 way this project's files get destroyed. Instead, make ASCII-only edits to cp1251 files with **byte-safe** tools that don't transcode: `perl -i -pe 's/.../.../'` (operates on raw bytes), `sed -i` by line number, or PowerShell reading/writing a `[byte[]]` via `[System.IO.File]::ReadAllBytes/WriteAllBytes`.
- If a cp1251 file's Cyrillic has already been turned into `EF BF BD` (renders as `пїЅ` when re-read as cp1251), it cannot be repaired in place — restore the clean text with `git checkout HEAD -- <file>`, then re-apply only the genuine ASCII code changes with the byte-safe tools above.
- When you genuinely need to add Russian text, write that file (or fragment) explicitly in cp1251 — e.g. via PowerShell `[System.Text.Encoding]::GetEncoding(1251)` and `[System.IO.File]::WriteAllText(...)` — and verify the bytes (e.g. `января` → `FF ED E2 E0 F0 FF`). `sources/player/phone_clock.inc` is an example of a cp1251 file holding Russian month/weekday names; keep it in cp1251.
- This applies to **Cyrillic in comments too**, not just strings — a `// пусто` comment saved as UTF-8 still corrupts the file's encoding. If you cannot write a Cyrillic comment as cp1251, write it in English (ASCII) instead. Never let a UTF-8 Cyrillic byte sequence land in a `.inc`/`.pwn` source file.
- **Before finishing any task that edited a Cyrillic source file, verify no UTF-8 Cyrillic crept in.** A correct cp1251 file has no `D0`/`D1` lead bytes followed by a `0x80–0xBF` continuation byte. Check with: `grep -laP '[\xD0\xD1][\x80-\xBF]' sources/**/*.inc sources/**/*.pwn` — it must print nothing. If a file is flagged, do a byte-level replace of the UTF-8 sequence with its cp1251 equivalent (do **not** re-save the whole file as UTF-8).

## Do not touch without explicit need

- Bundled `qawno/` (includes + `*.exe`), `omp-server.exe`, and the engine binaries in `components/` and `plugins/`.
- `gamemodes/flame.amx` — it is a build artifact only, never hand-edit.
- Mass changes to `config.json`, `database/flame.sql`, or `scriptfiles/` runtime data.
- Unrelated changes in the git tree — check `git status --short` before editing.

Project is in early development: backward compatibility with old accounts/saved data is **not** required unless the user asks for it.

## Smartphone subsystem notes

- Logic in `sources/player/phone.inc`; textdraws in `sources/textdraws/iphone.inc` (generated from root `iphone.txt.txt`).
- Wallpaper reuses the **global** `iPhone[6..11]` background pieces so they render *below* the status bar/icons; per-player color comes from setting `TextDrawColor` right before `TextDrawShowForPlayer` (captured at show time, so simultaneous viewers don't clash). Per-player overlays render *on top* of globals — don't use them.
- Clock: `PhoneUpdateClock()` in `sources/player/phone_clock.inc` (cp1251 — Russian month/weekday names) runs on open and every second via `Phone_PlayerSecTimer`.
- Item id `INV_ITEM_PHONE = 6`, param `INV_PHONE_PARAM = 1`; wallpaper choice saved in `PlayerInventory[playerid][slot][invInfo]`.
- SMS history in MySQL table `phone_messages` — keep the per-dialog limit at 100, prune older rows after inserts.
- `/givephone` issues a phone for local testing.
