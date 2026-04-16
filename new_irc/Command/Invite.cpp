/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 15:50:42 by doferet           #+#    #+#             */
/*   Updated: 2026/04/16 15:27:13 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Invite.hpp"

void Invite::execute(Client &client, std::string &input)
{
    std::stringstream ss(input);
    std::string targetNick, channelName;

    ss >> targetNick >> channelName;
    if (channelName[0] == '#' || channelName[0] == '&')
    {
        channelName.erase(0, 1);
    }
    //std::cout<<"Channel Name :|"<<channelName<<"|"<<std::endl;
    // for (std::map<std::string, Channel*>::iterator i = _channels.begin(); i != _channels.end();i++)
    // {
    //     std::cout<<"Channel Name dans la map :|"<<i->first<<"|"<<std::endl;
    // }
    std::map<std::string, Channel*>::iterator chan = _channels.find(channelName);
    if (chan == _channels.end())
    {
        client.addToOutput(":ircserv 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n");
        return;
    }
    if (!chan->second->isUserInChannel(client.getId())) {
        client.addToOutput(":ircserv 442 " + client.getNickname() + " " + channelName + " :You're not on that channel\r\n");
        return;
    }
    int targetId = getIdByNick(targetNick);
    if (chan->second->isUserInChannel(targetId)) {
        client.addToOutput(":ircserv 443 " + client.getNickname() + " " + targetNick + " " + channelName + " :User already on channel\r\n");
        return;
    }
    if (chan->second->isInviteOnly() && !chan->second->isUserOperator(client.getId()))
    {
        client.addToOutput(":ircserv 482 " + client.getNickname() + " " + channelName + " :You're not channel operator\r\n");
        return;
    }
    client.addToOutput(":ircserv 341 " + client.getNickname() + " " + targetNick + " " + channelName + "\r\n");
    int c = 0;
    for (size_t i = 0; i <_cli.size();i++)
    {
        if (_cli[i].getId() == targetId)
        {
            c = i;
            break;
        }
    }
    _cli[c].addToOutput(":" + client.getNickname() + "!" + client.getUsername() + "@localhost INVITE " + _cli[c].getNickname() + " :" + channelName + "\r\n");
    chan->second->addInvit(targetId);
}
