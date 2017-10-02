# InfixPostfix
Converting Infix expression to Postfix and evaluating it
# The Algorithm
## Converting Infix expression to Postfix
Let infix be the input expression, postfix the output expression and opstack operator stack. <br />
If infix begins with -, set firstMinus boolean flag to true and set infix scanning index(i) to 1, otherwise set firstMinus to false and ii to 0. <br />
Now start scanning infix from i character by character (c). <br />
1. If c is operand, while this is true append it to postfix, and set c to infix at i = i+1. <br />
   If firstMinus is true and infix character at 1 is not left bracket append @ (sign for unary minus) to postfix. <br />
2. If c is operator: <br />
   1. If opstack is empty, just push c on opstack
   2. If c is left bracket, push it on opstack
   3. If c is right bracket, pop every opstack element while opstack top element is not left bracket and append it to postfix, and after pop the left bracket (top opstack element). If firstMinus is true, append @ to postfix. <br />
   4. If c is minus and character before c was left bracket, append @ to postfix. <br />
   5. If c is any other operator, while opstack top operator has higher or same priority, append them to postfix and pop from opstack. Now push c on opstack. <br />
3. If opstack is not empty, append its elements to postfix and pop them. <br />

Now return postfix. <br />

## Evaluating postfix expression
Let postfix be the input expression, operandStack be the operand Stack. <br />
Start scanning postfix character by character (c). <br />
1. If c is operand, push it on opstack. <br />
2. If c is operator: <br />
  1. If c is @(unary minus), pop operandStack top element and push its negative. <br />
  2. If c is any other operator (+, -, * or /), pop two operands from operandStack, do the operation indicated by c and push the result on operandStack. <br />
  
Now return operandStack top element (the result). <br />
