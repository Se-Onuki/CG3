#include <iostream>
#include <stdint.h>
#include <random>
#include <chrono>
#include <functional>

int32_t GetRandom(int32_t min, int32_t max) {

	if (min >= max) { return min; }

	static std::mt19937 gen;
	static bool init;
	if (!init) {
		std::random_device rd;
		gen.seed(rd());
		init = true;
	}
	std::uniform_int_distribution<int32_t> dist(min, max);
	return dist(gen);
}

/// @brief 遅延実行
/// @param delay 遅延秒数
/// @param func 実行する関数
template<typename T>
T DelayFunction(int32_t delay, const std::function<T()> &func) {
	std::this_thread::sleep_for(std::chrono::seconds(delay));
	func();
}


int main(void) {

	char input = '\0';

	std::cout << "半[奇数]か丁[偶数]を当てるゲームを行います。" << std::endl;
	std::cout << "半[0]か丁[1]のどちらかを入力してください。" << std::endl;

	while (true) {
		std::cout << "数値を入力してください。 >> ";
		// 入力処理
		std::cin >> input;

		if (input == '0' || input == '1') {
			break;
		}
		else {
			std::cout << "正しい値を入力してください。" << std::endl;
		}
	}

	int32_t dice;

	DelayFunction<void>(3, [&dice]() {
		dice = GetRandom(1, 6);
		});
	std::cout << "賽の出目は[" << dice << "]でした" << std::endl;;

	if (dice % 2 == 0) {
		std::cout << "賽の出目は[偶数]でした。" << std::endl;
	}
	else {
		std::cout << "賽の出目は[奇数]でした。" << std::endl;
	}

	if (input == '0') {
		std::cout << "入力した値は半[奇数]なので、";
	}
	else {
		std::cout << "入力した値は丁[偶数]なので、";
	}

	if ((input == '0' && dice % 2 == 1) || (input == '1' && dice % 2 == 0)) {
		std::cout << "正解です。" << std::endl;
	}
	else {
		std::cout << "不正解です。" << std::endl;
	}

	return 0;
}