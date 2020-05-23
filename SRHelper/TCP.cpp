#include "pch.h"
#include "TCP.h"
#include <thread>

namespace SpaRcle {
	namespace Network {
		bool TCP::isLoadWSAStartup = false;

		SpaRcle::Network::TCP::TCP(std::string ip, int port, Debug* debug) {
			if (ip == "localhost") ip = "127.0.0.1";

			this->ip = ip;
			this->port = port;
			this->debug = debug;

			client_thread = std::thread();
			server_thread = std::thread();
		}

		SpaRcle::Network::TCP::~TCP() { Close(); }

		bool TCP::Run() {
			debug->Info("Running TCP client-server...\n\tIp   : "+ip + "\n\tPort : "+std::to_string(port));

			if (!this->LoadWSAStartup()) return false;

			isRun = true;

			client_thread = std::thread(&SpaRcle::Network::TCP::Client, this);

			return true;
		}

		bool TCP::Close() {
			debug->Info("Stopping TCP client-server...\n\tIp   : " + ip + "\n\tPort : " + std::to_string(port));

			isRun = false;

			//closesocket(client_sock);
			//closesocket(server_sock);
			
			shutdown(client_sock, 0);
			shutdown(server_sock, 0);

			if (client_thread.joinable()) client_thread.detach();
			if (server_thread.joinable()) server_thread.detach();
			
			return true;
		}

		void TCP::Client() {
			SOCKADDR_IN addr;
			int sizeofaddr = sizeof(addr);
			addr.sin_addr.s_addr = inet_addr(ip.c_str());
			addr.sin_port = htons(port);
			addr.sin_family = AF_INET;

			SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
			bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
			listen(sListen, SOMAXCONN);
			debug->Network("TCP client listen to adress " + ip + ":" + std::to_string(port));

			char buffer[BUFFER_SIZE];
			memset(buffer, 0x00, BUFFER_SIZE);

			bool connect = false;
			std::string message;

			try {
				while (isRun) {
					if (!connect) {
						client_sock = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
						debug->Network("TCP client [" + ip + ":" + std::to_string(port) + ", socket: " + std::to_string(client_sock) + "] has been connected!");
						connect = true;
					}
					
					//int k = ::recv(client_sock, buffer, BUFFER_SIZE, 0);
					int k = recv(client_sock, buffer, sizeof(buffer), NULL);
					message = buffer;
					memset(buffer, 0x00, BUFFER_SIZE);

					if (k == 0) {
						debug->Network("TCP client [" + ip + ":" + std::to_string(port) + ", socket: " + std::to_string(client_sock) + "] has been disconnected!");
						connect = false;
					}
					else if (!message.empty()) {
						debug->Network("From [" + ip + ":" + std::to_string(port) + "] recive => "+ message);
					}
					 
					Sleep(300);
				}
			}
			catch (...) {
				debug->Error("Internal error in TCP client!\n\tIp   : " + ip + "\n\tPort : " + std::to_string(port));
			}
		}

		void TCP::Server() {
			while (isRun) {

			}
		}

		void TCP::Send(IPackage* data) {

		}
	}
}