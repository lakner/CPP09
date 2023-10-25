#include "PmergeMe.hpp"
#include <iostream>
#include <ctime>

int main(int argc, char* argv[])
{
	PmergeMe merger;
	double timeList, timeVec;

	if (argc < 2)
	{
		std::cout << "No arguments. Enter an sequence of positive integers to sort." << std::endl;
		return (1);
	}
	try
	{
		clock_t start = clock();
		for (int i = 1; i < argc; i++)
		{
			if (std::string(argv[i]).find_first_not_of("0123456789") != std::string::npos)
			{
				std::cerr << "Error: only positive integer arguments are allowed." << std::endl;
				return 1;
			}
			int arg = std::stoi(argv[i]);
			if (arg < 0)
			{
				std::cout << "Error: only positive integer arguments are allowed" << std::endl;
				return 1;
			}
			merger.addToVec(arg);
		}
		clock_t end = clock();
		timeVec = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

		start = clock();
		for (int i = 1; i < argc; i++)
		{
			if (std::string(argv[i]).find_first_not_of("0123456789") != std::string::npos)
			{
				std::cerr << "Error: only positive integer arguments are allowed." << std::endl;
				return 1;
			}
			int arg = std::stoi(argv[i]);
			if (arg < 0)
			{
				std::cout << "Error: only positive integer arguments are allowed" << std::endl;
				return 1;
			}
			merger.addToList(arg);
		}
		end = clock();
		timeList = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
	
		std::cout << "Before: ";
		merger.printVec();
		timeList += merger.sortList();
		timeVec += merger.sortVec();
		std::cout << "After: ";
		merger.printVec();
		// std::cout << "List after: ";
		// merger.printList();
		std::cout << "Time to process a range of " << argc - 1 << " elements with std::list: " << timeList << " us" << std::endl;
		std::cout << "Time to process a range of " << argc - 1 << " elements with std::vec: " << timeVec << " us" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}