/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:24:41 by doferet           #+#    #+#             */
/*   Updated: 2026/04/12 15:11:05 by doferet          ###   ########.fr       */
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

    virtual void execute(Client &client, std::string &input);
};


#endif