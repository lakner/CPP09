#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
	PmergeMe merger;
	try
	{
		for (int i = 1; i < argc; i++)
		{
			int arg = std::stoi(argv[i]);
			if (arg < 0)
			{
				std::cout << "Error: only positive integers are allowed" << std::endl;
				return 1;
			}
			merger.addToVec(arg);
			merger.addToList(arg);
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	merger.printList();
}