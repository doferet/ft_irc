/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:35:53 by doferet           #+#    #+#             */
/*   Updated: 2026/04/12 21:36:37 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Part.hpp"

void Part::execute(Client &client, std::string &input)
{
    if (input[0] == '#' || input[0] == '&')
    {
        input.erase(0, 1);
    }
    std::map<std::string, Channel*>::iterator channel = _channels.find(input);
    if (channel == _channels.end())
    {
        client.addToOutput(":ircserv 403 " + client.getNickname() + " " + input + " :No such channel\r\n");
        return;
    }
    if (channel->second->isUserInChannel(client.getNickname()) == false)
    {
        client.addToOutput(":ircserv 442 " + client.getNickname() + " " + input + " :You're not on that channel\r\n");
        return;
    }
    channel->second->sendMsgChannelMember(":" + client.getNickname() + "!" + client.getUsername() + "@localhost PART " + channel->second->getName() + "\r\n");
    channel->second->removeClient(client.getNickname());
}