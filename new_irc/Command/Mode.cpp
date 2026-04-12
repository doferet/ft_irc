/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:25:47 by doferet           #+#    #+#             */
/*   Updated: 2026/04/12 19:02:51 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mode.hpp"

void option_l(std::stringstream &ss, bool isPlus, std::map<std::string, Channel*>::iterator channel)
{
    if (isPlus == false)
    {
        channel->removeLimit();
        return ;
    }
    int limit;
    ss >> limit;
    if (ss.fail() || limit <= 0)
    {
        //ERR_INVALIDMODEPARAM :server 696 nick #channel l -5 :Invalid mode parameter
        return ;
    }
    channel->setLimit(limit);
}

void option_o(std::stringstream &ss, bool isPlus, std::map<std::string, Channel*>::iterator channel)
{
    std::string param;
    ss >> param;
    if (channel->isUserInChannel(param) == false)
    {
        //442     ERR_NOTONCHANNEL "<channel> :param not on that channel"
        return;
    }
    if (isPlus == false)
    {
        channel->removeOperator(param);
        return;
    }
    channel->setOperator(param);
}
    
void option_k(std::stringstream &ss, bool isPlus, std::map<std::string, Channel*>::iterator channel)
{
    std::string param;
    std::string passwordChannel = channel.getPwd();
    ss >> param;
    if (isPlus == false)
    {
        if (passwordChannel.empty() || passwordChannel == param)
            channel->setPassword("");
        return;
    }
    channel->setPassword(param);
}

void Mode::execute(Client &client, std::string &input)
{
    std::stringstream ss(input);
    std::string chanName;
    std::string option;
    std:string param;
    bool isPlus = false;
    ss >> chanName >> option;
    
    std::map<std::string, Channel*>::iterator channel = _channels.find(chanName);
    if (channel == _channels.end()){return;}
        // 403     ERR_NOSUCHCHANNEL "<channel name> :No such channel"
    if (channel->isUserInChannel(client.getName()) == false){return;}
        // 442     ERR_NOTONCHANNEL "<channel> :You're not on that channel"
    if (channel->isUserOperator(client.getName()) == false){return;}
        //502     ERR_USERSDONTMATCH ":Cant change mode for other users"
    if (option.size() != 2 || (option[0] != '+' && option[0] != '-')){return;}
        // 472     ERR_UNKNOWNMODE  "<char> :is unknown mode char to me"
    if (option[0] == '+')
        isPlus = true;
    switch(option[1])
    {
        case 'i':
            channel->changeInvitStatus(isPlus);
            break;
        case 't':
            channel->changeTopicStatus(isPlus);
            break;
        case 'o':
            option_o(ss, isPlus, channel);
            break;
        case 'l':
            option_l(ss, isPlus, channel);
            break;
        case 'k':
            option_k(ss, isPlus, channel);
            break;
        default:
        //472     ERR_UNKNOWNMODE  "<char> :is unknown mode char to me"
    }
    //MODE channel option parametres
    
    //-i Set/remove Invite-only channel
    //=>verifier si + ou -
    //=>verifier que le user est dans le channel
    //=>verifier que le user est op
    //pas de param
    
    //-t Set/remove the restrictions of the TOPIC command to channel operators
    //=>verifier si + ou -
    //=>verifier que le user est dans le channel 
    //=>si +t, seul les op peuvent changer le topic si -t tout le monde peut
    //pas de param
    
    //-o Give/take channel operator privilege
    //=> on doit deja etre op
    //=>verifier si + ou -
    //=>verifier que le user est dans le channel 
    //=>parametre = nom
    
    //-l Set/remove the user limit to channel
    //=>verifier qu'on est op
    //=>verifier si + ou -
    //=>verifier que le user est dans le channel 
    //=>limite valide que des chiffres
    //=>parametre = limite

    
    //-k Set/remove the channel key (password)
    //=>verifier si + ou -
    //=>verifier que le user est dans le channel
    //=>split les espaces, pas de caracteres speciaux
    //param = password
}