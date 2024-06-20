import styled from 'styled-components';

export const StyledButton = styled.button`
  padding: 0.5em 1em;
  margin: 0.5em;
  color: white;
  background-color: ${(props) => props.theme.primaryColor};
  border: none;
  border-radius: 3px;
  cursor: pointer;

  &:hover {
    background-color: ${(props) => props.theme.secondaryColor};
  }
`;
