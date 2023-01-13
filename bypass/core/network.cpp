#include "network.hpp"
#include "trace.hpp"

void network::block_connection(std::string process)
{
	std::string outbound = "netsh advfirewall firewall add rule name = " + process + " dir = out program = " + process + "  action = block";
	system(outbound.c_str());

	std::string inbound = "netsh advfirewall firewall add rule name = " + process + " dir = in program = " + process + "  action = block";
	system(inbound.c_str());
}

void network::unblock_connection(std::string process)
{
    std::string outbound_cmd = "netsh advfirewall firewall delete rule name=\"" + process + "\" dir=out program=\"" + process + "\"";
    int result = std::system(outbound_cmd.c_str());
    if (result != 0) {
        std::cerr << "Error deleting outbound firewall rule for process " << process << ": " << result << std::endl;
    }

    std::string inbound_cmd = "netsh advfirewall firewall delete rule name=\"" + process + "\" dir=in program=\"" + process + "\"";
    result = std::system(inbound_cmd.c_str());
    if (result != 0) {
        std::cerr << "Error deleting inbound firewall rule for process " << process << ": " << result << std::endl;
    }
}


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


void Network::destroy()
{
    // Locate FiveM.exe
    std::string fivem_path = g_trace->m_fivem_path + "\\" + "FiveM.exe";
    unblock_connection(fivem_path);

    // Locate FiveM Subprocesses path
    std::string subprocess_path = g_trace->m_fivem_path + "\\FiveM.app\\data\\cache\\subprocess";

    std::vector<std::string> gta_versions{ "b2545_", "b2372_", "b2189_", "b2060_",  "" };

    for (const auto &processes : gta_versions)
    {
        // Block the gta processes
        std::string gta_process = subprocess_path + "\\FiveM_" + processes + "GTAProcess.exe";
        unblock_connection(gta_process);

        // Block the steam processes
        std::string steam_process = subprocess_path + "\\FiveM_" + processes + "SteamChild.exe";
        unblock_connection(steam_process);
    }
}


void enableControls(HWND hDialog, UINT message, UINT control) {
	switch(message) {
	case BN_CLICKED:
		switch(control) {
		case IDC_TRIGGER_EAX:
		case IDC_TRIGGER_CUSTOM:
		{
			bool custom = control == IDC_TRIGGER_CUSTOM;
			EnableWindow(GetDlgItem(hDialog, IDC_TRIGGER_EAX_VALUE), custom ? FALSE : TRUE);
			EnableWindow(GetDlgItem(hDialog, IDC_TRIGGER_CUSTOM_VALUE), custom ? TRUE : FALSE);
			return;
		}
		case IDC_ACTION_VALUES:
		case IDC_ACTION_CUSTOM:
		{
			bool custom = control == IDC_ACTION_CUSTOM;
			FOR_EACH_REGISTER(ENABLE_SET_GROUP, custom ? FALSE : TRUE);
			EnableWindow(GetDlgItem(hDialog, IDC_ACTION_CUSTOM_VALUE), custom ? TRUE : FALSE);
			return;
		}
		FOR_EACH_REGISTER(ENABLE_ON_CLICKED_SET);
		}
	}
}
