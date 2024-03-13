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

	template <ConstExprString T>
	constexpr bool operator<(const StaticString<T> &other) const noexcept {
		return c_str() < other.c_str();
	}
};

// StaticStringをキーとするコンテナの実装
template <typename T, ConstExprString... StaticStrings>
struct StaticStringMap {
	inline static std::tuple<std::pair<StaticString<StaticStrings>, T>...> data_ = {
		std::make_tuple(std::make_pair(StaticString<StaticStrings>{}, T{})...)
	};

	// StaticStringから値を取得する
	template <ConstExprString Str>
	static constexpr const T &get() {
		return std::get<std::pair<StaticString<Str>, T>>(data_).second;
	}

	// StaticStringに対応する値を設定する
	template <ConstExprString Str>
	static constexpr void set(const T &value) {
		std::get<std::pair<StaticString<Str>, T>>(data_).second = value;
	}
};

int main() {
	// コンテナの初期化
	using MapType = StaticStringMap<std::string, "hello", "world">;
	std::string value1 = MapType::get<"hello">();
	std::string value2 = MapType::get<"world">();

	std::cout << "Value for key 'hello': " << value1 << std::endl;
	std::cout << "Value for key 'world': " << value2 << std::endl;

	// 値の変更
	MapType::set<"hello">("Bonjour");
	MapType::set<"world">("Monde");

	std::string newValue1 = MapType::get<"hello">();
	std::string newValue2 = MapType::get<"world">();

	std::cout << "Updated value for key 'hello': " << newValue1 << std::endl;
	std::cout << "Updated value for key 'world': " << newValue2 << std::endl;

	return 0;
}
