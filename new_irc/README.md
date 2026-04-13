*This project has been created as part of the 42 curriculum by doferet, asritz, tronguye*

# Ft_IRC, Internet Relay Chat

Internet Relay Chat or IRC is a text-based communication protocol on the Internet.
It offers real-time messaging that can be either public or private. Users can exchange direct messages and join group channels.
IRC clients connect to IRC servers in order to join channels. IRC servers are connected together to form a network.

## Description

In this project, we are going to learn how to create an Internet Relay Chat (IRC).

An IRC server is a system that allows multiple users to communicate with each other in real time through text messages. It acts as a central hub that manages connections between clients, handles the exchange of messages, and organizes discussions.

When users connect to the server, they choose a nickname and can join channels, which are group chat rooms identified by names like #general. The server keeps track of all connected users and which channels they belong to. When a user sends a message, the server receives it, processes it according to the IRC protocol, and then forwards it either to a specific user (private message) or to all members of a channel. In the case of channel messages, the server sends the message to everyone in the channel except the sender.

The server also enforces rules defined by the IRC protocol, such as command formats and error handling, ensuring that communication remains structured and consistent. In more advanced setups, multiple IRC servers can be connected together to form a network, allowing users on different servers to communicate seamlessly.

In short, an IRC server is a real-time communication system that connects users, manages conversations, and ensures messages are delivered correctly.

## Instructions

1) git clone the project
2) make -> to compile the project
3) to run the project -> ./ircserv <port> <password> | ex: ./ircserv 8080 mypassword
4) Test the project with a client. For example: IRSSI => /connect localhost <port> <password>
5) Testing commands:
    - PASS <mypassword>: Sends a password to the server before registering the user. It must be provided before NICK and USER commands to complete authentication
    - NICK <your_nickname>: Assigns a unique nickname to the client. If already registered, it can be used to change the current nickname.
    - USER <username> <hostname> <servername> <realname>: Completes the user registration process by providing identity information. This command is required after NICK and PASS (if used).
    - JOIN <channel_name>: Allows a user to enter a channel. If the channel does not exist, it is created automatically.
    - PRIVMSG <target> <message>: Sends a message to a user or a channel. It is the main command used for communication in IRC.
    - MODE <channel> <modes> [parameters]: with options -/+ o, l, k, t, i
    - QUIT [message]: Terminates the client’s connection to the IRC server. An optional message can be sent to other users to indicate the reason for leaving.
    - PART <channel> [message]: Removes the user from the specified channel. An optional message can be shown to other members of the channel.
    - KICK <channel> <user> [message]: Allows a channel operator to forcibly remove a user from the channel. An optional message can explain the reason for the kick.
    - TOPIC <channel> [topic]: 
        -> Without arguments: displays the current topic of the channel.
        -> With a topic: sets a new topic for the channel (usually restricted to operators or users with permission).
    - INVITE <user> <channel>: Sends an invitation to a user to join a channel. This is especially useful for invite-only channels.

## Resources

- http://abcdrfc.free.fr/rfc-vf/rfc1459.html#411
- https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.1
- https://webusers.i3s.unice.fr/~tettaman/Classes/L2I/ProgSys/11_IntroSockets.pdf
- https://www.geeksforgeeks.org/cpp/socket-programming-in-cpp/
- https://modern.ircdocs.horse/#errneedmoreparams-461
- https://medium.com/@afatir.ahmedfatir/small-irc-server-ft-irc-42-network-7cee848de6f9#:~:text=Part%202%3A%20Create%20a%20socket%20and%20handle%20the%20server%20signals.




