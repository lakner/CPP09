#ifndef BITCOINEXCHANGE_H
#define BITCOINEXCHANGE_H

#pragma once
#include <string>
#include <stdexcept>
#include <map>

class BitcoinExchange
{
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& orig);
	BitcoinExchange& operator=(const BitcoinExchange& orig);
	~BitcoinExchange();
	void readInputData(std::string fPrices);
	void printResults(std::string filename);

	class NoFileException : public std::exception
	{
		const char* what() const throw();
	};
	class RateTooLargeException : public std::exception
	{
		const char* what() const throw();
	};
	class RateTooSmallException : public std::exception
	{
		const char* what() const throw();
	};
	class BadDateException : public std::exception
	{
		const char* what() const throw();
	};
	
private:
	std::map< std::pair<std::string, float> > _btcPrices;
//	std::list< std::pair<std::string, float> > _btcValues;
	std::pair<std::string, float> processLine(std::string line, bool tooLarge);
	bool dateIsValid(std::string sdate);
	std::list< std::pair<std::string, float> > readInputfile(std::string filename);
};

#endif