#include <iostream>
#include <stdint.h>
#include <type_traits>

//SFINAE����낤�Ƃ����c�[
//template <typename T>
//struct is_number : std::integral_constant<std::is_integral<T>::value || std::is_floating_point<T>::value> {};

/// @brief min�֐�
/// @tparam T �^��
/// @param A ���lA
/// @param B ���lB
/// @return �������ق��̒l
template <typename T>
T Min(T A, T B) {
	return (A < B) ? A : B;
}

/// @brief min�֐�(char�^)
/// @param A ���lA
/// @param B ���lB
/// @return �󔒕���
template<>
char Min<char>(char A, char B) {
	std::cout << "�����ȊO�͑���ł��܂���" << std::endl;
	return ' ';
}

int main(void) {
	std::cout << Min(10, 20) << std::endl;
	std::cout << Min(10.f, 20.f) << std::endl;
	std::cout << Min(10.0, 20.0) << std::endl;
	std::cout << Min('o', 'h') << std::endl;
	return 0;
}