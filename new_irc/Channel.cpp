/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:23:30 by doferet           #+#    #+#             */
/*   Updated: 2026/04/14 21:50:32 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel()
{
	_isLimited = false;
	_limitNbr = 0;
	_invitStatus = false;
	_topicStatus = false;
}

Channel::Channel(const std::string &name)
{
	_name = name;
	_isLimited = false;
	_limitNbr = 0;
	_invitStatus = false;
	_topicStatus = false;
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

std::map<int, bool> Channel::getClients()
{
	return (_clients);
}

Client *Channel::findClientById(std::vector<Client> &server_clients, int id)
{
	for (size_t i = 0; i < server_clients.size(); i++)
	{
		if (server_clients[i].getId() == id)
			return (&server_clients[i]);
	}
	return (NULL);
}

std::vector<std::string> Channel::getNickClients(std::vector<Client> &server_clients)
{
	std::vector<std::string> nickList;
	std::map<int, bool>::iterator it = _clients.begin();
	while (it != _clients.end())
	{
		Client *client_found = findClientById(server_clients, it->first);
		if (client_found != NULL)
		{
			if (it->second == true)
				nickList.push_back("@" + client_found->getNickname());
			else
				nickList.push_back(client_found->getNickname());
		}
		it++;
	}
	return (nickList);
}

void Channel::addClient(Client &client, bool op)
{
	bool isOp = op;

	std::pair<int, bool> p(client.getId(), isOp);

	std::cout << "addClient key = |" << client.getId() << "|" << std::endl;
	std::cout << "nickname = |" << client.getNickname() << "|" << std::endl;
	std::cout << "Op ? = |" << isOp << "|" << std::endl;

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
	std::map<int, bool>::iterator it = _clients.find(id);
	it->second = true;
}

bool Channel::isUserInChannel(int id)
{
	//std::cout << "IsUserInChannel() id: " << id << std::endl;

	std::map<int, bool>::iterator it = _clients.begin();
	while (it != _clients.end())
	{
		//std::cout << "IsUserInChannel() id de _clients: " << it->first << std::endl;
		it++;
	}

	if (_clients.find(id) == _clients.end())
		return false;
	return true;
}

bool Channel::isUserOperator(int id)
{
	std::map<int, bool>::iterator it = _clients.find(id);
	if (it != _clients.end() && it->second == true)
		return true;
	return false;
}

void Channel::removeLimit()
{
	_isLimited = false;
}

void Channel::removeOperator(int id)
{
	std::map<int, bool>::iterator it = _clients.find(id);
	if (it != _clients.end())
		it->second = false;
}

void Channel::changeInvitStatus(bool status)
{
	_invitStatus = status;
}

void Channel::changeTopicStatus(bool status)
{
	_topicStatus = status;
}

void Channel::sendMsgChannelMember(Client &client, std::string msg, std::vector<Client> &server_clients, int msg_type)
{
	std::map<int, bool>::iterator it = _clients.begin();
	while (it != _clients.end())
	{
		Client *dest = findClientById(server_clients, it->first);
		if (dest != NULL && dest != &client)
		{
			if (msg_type == 0) // si Privmsg
				dest->addToOutput(":" + client.getNickname() +
								  "!" + client.getUsername() +
								  "@localhost PRIVMSG #" + _name +
								  " :" + msg + "\r\n");
			if (msg_type == 1) // si Quit
				dest->addToOutput(":" + client.getNickname() +
								  "!" + client.getUsername() +
								  "@localhost QUIT :" +
								  msg + "\r\n");
		}

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
