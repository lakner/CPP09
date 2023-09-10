#include "RPN.hpp"
#include <deque>
#include <iostream>

// I have to re-write this whole thing using a stack

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Wrong number of arguments" << std::endl;
		return(1);
	}

	std::string s_expr = argv[1];

	s_expr.erase(remove_if(s_expr.begin(), s_expr.end(), isspace), s_expr.end());
	if (!isdigit(s_expr[0]))
	{
		std::cout << "Error" << std::endl;
		return 1;
	}
	std::deque<double> rpnstack;
	//for (int i = 0; s_expr[i]; i++)
	double result = (s_expr[0] - '0');
	for (std::string::iterator it = (s_expr.begin()) + 1; it != s_expr.end(); it++)
	{
		std::cout << *it << std::endl;
		if (isdigit(*it))
		{
			rpnstack.push_back(*it - '0');
		}
		else
		{
			std::string operands = "+-*/";
			// std::cout << *it << std::endl;
			if (operands.find(*it) == std::string::npos)
			{
				std::cout << "Error: invalid character: " << *it << std::endl;
				return 1;
			}
			switch (*it)
			{
				result = rpnstack.back();
				rpnstack.pop_back();
				case '+':
					result += rpnstack.back();
					break;
				case '-':
					//result = rpnstack.top() - result;
					result -= rpnstack.back();
					break;
				case '*':
					result *= rpnstack.back();
					break;
				case '/':
					result = rpnstack.back() / result;
					break;
				default:
					std::cout << "Error" << std::endl;
					return 1;
			}
			rpnstack.pop_back();
			rpnstack.push_front(result);
			std::cout << "Result: " << result << std::endl;
		}
	}
	//result = rpnstack.();
	std::cout << result << std::endl;
	return 0;
}
