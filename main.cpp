#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <type_traits>

struct Vector3 {
	float x, y, z;

	static uint32_t size() { return 3u; }

	float *const begin() { return &x; }
	const float *const begin() const { return &x; }
	const float *const cbegin() const { return &x; }

	float *const end() { return begin() + size(); }
	const float *const end() const { return end(); }
	const float *const cend() const { return end(); }

	float *const data() { return begin(); }
	const float *const data() const { return begin(); }
	const float *const cdata() const { return begin(); }
};

struct VerticalVector3 {
	float x, y, z;

	uint32_t size() { return 3u; }

	float *const begin() { return &x; }
	const float *const begin() const { return &x; }
	const float *const cbegin() const { return &x; }

	float *const end() { return begin() + size(); }
	const float *const end() const { return end(); }
	const float *const cend() const { return end(); }

	float *const data() { return begin(); }
	const float *const data() const { return begin(); }
	const float *const cdata() const { return begin(); }
};

struct Mat2x2 {
	float m[2][2];

	uint32_t size() { return 4u; }

	float *const begin() { return *m; }
	const float *const begin() const { return *m; }
	const float *const cbegin() const { return *m; }

	float *const end() { return begin() + size(); }
	const float *const end() const { return end(); }
	const float *const cend() const { return end(); }

	float *const data() { return begin(); }
	const float *const data() const { return begin(); }
	const float *const cdata() const { return begin(); }
};

// Traits template declaration
template <typename T>
struct Traits;

// Traits specialization for void
template<>
struct Traits<void> {
	static constexpr auto Name = "void";
	static constexpr uint32_t Rows = 0u;
	static constexpr uint32_t Columns = 0u;
	using ElementType = void;
};

// Traits specialization for int32_t
template<>
struct Traits<int32_t> {
	using Type = int32_t;
	static constexpr auto Name = "int32_t";
	static constexpr uint32_t Rows = 1u;
	static constexpr uint32_t Columns = 1u;
	static constexpr uint32_t Size = Rows * Columns;
	using ElementType = int32_t;

	static const ElementType *CBegin(const Type &data) { return &data; }
	static const ElementType *End(const Type &data) { return CBegin(data) + Size; }
};

template<>
struct Traits<Vector3> {
	using Type = Vector3;
	static constexpr auto Name = "Vector3";
	static constexpr uint32_t Rows = 1u;
	static constexpr uint32_t Columns = 3u;
	static constexpr uint32_t Size = Rows * Columns;
	using ElementType = float;

	static const ElementType *CBegin(const Type &data) { return data.cbegin(); }
	static const ElementType *End(const Type &data) { return CBegin(data) + Size; }
};

template<>
struct Traits<VerticalVector3> {
	using Type = VerticalVector3;
	static constexpr auto Name = "VerticalVector3";
	static constexpr uint32_t Rows = 3u;
	static constexpr uint32_t Columns = 1u;
	static constexpr uint32_t Size = Rows * Columns;
	using ElementType = float;

	static const ElementType *CBegin(const Type &data) { return data.cbegin(); }
	static const ElementType *End(const Type &data) { return CBegin(data) + Size; }
};

template<>
struct Traits<Mat2x2> {
	using Type = Mat2x2;
	static constexpr auto Name = "Mat2x2";
	static constexpr uint32_t Rows = 2u;
	static constexpr uint32_t Columns = 2u;
	static constexpr uint32_t Size = Rows * Columns;
	using ElementType = float;

	static const ElementType *CBegin(const Type &data) { return data.cbegin(); }
	static const ElementType *End(const Type &data) { return CBegin(data) + Size; }
};

// ‰¼‚É•ÏŠ·‚Å‚«‚È‚¢Œ^‚ª—^‚¦‚ç‚ê‚½ê‡‚É‚Í‹ó•¶š‚ğ•Ô‚·
template <typename T, typename = void>
struct has_to_string : std::false_type {};

// std::to_string‚ª‘¶İ‚·‚éê‡‚É‚Í true_type ‚É‚È‚é“Áê‰»
template <typename T>
struct has_to_string<T, std::void_t<decltype(std::to_string(std::declval<T>()))>> : std::true_type {};

template<typename T>
std::string to_string(const T &data) {
	if constexpr (has_to_string<T>::value) {
		return std::to_string(data);
	}
	else {
		return to_string_custom(data);
	}
}

template <typename T>
std::string to_string_custom(const T &data) {
	uint32_t itemCount = Traits<T>::Size;
	if (itemCount == 0u) {
		return "";
	}
	std::string result;

	if (Traits<T>::Rows > 1u) {
		result += "{\n";
	}
	for (uint32_t y = 0; y < Traits<T>::Rows; ++y) {
		if (Traits<T>::Rows > 1u) {
			result += "\t";
		}
		if (Traits<T>::Columns > 1u) {
			result += "{ ";
		}
		for (uint32_t x = 0u; x < Traits<T>::Columns; ++x) {
			result += to_string(*(Traits<T>::CBegin(data) + y * Traits<T>::Columns + x));
			if (x < Traits<T>::Columns - 1u) {
				result += ", ";
			}
		}
		if (Traits<T>::Columns > 1u) {
			result += " }";
		}
		if (y < Traits<T>::Rows - 1u) {
			result += ",\n";
		}
	}

	if (Traits<T>::Rows > 1u) {
		result += "\n}";
	}

	return result;
}

int main() {

	int32_t scalarValue = 42;
	Vector3 vectorValue = { 0, 1, 2 };
	Mat2x2 matValue{ 0,1,2,3 };

	std::cout << "Scalar Value: " << to_string(10) << std::endl;
	std::cout << "Scalar Value: " << to_string(scalarValue) << std::endl;
	std::cout << "Vector Value: " << to_string(vectorValue) << std::endl;
	std::cout << "Mat Value: " << to_string(matValue) << std::endl;
	//std::cout << "Matrix Value: " << to_string(matrixValue) << std::endl;

	return 0;
}
