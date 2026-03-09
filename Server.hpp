/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:54:14 by doferet           #+#    #+#             */
/*   Updated: 2025/10/29 17:23:02 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#define FD_MAX 1024
#include <map>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>  
#include <sys/socket.h> 
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "Client.hpp"

class Server
{
	public:
		Server();
		~Server();
		void initServer(int port, std::string password);
		void serverSignal(int signum);

	private:
		std::map <int, Client> _clients;
		 bool server_signal;
};

#endif