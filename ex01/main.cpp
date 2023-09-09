#include "RPN.hpp"
#include <array>
#include <iostream>

int main(int argc, char **argv)
{
	std::array<char, 21> expression;

	if (argc != 2)
	{
		std::cout << "Wrong number of arguments" << std::endl;
		return(1);
	}

	std::string s_expr = argv[1];

	size_t j = 0;
	for (size_t i = 0; i < s_expr.length(); i++)
	{
		if (isspace(s_expr[i]))
			continue;
		expression[j] = s_expr[i];
		j++;
	}
	expression[j] = 0;
	std::cout << "j: " << j << std::endl;

	if (!(j % 2) || !validate(expression))
	{
		std::cout << "Error" << std::endl;
		return(1);
	}
	double result = expression[0] - '0';
	for (int i = 1; expression[i]; i+=2)
	{
		std::cout << result << std::endl;
		switch (expression[i + 1])
		{
			case '+':
				result += expression[i] - '0';
				break;
			case '-':
				result -= expression[i] - '0';
				break;
			case '*':
				result *= expression[i] - '0';
				break;
			case '/':
				result /= expression[i] - '0';
				break;
			default:
				std::cout << "Error" << std::endl;
				return 1;
		}
	}
	return 0;
}