#include "RPN.hpp"
#include <iostream>
#include <stack>


double eval(std::string expr)
{
		std::stack<double> rpnstack;
		double result;
		double op1 = 0;
		double op2 = 0;
		for (std::string::iterator it = (expr.begin()); it != expr.end(); it++)
		{
			if (isdigit(*it))
				rpnstack.push(*it - '0');
			else
			{
				std::string operands = "+-*/";
				if (operands.find(*it) == std::string::npos || rpnstack.size() < 2)
					throw "Error";
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
						throw "Error";
				}
				rpnstack.push(result);
			}
		}
	if (rpnstack.size() != 1)
		throw "Error";
	return result;
}