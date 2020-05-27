#include "pch.h"
#include "TCP.h"
#include <thread>
#include "SRString.h"

namespace SpaRcle {
	namespace Network {
		bool TCP::isLoadWSAStartup = false;

		SpaRcle::Network::TCP::TCP(std::string ip, int port, Debug* debug) {
			if (ip == "localhost") ip = "127.0.0.1";

			this->ip = ip;
			this->port = port;
			this->debug = debug;

			//client_thread = std::thread();
			server_thread = std::thread();

			this->state = PackState::NoneData;

			recive_data = std::vector<std::string>();
		}

		SpaRcle::Network::TCP::~TCP() { Close(); }

		bool TCP::Run() {
			debug->Info("Running TCP client-server...\n\tIp   : "+ip + "\n\tPort : "+std::to_string(port));

			if (!this->LoadWSAStartup()) { debug->Error("TCP::Run() : Failed loading WSAStartup dll!"); return false; }

			isRun = true;

			//client_thread = std::thread(&SpaRcle::Network::TCP::Client, this);
			server_thread = std::thread(&SpaRcle::Network::TCP::Server, this);

			//debug->Info("TCP client-server...\n\tIp   : " + ip + "\n\tPort : " + std::to_string(port) + " is run!");

			return true;
		}

		bool TCP::Close() {
			debug->Info("Stopping TCP client-server...\n\tIp   : " + ip + "\n\tPort : " + std::to_string(port));

			isRun = false;

			//closesocket(client_sock);
			//closesocket(server_sock);
			
			//shutdown(client_sock, 0);
			shutdown(server_sock, 0);

			//if (client_thread.joinable()) client_thread.detach();
			if (server_thread.joinable()) server_thread.detach();
			
			return true;
		}

		void TCP::Server() {
			/*
				 омпил€тор Visual Studio 2019 слишком тупой, чтобы пон€ть, что данный метод имеет какой-то смысл, 
				потому он просто берет и уничтожает его, оптимизиру€ программу. Ќо о чудо! ≈сли мы вызовем метод Sleep, 
				то он уже будет считать, что этот метод имеет великий смысл, и потому он не будет его удал€ть, просто замечательно.
				Ќо если мы передадим в Sleep 0, то он все таки про€вит свой ум, и удалит все к херам собачим. 
				ѕоэтому в данном методе об€зательно должен быть вызов Sleep(1) с аргументом в виде единички.
			*/
			Sleep(1); 

			try {
				SOCKADDR_IN addr;
				int sizeofaddr = sizeof(addr);
				addr.sin_addr.s_addr = inet_addr(ip.c_str());
				addr.sin_port = htons(port);
				addr.sin_family = AF_INET;

				SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
				bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
				listen(sListen, SOMAXCONN);
				debug->Network("TCP client-server listen to adress " + ip + ":" + std::to_string(port));

				char buffer[BUFFER_SIZE];
				memset(buffer, 0x00, BUFFER_SIZE);

				bool connect = false;
				std::string message;

				try {
					while (isRun) {
						if (!connect) {
							//client_sock = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
							server_sock = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
							//debug->Network("TCP client [" + ip + ":" + std::to_string(port) + ", socket: " + std::to_string(client_sock) + "] has been connected!");
							debug->Network("TCP client [" + ip + ":" + std::to_string(port) + ", socket: " + std::to_string(server_sock) + "] has been connected!");
							connect = true;
						}

						memset(buffer, 0x00, BUFFER_SIZE);
						//int k = recv(client_sock, buffer, sizeof(buffer), NULL);
						int k = recv(server_sock, buffer, sizeof(buffer), NULL);
						message = buffer;

						if (k == 0) {
							//debug->Network("TCP client [" + ip + ":" + std::to_string(port) + ", socket: " + std::to_string(client_sock) + "] has been disconnected!");
							debug->Network("TCP client [" + ip + ":" + std::to_string(port) + ", socket: " + std::to_string(server_sock) + "] has been disconnected!");
							connect = false;
						}
						else if (!message.empty()) {
							//debug->Network("From [" + ip + ":" + std::to_string(port) + "] recive => "+ message);
							std::string rm = std::string();

						ret:
							rm = Helper::String::Remove(message, '|');
							if (!rm.empty()) {
							ret_recv:
								if (!isRecv) {
									this->isSend = true;

									recive_data.push_back(rm);

									this->isSend = false;
								}
								else
									goto ret_recv;

								goto ret;
							}

						}

						message.clear();

						//Sleep(100);
					}
				}
				catch (std::runtime_error err) {
					debug->Error("Runtime internal error in TCP client-server!\n\tIp   : " + ip + "\n\tPort : " + std::to_string(port) + "\n\tWhat : " + err.what());
				}
				catch (std::exception err) {
					debug->Error("Exception as occurred! in TCP client-server!\n\tIp   : " + ip + "\n\tPort : " + std::to_string(port) + "\n\tWhat : " + err.what());
				}
				catch (...) {
					debug->Error("Unknown internal error in TCP client-server!\n\tIp   : " + ip + "\n\tPort : " + std::to_string(port));
				}
			}
			catch (...) {
				debug->Error("Failed running TCP client-server!\n\tIp   : " + ip + "\n\tPort : " + std::to_string(port));
			}
		}

		//void TCP::Server() {
		//	while (isRun) { }
		//}

		/*
		std::string TCP::Recv() {
		ret:
			if (!isSend) {
				isRecv = true;
				if (recive_data.size() > 0) {
					std::string data = recive_data[0];
					recive_data.erase(recive_data.begin());
					isRecv = false;
					return data;
				} else return std::string();
			}
			else {
				goto ret;
			}
		}*/
	}
}