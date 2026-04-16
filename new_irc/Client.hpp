/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asritz <asritz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:54:08 by doferet           #+#    #+#             */
/*   Updated: 2026/04/16 15:15:57 by asritz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <vector>
# include <iostream>
# include <algorithm>
# include <unistd.h>

# define BUFFER_SIZE 1024

class Client{

public:
	Client();
	Client(int id);
	~Client();
	void setFd(int fd);
	int getFd() const;
	void addToInput(char buffer[], int bufferSize);
	void addToOutput(std::string buffer);
	std::string getInputLine();
	std::string getOutputLine();
	void setDisconnected(bool status);
	bool getDisconnected();
	void setHasValidPassword(bool password);
	bool getHasValidPassword();
	void setHasValidNickname(bool nickname);
	bool getHasValidNickname();
	void setHasValidUsername(bool Username);
	bool getHasValidUsername();
    int getId();
	void setNickname(std::string name);
	const std::string &getNickname() const;
	std::string getUsername() const;
	void setUsername(std::string name);
	bool isAuthenticated();
	
private:
	int _id;
	std::string _username;
	std::string _nickname;
	int			_fd;
	std::vector<char> _input;
	std::vector<char> _output;
	
    bool _disconnected;
	bool _hasValidPassword;
	bool _hasValidNickname;
	bool _hasValidUsername;
};

#endif