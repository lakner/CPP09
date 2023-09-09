#include "BitcoinExchange.h"
#include <iostream>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Wrong number of arguments." << std::endl;
		return (1);
	}

	BitcoinExchange exchange;
	try
	{
		exchange.readInputData("data.csv");
		exchange.printResults(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}