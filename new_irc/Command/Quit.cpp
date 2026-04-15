/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:34:46 by doferet           #+#    #+#             */
/*   Updated: 2026/04/15 17:54:42 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Quit.hpp"

void Quit::execute(Client &client, std::string &input)
{
    // if (input[0] == '#' || input[0] == '&')
    // {
    //     input.erase(0, 1);
    // }
    //std::map<std::string, Channel *>::iterator channel = _channels.find(input);
    // if (channel == _channels.end())
    // {
    //     client.addToOutput(":ircserv 403 " + client.getNickname() + " " + input + " :No such channel\r\n");
    //     client.setDisconnected(true);
    //     return;
    // }
    // if (channel->second->isUserInChannel(client.getId()) == false)
    // {
    //     client.addToOutput(":ircserv 442 " + client.getNickname() + " " + input + " :You're not on that channel\r\n");
    //     client.setDisconnected(true);
        
    //     return;
    // }

    
    if (input.empty())
        input = "";
        
    // std::map<std::string, Channel *>::iterator it = _channels.begin();
    // while (it != _channels.end())
    // {
    //     it->second->sendMsgChannelMember(client, ":" + client.getNickname() + "!" + client.getUsername() + "@localhost QUIT :" + input + "\r\n", _cli, 1);
    //     it->second->removeClient(client.getId());
    //     if (it->second->isEmpty() == true)
    //     {
    //         delete it->second;
    //         _channels.erase(it);
    //     }
    //     else
    //         it++;
    // }
    client.addToOutput(":" + client.getNickname() + " QUIT :Client Quit\r\n");
    client.setDisconnected(true);
}