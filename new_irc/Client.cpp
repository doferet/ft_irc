/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:53:58 by doferet           #+#    #+#             */
/*   Updated: 2026/04/12 21:40:42 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client()
{
    _fd = -1;
    _disconnected = false;
    _hasValidNickname = false;
    _hasValidPassword = false;
    _hasValidUsername = false;
}
Client::~Client()
{
}

int Client::getFd() const{
    return _fd;
}

void Client::setFd(int fd)
{
    _fd = fd;
}
	
void Client::addToInput(char buffer[], int bufferSize)
{
    _input.insert(_input.end(), buffer, buffer + bufferSize);
}
	
void Client::addToOutput(std::string buffer)
{
    _output.insert(_output.end(), buffer.c_str(), buffer.c_str() + buffer.size());
}
	
std::string Client::getInputLine()
{
    std::string line;
    std::vector<char>::iterator it = std::find(_input.begin(), _input.end(), '\n');
    if (it == _input.end())
        return "";
    if (it != _input.begin() && *(it - 1) == '\r') {
        std::cout<<"on avait un \r dans l'entree"<<std::endl;
        --it;
    }
    line.insert(line.end(), _input.begin(), it);
    _input.erase(_input.begin(), it + 1);
    return line;    
}

std::string Client::getOutputLine()
{
    std::string line;
    std::vector<char>::iterator it = std::find(_output.begin(), _output.end(), '\n');
    if (it == _output.end())
        return "";
    line.insert(line.end(), _output.begin(), it + 1);
    _output.erase(_output.begin(), it + 1);
    return line;    
}

bool Client::getDisconnected()
{
    return _disconnected;
}

void Client::setDisconnected(bool status)
{
    _disconnected = status;
}

void Client::setHasValidPassword(bool status)
{
    _hasValidPassword = status;
}

bool Client::getHasValidPassword()
{
    return _hasValidPassword;
}

void Client::setHasValidNickname(bool nickname)
{
    _hasValidNickname = nickname;
}

bool Client::getHasValidNickname()
{
    return _hasValidNickname;
}

void Client::setHasValidUsername(bool Username)
{
    _hasValidUsername = Username;
}

bool Client::getHasValidUsername()
{
    return _hasValidUsername;
}

void Client::setNickname(std::string name)
{
    _nickname = name;
}

std::string Client::getNickname() const { return _nickname; }

std::string Client::getUsername() const { return _username; }


void Client::setUsername(std::string name)
{
    _username = name;
}

bool Client::isAuthenticated()
{
    return (_hasValidPassword && _hasValidNickname && _hasValidUsername);
}

	