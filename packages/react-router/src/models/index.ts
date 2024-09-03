import {LoaderFunctionArgs} from 'react-router-dom';

export const apiModels = {
  getIp: async ({request, params}: LoaderFunctionArgs) => {
    console.log('getIp', request);
    console.log('params', params);
    return new Promise(resolve => {
      setTimeout(
        () =>
          resolve({
            ip: '192.168.0.1',
            fn: 'getIp',
            params: params,
          }),
        1000,
      );
    });
  },
  getAsyncValue: async (
    params: LoaderFunctionArgs['params'],
    isError?: boolean,
  ) => {
    console.log('getAsyncValue');
    return new Promise((resolve, reject) => {
      setTimeout(() => {
        if (isError) reject({message: 'promise error'});

        resolve({
          ip: '',
          fn: 'getAsyncValue',
          params,
        });
      }, 1000);
    });
  },
};
