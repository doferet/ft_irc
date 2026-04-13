/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 17:29:23 by doferet           #+#    #+#             */
/*   Updated: 2026/04/13 19:04:57 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"

void Nick::execute(Client &client, std::string &input)
{
    if (input.empty())
        return;

    // Check if the nickname is already taken by iterating through the client vector
    for (size_t i = 0; i < _cli.size(); ++i)
    {
        if (_cli[i].getNickname() == input)
        {
            // Error: Nickname already in use (ERR_NICKNAMEINUSE 433)
            return;
        }
    }

    std::string old_nick = client.getNickname();
    client.setNickname(input);
    client.setHasValidNickname(true);
    std::cout << "Nickname set to: " << input << std::endl;
    client.addToOutput(":" + old_nick + "!" + client.getUsername() + "@localhost NICK :" + client.getNickname() + "\r\n");
}
