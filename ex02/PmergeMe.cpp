#include "PmergeMe.hpp"
#include <iostream>
#include <ctime>
#include <iterator>
#include <numeric>

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
	this->_vec = sortVec2(this->_vec);	
	clock_t end = clock();
	return(static_cast<double> (end - start)/CLOCKS_PER_SEC * 1000000);
}

double PmergeMe::sortList()
{
	clock_t start = clock();
	this->_list = sortList2(this->_list);
	clock_t end = clock();
	return(static_cast<double> (end - start)/CLOCKS_PER_SEC * 1000000);
}

std::vector<unsigned int> PmergeMe::sortVec2(std::vector<unsigned int> seq)
{
	if (std::is_sorted(seq.begin(), seq.end()))
		return (seq);
	std::vector<unsigned int> sorted;
	std::vector<unsigned int>::iterator it_smallest_sorted = std::max_element(seq.begin(), seq.end());
	std::vector<unsigned int>::iterator it_partner_of_smallest = std::max_element(seq.begin(), seq.end());
	for(std::vector<unsigned int>::iterator it = seq.begin(); it != seq.end();)
	{
		if (next(it) == seq.end())
		{
			sorted.push_back(*it);
			seq.erase(it);
		}
		else if (*it < *(next(it)))
		{
			if (*it < *it_smallest_sorted)
			{
				it_smallest_sorted = next(it);
				it_partner_of_smallest = it;
			}
			sorted.push_back(*(next(it)));
			seq.erase(next(it));
		}
		else
		{
			if (*(next(it)) < *it_smallest_sorted)
			{
				it_smallest_sorted = it;
				it_partner_of_smallest = next(it);
			}
			sorted.push_back(*it);
			seq.erase(it);
		}
		std::advance(it, 1);
	}
	sorted = sortVec2(sorted);
	sorted.insert(sorted.begin(), *it_partner_of_smallest);
	seq.erase(it_partner_of_smallest);
	insertRemainingVec(seq, sorted);
	return(sorted);
}

std::list<unsigned int> PmergeMe::sortList2(std::list<unsigned int> seq)
{
	if (std::is_sorted(seq.begin(), seq.end()))
		return (seq);
	std::list<unsigned int> sorted;
	//std::list<unsigned int> remainder;
	std::list<unsigned int>::iterator it_smallest_sorted = std::max_element(seq.begin(), seq.end());
	std::list<unsigned int>::iterator it_partner_of_smallest = std::max_element(seq.begin(), seq.end());
	for(std::list<unsigned int>::iterator it = seq.begin(); it != seq.end();)
	{
		if (next(it) == seq.end())
			break;
		else if (*it < *(next(it)))
		{
			if (*it < *it_smallest_sorted)
			{
				it_smallest_sorted = next(it);
				it_partner_of_smallest = it;
			}
			sorted.push_back(*(next(it)));
			seq.erase(next(it++));
		}
		else
		{
			if (*(next(it)) < *it_smallest_sorted)
			{
				it_smallest_sorted = it;
				it_partner_of_smallest = next(it);
			}
			sorted.push_back(*it);
			seq.erase(it++);
		}
		it++;
	}
	sorted.insert(sorted.begin(), *it_partner_of_smallest);
	seq.erase(it_partner_of_smallest);
	sorted = sortList2(sorted);
	insertRemainingList(seq, sorted);

	return(sorted);
}

void	PmergeMe::insertRemainingVec(std::vector<unsigned int> seq,
									std::vector<unsigned int>& sorted)
{
	std::vector<unsigned int> group_sizes;

	if (seq.size() <= 2)
		group_sizes.push_back(seq.size());
	else
	{
		group_sizes.push_back(2);
		group_sizes.push_back(2);
	
		unsigned int idx = 2;
		while (seq.size() 
			< static_cast<unsigned int> 
			(std::accumulate(group_sizes.begin(), group_sizes.end(), 0)))
		{
			group_sizes.push_back(group_sizes[idx - 1] + group_sizes[idx - 2]);
			idx ++;
		}
	}
	//for (unsigned int i = 0; i < group_sizes.size(); i++)
	for (std::vector<unsigned int>::iterator it = group_sizes.begin();
			it != group_sizes.end();
			std::advance(it, 1))
	{
		std::vector<unsigned int>::iterator it_tmp = seq.begin();
		std::advance(it_tmp, *it);
		std::vector<unsigned int> group(seq.begin(), it_tmp);
		seq.erase(seq.begin(), it_tmp);
		sorted = insertVec(sorted, group);
	}

}

void	PmergeMe::insertRemainingList(std::list<unsigned int> seq,
									std::list<unsigned int>& sorted)
{
	std::list<unsigned int> group_sizes;

	if (seq.size() <= 2)
		group_sizes.push_back(seq.size());
	else
	{
		group_sizes.push_back(2);
		group_sizes.push_back(2);
	
		//unsigned int idx = 2;
		std::list<unsigned int>::iterator it = seq.begin();
		std::list<unsigned int>::iterator it_tmp0 = seq.begin();
		std::list<unsigned int>::iterator it_tmp1 = seq.begin();
		std::advance(it, 2);
		std::advance(it_tmp1, 1);
		while (seq.size() 
			< static_cast<unsigned int> 
			(std::accumulate(group_sizes.begin(), group_sizes.end(), 0)))
		{
			group_sizes.push_back(*(it_tmp1) + *(it_tmp0));
			std::advance(it_tmp0, 1);
			std::advance(it_tmp1, 1);
		}
	}
	//for (unsigned int i = 0; i < group_sizes.size(); i++)
	for (std::list<unsigned int>::iterator it = group_sizes.begin();
			it != group_sizes.end();
			it++)
	{
		std::list<unsigned int>::iterator it_tmp = seq.begin();
		std::advance(it_tmp, *it);
		std::list<unsigned int> group(seq.begin(), it_tmp);
		seq.erase(seq.begin(), it_tmp);
		sorted = insertList(sorted, group);
	}
}

std::vector<unsigned int> PmergeMe::insertVec(std::vector<unsigned int> sorted,
								std::vector<unsigned int> group)
{
	// sort the group first, in descending order
	for (std::vector<unsigned int>::iterator it = group.begin();
			it != group.end(); 
			std::advance(it, 1))
	{
		if (*it < *(next(it)))
		{
			unsigned int tmp = *(next(it));
			*(next(it)) = *it;
			*it = tmp;
		}
		std::vector<unsigned int>::iterator cpy = it;
		std::vector<unsigned int>::iterator prev = cpy;
		std::advance(prev, -1);
		while (cpy != group.begin() && *cpy > *(prev))
		{
			unsigned int tmp = *(prev);
			*(prev) = *cpy;
			*cpy = tmp;
			std::advance(cpy, -1);
		}
	}

	// now insert elements of group back into the sorted part
	for (std::vector<unsigned int>::iterator it = group.begin();
			it != group.end(); 
			std::advance(it, 1))
	{
		std::vector<unsigned int> sub_sorted(group);
		std::vector<unsigned int>::iterator it_s, it_e, it_tmp;
		it_s = sub_sorted.begin();
		it_e = sub_sorted.end();

		while(*it > *it_s && *it < *it_e)
		{
			it_tmp = it_s;
			std::advance(it_tmp, group.size()/2);
			if (*it < *it_tmp)
				it_e = it_tmp;
			else
				it_s = it_tmp;
		}
		if (*it <= *it_s)
			sorted.insert(sorted.begin(), *it);
		else if (*it >= *it_e)
			sorted.push_back(*it);
	}
	return(sorted);
}

std::list<unsigned int> PmergeMe::insertList(std::list<unsigned int> sorted,
											std::list<unsigned int> group)
{
	// sort the group first, in descending order
	for (std::list<unsigned int>::iterator it = group.begin();
			it != group.end(); 
			std::advance(it, 1))
	{
		if (*it < *(next(it)))
		{
			unsigned int tmp = *(next(it));
			*(next(it)) = *it;
			*it = tmp;
		}
		std::list<unsigned int>::iterator cpy = it;
		std::list<unsigned int>::iterator prev = it;
		std::advance(prev, -1);
		while (cpy != group.begin() && *cpy > *(prev))
		{
			unsigned int tmp = *(prev);
			*(prev) = *cpy;
			*cpy = tmp;
			std::advance(cpy, -1);
		}
	}

	// now insert elements of group back into the sorted part
	for (std::list<unsigned int>::iterator it = group.begin();
			it != group.end(); 
			std::advance(it, 1))
	{
		//std::list<unsigned int> sub_sorted(sorted);
		std::list<unsigned int>::iterator it_s, it_e, it_tmp;
		it_s = sorted.begin();
		it_s++;
		it_e = sorted.end();
		it_e --;
	  int size = sorted.size();
		// TODO: Not sure what the fuck I'm trying to do here, it does not work.
		while(*it > *it_s && *it < *it_e && size > 0)
		{
			it_tmp = it_s;
			size /= 2;
			std::advance(it_tmp, size/2);

			if (*it < *it_tmp)
				it_e = it_tmp;
			else
				it_s = it_tmp;
		}
		if (*it <= *it_s)
		{
			it_s --;
			sorted.insert(it_s, *it);
		}
		else
			sorted.insert(it_e, *it);
	}
	return(sorted);
}