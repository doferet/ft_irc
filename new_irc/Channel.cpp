/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:23:30 by doferet           #+#    #+#             */
/*   Updated: 2026/04/09 19:26:06 by asritz           ###   ########.fr       */
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
