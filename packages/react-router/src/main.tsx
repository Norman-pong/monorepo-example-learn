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
