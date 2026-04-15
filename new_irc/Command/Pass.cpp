/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 17:29:31 by doferet           #+#    #+#             */
/*   Updated: 2026/04/15 15:59:51 by asritz           ###   ########.fr       */
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
        client.addToOutput(":ircserv 464 " + client.getNickname() + " :Password incorrect\r\n");
        client.setHasValidPassword(true);
        return;
    }
    client.addToOutput(":ircserv 464 " + client.getNickname() + " :Password incorrect\r\n");
}
