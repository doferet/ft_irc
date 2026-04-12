/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:25:47 by doferet           #+#    #+#             */
/*   Updated: 2026/04/12 21:23:54 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mode.hpp"

int checkLimit(std::string param)
{
    char *ptr;
    long res = strtol(param.c_str(), &ptr, 10);
    
    if (*ptr != 0 || ptr - param.c_str() > 8)
        return -1;
    return res;
}

void option_l(std::stringstream &ss, bool isPlus, std::map<std::string, Channel*>::iterator channel, Client &client)
{
    if (isPlus == false)
    {
        channel->second->removeLimit();
        channel->second->sendMsgChannelMember(":" + client.getNickname() + "!" + client.getUsername() + "@localhost MODE " + channel->second->getName() + " -l " + "\r\n");
        return ;
    }
    std::string param;
    ss >> param;
    int limit = checkLimit(param);
    if (param.empty())
    {
        client.addToOutput(":ircserv 461 " + client.getNickname() + " MODE :Not enough parameters\r\n");
        return;
    }
    if (limit <= 0)
    {
        client.addToOutput(":ircserv 696 " + client.getNickname() + " " + channel->first + " l " + param + " :Invalid mode parameter\r\n");
        return ;
    }
    channel->second->setLimit(limit);
    channel->second->sendMsgChannelMember(":" + client.getNickname() + "!" + client.getUsername() + "@localhost MODE " + channel->second->getName() + " +l " + param + "\r\n");
}

void option_o(std::stringstream &ss, bool isPlus, std::map<std::string, Channel*>::iterator channel, Client &client)
{
    std::string param;
    ss >> param;
    if (param.empty())
    {
        client.addToOutput(":ircserv 461 " + client.getNickname() + " MODE :Not enough parameters\r\n");
        return;
    }
    if (channel->second->isUserInChannel(param) == false)
    {
        client.addToOutput(":ircserv 442 " + client.getNickname() + " " + channel->first + " :They aren't on that channel\r\n");
        return;
    }
    if (isPlus == false)
    {
        channel->second->removeOperator(param);
        channel->second->sendMsgChannelMember(":" + client.getNickname() + "!" + client.getUsername() + "@localhost MODE " + channel->second->getName() + " -o " + param + "\r\n");
        return;
    }
    channel->second->setOperator(param);
    channel->second->sendMsgChannelMember(":" + client.getNickname() + "!" + client.getUsername() + "@localhost MODE " + channel->second->getName() + " +o " + param + "\r\n");
}
    
void option_k(std::stringstream &ss, bool isPlus, std::map<std::string, Channel*>::iterator channel, Client &client)
{
    std::string param;
    std::string passwordChannel = channel->second->getPwd();
    ss >> param;
    if (isPlus == false)
    {
        if (passwordChannel.empty() || passwordChannel == param)
            channel->second->setPassword("");
        channel->second->sendMsgChannelMember(":" + client.getNickname() + "!" + client.getUsername() + "@localhost MODE " + channel->second->getName() + " -k " + param + "\r\n");
        return;
    }
    if (param.empty())
    {
        client.addToOutput(":ircserv 461 " + client.getNickname() + " MODE :Not enough parameters\r\n");
        return;
    }
    if (!passwordChannel.empty())
    {
        client.addToOutput(":ircserv 467 " + client.getNickname() + " " + channel->first + " :Channel key already set\r\n");
        return;
    }
    channel->second->setPassword(param);
    channel->second->sendMsgChannelMember(":" + client.getNickname() + "!" + client.getUsername() + "@localhost MODE " + channel->second->getName() + " +k " + param + "\r\n");
}

void Mode::execute(Client &client, std::string &input)
{
    std::stringstream ss(input);
    std::string chanName;
    std::string option;
    std::string param;
    bool isPlus = false;
    ss >> chanName >> option;
    
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
    if (channel->second->isUserInChannel(client.getNickname()) == false)
    {
        client.addToOutput(":ircserv 442 " + client.getNickname() + " " + chanName + " :You're not on that channel\r\n");
        return;
    }
    if (channel->second->isUserOperator(client.getNickname()) == false)
    {
        client.addToOutput(":ircserv 482 " + client.getNickname() + " " + chanName + " :You're not channel operator\r\n");
        return;
    }
    if (option.size() != 2 || (option[0] != '+' && option[0] != '-'))
    { 
        client.addToOutput(":ircserv 472 " + client.getNickname() + " " + option + " :is unknown mode char to me\r\n");
        return;
    }
    if (option[0] == '+')
        isPlus = true;
    switch(option[1])
    {
        case 'i':
            channel->second->changeInvitStatus(isPlus);
            channel->second->sendMsgChannelMember(":" + client.getNickname() + "!" + client.getUsername() + "@localhost MODE " + chanName + option + param + "\r\n");
            break;
        case 't':
            channel->second->changeTopicStatus(isPlus);
            channel->second->sendMsgChannelMember(":" + client.getNickname() + "!" + client.getUsername() + "@localhost MODE " + chanName + option + param + "\r\n");
            break;
        case 'o':
            option_o(ss, isPlus, channel, client);
            break;
        case 'l':
            option_l(ss, isPlus, channel, client);
            break;
        case 'k':
            option_k(ss, isPlus, channel, client);
            break;
        default:
            client.addToOutput(":ircserv 472 " + client.getNickname() + " " + std::string(1, option[1]) + " :is unknown mode char to me\r\n");
            return;
    }
}