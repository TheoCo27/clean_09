/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:53:17 by theog             #+#    #+#             */
/*   Updated: 2025/09/03 19:08:57 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <ctime>
#include <iomanip>
#include <cstdlib>

typedef std::vector<std::pair<int, int> > t_pair_vec;
typedef std::vector<std::pair<int, int> >::iterator t_pvec_it;

bool checker(char **argv);
void PmergeSort(char **argv, int argc);
std::vector<int> jacobsthal_sequence(int n);
void binary_insert(std::vector<int>& sorted, int value);
double timer(int mode);
void print_time(size_t nb_elements, std::string container_name);
std::deque<int> jacobsthal_sequence_d(int n);
void binary_insert_d(std::deque<int>& sorted, int value);
void PmergeSort_v(char **argv, int argc);
int ft_stoi(std::string str);