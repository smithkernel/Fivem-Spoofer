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

void network::setup()
{
	// Locate FiveM.exe
	auto fivem_path = g_trace->m_fivem_path + "\\FiveM.exe";
	block_connection(fivem_path);


	// Locate FiveM Subprocesses path
	auto subprocess_path = g_trace->m_fivem_path + "\\FiveM.app\\data\\cache\\subprocess";

	std::vector<std::string> gta_versions{ "b2545_", "b2372_", "b2189_", "b2060_",  "" };

	for (auto processes : gta_versions)
	{
		// Block the gta processes
		auto gta_process = subprocess_path + "\\FiveM_" + processes + "GTAProcess.exe";
		block_connection(gta_process);

		// Block the steam processes
		auto steam_process = subprocess_path + "\\FiveM_" + processes + "SteamChild.exe";
		block_connection(steam_process);
	}

}


void network::destroy()
{
	// Locate FiveM.exe
	auto fivem_path = g_trace->m_fivem_path + "\\" + "FiveM.exe";
	unblock_connection(fivem_path);

	// Locate FiveM Subprocesses path
	auto subprocess_path = g_trace->m_fivem_path + "\\FiveM.app\\data\\cache\\subprocess";

	std::vector<std::string> gta_versions{ "b2545_", "b2372_", "b2189_", "b2060_",  "" };

	for (auto processes : gta_versions)
	{
		// Block the gta processes
		auto gta_process = subprocess_path + "\\FiveM_" + processes + "GTAProcess.exe";
		unblock_connection(gta_process);

		// Block the steam processes
		auto steam_process = subprocess_path + "\\FiveM_" + processes + "SteamChild.exe";
		unblock_connection(steam_process);
	}
}
