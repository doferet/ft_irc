/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:25:47 by doferet           #+#    #+#             */
/*   Updated: 2026/04/12 14:36:48 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mode.hpp"

void Mode::execute(Client &client, std::string &input)
{
    (void)client;
    (void) input;
    //-i Set/remove Invite-only channel
    //=>verifier si + ou -
    //=>verifier que le user est dans le channel
    //=>verifier que le user est op
    
    //-t Set/remove the restrictions of the TOPIC command to channel operators
    //=>verifier si + ou -
    //=>verifier que le user est dans le channel 
    //=>si +t, seul les op peuvent changer le topic si -t tout le monde peut
    
    //-o Give/take channel operator privilege
    //=> on doit deja etre op
    //=>verifier si + ou -
    //=>verifier que le user est dans le channel 
    //=>
    
    //-l Set/remove the user limit to channel
    //=>verifier qu'on est op
    //=>verifier si + ou -
    //=>verifier que le user est dans le channel 
    //=>limite valide que des chiffres
    //=>

    
    //-k Set/remove the channel key (password)
    //=>verifier si + ou -
    //=>verifier que le user est dans le channel
    //=>split les espaces, pas de caracteres speciaux
}