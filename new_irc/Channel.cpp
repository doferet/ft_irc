/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:23:30 by doferet           #+#    #+#             */
/*   Updated: 2026/04/13 22:37:10 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel()
{
	_isLimited = false;
	_limitNbr = 0;
	_invitStatus = false;
}

Channel::Channel(const std::string &name)
{
	_name = name;
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

bool Channel::getTopicStatus()
{
	return (_topicStatus);
}

bool Channel::getInvitStatus()
{
	return (_invitStatus);
}

std::vector<int> Channel::getInvited()
{
	return (invited);
}

size_t Channel::getSizeClients()
{
	return (_clients.size());
}

std::map<int, std::pair<Client &, bool> > Channel::getClients()
{
	return (_clients);
}

std::vector<std::string> Channel::getNickClients()
{
	std::vector<std::string> nickList;
	std::map<int, std::pair<Client &, bool> >::iterator it = _clients.begin();
	while (it != _clients.end())
	{
		std::pair<Client &, bool> p = it->second;
		Client &cli = p.first;
		std::string op;
		if (p.second == true)
			op = "@";
		else
			op = "";
		nickList.push_back(op + cli.getNickname());
		it++;
	}
	return (nickList);
}

void Channel::addClient(Client &client, bool op)
{
	bool isOp = op;

	std::cout << "adresse du client dans addClient():" << &client << std::endl;

	std::pair<Client &, bool> next_pair(client, isOp);
	std::cout << "adresse du next_pair dans addClient():" << &next_pair.first << std::endl;
	std::pair<int, std::pair<Client &, bool> > p(client.getId(), next_pair);

	std::cout << "addClient key = |" << client.getUsername() << "|" << std::endl;
	std::cout << "nickname = |" << client.getNickname() << "|" << std::endl;

	_clients.insert(p);
}

void Channel::removeClient(int id)
{
	_clients.erase(id);
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

void Channel::setOperator(int id)
{
	std::map<int, std::pair<Client &, bool> >::iterator it = _clients.find(id);
	it->second.second = true;
}

// bool Channel::isUserInChannel(Client &client)
// {
// 	std::map<std::string &, std::pair<Client &, bool>>::iterator it = _clients.begin();
// 	while (it != _clients.end())
// 	{
// 		if (&(it->second.first) == &client)
// 			return true;
// 		it++;
// 	}
// 	return false;
// }

bool Channel::isUserInChannel(int id)
{
	std::cout << "IsUserInChannel() id: " << id << std::endl;
	
	std::map<int, std::pair<Client &, bool> >::iterator it = _clients.begin();
	while (it != _clients.end())
	{
		std::cout << "IsUserInChannel() nick de _clients: " << it->second.first.getNickname() << std::endl;
		it++;
	}
	
	if (_clients.find(id) == _clients.end())
		return false;
	return true;
}

bool Channel::isUserOperator(int id)
{
	std::map<int, std::pair<Client &, bool> >::iterator it = _clients.find(id);
	if (it != _clients.end() && it->second.second == true)
		return true;
	return false;
}

void Channel::removeLimit()
{
	_isLimited = false;
}

void Channel::removeOperator(int id)
{
	std::map<int, std::pair<Client &, bool> >::iterator it = _clients.find(id);
	if (it != _clients.end())
		it->second.second = false;
}

void Channel::changeInvitStatus(bool status)
{
	_invitStatus = status;
}

void Channel::changeTopicStatus(bool status)
{
	_topicStatus = status;
}

void Channel::sendMsgChannelMember(Client &client, std::string msg)
{
	std::map<int, std::pair<Client &, bool> >::iterator it = _clients.begin();
	while (it != _clients.end())
	{
		it->second.first.addToOutput(":" + client.getNickname() +
									 "!" + client.getUsername() +
									 "@localhost PRIVMSG " + it->second.first.getNickname() +
									 " :" + msg + "\r\n"
									);
		it++;
	}
}
bool Channel::isEmpty()
{
	if (_clients.size() == 0)
		return true;
	return false;
}


// faire un sendMsgChannel() qui enverra à tous ses membres le meme msg
// si le dernier client quitte le channel, le channel se ferme
