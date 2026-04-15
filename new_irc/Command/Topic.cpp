/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:50:46 by doferet           #+#    #+#             */
/*   Updated: 2026/04/15 12:31:05 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Topic.hpp"

// TOPIC <channel> :<new_topic> to change topic || TOPIC <channel> to view current topic

void Topic::execute(Client &client, std::string &input)
{
    std::stringstream ss(input);
    std::string channelName, newTopic;

    ss >> channelName;
    std::getline(ss, newTopic);
      if (channelName[0] == '#' || channelName[0] == '&')
    {
        channelName.erase(0, 1);
    }
    std::map<std::string, Channel*>::iterator it = _channels.find(channelName);
    if (it == _channels.end())
    {
        client.addToOutput(":ircserv 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n");
        return;
    }
    if (!it->second->isUserInChannel(client.getId()))
    {
        client.addToOutput(":ircserv 442 " + client.getNickname() + " " + channelName + " :You're not on that channel\r\n");
        return;
    }

    if (newTopic.empty())
    {
        if (it->second->getTopic().empty())
            client.addToOutput(":ircserv 331 " + client.getNickname() + " " + channelName + " :No topic is set\r\n");
        else
            client.addToOutput(":ircserv 332 " + client.getNickname() + " " + channelName + " :" + it->second->getTopic() + "\r\n");
        return;
    }

    if (!newTopic.empty() && newTopic[0] == ' ') newTopic.erase(0, 1);
    if (!newTopic.empty() && newTopic[0] == ':') newTopic.erase(0, 1);
    
    if (it->second->getTopicStatus() == true && !it->second->isUserOperator(client.getId())) {
        client.addToOutput(":ircserv 482 " + client.getNickname() + " " + channelName + " :You're not channel operator\r\n");
        return;
    }

    it->second->setTopic(newTopic);

    std::string topicMsg = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost TOPIC " + channelName + " :" + newTopic + "\r\n";
    it->second->sendMsgChannelMember(client, topicMsg, _cli, 2);
}