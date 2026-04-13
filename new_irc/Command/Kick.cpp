/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:10:24 by tronguye          #+#    #+#             */
/*   Updated: 2026/04/13 22:15:04 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Kick.hpp"


// KICK #channel target_nick :reason
void Kick::execute(Client &client, std::string &input)
{
    std::stringstream ss(input);
    std::string channelName, targetNick, reason;

    ss >> channelName >> targetNick;
    std::getline(ss, reason); // Capture the rest as the reason

    // 1. Find the channel in the server's map
    std::map<std::string, Channel*>::iterator chanIt = _channels.find(channelName);
    if (chanIt == _channels.end()) {
        client.addToOutput(":ircserv 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n");
        return;
    }
    Channel *chan = chanIt->second;

    // 2. Check if the sender is an operator
    if (!chan->isUserOperator(client.getId())) {
        client.addToOutput(":ircserv 482 " + client.getNickname() + " " + channelName + " :You're not channel operator\r\n");
        return;
    }

    // 3. Check if the target is in the channel
    if (!chan->isUserInChannel(getIdByNick((targetNick)))) {
        client.addToOutput(":ircserv 441 " + client.getNickname() + " " + targetNick + " " + channelName + " :They aren't on that channel\r\n");
        return;
    }

    // 4. Format reason (remove leading ':' if present)
    if (!reason.empty() && reason[0] == ' ') reason.erase(0, 1);
    if (!reason.empty() && reason[0] == ':') reason.erase(0, 1);
    if (reason.empty()) reason = "Kicked by " + client.getNickname();

    // 5. Notify the channel BEFORE removing the user
    // Format: :Sender!User@Host KICK #channel Target :Reason
    std::string kickNotice = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost KICK " 
                            + channelName + " " + targetNick + " :" + reason + "\r\n";
    chan->sendMsgChannelMember(client, kickNotice);

    chan->removeClient(getIdByNick(targetNick));
}
