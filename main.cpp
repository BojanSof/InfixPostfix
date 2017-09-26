#include "infixpostfix.h"
#include <iomanip>
#include <iostream>

int main(){
    std::string expression = "";
    do{
    std::cout << "Enter expression (exit to quit): ";
    std::getline(std::cin, expression);
    if(expression == "exit") return 0;
    double result = Evaluate(expression);
    std::cout << expression << " = " << std::fixed << std::setprecision(5) << result << std::endl;
    } while(expression != "exit");
    return 0;
}
