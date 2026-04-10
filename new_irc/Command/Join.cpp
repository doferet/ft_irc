/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:14:35 by asritz            #+#    #+#             */
/*   Updated: 2026/04/09 19:24:28 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"


void Join::execute(Client &client, std::string &input)
{
	std::cout << "dans join ligne a traiter : |" << input << "|" << std::endl;

	if (!client.isAuthenticated())
	{
		std::cout << "client non authentifie, output : 451\n";
		client.addToOutput(":server 451 * :You have not registered\r\n");
		return;
	}
	
	std::cout << "client authentifie, output NOTICE\n";
	client.addToOutput(":server NOTICE * :JOIN not implemented yet\r\n");

	Channel *newChannel = new Channel(input);
	std::pair<std::string, Channel*> p(newChannel->getName(), newChannel);
	
	_channels.insert(p);

	
}
