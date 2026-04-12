/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:23:30 by doferet           #+#    #+#             */
/*   Updated: 2026/04/12 21:15:38 by asritz           ###   ########.fr       */
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

bool Channel::getInvitStatus()
{
	return (_invitStatus);
}

std::vector<std::string> Channel::getInvited()
{
	return (invited);
}

size_t Channel::getSizeClients()
{
	return (_clients.size());
}

std::map<std::string, std::pair<Client &, bool> > Channel::getClients()
{
	return (_clients);
}

std::vector<std::string> Channel::getNickClients()
{
	std::vector<std::string> nickList;
	std::map<std::string, std::pair<Client &, bool> >::iterator it = _clients.begin();
	while (it != _clients.end())
	{
		std::pair<Client &, bool> p = it->second;
		Client & cli = p.first;
		std::string op;
		if (p.second == true)
			op = "@";
		else
			op = "";
		nickList.push_back(op + cli.getNickname());
	}
	return (nickList);
}

void Channel::addClient(Client &client, bool op)
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
	std::map<std::string, std::pair<Client &, bool> >::iterator it = _clients.find(nickname);
	it->second.second = true;
}

bool Channel::isUserInChannel(std::string nickname)
{
	if (_clients.find(nickname) == _clients.end())
		return true;
	return false;
}

void Channel::removeLimit()
{
	_isLimited = false;
}

void Channel::removeOperator(std::string nickname)
{
	std::map<std::string, std::pair<Client &, bool> >::iterator it = _clients.find(nickname);
	it->second.second = false;
}

void Channel::changeInvitStatus(bool status)
{
	_invitStatus = status;
}

void Channel::sendMsgChannelMember(std::string msg)
{
	std::map<std::string, std::pair<Client &, bool> >::iterator it = _clients.begin();
	while (it != _clients.end())
	{
		send(it->second.first.getFd(), msg.c_str(), msg.size(), 0);
	}
}

// faire un sendMsgChannel() qui enverra à tous ses membres le meme msg
// si le dernier client quitte le channel, le channel se ferme
