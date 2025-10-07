/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:48:07 by doferet           #+#    #+#             */
/*   Updated: 2025/10/07 15:17:38 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cstring>      // memset, strlen
#include <unistd.h>     // close()
#include <sys/socket.h> // socket, bind, listen, accept
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h>  // inet_ntoa
#include "Error.hpp"

int main() {
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli; 

    // socket create and verification 
    try{ 
        sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    } catch (std::exception &e)
    {
        std::cerr << "socket failed" << std::endl;
    }
    
    bzero(&servaddr, sizeof(servaddr)); 

    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
    servaddr.sin_port = htons(8081); 
  
    // Binding newly created socket to given IP and verification 
    try{
        
    }
    bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
   
    listen(sockfd, 10);
    len = sizeof(cli);
    connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
    if (connfd < 0) { 
        printf("server acccept failed...\n"); 
    } 
    else
        printf("server acccept the client...\n");
}