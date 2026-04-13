/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:01:54 by doferet           #+#    #+#             */
/*   Updated: 2026/04/13 22:14:29 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ACommand.hpp"


ACommand::ACommand(std::map<std::string, Channel*> &channels, std::vector<Client> &cli, std::string &serverPassword) :_channels(channels),  _cli(cli), _serverPassword(serverPassword)
{
    
}

ACommand::~ACommand()
{
    
}

int ACommand::getIdByNick(std::string nickname)
{
    for (size_t i = 0; i < _cli.size(); i++)
    {
        if (_cli[i].getNickname() == nickname)
            return (_cli[i].getId());
    }
    return (-1);
}
