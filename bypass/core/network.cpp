#include "network.hpp"
#include "trace.hpp"

void network::block_connection(std::string process)
{
	std::string outbound = "netsh advfirewall firewall add rule name = " + process + " dir = out program = " + process + "  action = block";
	system(outbound.c_str());

	std::string inbound = "netsh advfirewall firewall add rule name = " + process + " dir = in program = " + process + "  action = block";
	system(inbound.c_str());
}

void Network {
public:
    static void unblock_connection(const std::string& process_name) {
        std::string outbound_command = "netsh advfirewall firewall delete rule name=\"" + process_name + "\" program=\"" + process_name + "\" dir=out";
        std::string inbound_command = "netsh advfirewall firewall delete rule name=\"" + process_name + "\" program=\"" + process_name + "\" dir=in";

        int outbound_result = system(outbound_command.c_str());
        int inbound_result = system(inbound_command.c_str());

        if (outbound_result != 0 || inbound_result != 0) {
            throw std::runtime_error("Failed to unblock connection for process " + process_name);
        }
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

void network::unblockConnections()
{
    // Get the path to the FiveM executable file
    const std::string fivemPath = getFivemPath();

    // Unblock network connections to FiveM
    if (!unblockConnection(fivemPath)) {
        throw std::runtime_error("Failed to unblock network connections to FiveM");
    }

    // Get the path to the subprocess directory
    const std::string subprocessPath = getSubprocessPath();

    // List of GTA versions
    const std::vector<std::string> gtaVersions = getGtaVersions();

    // Unblock network connections to subprocesses for each GTA version
    for (const auto& version : gtaVersions)
    {
        const std::string gtaProcessPath = subprocessPath + "/FiveM_" + version + "GTAProcess.exe";
        const std::string steamProcessPath = subprocessPath + "/FiveM_" + version + "SteamChild.exe";

        if (!unblockConnection(gtaProcessPath)) {
            throw std::runtime_error("Failed to unblock network connections to " + gtaProcessPath);
        }

        if (!unblockConnection(steamProcessPath)) {
            throw std::runtime_error("Failed to unblock network connections to " + steamProcessPath);
        }
    }
}


// Get the path to the FiveM.exe file
std::string network::getFivemPath()
{
    // TODO: implement the logic to get the path to FiveM.exe
    return "";
}

// Get the path to the subprocess directory
std::string network::getSubprocessPath()
{
    // TODO: implement the logic to get the path to the subprocess directory
    return "";
}

// Get the list of GTA versions
std::vector<std::string> network::getGtaVersions()
{
    // TODO: implement the logic to get the list of GTA versions
    return {};
}

// Unblock network connections to a file
void network::unblockConnection(const std::string& filePath)
{
    // TODO: implement the logic to unblock network connections to a file
}

