#include "Nick.hpp"

Nick::Nick(std::map<std::string, Channel> &channels, std::vector<Client> &cli, std::string &serverPassword)
    : ACommand(channels, cli, serverPassword)
{}

void Nick::execute(Client &client, std::string &input)
{
    if (input.empty())
        return ;
    
    // Check if the nickname is already taken by iterating through the client vector
    for (size_t i = 0; i < _cli.size(); ++i) {
        if (_cli[i].getNickname() == input) {
            // Error: Nickname already in use (ERR_NICKNAMEINUSE 433)
            return;
        }
    }

    client.setNickname(input);
    client.setHasValidNickname(true);
    std::cout << "Nickname set to: " << input << std::endl;
}