#ifndef USER_HPP
# define USER_HPP

# include "ACommand.hpp"

class User : public ACommand {
public:
    User(std::map<std::string, Channel> &channels, std::vector<Client> &cli, std::string &serverPassword);
    
    static ACommand* create(std::map<std::string, Channel> &channels, std::vector<Client> &cli, std::string &serverPassword);
    
    virtual void execute(Client &client, std::string &input);
};

#endif