/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:22:45 by doferet           #+#    #+#             */
/*   Updated: 2026/04/14 17:14:16 by asritz           ###   ########.fr       */
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
    // bool isUserInChannel(Client &client);

    bool isUserOperator(int id);

    void removeLimit();
    void removeOperator(int id);

    void changeInvitStatus(bool status);
    void changeTopicStatus(bool status);

    void sendMsgChannelMember(Client &client, std::string msg, std::vector<Client> &server_clients);

private:
    std::string _name;
    std::string _topic;
    std::string _pwdChannel; // -k
    bool _isLimited;         // -l
    int _limitNbr;           // pour -l
    bool _invitStatus;       // pour -i
    bool _topicStatus;

    std::map<int, bool> _clients; // id du client en cle , le role de ce client dnas la pair
    std::vector<int> invited;     // vers l'id des client invites pour conserve la bonne invit en cas de changeent de nickname

    // fct pour envoyer message a tout les clients sauf l'emetteur privmsg (client.addToOutput)
};

#endif