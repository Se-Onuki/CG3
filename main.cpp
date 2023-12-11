#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

class String {
public:
	String(const char *const name = "") {
		*this = name;
	}

	/// @brief 文字列の代入
	/// @param str 文字列
	/// @return 文字列クラス
	inline String &operator=(const char *const str) {
		size_t nameLength = std::strlen(str) + 1u;
		string.resize(nameLength);

		std::copy(str, str + nameLength, string.begin());

		return *this;
	}

	/// @brief 文字列の追加
	/// @param str 文字列
	/// @return 文字列クラス
	inline String &operator+=(const char *const str) {
		size_t nameLength = std::strlen(str);
		size_t beforeLength = string.size();
		string.resize(beforeLength + nameLength);

		std::copy(str, str + nameLength, &string.begin()[beforeLength - 1u]);

		return *this;
	}

	inline String &operator+= (const String &str) {
		return *this += str.data();
	}

	/// @brief 文字列の追加
	/// @param str 文字列
	/// @return 文字列クラス
	inline String operator+(const char *const str) const {
		String result = *this;

		size_t nameLength = std::strlen(str);
		size_t beforeLength = string.size();
		result.string.resize(beforeLength + nameLength);

		std::copy(str, str + nameLength, &result.string.begin()[beforeLength - 1u]);

		return result;
	}

	inline String operator+ (const String &str) const {
		return *this + str.data();
	}

	char *const data() { return string.data(); }
	const char *const data()const { return string.data(); }

	std::vector<char>::iterator begin() { return string.begin(); }
	std::vector<char>::const_iterator begin() const { return string.begin(); }

	std::vector<char>::iterator end() { return string.end(); }
	std::vector<char>::const_iterator end() const { return string.end(); }

	static String to_string(int32_t value) {
		String result{};

		// valueが0の場合は"0"を追加して終了
		if (value == 0) {
			result = "0";
			return result;
		}

		// valueが負の場合は結果にマイナス符号を追加して、valueを正にする
		if (value < 0) {
			result.string.push_back('-');
			value = -value;
		}

		// 数値を文字列に変換して逆順に結果に追加
		while (value > 0) {
			char digit = '0' + (value % 10);
			result.string.push_back(digit);
			value /= 10;
		}

		// 文字列を逆順にする
		std::reverse(result.string.begin() + (result.string.front() == '-'), result.string.end());

		return result;
	}

private:
	std::vector<char> string;
};

std::ostream &operator<<(std::ostream &stream, const String &value) {
	return stream << value.data();
}

struct StationList {

	using StringList = std::list<String>;

	StringList stationList_;

	void push_back(const char *const name) {
		this->stationList_.push_back(name);
	}

	StringList::iterator begin() { return stationList_.begin(); }

	StringList::iterator end() { return stationList_.end(); }

};

int main(void) {

	StationList stationList;
	stationList.push_back("Tokyo");
	stationList.push_back("Kanda");
	stationList.push_back("Akihabara");
	stationList.push_back("Okachimachi");
	stationList.push_back("Ueno");
	stationList.push_back("Uguisudani");
	stationList.push_back("Nippori");
	stationList.push_back("Tabata");
	stationList.push_back("Komagome");
	stationList.push_back("Sugamo");
	stationList.push_back("Otsuka");
	stationList.push_back("Ikebukuro");
	stationList.push_back("Mejiro");
	stationList.push_back("Takadanobaba");
	stationList.push_back("Shin-Okubo");
	stationList.push_back("Shinjuku");
	stationList.push_back("Yoyogi");
	stationList.push_back("Harajuku");
	stationList.push_back("Shibuya");
	stationList.push_back("Ebisu");
	stationList.push_back("Meguro");
	stationList.push_back("Gotanda");
	stationList.push_back("Osaki");
	stationList.push_back("Shinagawa");
	stationList.push_back("Tamachi");
	stationList.push_back("Hamamatsucho");
	stationList.push_back("Shimbashi");
	stationList.push_back("Yurakucho");

	int32_t index = 0u;
	const String jy{ "JY" };
	for (const auto &stationItem : stationList) {
		std::cout << jy + String::to_string(++index) + " " + stationItem << std::endl;
	}

	return 0;
}