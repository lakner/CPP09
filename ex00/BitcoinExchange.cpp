#include <fstream>
#include <sstream>
#include <iostream>
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &orig)
{
	*this = orig;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &orig)
{
	if (this != &orig)
	{
		_btcValues = orig._btcValues;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{

}

const char* BitcoinExchange::NoFileException::what() const throw()
{
	return("Couldn't open input file.");
}

const char* BitcoinExchange::RateTooLargeException::what() const throw()
{
	return("Rate greater than 1000.");
}

const char* BitcoinExchange::RateTooSmallException::what() const throw()
{
	return("Rate not a positive number.");
}

const char* BitcoinExchange::BadDateException::what() const throw()
{
	return("Invalid date.");
}

std::list< std::pair<std::string, float> > 
BitcoinExchange::readInputfile(std::string filename)
{
	std::list<std::pair <std::string, float> > contents;
	std::ifstream infile(filename);
	std::string line;

	if (!infile.is_open())
		throw NoFileException();
	
	// discard the first line
	std::getline(infile, line);

	// read the rest
	while (std::getline(infile, line))
		contents.push_back(processLine(line, false));

	return(contents);
}

std::pair<std::string, float> BitcoinExchange::processLine(std::string line, bool tooLarge)
{
	std::pair<std::string, float> pair;
	std::string date;
	std::string s_rate;
	float rate;

	std::istringstream ss(line);
	if (line.find('|') != std::string::npos)
		std::getline(ss, date, '|');
	else
		std::getline(ss, date, ',');
	std::getline(ss, s_rate);

	if (!dateIsValid(date))
		throw BadDateException();
	rate = stof(s_rate);
	if (rate < 0)
		throw RateTooSmallException();
	else if (rate > 1000 && tooLarge)
		throw RateTooLargeException();
	pair = std::make_pair(date, rate);
	return (pair);
}

bool BitcoinExchange::dateIsValid(std::string sdate)
{
	// remove all the spaces
	sdate.erase(remove(sdate.begin(), sdate.end(), ' '), sdate.end());
	if (sdate.length() != 10)
		return (false);
	if (sdate[4] != '-' && sdate[8] != '-')
		return (false);
	int year = stoi(sdate.substr(0, 4));
	int month = stoi(sdate.substr(5, 2));
	int day = stoi(sdate.substr(8, 2));

	//std::cout << year << " " << month << " " << day << std::endl;
	if (year < 0 || day < 1 || month < 1 || month > 12 || day > 31)
		return (false);
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return (false);
	if (month == 2)
	{
		if (((!(year % 4) && !(year % 100)) || !(year % 400))
			&& day > 29)
			return (false);
		else if (day > 28)
			return (false);
	}
	return (true);
}

void BitcoinExchange::readInputData(std::string fPrices)
{
	_btcPrices = readInputfile(fPrices);
}

void BitcoinExchange::printResults(std::string filename)
{
	std::list<std::pair <std::string, float> > contents;
	std::ifstream infile(filename);
	std::string line;

	if (!infile.is_open())
		throw NoFileException();
	
	// discard the first line
	std::getline(infile, line);
	std::pair<std::string, float> values;
	// read the rest
	while (std::getline(infile, line))
	{
		try
		{
			values = processLine(line, true);
		}
		catch (std::exception &ex)
		{
			std::cout << "Error: " << ex.what() << std::endl;
			continue;
		}
		for (std::list<std::pair<std::string, float> >::iterator it2 = _btcPrices.begin();
			it2 != _btcPrices.end(); it2++)
		if (values.first == it2->first || 
			(values.first > it2->first && it2 == _btcPrices.begin() ))
		{
			std::cout << values.first << " => " 
					<< it2->second << " = " 
					<< it2->second * values.second << std::endl;
			
			break;
		}
		else if (values.first > it2->first)
		{
			it2 --;
			std::cout << values.first << " => " 
				<< it2->second << " " 
				<< values.second * it2->second << std::endl;
			break;
		}
	}
}