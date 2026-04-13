/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:24:41 by doferet           #+#    #+#             */
/*   Updated: 2026/04/13 22:24:48 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_HPP
# define MODE_HPP

#include "ACommand.hpp"

class Mode : public ACommand
{
public:
    Mode(std::map<std::string, Channel *> &channels, std::vector<Client> &cli, std::string &serverPassword): ACommand(channels, cli, serverPassword) {};

    static ACommand *create(std::map<std::string, Channel *> &channels, std::vector<Client> &cli, std::string &serverPassword)
    {
        return new Mode(channels, cli, serverPassword);
    }

    void option_o(std::stringstream &ss, bool isPlus, std::map<std::string, Channel*>::iterator channel, Client &client);
    void option_k(std::stringstream &ss, bool isPlus, std::map<std::string, Channel*>::iterator channel, Client &client);
    void option_l(std::stringstream &ss, bool isPlus, std::map<std::string, Channel*>::iterator channel, Client &client);
    virtual void execute(Client &client, std::string &input);
};


#endif