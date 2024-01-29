#include <iostream>
#include <cstdio>
#include <string>
#include <chrono>

int main(void) {

	std::string originStr = std::string(100000, 'a');

	std::chrono::system_clock::time_point begin = std::chrono::system_clock::now();

	// コピー
	std::string copyStr = originStr;
	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

	std::chrono::microseconds diffA = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);



	begin = std::chrono::system_clock::now();
	// ムーブ代入
	std::string moveStr = std::move(originStr);
	end = std::chrono::system_clock::now();

	std::chrono::microseconds diffB = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

	std::cout << "100,000文字を移動とコピーで比較しました。" << std::endl;

	std::cout << "コピー: " << diffA << std::endl;
	std::cout << "移動: " << diffB << std::endl;

	return 0;

}