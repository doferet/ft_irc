/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:04:12 by asritz            #+#    #+#             */
/*   Updated: 2026/04/16 16:53:10 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Privmsg.hpp"

std::string get_dest(std::string input)
{
	size_t n = input.find(":");

	if (n == std::string::npos)
		return ("");
	return (input.substr(0, n - 1));
}

std::string get_msg(std::string input)
{
	size_t n = input.find(":");

	if (n == std::string::npos)
		return ("");
	return (input.substr(n + 1, (input.size() - n + 1)));
}

void Privmsg::execute(Client &client, std::string &input)
{

	std::string dest = get_dest(input);
	std::string msg = get_msg(input);

	if (dest[0] == '#')
	{
		std::map<std::string, Channel *>::iterator it = _channels.begin();

		bool found_channel = false;
		while (it != _channels.end())
		{
			if (it->first == dest.substr(1, (dest.size() - 1)))
			{
				found_channel = true;
				if (it->second->isUserInChannel(client.getId()))
				{
					it->second->sendMsgChannelMember(client, msg, _cli, 0);
				}
				else
				{
					client.addToOutput(":ircserv 442 " + client.getNickname() + " #" + dest.substr(1, (dest.size() - 1)) + " :You're not on that channel\r\n");
					return;
				}
			}
			it++;
		}
		if (!found_channel)
		{
			client.addToOutput(":ircserv 403 #" + dest.substr(1, (dest.size() - 1)) + " :No such channel\r\n");
			return;
		}
	}
	else if (dest.empty())
	{
		client.addToOutput(":ircserv 401 " + client.getNickname() + " :No such nick\r\n");
		return;
	}
	else 
	{
		bool found_dest = false;
		for (size_t i = 0; i < _cli.size(); i++)
		{
			if (_cli[i].getNickname() == dest)
			{
				_cli[i].addToOutput(":" + client.getNickname() + "!" + client.getUsername() + "@localhost PRIVMSG " + _cli[i].getNickname() + " :" + msg + "\r\n");
				found_dest = true;
			}
		}
		if (!found_dest)
		{
			client.addToOutput(":ircserv 401 " + client.getNickname() + " :No such nick\r\n");
			return;
		}
	}
}
