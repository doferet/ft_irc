/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:22:45 by doferet           #+#    #+#             */
/*   Updated: 2026/04/16 17:01:31 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <map>
#include <utility>
#include <sys/socket.h>
#include "Client.hpp"

class Channel
{
public:
    Channel();
    Channel(const std::string &name);
    ~Channel() {};

    std::string getName();
    std::string getTopic();
    std::string getPwd();

    bool isLimited();
    bool getTopicStatus();
    int getLimitNbr();
    bool getInvitStatus();
    std::vector<int> getInvited();
    size_t getSizeClients();
    std::map<int, bool> getClients();
    Client *findClientById(std::vector<Client> &server_clients, int id);
    std::vector<std::string> getNickClients(std::vector<Client> &server_clients);

    void addClient(Client &client, bool isOp);
    void removeClient(int id);

    void setLimit(int limit);
    void setTopic(std::string topic);
    void setPassword(std::string password);
    void setOperator(int id);

    bool isEmpty();
    bool isUserInChannel(int id);
    bool isInviteOnly();
    bool isUserOperator(int id);

    void removeLimit();
    void removeOperator(int id);

    void changeInvitStatus(bool status);
    void changeTopicStatus(bool status);

    void sendMsgChannelMember(Client &client, std::string msg, std::vector<Client> &server_clients, int type);
    void addInvit(int client_id);

private:
    std::string _name;
    std::string _topic;
    std::string _pwdChannel; // -k
    bool _isLimited;         // -l
    int _limitNbr;           // -l
    bool _invitStatus;       // -i
    bool _topicStatus;       // -t

    std::map<int, bool> _clients; // id en cle , role (Op)
    std::vector<int> invited;     // id des client invites
};

#endif