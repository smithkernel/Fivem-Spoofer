#pragma once
#include "common.hpp"

class network
{
public:
    void setup();
    void destroy();
private:
    void block_connection(std::string process);
    void unblock_connection(std::string process);
};

inline std::unique_ptr<network> g_network;

void network::setup()
{
    // Add code here to set up the network
}

void network::destroy()
{
    // Add code here to clean up and destroy the network
}

void network::block_connection(std::string process)
{
    // Add code here to block a connection for the specified process
}

void network::unblock_connection(std::string process)
{
    // Add code here to unblock a connection for the specified process
}
