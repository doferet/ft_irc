#include "User.hpp"
#include <sstream>

User::User(std::map<std::string, Channel> &channels, std::vector<Client> &cli, std::string &serverPassword) 
    : ACommand(channels, cli, serverPassword) {}

void User::execute(Client &client, std::string &input) {
    if (client.isAuthenticated()) return;

    std::stringstream ss(input);
    std::string user, host, server, real;
    ss >> user >> host >> server;
    std::getline(ss, real);

    if (user.empty() || real.empty()) return;

    client.setUsername(user); // Needed add
    client.setHasValidUsername(true);

    if (client.isAuthenticated()) {
        std::cout << "Registration complete!" << std::endl;
        client.addToOutput("Welcome to the network\r\n");
    }
}