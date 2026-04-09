#ifndef NICK_HPP
#define NICK_HPP

#include "ACommand.hpp"

class Nick : public ACommand
{
public:
    Nick(std::map<std::string, Channel> &channels, std::vector<Client> &cli, std::string &serverPassword);
    
    static ACommand* create(std::map<std::string, Channel> &channels, std::vector<Client> &cli, std::string &serverPassword);
    
    virtual void execute(Client &client, std::string &input);
};

#endif