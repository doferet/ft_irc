/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:05:12 by doferet           #+#    #+#             */
/*   Updated: 2026/04/14 19:10:07 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "CommandFactory.hpp"

CommandFactory::CommandFactory(std::map<std::string, Channel*> &cha, std::vector<Client> &cli, std::string &pass) : _channels(cha), _cli(cli), _serverPassword(pass)
{
    //ajouter les commandes ici au fur et a mesure
    creators["PASS"] = &Pass::create;
    creators["JOIN"] = &Join::create;
    creators["NICK"] = &Nick::create;
    creators["USER"] = &User::create;
    creators["PRIVMSG"] = &Privmsg::create;
    creators["PING"] = &Ping::create;
    creators["MODE"] = &Mode::create;
    creators["PART"] = &Part::create;
    creators["QUIT"] = &Quit::create;
    creators["TOPIC"] = &Topic::create;
    creators["KICK"] = &Kick::create;

}

ACommand* CommandFactory::create(const std::string &name)
{
    std::map<std::string, CreateFn>::iterator it = creators.find(name);
    if (it != creators.end())
        return it->second(_channels, _cli, _serverPassword);
    return NULL;
}

//commande a implementer au minimum
// PING 
// PASS
// NICK
// USER
// JOIN
// PRIVMSG
// KICK
// INVITE
// TOPIC
// MODE
// PART
// QUIT