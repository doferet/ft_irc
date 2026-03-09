/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:53:34 by doferet           #+#    #+#             */
/*   Updated: 2025/11/03 11:07:57 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server()
{
	
}

Server::~Server()
{
	
}

void Server::initServer(int port, std::string password)
{
	int sockfd, connfd;
    socklen_t len;
    struct sockaddr_in servaddr;
	(void)port;
	(void)password;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1)
    {
        throw std::runtime_error("socket error");
    }
    bzero(&servaddr, sizeof(servaddr)); 
	
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
    servaddr.sin_port = htons(8081); 
	
	int optval = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
        throw std::runtime_error("bind error");
    }
    if (listen(sockfd, 10) == -1)
    {
        throw std::runtime_error("listen error");
    }
    //len = sizeof(cli);
    select + FD_ZERO etc...
    //connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
    if (connfd == -1) {
        throw std::runtime_error("server accept failed...");
    } 
}

void Server::serverSignal(int signum)
{
    Server::server_signal = false;

    (void)signum;
    std::cout << "signal received" << std::endl;
    Server::server_signal = true;
}


