#include <iostream>
#include <stdint.h>

// 初期の再帰賃金
constexpr int32_t basePay = 100;

// 通常の賃金
constexpr int32_t normalPay = 1072;

/// @brief 賃金の上昇量
/// @param previousPay 前の時間の賃金
/// @return 現在の時間の給料
int AmountOfRise(const int32_t previousPay) {
	if (previousPay <= 0) { return basePay; }

	return (previousPay * 2) - 50;
}

/// @brief	就業時間の計算
/// @param hours 就業時間 
/// @return 総賃金
int32_t CalcPay(const int32_t hours) {

	if (hours <= 0) { return 0; }

	int32_t thisPay = 0;
	for (uint32_t i = 0; i < hours; i++) {
		thisPay = AmountOfRise(thisPay);
	}

	return thisPay + CalcPay(hours - 1);

}

int main(void) {
	// 就業時間
	constexpr int32_t workingTime = 12;

	for (uint32_t i = 1; i <= workingTime; i++) {
		std::cout << "就業時間[" << i << "] : " << "通常体系[" << normalPay * i << "]円 / 再帰体系[" << CalcPay(i) << "]円" << std::endl;
	}

	return 0;
}