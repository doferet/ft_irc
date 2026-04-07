/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:22:45 by doferet           #+#    #+#             */
/*   Updated: 2026/04/06 22:01:41 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <map>
# include <utility>
# include "Client.hpp"
//# include "Server.hpp"

class Channel{
    public:
        Channel();
        ~Channel();

    private:
        std::map<std::string, std::pair<Client& , int> > _clients; //client name en cle , une ref vers le client et le role de ce client dnas la pair
        std::vector<std::string> invited; //ref vers le nickname des client invites pour conserve la bonne invit en cas de changeent de nickname

        //fct pour envoyer message a tout les clients sauf l'emetteur privmsg (client.addToOutput)
};

#endif