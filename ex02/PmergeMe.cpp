#include "PmergeMe.hpp"
#include <iostream>
#include <ctime>
#include <iterator>
#include <numeric>
#include <cmath>

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
	if (std::is_sorted(seq.begin(), seq.end()) || seq.size() <= 1)
		return (seq);
	std::vector<unsigned int> sorted;
	int partner_of_smallest;

	for (unsigned int i = 0; i < seq.size() - 1; i++)
	{
		if (seq[i] < seq[i + 1])
		{
			sorted.push_back(seq[i + 1]);
			if (seq[i + 1] == *(std::min_element(sorted.begin(), sorted.end())))
				partner_of_smallest = seq[i];
			seq.erase(seq.begin() + i + 1);
		}
		else // if seq[i + 1] <= seq[i]
		{
			sorted.push_back(seq[i]);
			if (seq[i] == *(std::min_element(sorted.begin(), sorted.end())))
				partner_of_smallest = seq[i + 1];
			seq.erase(seq.begin() + i);
		}
	}
	sorted.insert(sorted.begin(), partner_of_smallest);
	seq.erase(std::find(seq.begin(), seq.end(), partner_of_smallest));
	sorted = sortVec2(sorted);
	insertRemainingVec(seq, sorted);

	return(sorted);
}

std::list<unsigned int> PmergeMe::sortList2(std::list<unsigned int> seq)
{
	if (std::is_sorted(seq.begin(), seq.end()))
		return (seq);
	std::list<unsigned int> sorted;
	int partner_of_smallest;

	for(unsigned int i=0; i < seq.size() - 1; i++)
	{
		std::list<unsigned int>::iterator it = seq.begin();
		std::advance(it, i);
		if (*it < *next(it))
		{
			sorted.push_back(*next(it));
			if (*next(it) == *(std::min_element(sorted.begin(), sorted.end())))
				partner_of_smallest = *it;
			seq.erase(next(it));
		}
		else // if (*it < *(next(it)))
		{
			sorted.push_back(*it);
			if (*it == *(std::min_element(sorted.begin(), sorted.end())))
				partner_of_smallest = *(next(it));
			seq.erase(it);
		}
	}
	sorted.insert(sorted.begin(), partner_of_smallest);
	seq.erase(std::find(seq.begin(), seq.end(), partner_of_smallest));
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
		int i = 2;
		while (seq.size() 
			> static_cast<unsigned int> 
			(std::accumulate(group_sizes.begin(), group_sizes.end(), 0)))
		{
			int tmp = group_sizes.back();
			group_sizes.push_back((1 << i) - tmp);
			i++;
		}
	}
	for (std::vector<unsigned int>::iterator it = group_sizes.begin();
			it != group_sizes.end();
			it++)
	{
		std::vector<unsigned int>::iterator group_end;

		if (seq.begin() + *it <= seq.end())
			group_end = seq.begin() + *it;
		else
			group_end = seq.end();
		std::vector<unsigned int> group(seq.begin(), group_end);
		seq.erase(seq.begin(), group_end);
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
		int i = 2;
		while (seq.size()
			> static_cast<unsigned int> 
			(std::accumulate(group_sizes.begin(), group_sizes.end(), 0)))
		{
			int tmp = group_sizes.back();
			group_sizes.push_back((1 << i) - tmp);
			i++;
		}
	}
	for (std::list<unsigned int>::iterator it = group_sizes.begin();
			it != group_sizes.end();
			it++)
	{
		std::list<unsigned int>::iterator group_it = seq.begin();
		std::list<unsigned int>::iterator group_end = seq.begin();
		std::advance(group_it, *it);
		if (*it <= seq.size())
			std::advance(group_end, *it);
		else
			group_end = seq.end();
		std::list<unsigned int> group(seq.begin(), group_end);
		seq.erase(seq.begin(), group_end);
		sorted = insertList(sorted, group);
	}
}


std::vector<unsigned int> PmergeMe::insertVec(std::vector<unsigned int> sorted,
											std::vector<unsigned int> group)
{
	for (int i = group.size() - 1; i >= 0; i --)
	{
		int start_idx = 0; 
		int end_idx = sorted.size() - 1;

		if (group[i] < sorted[start_idx])
			sorted.insert(sorted.begin(), group[i]);
		else if (group[i] > sorted[end_idx])
			sorted.insert(sorted.begin() + end_idx + 1, group[i]);
		else if (end_idx - start_idx == 1)
			sorted.insert(sorted.begin() + end_idx, group[i]);
		else
		{
			while (end_idx - start_idx > 1)
			{
				int mid = (end_idx - start_idx) / 2 + start_idx;
				if (group[i] <= sorted[mid])
					end_idx = mid;
				else // group[i] > sorted[mid]
					start_idx = mid;
			}
			sorted.insert(sorted.begin() + start_idx + 1, group[i]);
		}
	}
	return(sorted);
}


std::list<unsigned int> PmergeMe::insertList(std::list<unsigned int> sorted,
											std::list<unsigned int> group)
{
	int group_size = group.size();
	if (!group_size)
		return(sorted);
	std::list<unsigned int>::iterator group_it = group.end();
	//group_it --;
	do
	{
		group_it --;
		std::list<unsigned int>::iterator sort_begin = sorted.begin();
		std::list<unsigned int>::iterator sort_end = sorted.end();
		/////Try this line tomorrow
		if (sort_end != group.begin())
			std::advance(sort_end, - 1);
		//// Or maybe use reverse iterator!

		if (*group_it < *(sorted.begin()))
			sorted.push_front(*group_it);
		else if (*group_it > (sorted.back()))
			sorted.insert(sorted.end(), *sort_end);
		else if (sorted.size() == 2)
			sorted.insert(next(sorted.begin()), *group_it);
		else
		{
			while (next(sort_begin) != sort_end)
			{
				int mid_distance = std::distance(sort_begin, sort_end) / 2;
				std::list<unsigned int>::iterator mid = sort_begin;
				std::advance(mid, mid_distance);
				if (*group_it <= *mid)
					sort_end = mid;
				else // group[i] > sorted[mid]
					sort_begin = mid;
			}
			sorted.insert(++sort_begin, *group_it);
		}
		//group_it --;
		group_size --;
	} while (group_size);
	return(sorted);
}