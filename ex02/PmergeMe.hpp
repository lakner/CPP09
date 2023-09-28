#ifndef PMERGEME_H
#define PMERGEME_H

#pragma once
#include <vector>
#include <list>

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
		std::vector<unsigned int> _vec;
		std::list<unsigned int> _list;

};

#endif