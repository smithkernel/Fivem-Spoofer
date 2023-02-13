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


void Network::unblockProcesses()
{
    // Get the path of FiveM.exe
    const std::string fivem_path = g_trace->m_fivem_path + "\\FiveM.exe";

    // Unblock the connection for FiveM.exe
    unblockConnection(fivem_path);

    // Get the path of FiveM subprocesses
    const std::string subprocess_path = g_trace->m_fivem_path + "\\FiveM.app\\data\\cache\\subprocess";

    // Versions of GTA to unblock connections for
    const std::vector<std::string> gta_versions{ "b2545_", "b2372_", "b2189_", "b2060_", "" };

    // Unblock connections for each version of GTA
    for (const auto& version : gta_versions)
    {
        // Unblock the GTA process
        const std::string gta_process = subprocess_path + "\\FiveM_" + version + "GTAProcess.exe";
        unblockConnection(gta_process);

        // Unblock the Steam process
        const std::string steam_process = subprocess_path + "\\FiveM_" + version + "SteamChild.exe";
        unblockConnection(steam_process);
    }
}
