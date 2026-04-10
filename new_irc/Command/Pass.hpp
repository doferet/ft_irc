/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 21:54:48 by doferet           #+#    #+#             */
/*   Updated: 2026/04/09 19:11:03 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASS_HPP
# define PASS_HPP

// # include "Server.hpp"
# include "ACommand.hpp"

// class Pass : public ACommand {
// public:
//     Pass(std::map<std::string, Channel&> &channels,
//          std::vector<Client> &cli,
//          bool needAuth,
//          std::string &password)
//         : ACommand(channels, cli, needAuth, password)
//     {}

//     static ACommand* create(std::map<std::string, Channel&> &channels,
//                             std::vector<Client> &cli,
//                             bool needAuth,
//                             std::string &password) {
//         return new Pass(channels, cli, needAuth, password);
//     }

//     virtual void execute(){}
// };

class Channel;
class Client;


class Pass : public ACommand {
public:
    Pass(std::map<std::string, Channel*> &channels, std::vector<Client> &cli, std::string &serverPassword): ACommand(channels, cli, serverPassword){};
    static ACommand* create(std::map<std::string, Channel*> &channels, std::vector<Client> &cli, std::string &serverPassword) {
        return new Pass(channels, cli, serverPassword);
    }
    virtual void execute(Client &client, std::string &input);
    
};

#endif