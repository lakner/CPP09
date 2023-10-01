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
		void insertRemainingVec(std::vector<unsigned int>remaining, std::vector<unsigned int> sorted);

	private:
		std::list<unsigned int> sortList2(std::list<unsigned int>);
		std::vector<unsigned int> sortVec2(std::vector<unsigned int>);
		void insertRemainingVec(std::vector<unsigned int> remaining,
								std::vector<unsigned int> sorted);
		void insertRemainingList(std::list<unsigned int> remaining,
								std::list<unsigned int> sorted);
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