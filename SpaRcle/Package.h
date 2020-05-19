#pragma once
#include <string>
#include <TCP.h>

namespace SpaRcle {
	namespace Network {
		struct Move : public IPackage {
		public:
			Move(std::string bone, float value) {
				this->bone = bone; 
				this->value = value;
			}

			inline std::string GetData() override {
				return bone + "|" + std::to_string(value);
			};

			std::string bone;
			float value;
		};
	}
}