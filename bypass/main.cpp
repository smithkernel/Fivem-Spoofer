#include "core/trace.hpp"
#include "core/network.hpp"

int main()
{
	int choice;

	while (true)
	{
		system("cls");

		std::cout << R"(
                                            
                                                            
 ::::::::  :::::::::: :::::::::  :::    ::: :::::::::   ::::::::  
:+:    :+: :+:        :+:    :+: :+:    :+: :+:    :+: :+:    :+: 
+:+        +:+        +:+    +:+ +:+    +:+ +:+    +:+ +:+        
+#++:++#++ +#++:++#   +#++:++#:  +#+    +:+ +#++:++#+  +#++:++#++ 
       +#+ +#+        +#+    +#+ +#+    +#+ +#+               +#+ 
#+#    #+# #+#        #+#    #+# #+#    #+# #+#        #+#    #+# 
 ########  ########## ###    ###  ########  ###         ########  
                                                                  
                                                               

	This is the free version, do not sell or use it for profit.
	Create By : Serups#0001 | Support Fivem Version 6287
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
	
				std::cout << "  [1]  :  " << "Cleaner" << std::endl;
				std::cout << "  [2]  :  " << "Bypass" << std::endl;
				std::cout << "  [3]  :  " << "Disable Bypass" << std::endl;
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
