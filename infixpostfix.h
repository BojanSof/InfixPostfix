//Converting Infix expression to Postfix and evaluating
#include <algorithm>
#include <stack>
#include <string>
//character is operand if it is digit 0-9 or decimal point (.)
inline bool isOperand(char c){
    if((c >= '0' && c <= '9') || c == '.') return true;
    else return false;
}
inline bool isOperator(char c){
    if(c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c == '@') return true;
    else return false;
}
//unary minus (@) has highest priority operator and operators * and / have higher priority than + and -
int priority(char op){
    int p;
    if(op == '@') p = 3;
    else if(op == '*' || op == '/') p = 2;
    else if(op == '+' || op == '-') p = 1;
    else p = 0;
    return p;
}
/* 
 * InFix to PostFix algorithm:
 * infix is the input string, postfix is the output string, opstack is operators stack (char stack)
 * Start scaning the input infix expression from left to right character by character:
 * 1. If character is operand, add it to postfix.
 * 2. 1. If character is operator and the opstack is empty, push it on opstack.
 *    2. If character is left bracket, push it on opstack.
 *    3. If character is right bracket, pop every opstack element and add it to postfix while opstack.top() is left bracket.
 *    4. If character is operator and has higher priority than opstack.top(), push it on opstack.
 *    5. If character is operator and has lower or same priority as opstack.top(), pop every opstack element which 
 *       has higher 
 *       or same priority as the operator, add it to postfix, than push the operator on opstack.
 * 3. If all characters are scaned and opstack is not empty, pop every opstack element and add it to postfix.
 * 4. Return the postfix string
 */
std::string InfixToPostfix(const std::string& infix){
    std::string postfix = ""; //output string
    std::stack<char> opstack; //operator stack
    bool firstMinus = (infix.at(0) == '-') ? true : false;
    size_t i = firstMinus ? 1 : 0; //if expression begins with -, start scanning characters from 1
    for(; i < infix.length(); i++){
        char c = infix.at(i); //scaned character
        if(c == ' ') continue; //if c is space, skip this iteration
        //support multidigit numbers and decimals
        if(isOperand(c)){
            //while character is operand, append it to postfix
            while(isOperand(c)){
                postfix += c;
                i++;
                //if i is equal infix.length() than we have passed every character, so break the loop
                if(i == infix.length()) break;
                c = infix.at(i);
            }
            //append empty space to seperate multidigit numbers
            postfix += " ";
            //if expression began with minus and second character wasn't left bracket, append @(unary minus) to postfix
            if(firstMinus && infix.at(1) != '('){
                postfix +="@ ";
                firstMinus = false;
            }
            //i now is at operator, but then in the for loop it increments and we will skip the operator, so decrement it
            i--;
        } 
        else if(isOperator(c)){
            if(opstack.empty()) opstack.push(c);
            else if(c == '(') opstack.push(c);
            //if operator is right bracket, append every character to postfix, while opstack.top() is not left bracket
            else if(c == ')'){
                while(!opstack.empty() && opstack.top() != '('){
                    postfix += opstack.top();
                    postfix += " ";
                    opstack.pop();
                }
                //now pop the left bracket from opstack
                opstack.pop();
                //if infix expression began with -, append @ (unary minus) to postfix 
                if(firstMinus){
                    postfix += "@ ";
                    firstMinus = false;
                }
            }
            else if(c == '-' && infix.at(i-1) == '(' ) opstack.push('@'); //if - is after (, then this - is unary
            else{
                //if the operator has lower or same priority as opstack.top(), append every opstack element which
                //has higher or same priority
                while( !opstack.empty() && ( priority(c) <= priority(opstack.top()) ) ){
                    postfix += opstack.top();
                    postfix += " ";
                    opstack.pop();
                }
                //now push the operator
                opstack.push(c);
            }
            
        }
            
    }
    //now if the opstack is not empty, append every element to postfix
    while(!opstack.empty()){
        postfix += opstack.top();
        postfix += " ";
        opstack.pop();
    }
    return postfix;
}
/*
 * Postfix expression evaluation:
 * postfix is the input string, operandStack is operands stack (double stack)
 * Start scanning the input postfix string character by character.
 * 1. If character is operand, push it on operandStack.
 * 2. If character is operator, pop two top elements of operandStack, do the operation
 *    on these elements, and push the result on operandStack again.
 * 3. At the end the result of the expression will be the top operandStack element, so return it.
 */
double EvaluatePostfix(std::string postfix){
    double op1, op2, result; //these will hold the two operands and the result of the operation
    std::stack<double> operandStack; //operand stack
    for(size_t i = 0; i < postfix.length(); i++){
        char c = postfix.at(i);
        if(c == ' ') continue; //if c is space, skip this iteration
        //Scaning multidigit numbers
        if(isOperand(c)){
            size_t j = i; //j will be the end of the number in the string
            while(isOperand(postfix.at(j))) j++; //find where does the number end
            operandStack.push(std::stod(postfix.substr(i, j))); //push the number on operandStack
            i = j; //now i must be set to j to skip the already scanned number (its digits)
        }
        else if(isOperator(c)){
            //if c is @ (unary minus), pop the top operandStack element and push its negative
            if(c == '@'){
                double op = -operandStack.top();
                operandStack.pop();
                operandStack.push(op);
            } else{
                //now because c is operator, pop two operands from operandStack
                op1 = operandStack.top();
                operandStack.pop();
                op2 = operandStack.top();
                operandStack.pop();
                //now examine the operation
                switch(c){
                    case '+':
                        result = (op1 + op2);
                    break;
                    case '-':
                        result = (op2 - op1);
                    break;
                    case '*':
                        result = (op1 * op2);
                    break;
                    case '/':
                        result = (op2 / op1);
                    break;
                }
                //push the result back to operandStack
                operandStack.push(result);
            }
        }
    }
    //return the result of the expression which is the top element of operandStack
    return operandStack.top();
}
//
double Evaluate(std::string expression){
    return EvaluatePostfix(InfixToPostfix(expression));
}
 
   
