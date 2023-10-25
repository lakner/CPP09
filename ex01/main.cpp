#include "RPN.hpp"
#include <stack>
#include <iostream>

int main(int argc, char **argv)
{
	try
	{
		if (argc != 2)
			throw "Error";

	// 	std::cout << "Wrong number of arguments" << std::endl;
	// 	return(1);
	// }

	std::string s_expr = argv[1];
		s_expr.erase(remove_if(s_expr.begin(), s_expr.end(), isspace), s_expr.end());
		if (!isdigit(s_expr[0]))
			throw "Error";
		double result = eval(s_expr);
		std::cout << result << std::endl;
	}
	catch (...)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	return 0;
}
