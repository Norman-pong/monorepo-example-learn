import React from 'react';
import { ThemeProvider } from 'styled-components';
import GlobalStyles from './components/Styled/GlobalStyles'
import theme from './components/Styled/Theme';
import Button from './components/Button';
import Input from './components/Input';

const App = () => (
  <ThemeProvider theme={theme}>
    <GlobalStyles />
    <div>
      <Button>Click Me</Button>
      <Input placeholder="Enter text" />
    </div>
  </ThemeProvider>
);

export default App;
