#pragma once
#include "common.hpp"

class Network
{
public:
    Network();
    ~Network();

    void setup();
    void destroy();

private:
    void blockConnection(const std::string& process);
    void unblockConnection(const std::string& process);
};

inline std::unique_ptr<Network> g_network;
