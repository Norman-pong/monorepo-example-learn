## Promise 组合拳

<aside>
💡

一个 Promise 实现加载、渲染、错误处理等应用

</aside>

关键组件

- `React.Suspense`
- `Await`

关键函数

- `useAsyncValue` ：获取 Promise 返回值
- `useAsyncError` ：获取 Promise 错误值

```bash
export const apiModels = {
  getAsyncValue: async (isError?: boolean) => {
    console.log('getAsyncValue');
    return new Promise((resolve, reject) => {
      setTimeout(() => {
        if (isError) reject({message: 'promise error'});
        resolve({
          ip: '',
          fn: 'getAsyncValue',
          params: '',
        });
      }, 1000);
    });
  },
};
```

```bash
import React from 'react';
import {createRoot} from 'react-dom/client';
import {Await, useAsyncError, useAsyncValue} from 'react-router-dom';
import {apiModels} from '../models';

function Loading() {
  return <div>loading...</div>;
}

function ErrorElement() {
  const error = useAsyncError();
  console.log('error', error);
  return <div>{error.message}</div>;
}

function RenderList() {
  const variants = useAsyncValue();
  console.log(variants);
  return <div>{JSON.stringify(variants)}</div>;
}

createRoot(document.getElementById('root')!).render(
  <React.Suspense fallback={<Loading />}>
    <Await
	    resolve={apiModels.getAsyncValue()}
	    errorElement={<ErrorElement />}
	    >
      <RenderList />
    </Await>
  </React.Suspense>,
);
```

<aside>
💡

Await resolve 不能直接使用函数，需要使用 state 作为值，不然变更状态时，函数将会重新执行。渲染数据使用 state 保存，使用 useEffect 更新数据。

</aside>

## 获取数据后再渲染

[loader](https://reactrouter.com/en/main/route/loader#loader)

```tsx
import {StrictMode} from 'react';
import {createRoot} from 'react-dom/client';
import {createBrowserRouter, Navigate, RouterProvider} from 'react-router-dom';
import {IpView} from './pages/ip';
import {apiModels} from './models';
import {Loading} from './components/loading';
import {Loader} from './pages/loader';

const router = createBrowserRouter([
  {
    path: '/',
    element: <Navigate to="/ip/12" />,
  },
  {
    path: '/ip',
    element: <IpView />,
    children: [
      {
        path: ':id',
        loader: apiModels.getIp,
      },
    ],
  },
  {
    path: '/loader',
    element: <Loader />,
    loader: apiModels.getIp,
    children: [
      {
        path: ':id',
      },
    ],
  },
]);

createRoot(document.getElementById('root')!).render(
  <StrictMode>
    <RouterProvider
      router={router}
      fallbackElement={<Loading str="router" />}
    />
  </StrictMode>,
);
```

### 问题

目前在 `Await` 组件配合 `useAsyncValue` 时，使用 Link 跳转则会出现两次渲染（更新前和更新后各渲染一次）。详见 `demo/ip` 页面

```tsx
const RenderList = React.memo(() => {
  const variants = useAsyncValue();
  return <div>{JSON.stringify(variants)}</div>;
});

export const IpView = () => {
  const data = useLoaderData();
  const param = useParams();

  const [list, setList] = React.useState<Promise<unknown>>();

  const getAsyncValue = () => {
    setList(apiModels.getAsyncValue(param));
  };
  useEffect(() => getAsyncValue(), [param]);

  const [count, setCount] = React.useState(0);
  return (
    <div
      style={{
        display: 'flex',
        gap: '10px',
        width: '50vw',
        flexDirection: 'column',
      }}>
      <button onClick={() => setCount(count + 1)}>count: {count}</button>
      <Link
        unstable_viewTransition
        to={`/ip/${Math.floor(Math.random() * 90) + 10}`}
        children="to-transparent"
      />
      <Link
        unstable_viewTransition
        to={`/loader/${Math.floor(Math.random() * 90) + 10}`}>
        to-loader
      </Link>
      <React.Suspense fallback={<Loading />}>
        <Await resolve={list} errorElement={<ErrorElement />}>
          <RenderList />
        </Await>
      </React.Suspense>
    </div>
  );
};
```