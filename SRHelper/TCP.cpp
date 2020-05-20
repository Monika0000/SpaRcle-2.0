#include "pch.h"
#include "TCP.h"
#include <thread>

namespace SpaRcle {
	namespace Network {
		SpaRcle::Network::TCP::TCP(std::string ip, int port, Debug* debug) {
			this->ip = ip;
			this->port = port;
			this->debug = debug;

			client_thread = std::thread();
			server_thread = std::thread();
		}

		SpaRcle::Network::TCP::~TCP() {

		}

		bool TCP::Run() {
			debug->Info("Running TCP client-server...\n\tIp   : "+ip + "\n\tPort : "+std::to_string(port));

			isRun = true;

			return true;
		}

		bool TCP::Close() {
			debug->Info("Stopping TCP client-server...\n\tIp   : " + ip + "\n\tPort : " + std::to_string(port));

			isRun = false;

			if (client_thread.joinable()) client_thread.join();
			if (server_thread.joinable()) server_thread.join();

			return true;
		}

		void TCP::Client() {
			while (isRun) {

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