/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:34:46 by doferet           #+#    #+#             */
/*   Updated: 2026/04/14 20:57:39 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Quit.hpp"

void Quit::execute(Client &client, std::string &input)
{
    if (input[0] == '#' || input[0] == '&')
    {
        input.erase(0, 1);
    }
    std::map<std::string, Channel *>::iterator channel = _channels.find(input);
    if (channel == _channels.end())
    {
        client.addToOutput(":ircserv 403 " + client.getNickname() + " " + input + " :No such channel\r\n");
        return;
    }
    if (channel->second->isUserInChannel(client.getId()) == false)
    {
        client.addToOutput(":ircserv 442 " + client.getNickname() + " " + input + " :You're not on that channel\r\n");
        return;
    }
    for (channel = _channels.begin(); channel != _channels.end(); ++channel)
    {
        channel->second->sendMsgChannelMember(client, ":" + client.getNickname() + "!" + client.getUsername() + "@localhost QUIT :" + input + "\r\n", _cli, 0);
        channel->second->removeClient(client.getId());
        if (channel->second->isEmpty() == true)
        {
            std::map<std::string, Channel *>::iterator tmp = channel;
            ++channel;
            _channels.erase(tmp);
        }
    }
    client.setDisconnected(true);
}