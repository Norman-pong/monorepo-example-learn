import React, {useEffect} from 'react';
import {
  Await,
  Link,
  useAsyncValue,
  useLoaderData,
  useParams,
} from 'react-router-dom';
import {Loading} from '../components/loading';
import {apiModels} from '../models';
import {ErrorElement} from '../components/error';

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
      <div>getIp: {JSON.stringify(data)}</div>
      <div>param: {JSON.stringify(param)}</div>
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
      <React.Suspense fallback={<Loading />}>
        <Await resolve={list} errorElement={<ErrorElement />}>
          <RenderList />
        </Await>
      </React.Suspense>
    </div>
  );
};
