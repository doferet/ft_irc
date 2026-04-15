/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 17:29:31 by doferet           #+#    #+#             */
/*   Updated: 2026/04/15 16:45:05 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pass.hpp"

void Pass::execute(Client &client, std::string &input)
{
    // std::cout<<"dans pass ligne a traiter : |"<< input<<"|"<<std::endl;
    // std::cout<<"dans pass le password attendu est : |"<< _serverPassword<<"|"<<std::endl;
    std::string password;
    if (client.isAuthenticated())
    {
        client.addToOutput(":ircserv 462 " + client.getNickname() + " :You may not register\r\n");
        return;
    }
    if (_serverPassword == input)
    {
        client.setHasValidPassword(true);
        return;
    }
    client.addToOutput(":ircserv 464 " + client.getNickname() + " :Password incorrect\r\n");
}
