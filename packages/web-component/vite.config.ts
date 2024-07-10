import { defineConfig } from 'vite'
import packageConfig from './package.json'

// https://vitejs.dev/config/
export default defineConfig({
  build: {
    minify: 'esbuild',
    target: 'esnext',
    // minifyWhitespace: true,
    // minifyIdentifiers: true,
    terserOptions: {},
    outDir: `../../dist/${packageConfig.name}`
  }
})
