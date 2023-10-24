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
		public:
			BadDateException(const char* err);
			const char* what() const throw();
		private:
			const char* err;
	};
	
private:
	std::map< std::string, double > _btcPrices;
	std::map< std::string, double > _btcValues;
	std::pair< std::string, double > processLine(std::string line, bool tooLarge);
	bool dateIsValid(std::string sdate);
	std::map< std::string, double > readInputfile(std::string filename);
};

#endif