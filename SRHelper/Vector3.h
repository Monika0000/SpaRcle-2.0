#pragma once
#include "SRString.h"

namespace SpaRcle {
	namespace Helper {
		struct Vector3 {
			float x = 0.f, y = 0.f, z = 0.f;

			const std::string GetString() const {
				return "(" + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + ")";
			}
			static Vector3* FromString(std::string str) {
				Vector3* vec = new Vector3();

				if (str[0] == '(' && str[str.size() - 1] == ')') {
					str.erase(str.begin());
					str.erase(str.begin()+str.size() - 1);
					std::string* spl = String::FixedSplit(str, " ", 3);
					if (spl) {
						try {
							vec->x = (float)atof(spl[0].c_str());
							vec->y = (float)atof(spl[1].c_str());
							vec->z = (float)atof(spl[2].c_str());
						}
						catch (...) {
							Debug::InternalError("Vector3::FromString() : \"" + str + "\" is not Vector3!");
							delete vec;
							delete[] spl;
							return nullptr;
						}
						delete[] spl;
					}
					else {
						delete vec;
						return nullptr;
					}
				}
				else {
					Debug::InternalError("Vector3::FromString() : \"" + str + "\" is not Vector3!");
					delete vec;
					return nullptr;
				}

				return vec;
			}
		};
	}
}