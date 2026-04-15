/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 17:47:23 by doferet           #+#    #+#             */
/*   Updated: 2026/04/15 17:02:09 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

volatile sig_atomic_t g_stop = 0;

Server::Server(int port, std::string &password) : _port(port), _password(password), _factory(_channels, _clients, _password)
{
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1)
    {
        throw IRCServException(std::string("unable to create socket ") + strerror(errno));
    }
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(_port);
    if (bind(_socket, (const struct sockaddr *)&servaddr, sizeof(servaddr)))
    {
        throw IRCServException(std::string("unable to bind socket ") + strerror(errno));
    }
    if (listen(_socket, 10))
    {
        throw IRCServException(std::string("listen failure ") + strerror(errno));
    }
    std::cout << "successfully connected to port : " << _port << std::endl;
    signal(SIGPIPE, SIG_IGN);
    _id = 0;
}

Server::~Server()
{
    cleanServer();
}

int Server::getnfds()
{
    int nfds = _socket;
    for (std::vector<Client>::iterator cIt = _clients.begin(); cIt != _clients.end(); ++cIt)
    {
        if (cIt->getFd() > nfds)
            nfds = cIt->getFd();
    }
    return nfds + 1;
}

void Server::initSets()
{
    FD_ZERO(&_read);
    FD_ZERO(&_write);
    FD_ZERO(&_error);
    FD_SET(_socket, &_write);
    FD_SET(_socket, &_read);
    FD_SET(_socket, &_error);
    for (std::vector<Client>::iterator cIt = _clients.begin(); cIt != _clients.end(); ++cIt)
    {
        FD_SET(cIt->getFd(), &_write);
        FD_SET(cIt->getFd(), &_read);
        FD_SET(cIt->getFd(), &_error);
    }
}

void Server::removeClientInAllChannels(Client client)
{
    int id = client.getId();

    std::map<std::string, Channel *>::iterator chanit = _channels.begin();
    while (chanit != _channels.end())
    {
        std::map<std::string, Channel *>::iterator next = chanit;
        next++;

        if (chanit->second && chanit->second->isUserInChannel(id)) // si il y a un channel et que le client est dedans
        {
            chanit->second->sendMsgChannelMember(client, "Connection closed", _clients, 1);
            chanit->second->removeClient(id);
            if (chanit->second->isEmpty())
            {
                delete chanit->second;
                _channels.erase(chanit);
            }
        }
        chanit = next;
    }
}

int Server::clientSocketOperation(int index)
{
    int fd = _clients[index].getFd();
    char buffer[BUFFER_SIZE];

    if (FD_ISSET(fd, &_read))
    {
        ssize_t recvSize = recv(fd, buffer, BUFFER_SIZE, 0);
        // std::cout << "recv size : " << recvSize << std::endl;
        if (recvSize <= 0)
        {
            removeClientInAllChannels(_clients[index]);
            _clients[index].setDisconnected(true);
            std::cout << "Client is deconnected\n";
        }
        else
        {
            // std::cout << "Le client du fd : " << fd << " a envoyé : ";
            // std::cout.write(buffer, recvSize);
            // std::cout << " (taille : " << recvSize << ")\n";
            _clients[index].addToInput(buffer, recvSize);
        }
    }
    if (FD_ISSET(fd, &_write))
    {
        std::string buf = _clients[index].getOutputLine();

        if (!buf.empty())
        {
            //ssize_t n = 
            send(fd, buf.c_str(), buf.size(), 0);
            // std::cout << "send fd :" << fd << std::endl;
            // std::cout << "send return : " << n << std::endl;
            // std::cout << "buf du send : " << buf << std::endl;
        }

        // si le res de cIt->getOutput n'est pas vide l'ecrire avec send();
        //  send(fd, "coucou le client ici le serveru", strlen("coucou le client ici le serveru"), 0);
    }
    if (FD_ISSET(fd, &_error))
    {
        removeClientInAllChannels(_clients[index]);
        _clients[index].setDisconnected(true);
        std::cout << "Client is deconnected\n";
    }
    if (_clients[index].getDisconnected() == true)
    {
        // verifier si le client est dans un channel avant de close le fd (en gros le QUIT)
        removeClientInAllChannels(_clients[index]);
        close(fd);
        _clients.erase(_clients.begin() + index);
        return index - 1;
    }
    return index;
}

void handleSignal(int)
{
    g_stop = 1;
}

static void setupSignals()
{
    struct sigaction sa;

    std::memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handleSignal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGHUP, &sa, NULL);
}

void Server::run()
{
    unsigned int len = sizeof(cli);

    setupSignals();
    while (!g_stop)
    {
        initSets();
        int nfds = getnfds();
        _timeout.tv_sec = 0;
        _timeout.tv_usec = 100000;
        if (select(nfds, &_read, &_write, &_error, &_timeout) == -1)
        {
            throw IRCServException(std::string("unexpected select error : ") + strerror(errno));
        }
        if (FD_ISSET(_socket, &_read))
        {
            Client newClient(_id++);
            // std::cout << "action sur read" << std::endl;
            int clientFd = accept(_socket, &cli, &len);
            if (clientFd != -1)
            {
                _clients.push_back(newClient);
                _clients.back().setFd(clientFd);
                // std::cout << "le fd du mouveau client est : " << clientFd << std::endl;
                // std::cout << "liste des fds clients" << std::endl;
                // for (size_t i = 0; i < _clients.size(); i++)
                // {
                //     std::cout << "fd[" << i << "]=" << _clients[i].getFd() << std::endl;
                // }
            }
        }
        if (FD_ISSET(_socket, &_error))
        {
            throw IRCServException(std::string("unexpected error on socket fd : ") + strerror(errno));
        }
        // loop sur les clients pour IO operation
        for (size_t i = 0; i < _clients.size(); i++)
        {
            i = clientSocketOperation(i);
        }
        // loop client pour faires les actions
        for (std::vector<Client>::iterator cIt = _clients.begin(); cIt != _clients.end(); ++cIt)
        {
            std::string str = cIt->getInputLine();
            while (!str.empty())
            {
                std::string commandName = extractCommandName(str);
                if (str.size() > 0)
                {
                    if (commandName == "CAP")
                    {
                        cIt->addToOutput(":ircserver CAP * LS :\r\n");
                        str = cIt->getInputLine();
                        continue;
                    }

                 // std::cout << "ligne a traiter pour client " << cIt->getFd() << " : " << str << std::endl;
                    ACommand *command = _factory.create(commandName);
                    std::cout << "CommandName recu : " << commandName << std::endl;
                    if (command != NULL)
                    {
                       // std::cout << "Avant Execution de la commande : " << commandName << std::endl;
                       command->execute(*cIt, str);
                        // std::cout << "Apres Execution de la commande : " << commandName << std::endl;

                        delete command;
                    }
                    else
                    {
                        cIt->addToOutput(": 421 " + cIt->getUsername() + " " + commandName + " Unknown command(custom)\r\n");
                    }
                    str = cIt->getInputLine();
                }
  
            }
        }
    }
    cleanServer();
}

std::string Server::extractCommandName(std::string &str)
{
    size_t pos = 0;
    std::string command;

    while (!str.empty() && std::isspace(str[0]))
        str.erase(0, 1);
    while (pos < str.size() && !std::isspace(str[pos]))
        pos++;
    command = str.substr(0, pos);
    str.erase(0, pos);
    while (!str.empty() && std::isspace(str[0]))
        str.erase(0, 1);
    return command;
}

void Server::cleanServer()
{
    for (size_t i = 0; i < _clients.size(); ++i)
    {
        int fd = _clients[i].getFd();
        if (fd >= 0)
        {
            close(fd);
            _clients[i].setFd(-1);
        }
    }
    _clients.clear();

    if (_socket >= 0)
    {
        close(_socket);
        _socket = -1;
    }

    for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it)
        delete it->second;
    _channels.clear();
}
