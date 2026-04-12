/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tronguye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 13:45:23 by tronguye          #+#    #+#             */
/*   Updated: 2026/04/12 13:45:24 by tronguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

//CURRENT BOT ONLY SPEAK TO #GENERAL, CAN UPDATE MORE

void sendIRC(int fd, std::string msg) {
    msg += "\r\n";
    send(fd, msg.c_str(), msg.length(), 0);
}

int main(int ac, char **av) {
    if (ac != 4)
        return (std::cerr << "Usage: ./ircbot <host> <port> <pass>\n", 1);

    // Seed for random features
    std::srand(std::time(0));

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(std::atoi(av[2])); //Port to int
    inet_pton(AF_INET, av[1], &addr.sin_addr); //IP to binary

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) return 1;

    // Handshake
    sendIRC(sock, "PASS " + std::string(av[3]));
    sendIRC(sock, "NICK InfoBot");
    sendIRC(sock, "USER bot 0 * :42 IRC Helper");
    sendIRC(sock, "JOIN #general");
    // can add more JOIN to listen on the whole server

    char buf[1024];
    while (true) {
        int bytes = recv(sock, buf, 1023, 0);
        if (bytes <= 0) break;
        buf[bytes] = '\0';
        std::string incoming(buf);

        // 1. PING/PONG (Keep connection alive)
        if (incoming.find("PING") == 0)
            sendIRC(sock, "PONG " + incoming.substr(5));

        // 2. PRIVMSG logic (Triggers)
        // .find() returns the index where the word starts, npos if not found
        if (incoming.find("PRIVMSG") != std::string::npos) {
            
            // Feature: Help Menu
            if (incoming.find(":!help") != std::string::npos) {
                sendIRC(sock, "PRIVMSG #general :Commands: !roll, !joke, !info, !ping");
            }
            
            // Feature: Dice Roller (!roll)
            else if (incoming.find(":!roll") != std::string::npos) {
                int die = (std::rand() % 6) + 1;
                // We use a stringstream or simple conversion
                std::string result = (die == 1 ? "1" : die == 2 ? "2" : die == 3 ? "3" : die == 4 ? "4" : die == 5 ? "5" : "6");
                sendIRC(sock, "PRIVMSG #general :You rolled a " + result + "!");
            }

            // Feature: Random Joke (!joke)
            else if (incoming.find(":!joke") != std::string::npos) {
                int r = std::rand() % 3;
                if (r == 0)
                    sendIRC(sock, "PRIVMSG #general :Why do programmers prefer dark mode? Because light attracts bugs.");
                else if (r == 1)
                    sendIRC(sock, "PRIVMSG #general :How many programmers does it take to change a light bulb? None, that is a hardware problem.");
                else
                    sendIRC(sock, "PRIVMSG #general :0 is false, 1 is true, and eating 2 pizza slices is just right.");
            }

            // Feature: Server Info (!info)
            else if (incoming.find(":!info") != std::string::npos) {
                sendIRC(sock, "PRIVMSG #general :I am a cool bot running on an IRC Server.");
            }
        }
    }
    close(sock);
    return 0;
}
