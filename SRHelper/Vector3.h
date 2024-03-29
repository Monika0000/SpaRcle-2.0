#pragma once
#include "SRString.h"

namespace SpaRcle {
	namespace Helper {
		struct Vector2i {
			int x, y;
		};
		struct Vector2f {
			float x, y;
		};
		struct Vector2d {
			double x, y;
			void Normalize() {
				float length = std::sqrt(x * x + y *y);

				// normalize vector
				x /= length;
				y /= length;
			}
		};

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

			static Vector3* Copy(Vector3* vec) {
				Vector3* _new = new Vector3{ vec->x, vec->y, vec->z };
				return _new;
			}
			static Vector3* Normalize(Vector3* v) {
				float len = std::sqrt(v->x * v->x + v->y * v->y + v->z * v->z);

				if (len != 0.) {
					v->x /= len;
					v->y /= len;
					v->z /= len;
				}
				return v;
			}
		};
	}
}