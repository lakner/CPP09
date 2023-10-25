#include "RPN.hpp"
#include <iostream>
#include <stack>

int throwTheError()
{
	std::cout << "Error" << std::endl;
	return(1);
}


double eval(std::string expr)
{
		std::stack<double> rpnstack;
		double result;// = (s_expr[0] - '0');
		double op1 = 0;
		double op2 = 0;
		for (std::string::iterator it = (expr.begin()); it != expr.end(); it++)
		{
			if (isdigit(*it))
				rpnstack.push(*it - '0');
			else
			{
				std::string operands = "+-*/";
				if (operands.find(*it) == std::string::npos)
					return(throwTheError());
				if (!rpnstack.size())
					return(throwTheError());
				// result = rpnstack.front();
				// rpnstack.pop_front();
				op1 = rpnstack.top();
				rpnstack.pop();
				op2 = rpnstack.top();
				rpnstack.pop();
				switch (*it)
				{
					case '+':
						result = op1 + op2;
						break;
					case '-':
						result = op2 - op1;
						break;
					case '*':
						result = op2 * op1;
						break;
					case '/':
						result = op2 / op1;
						break;
					default:
						std::cout << "Error" << std::endl;
						return 1;
				}
				rpnstack.push(result);
			}
		}
	return result;
}