/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:54:14 by doferet           #+#    #+#             */
/*   Updated: 2025/10/15 16:16:24 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include <map>
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>  
#include <sys/socket.h> 
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
};

#endif