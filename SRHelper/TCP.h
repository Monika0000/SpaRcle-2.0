#pragma once
#include <string>
#include "Debug.h"

namespace SpaRcle {
	namespace Network {
		using namespace Helper;

		class TCP {
		public:
			TCP(std::string ip, int port, Debug* debug);
			~TCP();
		public:
			bool Run();
		private:
			bool isRun;
		public:
			template <typename T> void Send(T data);
		private:
			std::string ip;
			int port;
			Debug* debug;
		};

	}
}

