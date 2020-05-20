#include "pch.h"
#include "SRHelper.h"

namespace SpaRcle {
	namespace Helper {
		const std::string String::VALID_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		std::default_random_engine String::generator = std::default_random_engine();
		std::uniform_int_distribution<int> String::distribution = std::uniform_int_distribution<int>(0, VALID_CHARS.size() - 1);
	}
}