#pragma once
#include <string>
#include <vector>

namespace SpaRcle {
	namespace Helper {
		class Array {
		private:
			~Array() { };
			Array() { };
		public:
			template <typename T> static const bool Contains(std::vector<T>& Vec, const T& Element) {
				if (std::find(Vec.begin(), Vec.end(), Element) != Vec.end()) return true;
				return false;
			};
		};
	}
}
