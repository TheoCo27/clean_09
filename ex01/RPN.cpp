/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcohen <tcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 08:35:38 by theog             #+#    #+#             */
/*   Updated: 2025/09/03 18:47:06 by tcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

void print_stack(std::stack<int> s)
{
    // Tant que la pile n'est pas vide, on affiche l'élément du sommet et on le retire
    while (!s.empty()) {
        std::cout << s.top() << " "; // Afficher le sommet
        s.pop(); // Retirer l'élément du sommet
    }
    std::cout << std::endl; // Saut de ligne après l'affichage
}

bool check_allowed_whitespace(std::string str)
{
    if (str[0] == ' ')
    {
        std::cerr << "Error: Expression cannot start with space" << std::endl;
        return false;
    }
	for (int i = 0; str[i]; i++)
	{
		if (std::isspace(static_cast<int>(str[i])))
			if(str[i] != ' ')
			{
				std::cerr << "Error: Only spaces allowed" << std::endl;
				return false;
			}
        if (i != 0 && str[i] == ' ' && str[i - 1] == ' ')
        {
            std::cerr << "Error: Can't have two spaces in a row" << std::endl;
            return false;
        }
	}
    if (str[str.size() - 1] == ' ')
    {
        std::cerr << "Error: Expression cannot end with space" << std::endl;
        return false;
    }
	return true;
}

bool is_operator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return true;
    return false;
}

bool check_forbidden_char(std::string input)
{
    if (input.empty())
    {
        std::cerr << "Input cannot be empty" << std::endl;
        return false;
    }
    if (check_allowed_whitespace(input) == false)
        return false;
    for(int i = 0; input[i]; i++)
    {
        if (!std::isdigit(static_cast<int>(input[i])) && input[i] != '-' 
            && input[i] != '+' && input[i] != '*' && input[i] != '/' && input[i] != ' ')
        {
            std::cerr << "Error: Use only digits and + - * / operators" << std::endl;
            return false;
        }   
    }
    return true;
}

bool check_operator_nb(std::string input)
{
    int op_count = 0, space_count = 0, nb_count = 0;

    for(size_t i = 0; input[i]; i++)
    {
        if (input[i] == '+' || input[i] == '*' || input[i] == '/')
            op_count++;
        if (input[i] == '-' && i != input.size() - 1 && !std::isdigit(input[i + 1]))
            op_count ++;
        if (input[i] == ' ')
            space_count++;
    }
    nb_count = (space_count + 1) - op_count;
    if (op_count < 1 || nb_count < 2)
    {
        std::cerr << "Error: Wrong syntax" << std::endl;
        return false;
    }
    if(!(nb_count == op_count + 1))
    {
        if (nb_count > op_count + 1)
            std::cerr << "Too much numbers or not enough operators" << std::endl;
        if (nb_count < op_count + 1)
            std::cerr << "Too much operators or not enough numbers" << std::endl;
        return false;
    }
    return true;
}

bool RP_checker(std::string input)
{
    if (check_forbidden_char(input) == false)
        return false;
    if (check_operator_nb(input) == false)
        return false;
    return true;
}
int get_top(std::stack<int>& rp_stack)
{
    // std::cout << "stack before pop ---" << std::endl;
    // print_stack(rp_stack);
    if (rp_stack.empty())
        throw std::invalid_argument("Error: Cannot make operation with empty stack");
    int a = rp_stack.top();
    rp_stack.pop();
    // std::cout << "stack after pop ---" << std::endl;
    // print_stack(rp_stack);
    return(a);
}
int execute_operation(std::stack<int>& rp_stack, char op)
{
    long a = 0, b = 0, result = 0;

    a = get_top(rp_stack);
    b = get_top(rp_stack);
    //std::cout << "a = " << a << " et b = " << b << std::endl;
    if(op == '+')
        result = b + a;
    if(op == '-')
        result = b - a;
    if(op == '*')
        result = b * a;
    if(op == '/')
    {
        if (a == 0)
            throw std::invalid_argument("Error: Cannot divide by 0");
        else
            result = b / a;
    }
    if (result > std::numeric_limits<int>::max() || result < std::numeric_limits<int>::min())
        throw std::overflow_error("Error: result out of int range");
    rp_stack.push(static_cast<int>(result));
    //std::cout << a << " " << op << " " << b << " = " << result << std::endl;
    return (static_cast<int>(result));
}

bool check_int_overflow(std::string input)
{
	if (input.size() > 11)
	{
		std::cerr << "Error: input out of int range" << std::endl;
		return false;
	}
	for(int i = 0; input[i]; i++)
	{
		if (input[i] == '-' && i != 0)
		{
			std::cerr << "Error: sign '-' can only appear at the begining of a number" << std::endl;
			return false;	
		}
		if (input[i] == '-' && i == 0)
			continue;
		if (!std::isdigit(static_cast<int>(input[i])))
		{
			std::cerr << "Error: each operator must be isolated by spaces only sign '-' is allowed" << std::endl;
			return false;	
		}
		
	}
	long value = std::atol(input.c_str());
	if (value > 2147483647 || value < -2147483648)
	{
		std::cerr << "Error: input out of int range" << std::endl;
		return false;
	}
	return true;
}

int RP_calculator(std::string input)
{
    std::stack<int> rp_stack;
    std::stringstream ss(input);
    std::string token;
    int nb;

    while(std::getline(ss, token, ' '))
    {
        if (token.empty())
            throw std::invalid_argument("Error, please use clean syntax");
        if ((!is_operator(token[0])) || (token.length() > 1 && token[0] == '-' && std::isdigit(token[1])))
        {
			if (check_int_overflow(token) == false)
				return 1;
            nb = std::atoi(token.c_str());
            rp_stack.push(nb);
        }
        // if ((token.length() == 1 && std::isdigit(token[0])) || (token.length() == 2 && token[0] == '-' && std::isdigit(token[1])))
        // {
        //     nb = std::stoi(token);
        //     rp_stack.push(nb);
        // }
        else if(token.length() == 1 && is_operator(token[0]))
            execute_operation(rp_stack, token[0]);
        else
            throw std::invalid_argument("Error: " + token + " ,please use clean syntax");
    }
    std::cout << rp_stack.top() << std::endl;
    return 0;
}