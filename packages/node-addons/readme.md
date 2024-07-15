# 说明

## 依赖

- python >= 3.12
- node-gyp >= 10.1.0
- nodejs >= 20.14.0


## 使用

```bash
npm install -g node-gyp
```

进入对应目录

```bash
# /function/napi
node-gyp configure build

node addon.cjs
```

