#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

class String {
public:
	String(const char *const name = "") {
		*this = name;
	}

	/// @brief 文字列の代入
	/// @param str 文字列
	/// @return 文字列クラス
	inline String &operator=(const char *const str) {
		// 文字列長 + 終端文字
		size_t nameLength = std::strlen(str) + 1u;
		// 再確保
		string.resize(nameLength);

		// メモリコピー
		std::copy(str, str + nameLength, string.begin());

		return *this;
	}

	/// @brief 文字列の追加
	/// @param str 文字列
	/// @return 文字列クラス
	inline String &operator+=(const char *const str) {
		// 文字列長
		size_t nameLength = std::strlen(str);
		// 文字列長 + 終端文字
		size_t beforeLength = string.size();
		// 再確保
		string.resize(beforeLength + nameLength);

		// メモリコピー
		std::copy(str, str + nameLength, &string.begin()[beforeLength - 1u]);

		return *this;
	}

	inline String &operator+= (const String &str) {
		return *this += str.data();
	}

	inline String &operator+= (const char str) {
		string.back() = str;
		string.push_back('\0');
		return *this;
	}

	/// @brief 文字列の追加
	/// @param str 文字列
	/// @return 文字列クラス
	inline String operator+(const char *const str) const {
		// 返す変数
		String result = *this;

		// 文字列長
		size_t nameLength = std::strlen(str);
		// 文字列長 + 終端文字
		size_t beforeLength = result.string.size();
		// 再確保
		result.string.resize(beforeLength + nameLength);

		// メモリコピー
		std::copy(str, str + nameLength, &result.string.begin()[beforeLength - 1u]);

		return result;
	}

	inline String operator+ (const String &str) const {
		return *this + str.data();
	}

	inline bool operator==(const String &str) const {
		return not(std::strcmp(this->data(), str.data()));
	}

	inline bool operator==(const char *const str) const {
		return not(std::strcmp(this->data(), str));
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
		bool isMinus = false;

		// valueが負の場合は結果にマイナス符号を追加して、valueを正にする
		if (value < 0) {
			isMinus = true;
			value = -value;
		}

		// 数値を文字列に変換して逆順に結果に追加
		while (value != 0) {
			char digit = '0' + (value % 10);
			result.string.push_back(digit);
			value /= 10;
		}
		// マイナス記号の追加
		if (isMinus) {
			result.string.push_back('-');
		}

		// 文字列を逆順にする
		std::reverse(result.string.begin(), result.string.end());

		return result;
	}


private:
	// 文字列
	std::vector<char> string;
};

std::ostream &operator<<(std::ostream &stream, const String &value) {
	return stream << value.data();
}

using NumID = std::pair<uint32_t, String>;

bool operator <(const NumID &a, const NumID &b) {
	return a.first < b.first;
}

bool cmp(const NumID &a, const NumID &b)
{
	return a.first < b.first;
}


int main(void) {

	// ファイル
	FILE *file;
	fopen_s(&file, "PG3_05_02.txt", "r");
	// もしファイルが開けなかったらエラーとして扱う
	if (not file) {
		std::cerr << "Failed to open the file." << std::endl;
		return 1;
	}

	std::list<String> nameList;

	String bufferVec;
	char c;

	bool inQuote = false;
	bool isBackSlash = false;

	while ((c = fgetc(file)) != EOF) {

		// ダブルクオートで囲われているなら
		if (not isBackSlash && c == '"') {
			// クオート内部であるなら
			if (inQuote) {
				// 文字列にバッファのデータを転送
				nameList.push_back(bufferVec.data());
				// バッファを初期化
				bufferVec = "";
				// クオートから出る
				inQuote = false;
			}
			else {
				// クオートの中に入る
				inQuote = true;
			}
		}
		// クオートが有効ならバッファに追加
		else if (inQuote) {
			// バックスラッシュが有効か、文字がバックスラッシュでない場合追加
			if (isBackSlash || c != '\\') {
				bufferVec += c;
			}
		}

		// バックスラッシュが有効か切り替える
		if (not isBackSlash && c == '\\') {
			isBackSlash = true;
		}
		else {
			isBackSlash = false;
		}
	}
	fclose(file);

	std::list<std::pair<uint32_t, String>> sortList;

	for (const auto &nameItem : nameList) {

		uint32_t nameNum;
		String numText;
		for (char item : nameItem) {
			if (isdigit(item)) {
				numText += item;
			}
		}
		char *end;
		nameNum = static_cast<uint32_t>(strtol(numText.data(), &end, 10u));

		sortList.push_back(std::make_pair(nameNum, nameItem));
	}

	sortList.sort(cmp);


	for (const auto &str : sortList) {
		std::cout << str.second << std::endl;
	}



	return 0;
}