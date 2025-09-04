/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 08:35:40 by theog             #+#    #+#             */
/*   Updated: 2025/09/03 18:04:23 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <limits>
#include <string>
#include <cstdlib>
#include <cerrno>

bool RP_checker(std::string input);
int RP_calculator(std::string input);