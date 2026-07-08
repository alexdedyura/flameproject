// @ts-check
// Docusaurus config — https://docusaurus.io/docs/api/docusaurus-config
import {themes as prismThemes} from 'prism-react-renderer';

/** @type {import('@docusaurus/types').Config} */
const config = {
  title: 'Flame Project',
  tagline: 'Open Source RPG-гейммод для open.mp',
  favicon: 'img/favicon.svg',

  // Продакшн-адрес GitHub Pages: https://alexdedyura.github.io/flameproject/
  url: 'https://alexdedyura.github.io',
  baseUrl: '/flameproject/',

  organizationName: 'alexdedyura',
  projectName: 'flameproject',
  trailingSlash: false,

  onBrokenLinks: 'throw',

  markdown: {
    hooks: {
      onBrokenMarkdownLinks: 'warn',
    },
  },

  i18n: {
    defaultLocale: 'ru',
    locales: ['ru'],
  },

  presets: [
    [
      'classic',
      /** @type {import('@docusaurus/preset-classic').Options} */
      ({
        docs: {
          routeBasePath: '/', // документация обслуживается из корня сайта
          sidebarPath: './sidebars.js',
          editUrl:
            'https://github.com/alexdedyura/flameproject/tree/main/website/',
        },
        blog: false,
        theme: {
          customCss: './src/css/custom.css',
        },
      }),
    ],
  ],

  themeConfig:
    /** @type {import('@docusaurus/preset-classic').ThemeConfig} */
    ({
      image: 'img/social-card.svg',
      colorMode: {
        defaultMode: 'dark',
        respectPrefersColorScheme: true,
      },
      navbar: {
        title: 'Flame Project',
        logo: {
          alt: 'Flame Project',
          src: 'img/logo.svg',
        },
        items: [
          {
            type: 'docSidebar',
            sidebarId: 'docsSidebar',
            position: 'left',
            label: 'Документация',
          },
          {
            href: 'https://github.com/alexdedyura/flameproject',
            label: 'GitHub',
            position: 'right',
          },
        ],
      },
      footer: {
        style: 'dark',
        links: [
          {
            title: 'Документация',
            items: [
              {label: 'Введение', to: '/'},
              {label: 'Установка', to: '/getting-started/requirements'},
              {label: 'Игровые системы', to: '/systems/authorization'},
            ],
          },
          {
            title: 'Проект',
            items: [
              {label: 'GitHub', href: 'https://github.com/alexdedyura/flameproject'},
              {label: 'open.mp', href: 'https://www.open.mp/'},
            ],
          },
        ],
        copyright: `Flame Project © ${new Date().getFullYear()} Alex Dedyura. Лицензия GNU GPL v3.0.`,
      },
      prism: {
        theme: prismThemes.github,
        darkTheme: prismThemes.dracula,
        additionalLanguages: ['bash', 'json', 'sql', 'ini', 'batch'],
      },
    }),
};

export default config;
