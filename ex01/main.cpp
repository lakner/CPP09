#include "RPN.hpp"
#include <stack>
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
	double result = eval(s_expr);
	std::cout << result << std::endl;
	return 0;
}
