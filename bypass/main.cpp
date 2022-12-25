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
