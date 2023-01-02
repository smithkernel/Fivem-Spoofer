#pragma once
#include "common.hpp"

class Trace
{
public:
    Trace();  // Added default constructor
    ~Trace(); // Added destructor

    void Setup();
    void Destroy();
    void SetLaunchBuild(const std::string& launch_build); // Added const and reference to launch_build argument
    std::string GetLaunchBuild() const; // Added const to function
    std::string SetFolder(const std::string& title); // Added const and reference to title argument

private:
    std::string m_save_path{ "save.txt" };
    std::string m_fivem_path;
    std::string m_citizen_ini_path{ "\\FiveM.app\\CitizenFX.ini" };
};

inline std::unique_ptr<Trace> g_trace; // Changed g_trace to use PascalCase
