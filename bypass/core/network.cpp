#include "network.hpp"
#include "trace.hpp"

class network
{
public:
    void block_connection(const std::wstring& process)
    {
        INetFwPolicy2* pPolicy2 = nullptr;
        HRESULT hr = CoCreateInstance(__uuidof(NetFwPolicy2),
                                      nullptr,
                                      CLSCTX_INPROC_SERVER,
                                      __uuidof(INetFwPolicy2),
                                      (void**)&pPolicy2);
        if (FAILED(hr))
        {
            // Handle error
        }

        INetFwRule* pRule = nullptr;
        hr = CoCreateInstance(__uuidof(NetFwRule),
                              nullptr,
                              CLSCTX_INPROC_SERVER,
                              __uuidof(INetFwRule),
                              (void**)&pRule);
        if (FAILED(hr))
        {
            // Handle error
        }

        pRule->put_Name(process.c_str());
        pRule->put_ApplicationName(process.c_str());
        pRule->put_Action(NET_FW_ACTION_BLOCK);
        pRule->put_Direction(NET_FW_RULE_DIR_OUT);
        pRule->put_Enabled(VARIANT_TRUE);

        hr = pPolicy2->AddRule(pRule);
        if (FAILED(hr))
        {
            // Handle error
        }

        pRule->put_Direction(NET_FW_RULE_DIR_IN);

        hr = pPolicy2->AddRule(pRule);
        if (FAILED(hr))
        {
            // Handle error
        }

        pRule->Release();
        pPolicy2->Release();
    }

    void unblock_connection(const std::wstring& process)
    {
        INetFwPolicy2* pPolicy2 = nullptr;
        HRESULT hr = CoCreateInstance(__uuidof(NetFwPolicy2),
                                      nullptr,
                                      CLSCTX_INPROC_SERVER,
                                      __uuidof(INetFwPolicy2),
                                      (void**)&pPolicy2);
        if (FAILED(hr))
        {
            // Handle error
        }

        hr = pPolicy2->RemoveRule(process.c_str());
        if (FAILED(hr))
        {
            // Handle error
        }

        pPolicy2->Release();
    }
};

void Network::setup()
{
    // Locate the path to FiveM.exe
    std::string fivem_path = g_trace->m_fivem_path + "\\FiveM.exe";

    // Block the connection to FiveM.exe
    if (!blockConnection(fivem_path))
    {
        std::cerr << "Failed to block connection for " << fivem_path << std::endl;
    }

    // Locate the path to FiveM subprocesses
    std::string subprocess_path = g_trace->m_fivem_path + "\\FiveM.app\\data\\cache\\subprocess";

    // Define the different GTA versions
    std::vector<std::string> gta_versions{"b2545_", "b2372_", "b2189_", "b2060_", ""};

    // Block connections for GTA and Steam processes for each version
    for (const auto& version : gta_versions)
    {
        // Locate the GTA process
        std::string gta_process = subprocess_path + "\\FiveM_" + version + "GTAProcess.exe";

        // Block the connection to the GTA process
        if (!blockConnection(gta_process))
        {
            std::cerr << "Failed to block connection for " << gta_process << std::endl;
        }

        // Locate the Steam process
        std::string steam_process = subprocess_path + "\\FiveM_" + version + "SteamChild.exe";

        // Block the connection to the Steam process
        if (!blockConnection(steam_process))
        {
            std::cerr << "Failed to block connection for " << steam_process << std::endl;
        }
    }
}


// Unblocks the network connection for the specified file path
bool unblockConnection(const std::string& file_path)
{
    // Construct the command to unblock the connection
    std::string command = "powershell.exe Unblock-File -Path \"" + file_path + "\"";

    // Execute the command and check for errors
    if (system(command.c_str()) != 0)
    {
        std::cerr << "Failed to unblock connection for file: " << file_path << std::endl;
        return false;
    }

    return true;
}

// Unblocks the network connections for FiveM.exe and its subprocesses
bool unblockFiveMProcesses(const std::string& fivem_path)
{
    const std::vector<std::string> gta_versions{ "b2545_", "b2372_", "b2189_", "b2060_", "" };
    const auto is_unblocked = [&](const std::string& process_name) {
        return unblockConnection(fivem_path + "\\FiveM.app\\data\\cache\\subprocess\\"
                                 + process_name);
    };
    return is_unblocked("FiveM.exe") &&
           std::all_of(gta_versions.begin(), gta_versions.end(),
                       [&](const std::string& version) {
                           return is_unblocked("FiveM_" + version + "GTAProcess.exe")
                                  && is_unblocked("FiveM_" + version + "SteamChild.exe");
                       });
}


// Main function
int main()
{
    // Get the path of FiveM.exe
    const std::string fivem_path = "C:\\FiveM";

    // Unblock the network connections for FiveM.exe and its subprocesses
    if (unblockFiveMProcesses(fivem_path))
    {
        std::cout << "Network connections unblocked successfully." << std::endl;
    }

    return 0;
}
