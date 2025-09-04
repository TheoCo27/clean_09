/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 09:30:30 by tcohen            #+#    #+#             */
/*   Updated: 2025/09/03 17:37:39 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// int main(int argc, char **argv)
// {
// 	(void)argv;
// 	if (argc != 2)
// 	{
// 		std::cerr << "Wrong Format, please use: ./btc your_file.csv\n";
// 		return (EXIT_FAILURE);
// 	}
// 	std::string str = "2022-12-01 | 2147483649";
// 	check_input_line(str);
// 	return (0);
// }


int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Wrong Format, please use: ./btc your_file\n";
		return (EXIT_FAILURE);
	}
	try{
		(BitcoinExchange(argv[1]));
	}
	catch(std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}