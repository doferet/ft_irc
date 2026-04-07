/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 17:47:23 by doferet           #+#    #+#             */
/*   Updated: 2026/04/06 22:34:52 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, std::string &password): _port(port), _password(password), _factory(_channels, _clients, _password)
{
    _socket = socket(AF_INET, SOCK_STREAM, 0); 
    if (_socket == -1) {
        throw IRCServException(std::string("unable to create socket ") + strerror(errno));
    }
    bzero(&servaddr, sizeof(servaddr)); 

    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(_port); 
    if (bind(_socket, (const struct sockaddr *)&servaddr, sizeof(servaddr))) {
        throw IRCServException(std::string("unable to bind socket ") + strerror(errno));
    }
    if (listen(_socket, 10)) {
        throw IRCServException(std::string("listen failure ") + strerror(errno));
    }
    std::cout<<"successfully connected to port : "<<_port<<std::endl;
    signal(SIGPIPE, SIG_IGN);
}

// Server::Server(const Server &copy)
// {
// }
// Server &Server::operator=(const Server &copy)
// {
//     return *this;
// }

Server::~Server()
{
    
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

int Server::clientSocketOperation(int index)
{
    int fd = _clients[index].getFd();
    char buffer[BUFFER_SIZE];
    // std::cout<<"loop socket client"<<std::endl;
    if (FD_ISSET(fd, &_read))
    {
        ssize_t recvSize = recv(fd, buffer, BUFFER_SIZE, 0);
        std::cout<<"recv size : "<<recvSize<<std::endl;
        if (recvSize <= 0)
        {
        //0 cient s'est deco 
        //-1 erreur sur le socket
        //dans tout les cas quitter les channels et degager le client
            _clients[index].setDisconnected(true);
        }
        else 
        {
            std::cout << "Le client du fd : " << fd << " a envoyé : ";
            std::cout.write(buffer, recvSize);
            std::cout << " (taille : " << recvSize << ")\n";
            _clients[index].addToInput(buffer, recvSize);
        }
    }
    if (FD_ISSET(fd, &_write))
    {
        //si le res de cIt->getOutput n'est pas vide l'ecrire avec send();
        // send(fd, "coucou le client ici le serveru", strlen("coucou le client ici le serveru"), 0);
    }
    if (FD_ISSET(fd, &_error))
    {
        //degager le client du vector le destructeur fermera le fd le virer de tout ses channels
        _clients[index].setDisconnected(true);
    }
    if (_clients[index].getDisconnected() == true)
    {
        close(fd);
        _clients.erase(_clients.begin() + index);
        return index - 1;
    }
    return index;
}

void Server::run()
{
    unsigned int len = sizeof(cli);
    while (1)
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
            Client newClient;
            std::cout << "action sur read" << std::endl;
            int clientFd = accept(_socket, &cli, &len);
            _clients.push_back(newClient);
            _clients.back().setFd(clientFd);
            std::cout<<"le fd du mouveau client est : "<<clientFd<<std::endl;
            std::cout<<"liste des fds clients"<<std::endl;
            for (size_t i = 0; i < _clients.size(); i++){std::cout<<"fd["<<i<<"]="<<_clients[i].getFd()<<std::endl;}
        }
        if (FD_ISSET(_socket, &_error))
        {
            throw IRCServException(std::string("unexpected error on socket fd : ") + strerror(errno));
        }
        //loop sur les clients pour IO operation
        for (size_t i = 0; i < _clients.size(); i++)
        {
            i = clientSocketOperation(i);
        }
        //loop client pour faires les actions
        for (std::vector<Client>::iterator cIt = _clients.begin(); cIt != _clients.end(); ++cIt)
        {
            std::string str = cIt->getInputLine(), commandName = extractCommandName(str);
            if (str.size() > 0)
            {
                std::cout<<"ligne a traiter pour client "<<cIt->getFd()<<" : "<<str<<std::endl;
                //il faut identifier la commande new ACommand avc le bon type et appeller command->execute
                ACommand *command = _factory.create(commandName);
                if (command != NULL)
                {
                    command->execute(*cIt, str);
                    delete command;
                    //attention si quit l'utilisateur est retire de la liste des clients et l'iterateur invalide
                }
                else
                {
                    std::cout<<"unknow command : "<<commandName<<std::endl;
                    //envoyer un message bien formate au client pour lu dire que la commande n'est pas trouvee
                }
            }
        }
    }
}

std::string Server::extractCommandName(std::string &str)
{
    size_t pos = 0;
    std::string command;

    while(!str.empty() && std::isspace(str[0]))
        str.erase(0, 1);
    while(pos < str.size() && !std::isspace(str[pos]))
        pos++;
    command = str.substr(0, pos);
    str.erase(0, pos);
    while(!str.empty() && std::isspace(str[0]))
        str.erase(0, 1);
    return command;
    //extraire le 1er mot trim les espaces enlever le nom de la cmd de la str puis return ce mot
}
