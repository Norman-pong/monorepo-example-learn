import React from 'react';
import { StyledButton } from './Button.styled';

const Button = ({ children }) => (
  <StyledButton>
    {children}
  </StyledButton>
);

export default Button;
