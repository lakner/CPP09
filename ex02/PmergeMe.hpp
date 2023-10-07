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
		//void insertRemainingVec(std::vector<unsigned int>remaining, std::vector<unsigned int> sorted);

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

		template<class T>
		T insert(T sorted, T group)
		{
			// sort the group first, in descending order
			for (typename T::iterator it = group.start();
					it != group.end(); 
					std::advance(it, 1))
			{
				if (*it < *(it.next()))
				{
					unsigned int tmp = *(it.next());
					*(it.next()) = *it;
					*it = tmp;
				}
				typename T::iterator cpy = it;
				while (cpy != group.begin() && *cpy > *(group.prev()))
				{
					unsigned int tmp = *(cpy.prev());
					*(cpy.prev()) = *cpy;
					*cpy = tmp;
					std::advance(cpy, -1);
				}
			}

			// now insert elements of group back into the sorted part
			for (typename T::iterator it = group.begin();
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
					if (*it < it_tmp)
						it_e = it_tmp;
					else
						it_s = it_tmp;
				}
				if (*it <= it_s)
					sorted.push_front(*it);
				else if (*it >= it_e)
					sorted.push_back(*it);
			}
		}
};

#endif