/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 17:29:45 by doferet           #+#    #+#             */
/*   Updated: 2026/04/11 17:29:46 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include <sstream>

void User::execute(Client &client, std::string &input)
{
    // if (client.isAuthenticated()) return;

    std::stringstream ss(input);
    std::string user, host, server, real;
    ss >> user >> host >> server;
    std::getline(ss, real);

    if (user.empty() || real.empty())
        return;

    client.setUsername(user); // Needed add
    client.setHasValidUsername(true);

    if (client.isAuthenticated())
    {
        std::cout << "Registration complete!" << std::endl;
        client.addToOutput(":localhost 001 " + client.getNickname() + " :Welcome to the Internet Relay Network " + client.getNickname() + "!" + client.getUsername() + "@localhost\r\n");

        client.addToOutput(":localhost 002 " + client.getNickname() + " :Your host is localhost, running version 1.0\r\n");

        client.addToOutput(":localhost 003 " + client.getNickname() + " :This server was created today\r\n");

        client.addToOutput(":localhost 004 " + client.getNickname() + " localhost 1.0 o itkol\r\n");

        client.addToOutput(":localhost 422 " + client.getNickname() + " :MOTD File is missing\r\n");
    }
}
