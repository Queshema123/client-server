// client-server.cpp: определяет точку входа для приложения.
//

#include "client-server.h"
#include "client_gui.hpp"
#include <thread>
int main()
{
	std::thread t(
		[]()
		{
			Server s;
			s.start();
		}
	);
	start();
	t.join();
	return 0;
}
