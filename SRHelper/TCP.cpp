#include "pch.h"
#include "TCP.h"

namespace SpaRcle {
	namespace Network {
		SpaRcle::Network::TCP::TCP(std::string ip, int port, Debug* debug) {
			this->ip = ip;
			this->port = port;
			this->debug = debug;
		}

		SpaRcle::Network::TCP::~TCP() {

		}

		bool TCP::Run() {
			debug->Info("Running TCP client-server...\n\tIp   : "+ip + "\n\tPort : "+std::to_string(port));

			isRun = true;

			return true;
		}

		template<typename T> void TCP::Send(T data) {

		}
	}
}