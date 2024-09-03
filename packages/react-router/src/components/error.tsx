import {useAsyncError} from 'react-router-dom';

export const ErrorElement = () => {
  const error = useAsyncError() as {message: string};
  console.log('error', error);
  return <div>{error.message}</div>;
};
