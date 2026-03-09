/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 21:47:47 by doferet           #+#    #+#             */
/*   Updated: 2026/03/09 19:40:11 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDFACTORY_HPP
# define COMMANDFACTORY_HPP

#include <map>
#include <vector>
#include <string>
#include "ACommand.hpp"
#include "Pass.hpp"

class Channel;
class Client;

typedef ACommand* (*CreateFn)(std::map<std::string, Channel> &, std::vector<Client> &, std::string &);

class CommandFactory {
private:
    std::map<std::string, Channel> & _channels;
    std::vector<Client> & _cli;
    std::string &_serverPassword;
   // std::map<std::string, CreateFn> creators;
   std::map<std::string, CreateFn> creators;
   
public:
    // CommandFactory();
    CommandFactory(std::map<std::string, Channel> &cha, std::vector<Client> &cli, std::string &pass);

    ACommand* create(const std::string& name);
};

#endif