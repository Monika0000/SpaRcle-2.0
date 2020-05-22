#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#include <string>
#include "Debug.h"
#include <thread>

#include <iostream>
#include <winsock.h>

namespace SpaRcle {
	namespace Network {
		const int BUFFER_SIZE = 4096;

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
			static bool isLoadWSAStartup;
			bool LoadWSAStartup() {
				if (!isLoadWSAStartup) {
					debug->System("Loading WSAStartup dll...");
					WSAData wsaData;
					WORD DLLVersion = MAKEWORD(2, 1);

					int r = WSAStartup(DLLVersion, &wsaData);
					if (r != 0) {
						debug->Error("Failed loading WSAStartup dll!");
						return false;
					}
					isLoadWSAStartup = true;
				}
				return true;
			}

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

