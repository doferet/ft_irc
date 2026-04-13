#include "Topic.hpp"

// TOPIC <channel> :<new_topic> to change topic || TOPIC <channel> to view current topic
void Topic::execute(Client &client, std::string &input) {
    std::stringstream ss(input);
    std::string channelName, newTopic;

    ss >> channelName;
    std::getline(ss, newTopic);

    // 1. Find the channel
    std::map<std::string, Channel*>::iterator it = _channels.find(channelName);
    if (it == _channels.end())
    {
        client.addToOutput(":ircserv 403 " + client.getNickname() + " " + channelName + " :No such channel\r\n");
        return;
    }
    Channel *chan = it->second;

    // 2. Check if the user is in the channel
    if (!chan->isUserInChannel(client.getNickname()))
    {
        client.addToOutput(":ircserv 442 " + client.getNickname() + " " + channelName + " :You're not on that channel\r\n");
        return;
    }

    // --- Case 1: VIEWING THE TOPIC ---
    if (newTopic.empty())
    {
        if (chan->getTopic().empty())
            client.addToOutput(":ircserv 331 " + client.getNickname() + " " + channelName + " :No topic is set\r\n");
        else
            client.addToOutput(":ircserv 332 " + client.getNickname() + " " + channelName + " :" + chan->getTopic() + "\r\n");
        return;
    }

    // --- Case 2: SETTING THE TOPIC ---
    if (!newTopic.empty() && newTopic[0] == ' ') newTopic.erase(0, 1);
    if (!newTopic.empty() && newTopic[0] == ':') newTopic.erase(0, 1);

    // Check +t mode (Consistent with your Mode.cpp logic)
    if (chan->getTopicStatus() == true && !chan->isUserOperator(client.getNickname())) {
        client.addToOutput(":ircserv 482 " + client.getNickname() + " " + channelName + " :You're not channel operator\r\n");
        return;
    }

    chan->setTopic(newTopic);

    // 3. BROADCAST
    // Format: :Nick!User@localhost TOPIC #channel :topic
    std::string topicMsg = ":" + client.getNickname() + "!" + client.getUsername() + "@localhost TOPIC " + channelName + " :" + newTopic + "\r\n";
    chan->sendMsgChannelMember(topicMsg);
}