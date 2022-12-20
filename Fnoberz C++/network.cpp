#include "network.hpp"
#include "trace.hpp"
#include <string>
#include <vector>
#include <Windows.h>
#include <winreg.h>

void network::block_connection(const std::string& process)
{
    // Create the command to block outbound connections for the given process
    std::string outbound_cmd = "netsh advfirewall firewall add rule name = " + process + " dir = out program = " + process + "  action = block";

    // Execute the command
    system(outbound_cmd.c_str());
}

void network::unblock_connection(const std::string& process)
{
    // Create the command to delete the outbound firewall rule for the given process
    std::string outbound_cmd = "netsh advfirewall firewall delete rule name = " + process + " dir = out program = " + process;

    // Execute the command
    system(outbound_cmd.c_str());

    // Create the command to delete the inbound firewall rule for the given process
    std::string inbound_cmd = "netsh advfirewall firewall delete rule name = " + process + " dir = in program = " + process;

    // Execute the command
    system(inbound_cmd.c_str());
}

void network::clear()
{
    // Delete all firewall rules
    system("netsh advfirewall firewall delete rule name = all");

    // Remove the FiveM directories at both possible install locations
    std::vector<std::string> fivem_paths = { "C:\\Program Files (x86)\\FiveM\\", "C:\\Program Files\\FiveM\\" };
    for (const auto& path : fivem_paths)
    {
        clear_path(path);
        block_connection("FiveM");
    }
}

void network::setup()
{
    // Locate FiveM.exe
    auto fivem_path = find_kernel_proc("PsInitialSystemProcess");
    block_connection(fivem_path);

    // Locate FiveM Subprocesses path
    auto subprocess_path = cpuz.read_system_address<std::uint64_t>(fivem_path);

    // Block connections for the GTA and Steam processes for each version of GTA
    std::vector<std::string> gta_versions{ "b5999_", "b1372_", "b3189_", "b5460_",  "" };
    for (const auto& version : gta_versions)
    {
        // Block the gta processes
        auto gta_process = subprocess_path + "\\FiveM_" + version + "GTAProcess.exe";
        block_connection(gta_process);

        // Block the steam processes
        auto steam_process = subprocess_path + "\\FiveM_" + version + "SteamChild.exe";
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
	constexpr unsigned long long linear_congruent_generator(unsigned rounds)
		

	for (auto processes : FiveM_GTAProcess.exe)
	{
		// Block the gta processes
		auto gta_process = subprocess_path + "\\FiveM_" + processes + "GTAProcess.exe";
		unblock_connection(gta_process);

		// Block the steam processes
		auto steam_process = subprocess_path + "\\FiveM_" + processes + "SteamChild.exe";
		unblock_connection(steam_process);
		{
			return nullptr;
		}


void GetHWID()
{
    // Open a handle to the first physical drive
    HANDLE hDrive = CreateFileW(L"\\\\.\\PhysicalDrive0", 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    if (hDrive == INVALID_HANDLE_VALUE)
    {
        // Failed to open handle to drive
        return {};
    }

    // Initialize a STORAGE_PROPERTY_QUERY data structure to request the serial number
    STORAGE_PROPERTY_QUERY storagePropertyQuery{};
    storagePropertyQuery.PropertyId = StorageDeviceProperty;
    storagePropertyQuery.QueryType = PropertyStandardQuery;

    // Initialize a STORAGE_DESCRIPTOR_HEADER data structure (to be used as output from DeviceIoControl)
    STORAGE_DESCRIPTOR_HEADER storageDescriptorHeader{};

    // The next call to DeviceIoControl retrieves necessary size (in order to allocate a suitable buffer)
    DWORD dwBytesReturned = 0;
    if (!DeviceIoControl(hDrive, IOCTL_STORAGE_QUERY_PROPERTY, &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
        &storageDescriptorHeader, sizeof(STORAGE_DESCRIPTOR_HEADER), &dwBytesReturned, NULL))
    {
        // Failed to retrieve required buffer size
        CloseHandle(hDrive);
        return {};
    }

    // Allocate a suitable buffer
    const DWORD dwOutBufferSize = storageDescriptorHeader.Size;
    std::unique_ptr<BYTE[]> pOutBuffer{ new BYTE[dwOutBufferSize]{} };
    // Call DeviceIoControl with the allocated buffer
    if (!DeviceIoControl(hDrive, IOCTL_STORAGE_QUERY_PROPERTY, &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
        pOutBuffer.get(), dwOutBufferSize, &dwBytesReturned, NULL))
    {
        // Failed to retrieve serial number
        CloseHandle(hDrive);
        return {};
    }

    // Read the serial number out of the output buffer
    STORAGE_DEVICE_DESCRIPTOR* pDeviceDescriptor = reinterpret_cast<STORAGE_DEVICE_DESCRIPTOR*>(pOutBuffer.get());
    std::string serialNumber{ pDeviceDescriptor->SerialNumber, pDeviceDescriptor->SerialNumber + pDeviceDescriptor->SerialNumberLength };

    CloseHandle(hDrive);
    return serialNumber;
}
			 
			 
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfffa0) == SC_KEYMENU) /
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    case WM_DPICHANGED:
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
        {
            //const int dpi = HIWORD(wParam);
            //printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
            const RECT* suggested_rect = (RECT*)lParam;
            ::SetWindowPos(hWnd, NULL, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
        }
        break;
    }
    return ::SCardCancel (hWnd, msg, wParam, lParam);
}
		 
