#include <array>
#include <chrono>
#include <immintrin.h>
#include <iostream>

static inline void TransponeArray(std::array<__m128, 2u> *data)
{
	/*static const __m256i indices = _mm256_set_epi32(5, 2, 7, 4, 1, 6, 3, 0);

	*data = _mm256_permutevar8x32_ps(*data, indices);*/

	//_mm256_storeu_ps(data, result);

	// static const uint32_t mask = _MM_SHUFFLE(1, 2, 3, 0); // 0,3,6,1,4,7,2,5

	// __m256 temp1 = _mm256_permute_ps(data, mask);
	// __m256 temp2 = _mm256_permute2f128_ps(temp1, temp1, 1);

	// data = _mm256_blend_ps(temp1, temp2, 0b01000100);

	/*__m128 input_low = _mm_loadu_ps(data);
	__m128 input_high = _mm_loadu_ps(data.data() + 4);*/

	constexpr uint32_t mask = _MM_SHUFFLE(1, 2, 3, 0); // 0, 3, 2, 1

	__m128 temp = _mm_permute_ps(data->at(0), mask);
	data->at(1) = _mm_shuffle_ps(data->at(1), data->at(1), mask);


	// Swap the second elements
	data->at(0) = _mm_blend_ps(temp, data->at(1), 0b0100);
	data->at(1) = _mm_blend_ps(data->at(1), temp, 0b0100);

	//__m128 temp2_low = _mm_shuffle_ps(temp1_low, temp1_low, _MM_SHUFFLE(2, 3, 0, 1)); // Swap low elements
	//__m128 temp2_high = _mm_shuffle_ps(temp1_high, temp1_high, _MM_SHUFFLE(2, 3, 0, 1)); // Swap high elements

	//data->at(0) = _mm_shuffle_ps(temp1_low, temp2_low, _MM_SHUFFLE(2, 0, 2, 0));
	//data->at(1) = _mm_shuffle_ps(temp1_high, temp2_high, _MM_SHUFFLE(2, 0, 2, 0));


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
		union/* alignas(16) */SimdVec {
			std::array<__m128, 2u> simd;
			std::array<float, 8u> arr;
			//Matrix3x3 m;
		};

		Matrix3x3 result;
		result.m[2][2] = m[2][2];

		// Load the data into a single __m128
		SimdVec calc = { _mm_load_ps(m.data()->data()), _mm_load_ps(m.data()->data() + 4u) };

		//SimdVec calc = { .m = *this };
		TransponeArray(&calc.simd);
		//// Transpose using shuffle
		//__m128 shuf1 = _mm_shuffle_ps(calc[0], calc[0], _MM_SHUFFLE(3, 1, 2, 0));
		//__m128 shuf2 = _mm_shuffle_ps(calc[1], calc[1], _MM_SHUFFLE(3, 1, 2, 0));

		//// Concatenate the shuffles to get the final transposed result
		//result.m[0][0] = _mm_cvtss_f32(calc[0]);
		//result.m[0][1] = _mm_cvtss_f32(shuf1);
		//result.m[0][2] = _mm_cvtss_f32(_mm_shuffle_ps(shuf2, shuf1, _MM_SHUFFLE(2, 0, 2, 0)));

		//result.m[1][0] = _mm_cvtss_f32(_mm_shuffle_ps(calc[0], shuf1, _MM_SHUFFLE(2, 0, 2, 0)));
		//result.m[1][1] = _mm_cvtss_f32(shuf2);
		//result.m[1][2] = _mm_cvtss_f32(_mm_shuffle_ps(shuf1, shuf2, _MM_SHUFFLE(3, 1, 3, 1)));

		//result.m[2][0] = _mm_cvtss_f32(_mm_shuffle_ps(shuf1, calc[1], _MM_SHUFFLE(3, 1, 3, 1)));
		//result.m[2][1] = _mm_cvtss_f32(_mm_shuffle_ps(shuf2, calc[1], _MM_SHUFFLE(3, 1, 3, 1)));

		_mm_store_ps(result.m.data()->data(), calc.simd[0]);
		_mm_store_ps(result.m.data()->data() + 4u, calc.simd[1]);

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
	const uint32_t iterations = 10000000u;

	Matrix3x3 matrix{ .m{
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
	} };
	// Initialize your matrix here...

	Matrix3x3 result;
	// Benchmark TransponeSIMD
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < iterations; ++i) {
		result = matrix.TransponeSIMD();
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> transponeSIMDDuration = end - start;
	std::cout << "TransponeSIMD Time: " << transponeSIMDDuration.count() << " seconds\n"
		<< result << std::endl;

	// Benchmark Transpone
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < iterations; ++i) {
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