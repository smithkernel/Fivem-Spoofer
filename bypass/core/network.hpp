#pragma once

#include <memory> // for std::unique_ptr
#include <string> // for std::string

class Network {
public:
    void setupNetwork(); 
    void destroyNetwork(); 
    void blockConnection(const std::string& processName) const; 
    void unblockConnection(const std::string& processName) const; 
private:
    void blockConnectionImpl(const std::string& processName); 
    void unblockConnectionImpl(const std::string& processName); 
};


extern std::unique_ptr<Network> g_network; // declared as extern to avoid linker errors
