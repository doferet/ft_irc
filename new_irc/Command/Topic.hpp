#ifndef TOPIC_HPP
#define TOPIC_HPP

#include "ACommand.hpp"

class Topic : public ACommand
{
public:
    Topic(std::map<std::string, Channel *> &channels, std::vector<Client> &cli, std::string &serverPassword): ACommand(channels, cli, serverPassword) {};

    static ACommand *create(std::map<std::string, Channel *> &channels, std::vector<Client> &cli, std::string &serverPassword)
    {
        return new Topic(channels, cli, serverPassword);
    }

    virtual void execute(Client &client, std::string &input);
};

#endif