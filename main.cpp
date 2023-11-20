
#include <iostream>
#include <stdint.h>
#include <random>
#include <chrono>
#include <functional>
#include <thread>

namespace SoLib {

	namespace Time {

		template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
		class Second final {
		public:
			Second(T time = 0.f) { time_ = time; }
			Second(const Second &) = default;
			Second &operator=(const Second &) = default;

			template <typename U, typename = std::enable_if_t<std::is_floating_point_v<U>>>
			Second(const Second<U> &other) { time_ = static_cast<T>(other.GetTime()); }
			template <typename U, typename = std::enable_if_t<std::is_floating_point_v<U>>>
			Second &operator=(const Second<U> &other) {
				time_ = static_cast<T>(other.GetTime());
				return *this;
			}

			using type = T;

			const T GetTime() const noexcept { return time_; }

			inline operator T () const noexcept { return time_; }

			inline operator std::chrono::duration<T>() const noexcept { return static_cast<std::chrono::duration<T>>(time_); };

		private:
			T time_;
		};

		using SecondF = Second<float>;

		/// @brief 遅延実行
		/// @param delay 遅延秒数
		/// @param func 実行する関数
		template<typename T, typename U>
		T SetTimeOut(const std::function<T()> &func, Second<U> delay) {
			std::this_thread::sleep_for(static_cast<std::chrono::duration<U>>(delay));
			func();
		}

		namespace literals {
			SecondF operator""_sec(long double _Val) noexcept {
				return SecondF{ static_cast<float>(_Val) };
			}
		}

	}

	using namespace Time;

	namespace Random {

		template <typename T>
		T GetRandom(T min, T max) {

			// 数値型でない場合
			if constexpr (not std::is_floating_point_v<T> && not std::is_integral_v<T>) {
				return min;
			}
			else {

				if (min >= max) { return min; }

				static std::mt19937 gen;
				static bool init;
				// 1回目の呼び出しなら初期化
				if (!init) {
					std::random_device rd;
					gen.seed(rd());
					init = true;
				}

				// T が浮動小数点型である場合
				if constexpr (std::is_floating_point_v<T>) {
					std::uniform_real_distribution<T> dist(min, max);
					return dist(gen);
				}
				// T が整数型である場合
				else if constexpr (std::is_integral_v<T>) {
					std::uniform_int_distribution<T> dist(min, max);
					return dist(gen);
				}
				// それ以外の場合(基本無いが)
				else {
					return T{};
				}
			}
		}
	}

	using namespace Random;
}

using namespace SoLib::Time::literals;


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

	std::string inputFace;

	if (input == '0') {
		inputFace = "半[奇数]";
	}
	else {
		inputFace = "丁[偶数]";
	}

	std::cout << input << " : " << inputFace << "を入力しました。" << std::endl;

	// 遅延する秒数
	// _secは秒数クラスのユーザー定義リテラル
	const SoLib::Time::Second sleepSecond = 3._sec;

	SetTimeOut<void>([input, &inputFace]()
		{

			const uint32_t dice = SoLib::GetRandom(1u, 6u);
			std::cout << "賽の出目は[" << dice << "]でした" << std::endl;;

			if (dice % 2 == 0) {
				std::cout << "賽の出目は[偶数]でした。" << std::endl;
			}
			else {
				std::cout << "賽の出目は[奇数]でした。" << std::endl;
			}


			std::cout << "入力した値は" << inputFace << "なので、";

			if ((input == '0' && dice % 2 == 1) || (input == '1' && dice % 2 == 0)) {
				std::cout << "正解です。" << std::endl;
			}
			else {
				std::cout << "不正解です。" << std::endl;
			}
		}, sleepSecond);


	return 0;
}
