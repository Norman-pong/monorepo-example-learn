import {useLoaderData} from 'react-router-dom';

export const Loader = () => {
  const data = useLoaderData();
  return <div>data: {JSON.stringify(data)}</div>;
};
