/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 21:37:14 by doferet           #+#    #+#             */
/*   Updated: 2026/04/12 19:46:12 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACOMMAND_HPP
# define ACOMMAND_HPP

# include "../Client.hpp"
# include "../Channel.hpp"
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
# include <stdlib.h>
# include <sstream>

class ACommand{
    protected:
        std::map<std::string, Channel*> &_channels;
        std::vector<Client> &_cli;
        std::string _serverPassword;
        // ACommand();
    public:
        ACommand(std::map<std::string, Channel*> &channels, std::vector<Client> &cli, std::string &ServerPassword);
        virtual ~ACommand();
        
        virtual void execute(Client &client, std::string &input) = 0;
};

#endif