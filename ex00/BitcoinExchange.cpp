/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 09:30:02 by tcohen            #+#    #+#             */
/*   Updated: 2025/09/03 17:41:58 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"


//CHECKER FUNCTIUNS


bool ends_with(std::string str, std::string suffix)
{
	if (str.empty())
		return false;
	if (str.length() <= suffix.length())
		return (false);
	if (str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0)
		return (true);
	return (false);
}

bool check_if_valid_int(std::string str)
{
	std::stringstream ss(str);
	int nb;
	char leftover;
	ss >> nb;
	if (ss.fail())
	{
		std::cerr << "Error: conversion to int impossible" << std::endl;
		return false;
	}
	if (nb > 1000 )
	{
		std::cerr << "Error: Too large a number" << std::endl;
		return false;
	}
	if (nb < 0)
	{
		std::cerr << "Error: Not a positive number" << std::endl;
		return (false);
	}
	if (ss >> leftover)
	{
		std::cerr << "Error: Bad input => "<< str << std::endl;
		return false;
	}
	return (true);
}

bool check_if_valid_float(std::string str)
{
	std::stringstream ss(str);
	float nb;
	char leftover;
	ss >> nb;
	if (ss.fail())
	{
		std::cerr << "Error: conversion to float impossible" << std::endl;
		return false;
	}
	if (nb > 1000 )
	{
		std::cerr << "Error: Too large a number" << std::endl;
		return false;
	}
	if (nb < 0)
	{
		std::cerr << "Error: Not a positive number" << std::endl;
		return (false);
	}
	if (ss >> leftover)
	{
		std::cerr << "Error: Bad input => "<< str << std::endl;
		return false;
	}
	return (true);
}

bool check_date(std::string date)
{
	// std::cout << date <<  std::endl;
	std::stringstream ss(date);
	char dash1, dash2;
	unsigned int year, month, day;
	char extra;
	unsigned int tab[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	ss >> year >> dash1 >> month >> dash2 >> day;
	if (ss.fail() || dash1 != '-' || dash2 != '-') 
		return false;
	if (year < 2009 || year > 2025 || month > 12 || month < 1)
		return false;
	if (day > tab[month - 1] || day < 1)
		return false;
	if (ss >> extra)
		return false;
	return true;
}

bool check_value(std::string value)
{
	// std::cout << value << std::endl;
	if (value.find('.'))
		return (check_if_valid_float(value));
	else
		return (check_if_valid_int(value));
}

int count_space(std::string str)
{
	int i = 0;
	int count = 0;
	while(str[i])
	{
		if (str[i] == ' ')
			count++;
		i++;
	}
	return count;
}

bool check_allowed_whitespace(std::string str)
{
	for (int i = 0; str[i]; i++)
	{
		if (std::isspace(static_cast<int>(str[i])))
			if(str[i] != ' ')
			{
				std::cerr << "Error: Forbidden char detected" << std::endl;
				return false;
			}
	}
	return true;
}

bool check_input_line(std::string line)
{
	if (line.find('|') == std::string::npos)
	{
		std::cerr << "Error: No delimiter '|' found\n";
		return false;
	}
	if (check_allowed_whitespace(line) == false)
		return false;
	if (count_space(line) != 2)
	{
		if (count_space(line) < 2)
			std::cerr << "Error: too few spaces" << std::endl;
		else
			std::cerr << "Error: too much spaces" << std::endl;
		return false;
	}
	int delimiter_pos = line.find('|');
	if (check_date(line.substr(0, delimiter_pos)) == false)
	{	std::cerr << "Error: bad input => "<< line.substr(0, delimiter_pos) << std::endl;
		return false;
	}
	if (check_value(line.substr(delimiter_pos + 1, line.length() - delimiter_pos)) == false)
		return false;
	return true;
}


// MAIN CODE
int data_to_map(std::map<t_date, float>& data_map) // prendre en parametre la reference de la map
{
	int year, month, day;
	float value;
	char dash1, dash2, comma, extra;
	int line_count = 0;
	std::ifstream file("data.csv");
	if (file.fail())
	{
		throw std::invalid_argument("Cannot open file data.csv");
		return 1;
	}
	std::string line;
	while(getline(file, line))
	{
		if (line_count == 0)
		{
			if (line != "date,exchange_rate")
			{
				throw std::invalid_argument("data.csv has been corrupted");
				return 1;
			}
			line_count++;
			continue;
		}
		t_date date;
		std::stringstream ss(line);
		ss >> year >> dash1 >> month >> dash2 >> day >> comma >> value;
		if (ss.fail() || dash1 != '-' || dash2 != '-' || comma != ',' || ss >> extra)
		{
			std::cerr << "Error: data.csv corrupted" << std::endl;
			return 1;
		}
		date.day = day;
		date.year = year;
		date.month = month;
		data_map[date] = value;
	}
	file.close();
	return 0;
}


void convert_input(std::map<t_date, float>& data_map, t_date date, float value)
{
	std::map<t_date, float>::iterator it = data_map.lower_bound(date);

    if (it == data_map.end() || it->first != date) {
        if (it == data_map.begin()) {
            std::cerr << "Error: no available date before " 
                      << date.year << "-" << date.month << "-" << date.day << std::endl;
            return;
        }
        --it;
    }

    float rate = it->second;
    float result = rate * value;

    std::cout << date.year << "-";
	if (date.month < 10)
		std::cout << "0";
	std ::cout << date.month << "-"; 
	if (date.day < 10)
		std::cout << "0";	
	std :: cout << date.day << " => " << value << " = " << result << std::endl;

}


int BitcoinExchange(std::string infile)
{
	float value;
	char dash1, dash2, pipe;
	int line_count = 0;
	std::ifstream file(infile.c_str());
	// if (ends_with(infile, ".csv") == false)
	// {
	// 	std::cerr << "Error: file needs to end with .csv" << std::endl;
	// 	return 1;
	// }
	if (file.fail())
	{
		throw std::invalid_argument("Cannot open file");
		return 1;
	}
	std::map<t_date, float> data_map;
	if (data_to_map(data_map) == 1)
		return 1;
	std::string line;
	while(getline(file, line))
	{
		if (line_count == 0)
		{
			if (line != "date | value")
			{
				throw std::invalid_argument("Please keep first line as 'date | value'");
				return 1;
			}
			line_count++;
			continue;
		}
		if (check_input_line(line) == false)
			continue;
		std::stringstream ss(line);
		t_date date;
		ss >> date.year >> dash1 >> date.month >> dash2 >> date.day >> pipe >> value;
		convert_input(data_map, date, value);
	}
	file.close();
	return 0;
}