/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:22:45 by doferet           #+#    #+#             */
/*   Updated: 2026/04/12 20:46:46 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <map>
#include <utility>
#include <sys/socket.h>
#include "Client.hpp"

class Channel{
    public:
        Channel();
        Channel(const std::string &name) : _name(name) {};
        ~Channel() {};

        std::string getName();
        std::string getTopic();
        std::string getPwd();
        
        bool isLimited();
        int getLimitNbr();

        void addClient(Client &client, bool isOp);
        void removeClient(std::string nickname);
        
        void setLimit(int limit);
        void setTopic(std::string topic);
        void setPassword(std::string password);
        void setOperator(std::string nickname);
        
        bool isUserInChannel(std::string nickname);
        bool isUserOperator(std::string nickname);
        
        void removeLimit();
        void removeOperator(std::string nickname);
        
        void changeInvitStatus(bool status);
        void changeTopicStatus(bool status);
        
         void sendMsgChannelMember(std::string msg);


    private:
        std::string _name;
        std::string _topic;
        std::string _pwdChannel; // -k
        bool _isLimited; // -l
        int _limitNbr; // pour -l
        bool _invitStatus; //pour -i
        bool _topicStatus;
        
        std::map<std::string, std::pair<Client & , bool> > _clients; //client username en cle , une ref vers le client et le role de ce client dnas la pair
        std::vector<std::string> invited; //ref vers le nickname des client invites pour conserve la bonne invit en cas de changeent de nickname

    // fct pour envoyer message a tout les clients sauf l'emetteur privmsg (client.addToOutput)
};

#endif