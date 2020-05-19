#pragma once
#include <string>
#include "Debug.h"
#include <iostream>
#include <thread>
#include <winsock.h>

namespace SpaRcle {
	namespace Network {
		using namespace Helper;

		__interface IPackage  {
			virtual std::string GetData() = 0;
		};

		class TCP {
		public:
			TCP(std::string ip, int port, Debug* debug);
			~TCP();
		public:
			bool Run();
			bool Close();
		private:
			void Client();
			void Server();
		private:
			bool isRun;
		public:
			void Send(IPackage* data);
		private:
			std::string ip;
			int port;

			Debug* debug;

			SOCKET client_sock;
			SOCKET server_sock;

			std::thread client_thread;
			std::thread server_thread;
		};

	}
}

