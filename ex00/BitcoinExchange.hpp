/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 09:30:07 by tcohen            #+#    #+#             */
/*   Updated: 2025/08/18 16:50:11 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

typedef struct s_date
{
	int year;
	int month;
	int day;

	bool operator<(const struct s_date& other) const{
		if (year != other.year)
			return year < other.year;
		if (month != other.month)
			return month < other.month;
		return day < other.day;
	}
	bool operator==(const struct s_date& other) const {
        return year == other.year && month == other.month && day == other.day;
    }

    bool operator!=(const struct s_date& other) const {
        return !(*this == other);
    }
} t_date;

int BitcoinExchange(std::string infile);
bool ends_with(std::string str, std::string suffix);
bool check_input_line(std::string line);