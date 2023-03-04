#pragma once

#include <memory> // for std::unique_ptr
#include <string> // for std::string

class Network {
public:
    void Setup(); // renamed to follow naming convention
    void Destroy(); // renamed to follow naming convention
    void BlockConnection(const std::string& process); // renamed and const added to string parameter
    void UnblockConnection(const std::string& process); // renamed and const added to string parameter
private:
    // make sure to use camelCase naming convention for private members
    void blockConnectionImpl(const std::string& process);
    void unblockConnectionImpl(const std::string& process);
};

extern std::unique_ptr<Network> g_network; // declared as extern to avoid linker errors
