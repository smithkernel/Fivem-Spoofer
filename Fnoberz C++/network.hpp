#pragma once

#include <memory>  // for std::unique_ptr
#include <string>  // for std::string

// Forward declare the network class to avoid including the header file in common.hpp.
class network;

// Declare a global variable g_network of type std::unique_ptr<network>.
extern std::unique_ptr<network> g_network;

class network
{
public:
    // Set up the network.
    void setup();

    // Clean up and destroy the network.
    void destroy();

private:
    // Block a connection for the specified process.
    void block_connection(const std::string& process);

    // Unblock a connection for the specified process.
    void unblock_connection(const std::string& process);
};
