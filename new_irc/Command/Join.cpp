/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:14:35 by asritz            #+#    #+#             */
/*   Updated: 2026/04/16 16:46:54 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"

std::string getPwd(std::string input)
{
	size_t n = input.find(" ");

	if (n == std::string::npos)
		return ("");
	return (input.substr(n + 1, (input.size() - n + 1)));
}

std::string getChannelName(std::string input)
{
	std::string name;
	for (size_t i = 1; i < input.size(); i++)
	{
		if (input[i] == ' ')
			break;
		name += input[i];
	}
	return (name);
}

std::string Join::getChannelMember(Channel *channel)
{
	std::string nickList;
	std::vector<std::string> cli = channel->getNickClients(_cli);
	for (size_t i = 0; i < cli.size(); i++)
		nickList += cli[i] + " ";
	return (nickList);
}

void Join::execute(Client &client, std::string &input)
{
	std::string pwd = getPwd(input);
	std::string channelName = getChannelName(input);


	if (!client.isAuthenticated())
	{
		client.addToOutput(":ircserver 451 * :You have not registered\r\n");
		return;
	}
	if (channelName.empty())
	{
		client.addToOutput(":ircserver 461 " + client.getNickname() + " :Not enough parameters\r\n");
		return;
	}
	std::map<std::string, Channel *>::iterator it_found_channel = _channels.find(channelName);

	bool verif_limit = false;
	bool verif_invit = false;
	bool verif_pwd = false;

	if (it_found_channel == _channels.end())
	{
		Channel *newChannel = new Channel(channelName);
		newChannel->addClient(client, true);
		std::pair<std::string, Channel *> p(channelName, newChannel);
		_channels.insert(p);
		client.addToOutput(":" + client.getNickname() + "!" + client.getUsername() + "@localhost JOIN #" + channelName + "\r\n" + ":ircserver 353 " + client.getNickname() + " = #" + channelName + " :@" + client.getNickname() + "\r\n" + ":ircserver 366 " + client.getNickname() + " #" + channelName + " :End of NAMES list\r\n");
	}
	else
	{
		Channel *found_channel = it_found_channel->second;
		if (found_channel->isUserInChannel(client.getId()))
		{
			client.addToOutput(":ircserver 443 " + client.getNickname() + " #" + found_channel->getName() + " :is already on channel\r\n");
			return;
		}
		
		if (found_channel->isLimited())
		{
			size_t limit_nbr = found_channel->getLimitNbr();
			if (limit_nbr > found_channel->getSizeClients())
			{
				verif_limit = true;
			}
			else
			{
				client.addToOutput(":ircserver 471 " + client.getNickname() + " #" + found_channel->getName() + " :Cannot join channel (+l)\r\n");
				return;
			}
		}
		else
			verif_limit = true;

		if (found_channel->getInvitStatus())
		{
			std::vector<int> invited_list = found_channel->getInvited();
			for (size_t i = 0; i < invited_list.size(); i++)
			{
				if (invited_list[i] == client.getId())
				{
					verif_invit = true;
				}
			}
			if (!verif_invit)
			{
				client.addToOutput(":ircserver 473 " + client.getNickname() + " #" + found_channel->getName() + " :Cannot join channel (+i)\r\n");
				return;
			}
		}
		else
			verif_invit = true;

		if (found_channel->getPwd() == "")
		{
			verif_pwd = true;
		}
		else
		{
			if (found_channel->getPwd() == pwd)
				verif_pwd = true;
			else
			{
				client.addToOutput(":ircserver 475 " + client.getNickname() + " #" + found_channel->getName() + " :Cannot join channel (+k)\r\n");
				return;
			}
		}
		
		if (verif_limit && verif_invit && verif_pwd)
		{
			found_channel->addClient(client, false);
			client.addToOutput(":" + client.getNickname() + "!" + client.getUsername() + "@localhost JOIN #" + found_channel->getName() + "\r\n" + ":ircserver 353 " + client.getNickname() + " = #" + found_channel->getName() + " :" + getChannelMember(found_channel) + "\r\n" + ":ircserver 366 " + client.getNickname() + " #" + found_channel->getName() + " :End of NAMES list\r\n");
		}
	}

}
