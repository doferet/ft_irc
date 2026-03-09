/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 21:37:14 by doferet           #+#    #+#             */
/*   Updated: 2026/03/09 19:33:51 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACOMMAND_HPP
# define ACOMMAND_HPP

# include "Client.hpp"
# include "Channel.hpp"
# include <iostream>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netinet/in.h>
# include <signal.h>
# include <map>
# include <vector>
# include <string>
# include <cctype>

class ACommand{
    protected:
        std::map<std::string, Channel> &_channels;
        std::vector<Client> &_cli;
        std::string _serverPassword;
        // ACommand();
    public:
        ACommand(std::map<std::string, Channel> &channels, std::vector<Client> &cli, std::string &ServerPassword);
        virtual ~ACommand();
        
        virtual void execute() = 0;
};

#endif