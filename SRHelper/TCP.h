#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#include "Debug.h"
#include <thread>
#include <vector>

#include <typeinfo>

#include <iostream>
#include <winsock.h>
#include "IPackage.h"

namespace SpaRcle {
	namespace Network {
		const int BUFFER_SIZE = 4096;

		using namespace Helper;

		/*
		class PackageString : public IPackage {
		public:
			std::string str;
			std::string GetSendData() override { return ""; }
			bool SetData(std::string data) override { return false; }
		public:
			PackageString(std::string str) : str(str) { };
			PackageString() : str(std::string()) { };
			~PackageString() { str.clear(); }
		};*/

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
			bool isSend;
			bool isRecv;
		public:
			void Send(IPackage* data);
			//std::string Recv();
			//!------------------------------------------
			template <typename T> IPackage* Recv() {
			ret:
				if (!isSend) {
					isRecv = true;
					//std::cout << recive_data.size() << std::endl;
					
					if (recive_data.size() > 0) {
						T* data = new T();
						if (!data->SetData(recive_data[0])) {
							debug->Error("Failed recv message from [" + ip + ":" + std::to_string(port) + ", socket: " + std::to_string(client_sock) + "]");
							recive_data.erase(recive_data.begin());
							delete data;
							return nullptr;
						}

						recive_data.erase(recive_data.begin());

						isRecv = false;
						return data;
					}
					else {
						isRecv = false;
						return nullptr;
					}
				}
				else {
					goto ret;
				}
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

