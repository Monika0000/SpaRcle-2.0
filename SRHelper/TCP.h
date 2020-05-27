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
		//const int BUFFER_SIZE = 4096;
		//const int BUFFER_SIZE = 8192;
		const int BUFFER_SIZE = 1024;

		enum class PackState {
			Begin, Reciving, End, NoneData
		};

		const std::string begin_name = "begin_pack";
		const std::string end_name =   "end_pack";

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

			//void Client();
			void Server();
		private:
			PackState state;
		private:
			bool isRun;
			bool isSend;
			bool isRecv;
		public:
			PackState GetState() { return state; }
			//!------------------------------------------
			bool Send(IPackage* data) {
				if (!data) {
					debug->Error("Failed send message to [" + ip + ":" + std::to_string(port) + ", socket: " + std::to_string(server_sock) + "] Data is nullptr!");
					return false;
				}
				bool result = false;
			ret:
				if (!isRecv) {
					isSend = true;

					std::string msg = data->GetSendData();

					debug->Network("Send : " + msg);

					if (send(server_sock, msg.c_str(), sizeof(msg.c_str()), 0) == SOCKET_ERROR) {
						debug->Error("Failed send message to [" + ip + ":" + std::to_string(port) + ", socket: " + std::to_string(server_sock) + "]");
					}

					msg.clear();

					result = true;

					isSend = false;
				} else goto ret;

				return result;
			}
			/*
			template <typename T> IPackage* Recv() {
			ret:
				if (!isSend) {
					isRecv = true;
					//std::cout << recive_data.size() << std::endl;
					
					if (recive_data.size() > 0) {
						T* data = nullptr;

						if (recive_data[0] == begin_name) {
							state = PackState::Begin;
						} else if (recive_data[0] == end_name) {
							state = PackState::End;
						} else {
							state = PackState::Reciving;
							data = new T();
							if (!data->SetData(recive_data[0])) {
								debug->Error("Failed recv message from [" + ip + ":" + std::to_string(port) + ", socket: " + std::to_string(client_sock) + "]");
								delete data;
							}
						}

						recive_data.erase(recive_data.begin());

						isRecv = false;
						return data;
					}
					else {
						state = PackState::NoneData;
						isRecv = false;
						return nullptr;
					}
				}
				else {
					goto ret;
				}
			}
			*/
			bool Recv(IPackage* pack) {
			ret:
				if (!isSend) {
					isRecv = true;
					if (recive_data.size() > 0) {
						if (recive_data[0] == begin_name) {
							state = PackState::Begin;
						}
						else if (recive_data[0] == end_name) {
							state = PackState::End;
						}
						else {
							state = PackState::Reciving;
							if (!pack->SetData(recive_data[0])) {
								//debug->Error("Failed recv message from [" + ip + ":" + std::to_string(port) + ", socket: " + std::to_string(client_sock) + "]");
								debug->Error("Failed recv message from [" + ip + ":" + std::to_string(port) + ", socket: " + std::to_string(server_sock) + "]");
							}
							else {
								recive_data.erase(recive_data.begin());
								return true;
							}
						}

						recive_data.erase(recive_data.begin());

						isRecv = false;
						return false;
					}
					else {
						state = PackState::NoneData;
						isRecv = false;
						return false;
					}
				}
				else goto ret;
			}
		private:
			std::vector<std::string> recive_data;
		private:
			std::string ip;
			int port;

			Debug* debug;

			//SOCKET client_sock;
			SOCKET server_sock;

			//std::thread client_thread;
			std::thread server_thread;
		};
	}
}

