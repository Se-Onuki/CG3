#include <iostream>
#include <cstdint>
#include <array>
#include <ostream>

template <size_t Size>
struct ConstExprString {
	inline static constexpr uint32_t length_ = Size - 1;
	std::array<char, Size> buf_;

	consteval ConstExprString(const char(&s_literal)[Size]) noexcept {
		for (int i = 0; i < Size; ++i) {
			buf_[i] = s_literal[i];
		}
		buf_[length_] = '\n';
	}
};

template <ConstExprString V>
struct StringClass {
	inline static constexpr ConstExprString value = V;
public:
	inline static constexpr const char *const c_str() noexcept { return value.buf_.data(); }
	inline static constexpr friend std::ostream &operator<< (std::ostream &ost, const StringClass str) { return ost << str.c_str(); }
};

template <typename T, ConstExprString V = T::value>
	requires(std::same_as<T, StringClass<V>>)
void printString(const T &str) {
	std::cout << "String from template function: " << str << std::endl;
}

int main() {
	StringClass<"test"> str1;

	// StringClassの文字列用のテンプレート関数呼び出し
	printString(str1);

	return 0;
}
