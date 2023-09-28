#include "PmergeMe.hpp"
#include <iostream>
#include <ctime>
#include <iterator>

PmergeMe::PmergeMe()
{

}

PmergeMe::PmergeMe(const PmergeMe& orig)
{
	*this = orig;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& orig)
{
	if (this != &orig)
	{
		_vec = orig._vec;
		_list = orig._list;
	}
	return *this;
}

PmergeMe::~PmergeMe()
{

}

void PmergeMe::addToList(unsigned int i)
{
	_list.push_back(i);
}

void PmergeMe::addToVec(unsigned int i)
{
	_vec.push_back(i);
}

void PmergeMe::printVec()
{
	for(std::vector<uint>::iterator it = _vec.begin(); it != _vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void PmergeMe::printList()
{
	for(std::list<uint>::iterator it = _list.begin(); it != _list.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

double PmergeMe::sortVec()
{
	clock_t start = clock();
	sortVec2(this->_vec);	
	clock_t end = clock();
	return(static_cast<double> (end - start)/CLOCKS_PER_SEC * 1000000);
}

double PmergeMe::sortList()
{
	clock_t start = clock();
	sortList2(this->_list);
	clock_t end = clock();
	return(static_cast<double> (end - start)/CLOCKS_PER_SEC * 1000000);
}

std::vector<unsigned int> PmergeMe::sortVec2(std::vector<unsigned int> seq)
{
	if (std::is_sorted(seq.begin(), seq.end()))
		return (seq);
	std::vector<unsigned int> larger_elems;
	std::vector<unsigned int>::iterator it_smallest = seq.begin();
	for(std::vector<unsigned int>::iterator it = seq.begin(); it != seq.end(); std::advance(it, 2))
	{
		if (*it < *(next(it)))
		{
			if (*it < *it_smallest)
				it_smallest = it;
			larger_elems.push_back(*(next(it)));
		}
		else
		{
			if (*(next(it)) < *it_smallest)
				it_smallest = next(it);
			larger_elems.push_back(*it);
		}
	}
	larger_elems = sortVec2(larger_elems);
	larger_elems.insert(larger_elems.begin(), *it_smallest);
	seq.erase(it_smallest);
	return(larger_elems);
}

std::list<unsigned int> PmergeMe::sortList2(std::list<unsigned int> seq)
{
	if (std::is_sorted(seq.begin(), seq.end()))
		return (seq);
	std::list<unsigned int> larger_elems;
	std::list<unsigned int>::iterator it_smallest = seq.begin();
	for(std::list<unsigned int>::iterator it = seq.begin(); it != seq.end(); std::advance(it, 2))
	{
		if (*it < *(next(it)))
		{
			if (*it < *it_smallest)
				it_smallest = it;
			larger_elems.push_back(*(next(it)));
		}
		else
		{
			if (*(next(it)) < *it_smallest)
				it_smallest = next(it);
			larger_elems.push_back(*it);
		}
	}
	larger_elems = sortList2(larger_elems);
	larger_elems.insert(larger_elems.begin(), *it_smallest);
	seq.erase(it_smallest);

	return(larger_elems);
}