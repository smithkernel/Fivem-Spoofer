#pragma once
#include "common.hpp"

class Network {
public:
    void Setup();
    void Destroy();
private:
    void BlockConnection(std::string process);
    void UnblockConnection(std::string process);
};

std::unique_ptr<Network> g_network;
