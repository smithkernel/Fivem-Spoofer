#include "trace.hpp"

void trace::setup()
{
    // Get values of environment variables
    std::string localappdata = getenv("LOCALAPPDATA");
    std::string appdata = getenv("APPDATA");

    // Attempt to remove DigitalEntitlements directory
    std::string digitalEntitlementsPath = localappdata + "\\DigitalEntitlements";
    if (std::filesystem::exists(digitalEntitlementsPath))
    {
        std::filesystem::remove_all(digitalEntitlementsPath);
        std::cout << "Removed: " << digitalEntitlementsPath << std::endl;
    }
    else
    {
        std::cout << "Couldn't Find: " << digitalEntitlementsPath << std::endl;
    }

    // Attempt to remove CitizenFX directory
    std::string citizenFxPath = appdata + "\\CitizenFX";
    if (std::filesystem::exists(citizenFxPath))
    {
        std::filesystem::remove_all(citizenFxPath);
        std::cout << "Removed: " << citizenFxPath << std::endl;
    }
    else
    {
        std::cout << "Couldn't Find: " << citizenFxPath << std::endl;
    }
}


INT CALLBACK browse_callback_proc(HWND hwnd, UINT uMsg, LPARAM lp, LPARAM pData)
{
	if (uMsg == BFFM_INITIALIZED) SendMessage(hwnd, BFFM_SETSELECTION, TRUE, pData);
	return 0;
}

void trace::destroy()
{
	m_fivem_path.clear();
	std::remove(m_save_path.c_str());
}

std::string trace::set_folder(std::string title)
{
    std::ifstream path(m_save_path);
    if (!path.good())
    {
        std::string appdata = getenv("LOCALAPPDATA");
        auto fivem_path = appdata + "\\" + "FiveM";

        BROWSEINFO br;
        ZeroMemory(&br, sizeof(BROWSEINFO));
        br.lpfn = browse_callback_proc;
        br.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
        br.hwndOwner = NULL;
        br.lpszTitle = title.c_str();
        br.lParam = (LPARAM)fivem_path.c_str();

        std::string ret;

        LPITEMIDLIST pidl = NULL;
        if ((pidl = SHBrowseForFolder(&br)) != NULL)
        {
            char buffer[_MAX_PATH];
            if (SHGetPathFromIDList(pidl, buffer)) ret = buffer;
        }

        if (!std::filesystem::exists(ret + "\\" + "FiveM.exe"))
        {
            return std::string();
        }

        if (!ret.empty())
        {
            std::ofstream save_path(m_save_path);
            save_path << ret << std::endl;
            save_path.close();
        }

        return ret;
    }
    else
    {
        std::string name;
        path >> name;

        if (!std::filesystem::exists(name + "\\" + "FiveM.exe"))
        {
            return std::string();
        }

        return name;
    }
}



void trace::set_launch_build()
{
	int choice;

	std::vector<const char*> m_builds = { "2545", "2372", "2189", "2060", "1604" };

	for (int i = 0; i < m_builds.size(); i++)
	{
		std::cout << "  [" << i + 1 << "]  :  " << m_builds[i] << std::endl;
	}
	std::cin >> choice;

	auto path = std::string(m_fivem_path + m_citizen_ini_path).c_str();

	if (std::filesystem::exists(path))
	{
		WritePrivateProfileString("Game", "SavedBuildNumber", m_builds[choice - 1], path);
	}
}

void fillCustomTrigger(HWND hDialog) {
	StringBuilder<32> customValue;

	HWND hValue = GetDlgItem(hDialog, IDC_TRIGGER_EAX_VALUE);

	if(GetWindowTextLengthW(hValue) > 0) {
		customValue.putString(L"eax == ");
		customValue.putWindowText(GetDlgItem(hDialog, IDC_TRIGGER_EAX_VALUE));
	}
	SetWindowTextW(GetDlgItem(hDialog, IDC_TRIGGER_CUSTOM_VALUE), customValue.getString());
}

void trace::get_launch_build()
{
	auto path = std::string(m_fivem_path + m_citizen_ini_path).c_str();
	auto buildNumber = 0;

	if (std::filesystem::exists(path))
	{
		buildNumber = GetPrivateProfileInt("Game", "SavedBuildNumber", buildNumber, path);
	}
	return std::to_string(buildNumber);
}

void loadString(std::wstring& string, FILE* file) {
	int strlen = 0;
	fread(&strlen, sizeof(strlen), 1, file);
	string.resize(strlen);
	fread(&string[0], sizeof(string[0]), strlen, file);
}
