/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:14:35 by asritz            #+#    #+#             */
/*   Updated: 2026/04/13 23:19:32 by asritz           ###   ########.fr       */
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

std::string getChannelMember(Channel *channel)
{
	std::string nickList;
	std::vector<std::string> cli = channel->getNickClients();
	for (size_t i = 0; i < cli.size(); i++)
		nickList += cli[i] + " ";
	return (nickList);
}

void Join::execute(Client &client, std::string &input)
{
	std::cout << "JOIN ligne a traiter : |" << input << "|" << std::endl;
	std::string pwd = getPwd(input);
	std::string channelName = getChannelName(input);
	std::cout << "JOIN Nom du Channel : |" << channelName << "|" << std::endl;
	std::cout << "JOIN pwd : |" << pwd << "|" << std::endl;

	if (!client.isAuthenticated())
	{
		std::cout << "client non authentifie, output : 451\n";
		client.addToOutput(":server 451 * :You have not registered\r\n");
		return;
	}
	if (channelName.empty())
	{
		client.addToOutput(":server 461 " + client.getNickname() + " :Not enough parameters\r\n");
		return;
	}
	std::map<std::string, Channel *>::iterator it_found_channel = _channels.find(channelName);

	bool verif_limit = false;
	bool verif_invit = false;
	bool verif_pwd = false;

	if (it_found_channel == _channels.end()) // si le channel existe pas
	{
		Channel *newChannel = new Channel(channelName);
		newChannel->addClient(client, true);
		std::pair<std::string, Channel *> p(channelName, newChannel);
		_channels.insert(p);
		client.addToOutput(":" + client.getNickname() + "!" + client.getUsername() + "@localhost JOIN #" + channelName + "\r\n" + ": 353 " + client.getNickname() + " = #" + channelName + " :@" + client.getNickname() + "\r\n" + ": 366 " + client.getNickname() + " #" + channelName + " :End of NAMES list\r\n");
	}
	else // si il existe
	{
		Channel *found_channel = it_found_channel->second;
		if (found_channel->isLimited()) // si le channel est limité en nombre (+l)
		{
			size_t limit_nbr = found_channel->getLimitNbr();
			if (limit_nbr > found_channel->getSizeClients())
			{
				verif_limit = true;
			}
			else
			{
				// error channel plein
				client.addToOutput(": 471 " + client.getNickname() + " #" + found_channel->getName() + " :Cannot join channel (+l)\r\n");
				return;
			}
		}
		else
			verif_limit = true;

		if (found_channel->getInvitStatus()) // si le channel a configuré des invits (+i)
		{
			std::vector<int> invited_list = found_channel->getInvited();
			for (size_t i = 0; i < invited_list.size(); i++)
			{
				if (invited_list[i] == client.getId()) // si le client fait parti des invités
				{
					verif_invit = true;
				}
			}
			if (!verif_invit)
			{
				// error client non invité
				client.addToOutput(": 473 " + client.getNickname() + " #" + found_channel->getName() + " :Cannot join channel (+i)\r\n");
				return;
			}
		}
		else
			verif_invit = true;

		if (found_channel->getPwd() == "") // si le channel a PAS pwd
		{
			verif_pwd = true;
		}
		else // si channel a un pwd (+k)
		{
			if (found_channel->getPwd() == pwd)
				verif_pwd = true;
			else
			{
				// error mdp mauvais
				client.addToOutput(": 475 " + client.getNickname() + " #" + found_channel->getName() + " :Cannot join channel (+k)\r\n");
				return;
			}
		}
//chzck si client esst dedqns qvqnt de lajouter
		// check si toutes les verifs sont bonnes
		if (verif_limit && verif_invit && verif_pwd)
		{
			found_channel->addClient(client, false);
			// msg pour dire que le client a été add au channel (afficher nombre d'Op + list membre)
			client.addToOutput(":" + client.getNickname() + "!" + client.getUsername() + "@localhost JOIN #" + found_channel->getName() + "\r\n" + ": 353 " + client.getNickname() + " = #" + found_channel->getName() + " :" + getChannelMember(found_channel) + "\r\n" + ": 366 " + client.getNickname() + " #" + found_channel->getName() + " :End of NAMES list\r\n");
		}
		// else
		// {
		// 	// error une verif au moins n'a pas abouti
		// 	client.addToOutput(": XXX " + client.getNickname() + " :Au moins une verif a été mauvaise\r\n");
		// }
	}
}

/*
	si le channel existe pas:
		- créer le channel
		- ajouter le client au channel + le mettre op
	si le channel existe:
		- check si limitNbr
		- check si pwd
		- check si client est invité
		- check si déjà dedans
			-> ajouter le client au channel


*/
