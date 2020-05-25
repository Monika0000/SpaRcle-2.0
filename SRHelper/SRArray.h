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
			template <typename T> static const int IndexOf(std::vector<T>& Vec, const T& Element) {
				const size_t size = Vec.size();
				for (size_t t = 0; t < size; t++) {
					if (Vec[t] == Element) return t;
				}
				return -1;
			};
			template <typename T> static const int Remove(std::vector<T>& Vec, const T& Element) {
				int index = IndexOf(Vec, Element);
				if (index != -1)
					Vec.erase(Vec.begin() + index);
				return index;
			};
		};
	}
}
