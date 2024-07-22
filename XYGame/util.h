#pragma once
#include <string>
#include <random>

namespace util {
	const wchar_t* intToWchar(int value) {
		std::string str = std::to_string(value);
		size_t len = str.length() + 1;
		wchar_t* wStr = new wchar_t[len];
		size_t chars = 0;
		mbstowcs_s(&chars, wStr, len, str.c_str(), ((size_t)-1));
		return const_cast<const wchar_t*>(wStr);
	}
	bool random() {
		std::uniform_int_distribution<int> range(0, 1);
		std::random_device rd;
		std::mt19937 gen(rd());
		return range(gen);
	}
}