/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:04:12 by asritz            #+#    #+#             */
/*   Updated: 2026/04/13 22:27:21 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Commandes à rentrer dans Irssi

	Pour envoyer un msg privé a qqn:
	/msg <dest_nick> <message>

	Pour vérifier les fenêtres d'ouvertes (et voir si on a reçu un msg)
	/windows list
	/window X (X = le numéro de la window)

*/

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
				found_channel = true;
				//if (it->second->isUserInChannel(client.getNickname()))
				if (it->second->isUserInChannel(client.getId()))
				{
					it->second->sendMsgChannelMember(client, msg);
				}
				else
				{
					client.addToOutput("442 " + client.getNickname() + " #" + dest.substr(1, (dest.size() - 1)) + " :You're not on that channel\r\n");
					return;
				}
			}
			it++;
		}
		if (!found_channel)
		{
			client.addToOutput("403 #" + dest.substr(1, (dest.size() - 1)) + " :No such channel\r\n");
			return;
		}

		//_channels.find(dest.substr(1, (dest.size() - 1)));
	}
	else if (dest.empty())
	{
		std::cout << "rentre dans la condition pour envoyer a un channel\n";
		client.addToOutput("401 " + client.getNickname() + " :No such nick\r\n");
		return;
	}
	else // pour envoyer a qqn
	{
		bool found_dest = false;
		for (size_t i = 0; i < _cli.size(); i++)
		{
			if (_cli[i].getNickname() == dest)
			{
				//_cli[i].addToOutput(":" + client.getNickname() + " PRIVMSG " + _cli[i].getNickname() + " :" + msg + "\r\n");
				_cli[i].addToOutput(":" + client.getNickname() + "!" + client.getUsername() + "@localhost PRIVMSG " + _cli[i].getNickname() + " :" + msg + "\r\n");
				found_dest = true;
			}
		}
		if (!found_dest)
		{
			std::cout << "Rentre dans condition pour envoyer a qqn\n";
			client.addToOutput("401 " + client.getNickname() + " :No such nick\r\n");
			return;
		}
	}
	// client.addToOutput(":server NOTICE * :PRIVMSG not implemented yet\r\n");
}
