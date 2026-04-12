/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:23:30 by doferet           #+#    #+#             */
/*   Updated: 2026/04/12 16:20:14 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel()
{
	_isLimited = false;
	_limitNbr = 0;
	_invitStatus = false;
}

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

void Channel::addClient(Client &client,  bool op)
{
	bool isOp = op;
		
	std::pair<Client &, bool> next_pair(client, isOp);
	std::pair<std::string, std::pair<Client &, bool> > p(client.getUsername(), next_pair);
	
	_clients.insert(p);
}

void Channel::setLimit(int limit)
{
	_isLimited = true;
	_limitNbr = limit;
}

void Channel::setTopic(std::string topic)
{
	_topic = topic;
}

void Channel::setPassword(std::string password)
{
	_pwdChannel = password;
}

void Channel::setOperator(std::string nickname)
{
	std::map<std::string, std::pair<Client& , bool> >::iterator it = _clients.find(nickname);
	it->second.second = true;
}

bool Channel::isUserInChannel(std::string nickname)
{
	if (_clients.find(nickname) == _clients.end())
		return false;
	return true;
}

bool Channel::isUserOperator(std::string nickname)
{
	std::map<std::string, std::pair<Client& , bool> >::iterator it = _clients.find(nickname);
	if (it != _clients.end() && it->second.second == true)
		return true;
	return false;
}
        
void Channel::removeLimit()
{
	_isLimited = false;
}

void Channel::removeOperator(std::string nickname)
{
	std::map<std::string, std::pair<Client& , bool> >::iterator it = _clients.find(nickname);
	if (it != _clients.end())
		it->second.second = false;
}

void Channel::changeInvitStatus(bool status)
{
	_invitStatus = status;
}
