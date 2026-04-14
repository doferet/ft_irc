/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 17:47:11 by doferet           #+#    #+#             */
/*   Updated: 2026/04/14 21:16:13 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <signal.h>
#include <map>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>
#include <errno.h>
#include "Client.hpp"
#include "Command/ACommand.hpp"
#include "Command/CommandFactory.hpp"
#include "Channel.hpp"
#include <csignal>

class Server
{
private:
    int _socket;
    int _port;
    std::string _password;
    struct sockaddr_in servaddr;
    struct sockaddr cli;
    struct timeval _timeout;
    fd_set _write;
    fd_set _read;
    fd_set _error;
    std::vector<Client> _clients;
    std::map<std::string, Channel *> _channels;
    CommandFactory _factory;
    int _id;

    Server();
    // Server(const Server &copy);
    // Server &operator=(const Server &copy);
    
    int getnfds();
    void initSets();
    int clientSocketOperation(int index);
    std::string extractCommandName(std::string &str);

public:
    Server(int port, std::string &password);

    ~Server();
    void removeClientInAllChannels(Client client);
    void run();

    class IRCServException : public std::exception
    {
    public:
        IRCServException(const std::string &m) : _message(m) {};
        virtual ~IRCServException() throw() {};
        virtual const char *what() const throw()
        {
            return _message.c_str();
        };

    private:
        const std::string _message;
    };
};

#endif