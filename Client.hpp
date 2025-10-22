/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doferet <doferet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:54:08 by doferet           #+#    #+#             */
/*   Updated: 2025/10/21 09:48:59 by doferet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>

class Client{

public:
	join;
	kick;
	invite;
	topic;
	mode;

private:
	std::string _username;
	std::string _nickname;

};

#endif