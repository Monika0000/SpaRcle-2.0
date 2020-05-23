#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#include <string>
#include "Debug.h"
#include <thread>
#include <vector>

#include <typeinfo>

#include <iostream>
#include <winsock.h>

namespace SpaRcle {
	namespace Network {
		const int BUFFER_SIZE = 4096;

		using namespace Helper;

		__interface IPackage  {
			/*
				ƒанный интерфейс предназначен дл€ харнени€ данных, которые необходимо отправить/получить через интернет
				 ласс, который реализует этот интерфейс, может быть передан в метод Send, и отправлен клиенту, благодар€ методу GetData,
				а метод Recv возвращает указанный тип данных, заполн€€ его пол€ данных, использу€ метод SetData
			*/
			virtual std::string GetSendData() = 0;
			virtual bool SetData(std::string data) = 0;
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
			template <typename T> IPackage* Recv() {
				if (recive_data.size() > 0) {
					T* data = new T();
					if (!data->SetData(recive_data[0])) {
						debug->Error("Failed recv message from [" + ip + ":" + std::to_string(port) + ", socket: " + std::to_string(client_sock) + "]");
						recive_data.erase(recive_data.begin());
						return nullptr;
					}

					recive_data.erase(recive_data.begin());

					return data;
				} else return nullptr;
			}
		private:
			std::vector<std::string> recive_data;
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

