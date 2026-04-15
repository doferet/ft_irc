/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 17:26:56 by doferet           #+#    #+#             */
/*   Updated: 2026/04/15 16:02:53 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ping.hpp"

void Ping::execute(Client &client, std::string &input)
{
    client.addToOutput("PONG " + input + "\r\n");
}
