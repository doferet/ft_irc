/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:48:07 by doferet           #+#    #+#             */
/*   Updated: 2025/10/09 14:43:37 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"
#include "Error.hpp"

int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cout << "Error" << std::endl;
        return 0;
    }
    Server serv;
    try{
        serv.initServer(std::atoi(av[1]), av[2]);
    } catch (std::exception &e)
    {
        std::cerr << e.what() <<std::endl;
    }
    
}