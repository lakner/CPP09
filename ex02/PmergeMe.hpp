#ifndef PMERGEME_H
#define PMERGEME_H

#pragma once
#include <vector>
#include <list>
#include <iterator>

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& orig);
		PmergeMe& operator=(const PmergeMe& orig);
		~PmergeMe();
		void addToVec(unsigned int i);
		void addToList(unsigned int i);
		void printVec();
		void printList();
		double sortList();
		double sortVec();

	private:
		std::list<unsigned int> sortList2(std::list<unsigned int>);
		std::vector<unsigned int> sortVec2(std::vector<unsigned int>);
		std::vector<unsigned int> _vec;
		std::list<unsigned int> _list;
		template<class T>
		T next(T it, typename std::iterator_traits<T>::difference_type n = 1)
		{
			std::advance(it, n);
			return (it);
		};
};

#endif