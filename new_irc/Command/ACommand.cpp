/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:01:54 by doferet           #+#    #+#             */
/*   Updated: 2026/03/09 19:33:42 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ACommand.hpp"


ACommand::ACommand(std::map<std::string, Channel> &channels, std::vector<Client> &cli, std::string &serverPassword) :_channels(channels),  _cli(cli), _serverPassword(serverPassword)
{
    
}

ACommand::~ACommand()
{
    
}