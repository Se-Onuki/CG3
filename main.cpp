#include <iostream>
#include <stdint.h>
#include <type_traits>

//SFINAEをやろうとした残骸
//template <typename T>
//struct is_number : std::integral_constant<std::is_integral<T>::value || std::is_floating_point<T>::value> {};

/// @brief min関数
/// @tparam T 型名
/// @param A 数値A
/// @param B 数値B
/// @return 小さいほうの値
template <typename T>
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