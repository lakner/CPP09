#include "RPN.hpp"
#include <deque>
#include <iostream>

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
		return(throwTheError());

	std::deque<double> rpnstack;
	double result = (s_expr[0] - '0');
	for (std::string::iterator it = (s_expr.begin()) + 1; it != s_expr.end(); it++)
	{
		if (isdigit(*it))
			rpnstack.push_back(*it - '0');
		else
		{
			std::string operands = "+-*/";
			if (operands.find(*it) == std::string::npos)
				return(throwTheError());
			if (!rpnstack.size())
				return(throwTheError());
			switch (*it)
			{
				result = rpnstack.back();
				rpnstack.pop_back();
				case '+':
					result += rpnstack.back();
					break;
				case '-':
					result -= rpnstack.back();
					break;
				case '*':
					result *= rpnstack.back();
					break;
				case '/':
					result /= rpnstack.back();
					break;
				default:
					std::cout << "Error" << std::endl;
					return 1;
			}
			rpnstack.pop_back();
			rpnstack.push_back(result);
		}
	}
	std::cout << result << std::endl;
	return 0;
}
