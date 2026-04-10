/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:14:25 by asritz            #+#    #+#             */
/*   Updated: 2026/04/09 19:11:54 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ACommand.hpp"


class Channel;
class Client;

class Join : public ACommand
{
public:
	Join(std::map<std::string, Channel*> &channels, std::vector<Client> &cli, std::string &serverPassword) : ACommand(channels, cli, serverPassword) {};
	virtual ~Join() {};

	static ACommand *create(std::map<std::string, Channel*> &channels, std::vector<Client> &cli, std::string &serverPassword)
	{
		return new Join(channels, cli, serverPassword);
	}

	virtual void execute(Client &client, std::string &input);
};
