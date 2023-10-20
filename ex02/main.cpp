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
			int arg = std::stoi(argv[i]);
			if (arg < 0)
			{
				std::cout << "Error: only positive integers are allowed" << std::endl;
				return 1;
			}
			merger.addToVec(arg);
		}
		clock_t end = clock();
		timeVec = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

		start = clock();
		for (int i = 1; i < argc; i++)
		{
			int arg = std::stoi(argv[i]);
			if (arg < 0)
			{
				std::cout << "Error: only positive integers are allowed" << std::endl;
				return 1;
			}
			merger.addToList(arg);
		}
		end = clock();
		timeList = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << "Before: ";
	merger.printList();
	merger.printVec();
	//timeList += merger.sortList();
	timeVec += merger.sortVec();
	std::cout << "List after: " << std::endl;
	merger.printList();
	std::cout << std::endl;
	std::cout << "Vec after: " << std::endl;
	merger.printVec();
	std::cout << std::endl;
	std::cout << "Time to process a range of " << argc - 1 << " elements with std::list: " << timeList << " us" << std::endl;
	std::cout << "Time to process a range of " << argc - 1 << " elements with std::vec: " << timeVec << " us" << std::endl;
}