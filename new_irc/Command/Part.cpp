/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:35:53 by doferet           #+#    #+#             */
/*   Updated: 2026/04/15 17:30:13 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Part.hpp"

void Part::execute(Client &client, std::string &input)
{
    std::stringstream ss(input);
    std::string param;
    std::string chanName;
    
    ss >> chanName;
    std::getline(ss, param);
    if (chanName[0] == '#' || chanName[0] == '&')
    {
        chanName.erase(0, 1);
    }
    std::map<std::string, Channel*>::iterator channel = _channels.find(chanName);
    if (channel == _channels.end())
    {
        client.addToOutput(":ircserv 403 " + client.getNickname() + " " + chanName + " :No such channel\r\n");
        return;
    }
    if (channel->second->isUserInChannel(client.getId()) == false)
    {
        client.addToOutput(":ircserv 442 " + client.getNickname() + " " + chanName + " :You're not on that channel\r\n");
        return;
    }
    if (!param.empty() && param[0] == ' ') param.erase(0, 1);
    if (!param.empty() && param[0] == ':') param.erase(0, 1);
    std::string partMsg = ":" + client.getNickname() + "!" +
                      client.getUsername() + "@localhost PART #" +
                      channel->second->getName() + " :" + param + "\r\n";
    channel->second->sendMsgChannelMember(client, partMsg, _cli, 2);
    channel->second->removeClient(client.getId());
    if (channel->second->isEmpty())
    {
        delete channel->second;
        _channels.erase(channel);
    }    
}