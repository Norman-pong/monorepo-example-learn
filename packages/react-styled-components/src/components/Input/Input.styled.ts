import styled from 'styled-components';

export const StyledInput = styled.input`
  padding: 0.5em;
  margin: 0.5em;
  color: ${(props) => props.theme.textColor};
  background: papayawhip;
  border: none;
  border-radius: 3px;
`;
