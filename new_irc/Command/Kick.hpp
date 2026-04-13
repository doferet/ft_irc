/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:10:18 by tronguye          #+#    #+#             */
/*   Updated: 2026/04/13 22:15:19 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KICK_HPP
#define KICK_HPP

#include "ACommand.hpp"

class Kick : public ACommand
{
public:
    Kick(std::map<std::string, Channel *> &channels, std::vector<Client> &cli, std::string &serverPassword) : ACommand(channels, cli, serverPassword) {};

    static ACommand *create(std::map<std::string, Channel *> &channels, std::vector<Client> &cli, std::string &serverPassword)
    {
        return new Kick(channels, cli, serverPassword);
    }

    virtual void execute(Client &client, std::string &input);
};

#endif
