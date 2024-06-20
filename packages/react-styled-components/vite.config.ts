import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import packageConfig from './package.json'

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [react()],
  build: {
    outDir: `../../dist/${packageConfig.name}`
  }
})
