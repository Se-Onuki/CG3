#include <array>
#include <chrono>
#include <immintrin.h>
#include <iostream>
#include <cstdio>

static inline void TransponeArray(std::array<__m128, 2u> *data)
{
	// 位置入れ替えのマスク
	constexpr int32_t mask = _MM_SHUFFLE(1, 2, 3, 0); // 0, 3, 2, 1
	// ブレンド時のマスク
	constexpr int32_t blendMask = 0b0100;
	// 位置を入れ替え
	data->at(1) = _mm_permute_ps(data->at(1), mask);
	__m128 temp = _mm_permute_ps(data->at(0), mask);
	// 特定の箇所の
	data->at(0) = _mm_blend_ps(temp, data->at(1), blendMask);
	data->at(1) = _mm_blend_ps(data->at(1), temp, blendMask);

}

struct Matrix3x3 {
	std::array<std::array<float, 3u>, 3u> m;
	inline Matrix3x3 Transpone() const
	{
		return Matrix3x3{ .m{
			this->m[0][0], this->m[1][0], this->m[2][0],
			this->m[0][1], this->m[1][1], this->m[2][1],
			this->m[0][2], this->m[1][2], this->m[2][2]} };
	}

	inline Matrix3x3 TransponeSIMD() const
	{

		Matrix3x3 result;
		result.m[2][2] = m[2][2];

		// 値を代入
		std::array<__m128, 2u> calc = { _mm_load_ps(m.data()->data()), _mm_load_ps(m.data()->data() + 4u) };
		// 転置関数
		TransponeArray(&calc);
		// 結果を代入
		_mm_store_ps(result.m.data()->data(), calc[0]);
		_mm_store_ps(result.m.data()->data() + 4u, calc[1]);

		return result;
	}

	static inline friend std::ostream &operator<<(std::ostream &os, const Matrix3x3 &matrix)
	{
		for (const auto &row : matrix.m) {
			for (const float &value : row) {
				os << value << " ";
			}
			os << std::endl;
		}
		return os;
	}
};

int main()
{
	constexpr uint32_t iterations = 100000000u;

	Matrix3x3 matrix{ .m{
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
	} };
	// Initialize your matrix here...

	Matrix3x3 result;
	// Benchmark TransponeSIMD
	auto start = std::chrono::high_resolution_clock::now();
	for (uint32_t i = 0u; i < iterations; ++i) {
		result = matrix.TransponeSIMD();
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> transponeSIMDDuration = end - start;
	std::cout << "TransponeSIMD Time: " << transponeSIMDDuration.count() << " seconds\n"
		<< result << std::endl;

	// Benchmark Transpone
	start = std::chrono::high_resolution_clock::now();
	for (uint32_t i = 0u; i < iterations; ++i) {
		result = matrix.Transpone();
	}
	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> transponeDuration = end - start;
	std::cout << "Transpone Time: " << transponeDuration.count() << " seconds\n"
		<< result << std::endl;

	// Calculate speedup
	double speedup = transponeDuration.count() / transponeSIMDDuration.count();
	std::cout << "Speedup: " << speedup << "x\n";

	return 0;
}