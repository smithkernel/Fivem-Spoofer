#include "core/trace.hpp"
#include "core/network.hpp"

int main()
{
	int choice;

	while (true)
	{
		system("cls");

		std::cout << R"(
                                            
                                                            
   d888888o.   8 8888                  .8.           ,o888888o.    8 8888     ,88' 8 8888888888     d888888o.   
 .`8888:' `88. 8 8888                 .888.         8888     `88.  8 8888    ,88'  8 8888         .`8888:' `88. 
 8.`8888.   Y8 8 8888                :88888.     ,8 8888       `8. 8 8888   ,88'   8 8888         8.`8888.   Y8 
 `8.`8888.     8 8888               . `88888.    88 8888           8 8888  ,88'    8 8888         `8.`8888.     
  `8.`8888.    8 8888              .8. `88888.   88 8888           8 8888 ,88'     8 888888888888  `8.`8888.    
   `8.`8888.   8 8888             .8`8. `88888.  88 8888           8 8888 88'      8 8888           `8.`8888.   
    `8.`8888.  8 8888            .8' `8. `88888. 88 8888           8 888888<       8 8888            `8.`8888.  
8b   `8.`8888. 8 8888           .8'   `8. `88888.`8 8888       .8' 8 8888 `Y8.     8 8888        8b   `8.`8888. 
`8b.  ;8.`8888 8 8888          .888888888. `88888.  8888     ,88'  8 8888   `Y8.   8 8888        `8b.  ;8.`8888 
 `Y8888P ,88P' 8 888888888888 .8'       `8. `88888.  `8888888P'    8 8888     `Y8. 8 888888888888 `Y8888P ,88P' 

	)" << '\n';

		g_network = std::make_unique<network>();
		g_trace = std::make_unique<trace>();

		while (true)
		{
			g_trace->m_fivem_path = g_trace->set_folder("Select FiveM Folder which contains FiveM.exe");

			system("cls");

			if (!g_trace->m_fivem_path.empty())
			{
				std::cout << "  [Selected Folder]  " << g_trace->m_fivem_path << std::endl;
				std::cout << "  [Launch Build]  " << g_trace->get_launch_build() << "\n" << std::endl;
	
				std::cout << "  [1]  :  " << "Remove traces" << std::endl;
				std::cout << "  [2]  :  " << "Bypass" << std::endl;
				std::cout << "  [3]  :  " << "Disable Bypass" << std::endl;
				std::cout << "  [4]  :  " << "Patch Reset" << std::endl;
				std::cin >> choice;

				switch (choice)
				{
					case 1:
					{
						g_trace->setup();
					}
					break;
					case 2:
					{
						g_network->setup();
					}
					break;
					case 3:
					{
						g_network->destroy();
					}
					break;
					case 4:
					{
						g_trace->destroy();
					}
					break;
					case 5:
					{
						g_trace->set_launch_build();
					}
					break;
				}
			}
			else
			{
				std::cout << "  [Error]  :  " << "select valid folder for FiveM" << "\n" << std::endl;
			}

			system("Pause");
		}

		system("Pause");
	}

}

void setup_wmi_api(IWbemLocator** ppLoc, IWbemServices** ppSvc) {
    HRESULT hr;

    // Initialize COM library
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr)) {
        printf("Failed to initialize COM library. Error code = 0x%x\n", hr);
        exit(1);
    }

    // Set up COM security
    hr = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_CONNECT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, 0);
    if (FAILED(hr)) {
        printf("Failed to initialize COM security. Error code = 0x%x\n", hr);
        CoUninitialize();
        exit(1);
    }

    // Create instance of WbemLocator object
    hr = CoCreateInstance(CLSID_WbemLocator, NULL, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID *) ppLoc);
    if (FAILED(hr)) {
        printf("Failed to create IWbemLocator object. Error code = 0x%x\n", hr);
        CoUninitialize();
        exit(1);
    }


    // Connect to the root\CIMV2 namespace with the current user.
    hr = (*ppLoc)->ConnectServer(BSTR(L"ROOT\\CIMV2"), NULL, NULL, NULL, 0, NULL, NULL, ppSvc);
    if (FAILED(hr)) {
        printf("Unable to connect to root\\cimv2. Error code = %x.\n", hr);
        (*ppLoc)->Release();
        CoUninitialize();
        exit(1);
    }

    // Set proxy so impersonation of the client occurs.
    hr = CoSetProxyBlanket(*ppSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
    if (FAILED(hr)) {
        printf("Could not set proxy blanket. Error code = %x.\n", hr);
       	(*ppSvc)->Release();
      	(*ppLoc)->Release();
        CoUninitialize();
        exit(1);
    }
}
