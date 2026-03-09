/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 17:47:01 by doferet           #+#    #+#             */
/*   Updated: 2026/03/08 17:46:23 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int checkPort(char *arg)
{
    char *end;
    
    if (strlen(arg) > 5)
        return -1;
    int port = strtol(arg, &end, 10);
    if (port < 0 || port > 65535 || *end != 0)
        return -1;
    return port;
}

int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cerr << "Error: Bad number argument.\n Expected: ./ircserv <port> <password>" << std::endl;
        return 1;
    }
    int port = checkPort(av[1]);
    std::string password = av[2];
    
    if (port == -1)
    {
        std::cerr << "Error: Bad port.\n Expected integer between 0-65535" << std::endl;
        return 1;
    }
    try
    {
        Server serv(port, password);
        serv.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}