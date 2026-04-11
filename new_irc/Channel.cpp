/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:23:30 by doferet           #+#    #+#             */
/*   Updated: 2026/04/11 20:16:23 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

std::string Channel::getName()
{
	return (_name);
}

std::string Channel::getTopic()
{
	return (_topic);
}

std::string Channel::getPwd()
{
	return (_pwdChannel);
}

bool Channel::isLimited()
{
	return (_isLimited);
}
int Channel::getLimitNbr()
{
	return (_limitNbr);
}

void Channel::addClient(Client &client)
{
	bool isOp = false;

	if (_clients.empty())
		isOp = true;

	std::pair<Client &, bool> next_pair(client, isOp);
	std::pair<std::string, std::pair<Client &, bool> > p(client.getUsername(), next_pair);

	_clients.insert(p);
}

void Channel::sendMsgChannelMember(std::string msg)
{
	std::map<std::string, std::pair<Client &, bool> >::iterator it = _clients.begin();
	while (it != _clients.end())
	{
		send(it->second.first.getFd(),  msg.c_str(), msg.size(), 0);
	}
}

// faire un sendMsgChannel() qui enverra à tous ses membres le meme msg
// si le dernier client quitte le channel, le channel se ferme
