#include <map>
#include <string>
#include <iostream>
#include <array>
#include <string_view>

// コンパイル時定義固定文字列
template <uint32_t Size>
struct ConstExprString {
	static constexpr uint32_t length_ = Size - 1;
	std::array<char, Size> buf_;

	// 文字列リテラルから推論を行うためのコンストラクタ
	constexpr ConstExprString(const char(&s_literal)[Size]) {
		for (uint32_t i = 0u; i < Size; i++) {
			buf_[i] = s_literal[i];
		}
	}
};

// 静的固定文字列
template <ConstExprString Str>
struct StaticString {
	static constexpr auto str_ = Str;

	constexpr std::string_view view() const noexcept { return { str_.data(), str_.length_ + 1 }; }

	constexpr const char *c_str() const noexcept { return str_.buf_.data(); }

	constexpr bool operator<(const StaticString &other) const noexcept {
		return std::string_view{ c_str(), str_.length_ } < std::string_view{ other.c_str(), other.str_.length_ };
	}
};

// StaticStringをキーとするコンテナの実装
template <typename T, ConstExprString... StaticStrings>
struct StaticStringMap {
	inline static constexpr std::tuple<std::pair<StaticString<StaticStrings>, T>...> data_ = {
		std::make_tuple(std::make_pair(StaticString<StaticStrings>{}, T{})...)
	};

	// StaticStringから値を取得する
	template <ConstExprString Str>
	static constexpr const T &get() {
		return std::get<std::pair<StaticString<Str>, T>>(data_).second;
	}
};

int main() {
	// コンテナの初期化
	using MapType = StaticStringMap<int, "hello", "world">;
	constexpr auto value1 = MapType::get<"hello">();
	constexpr auto value2 = MapType::get<"world">();

	std::cout << "Value for key 'hello': " << value1 << std::endl;
	std::cout << "Value for key 'world': " << value2 << std::endl;

	return 0;
}
