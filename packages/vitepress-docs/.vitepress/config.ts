import { defineConfig } from 'vitepress'
export default defineConfig({
  title: 'monorepo-react-learn',
  srcDir: './docs',
  outDir: '../../dist/docs',
  head: [
    ['link', { rel: 'icon', href: '/favicon.ico' }]
  ],
  vite: {
    server: {
      port: 4300
    }
  },
  ignoreDeadLinks: true,
  themeConfig: {
    search: {
      provider: 'local',
      options: {
        translations: {
          button: {
            buttonText: '搜索'
          }
        }
      }
    },
    sidebarMenuLabel: '菜单',
    lastUpdatedText: '最后更新',
    outlineTitle: '目录',
    returnToTopLabel: '回到最顶',
    // logo: 'https://hospital-fe-asset-1306793870.cos.ap-guangzhou.myqcloud.com/logo/hdf-logo-single.png',
    // logo: '/hdf-logo-single.png',
    socialLinks: [{
      icon: 'github',
      link: 'https://github.com/Norman-pong/monorepo-react-learn/tree/master'
    }]
  }
})