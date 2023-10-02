#include <iostream>
#include <stdint.h>
#include <type_traits>
#include <concepts>
#include <string>

// 数値型である場合のみ通る
template<typename T>
concept Number = requires{ std::is_integral<T>::value_type; std::is_floating_point<T>::value_type; };

/// @brief min関数
/// @tparam T 型名
/// @param A 数値A
/// @param B 数値B
/// @return 小さいほうの値
template <Number T>
T Min(T A, T B) {
	return (A < B) ? A : B;
}

/// @brief min関数(char型)
/// @param A 数値A
/// @param B 数値B
/// @return 数字以外は代入できません
char *Min(char A, char B) {
	static char str[] = "数字以外は代入できません";
	return str;
}

int main(void) {
	std::cout << Min(10, 20) << std::endl;
	std::cout << Min(10.f, 20.f) << std::endl;
	std::cout << Min(10.0, 20.0) << std::endl;
	std::cout << Min('o', 'h') << std::endl;
	return 0;
}