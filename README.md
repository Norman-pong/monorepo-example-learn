# monorepo 仓库

## 如何创建 monorepo 仓库

1. 初始化项目：`yarn init`
2. 配置 workspace 路径
   ```json
    // package.json
    {
      ...
      "workspaces": [
        "packages/*"
      ]
    }
  ```
3. 初始化 lerna : `npx lerna init`
4. 更新 lerna 配置
   ```json
    // lerna.json
    {
      ...
      "packages": [
        "packages/*"
      ]
    }
  ```

接下来进入 `package` 目录，就可以使用 `yarn create vite` 创建项目


## yarn 工具链

使用 lerna 作为 workspace 管理，详细查看 package.json 与 lerna.json

1. 快速安装所有依赖：`npx lerna bootstrap`
2. 发布新的版本：`npx lerna publish`