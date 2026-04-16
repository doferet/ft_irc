/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:04:27 by asritz            #+#    #+#             */
/*   Updated: 2026/04/16 16:56:13 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVMSG_HPP
#define PRIVMSG_HPP

#include "ACommand.hpp"

class Channel;
class Client;

class Privmsg : public ACommand
{
public:
	Privmsg(std::map<std::string, Channel *> &channels, std::vector<Client> &cli, std::string &serverPassword) : ACommand(channels, cli, serverPassword) {};
	virtual ~Privmsg() {};

	static ACommand *create(std::map<std::string, Channel *> &channels, std::vector<Client> &cli, std::string &serverPassword)
	{
		return new Privmsg(channels, cli, serverPassword);
	}

	virtual void execute(Client &client, std::string &input);
};

#endif
