#include <iostream>
#include <concepts>
#include <string>
#include <memory>
#include <functional>
#include <assert.h>
#include <array>

/// @brief 言語インターフェース
class ILanguage {
public:
	ILanguage() = default;
	virtual ~ILanguage() = default;

	/// @brief 挨拶
	/// @return 挨拶の文字列
	virtual const char *Hello() const = 0;

	/// @brief 別れの挨拶
	/// @return 別れの文字列
	virtual const char *GoodBye() const = 0;
};

/// @brief 言語インターフェースを継承しているかどうか
template <typename T>
concept IsBaseILanguage = std::derived_from<T, ILanguage>;

/// @brief 日本語
class Japanese final : public ILanguage {
public:
	Japanese() = default;
	~Japanese() = default;

	/// @brief 挨拶
	/// @return 挨拶の文字列
	const char *Hello() const override;

	/// @brief 別れの挨拶
	/// @return 別れの文字列
	const char *GoodBye() const override;

private:

};

class English final : public ILanguage {
public:
	English() = default;
	~English() = default;

	/// @brief 挨拶
	/// @return 挨拶の文字列
	const char *Hello() const override;

	/// @brief 別れの挨拶
	/// @return 別れの文字列
	const char *GoodBye() const override;

private:

};

class Human {
public:
	Human() = default;
	~Human() = default;

	/// @brief 言語の設定
	template <IsBaseILanguage T>
	void SetLanguage();

	/// @brief 文章を話す
	/// @param text 話す内容
	void Speak(const char *text) const;

	/// @brief 挨拶をする
	void Hello() const;

	/// @brief 別れの挨拶をする
	void GoodBye() const;

private:
	// 使用言語
	std::unique_ptr<ILanguage> usingLang_ = nullptr;

};

int main(void) {
	// それぞれの言語を使う人の配列
	std::array<Human, 2u> humanArray = {};

	// 言語設定
	humanArray[0u].SetLanguage<Japanese>();
	humanArray[1u].SetLanguage<English>();

	// それぞれ挨拶をする
	for (const auto &human : humanArray) {
		human.Hello();
		human.GoodBye();
	}

	return 0;
}

#pragma region 関数定義

const char *Japanese::Hello() const {
	static const std::string text = "こんにちは";
	return text.c_str();
}


const char *Japanese::GoodBye() const {
	static const std::string text = "さようなら";
	return text.c_str();
}


const char *English::Hello() const {
	static const std::string text = "Hello";
	return text.c_str();
}


const char *English::GoodBye() const {
	static const std::string text = "GoodBye";
	return text.c_str();
}

template <IsBaseILanguage T>
void Human::SetLanguage() {
	usingLang_ = std::make_unique<T>();
}
void Human::Speak(const char *text) const {
	std::cout << text << std::endl;
}

void Human::Hello() const {
	assert(usingLang_ && "言語が設定されていません");
	this->Speak(usingLang_->Hello());
}
void Human::GoodBye() const {
	assert(usingLang_ && "言語が設定されていません");
	this->Speak(usingLang_->GoodBye());
}

#pragma endregion