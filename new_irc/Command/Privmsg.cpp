/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:04:12 by asritz            #+#    #+#             */
/*   Updated: 2026/04/11 21:22:42 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Privmsg.hpp"

// /msg <dest_nick> <message>

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
	std::cout << "dans PRIVMSG, ligne a traiter: |" << input << "|" << std::endl;

	std::string dest = get_dest(input);
	std::string msg = get_msg(input);
	std::cout << "dans PRIVMSG, destinataire: |" << dest << "|" << std::endl;
	std::cout << "dans PRIVMSG, message à envoyer: |" << msg << "|" << std::endl;

	if (dest[0] == '#') // pour envoyer sur un channel
	{
		// faire verification: si channel existe, si client est membre
		// appeler ensuite channel.sendMsgChannel() pour qu'il se charge d'envoyer aux membres
		std::map<std::string, Channel *>::iterator it = _channels.begin();

		bool found_channel = false;
		while (it != _channels.end())
		{
			if (it->first == dest.substr(1, (dest.size() - 1)))
			{
				it->second->sendMsgChannelMember(msg);
				found_channel = true;
			}
		}
		if (!found_channel)
		{
			client.addToOutput("403 " + dest.substr(1, (dest.size() - 1)) + " :No such channel\r\n");
		}

		_channels.find(dest.substr(1, (dest.size() - 1)));
	}
	else if (dest.empty())
	{
		client.addToOutput("401 " + client.getNickname() + " :No such nick\r\n");
	}
	else // pour envoyer a qqn
	{
		bool found_dest = false;
		for (size_t i = 0; i < _cli.size(); i++)
		{
			if (_cli[i].getNickname() == dest)
			{
				// send(_cli[i].getFd(), msg.c_str(), msg.size(), 0);
				//_cli[i].addToOutput(":" + client.getNickname() + " PRIVMSG " + _cli[i].getNickname() + " :" + msg + "\r\n");
				_cli[i].addToOutput(":" + client.getNickname() + "!" + client.getUsername() + "@127.0.0.1 PRIVMSG " + _cli[i].getNickname() + " :" + msg + "\r\n");
				found_dest = true;
			}
		}
		if (!found_dest)
		{
			client.addToOutput("401 " + client.getNickname() + " :No such nick\r\n");
		}
	}

	// client.addToOutput(":server NOTICE * :PRIVMSG not implemented yet\r\n");
}
