/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:35:14 by doferet           #+#    #+#             */
/*   Updated: 2026/04/12 20:37:20 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUIT_HPP
# define QUIT_HPP

#include "ACommand.hpp"

class Quit : public ACommand
{
public:
    Quit(std::map<std::string, Channel *> &channels, std::vector<Client> &cli, std::string &serverPassword): ACommand(channels, cli, serverPassword) {};

    static ACommand *create(std::map<std::string, Channel *> &channels, std::vector<Client> &cli, std::string &serverPassword)
    {
        return new Quit(channels, cli, serverPassword);
    }

    virtual void execute(Client &client, std::string &input);
};

#endif