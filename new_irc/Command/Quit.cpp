/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 20:34:46 by doferet           #+#    #+#             */
/*   Updated: 2026/04/16 14:54:12 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Quit.hpp"

void Quit::execute(Client &client, std::string &input)
{
    if (input.empty())
        input = "";

    client.addToOutput(":" + client.getNickname() + " QUIT :Client Quit\r\n");
    client.setDisconnected(true);
}
