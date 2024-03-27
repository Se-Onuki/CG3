#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <tuple>
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <numeric>

constexpr float PI = 3.1415926538f;
constexpr float hPI = PI / 2;

struct Vector3 {
public:
	enum class Preset : uint32_t {
		kRight,
		kUp,
		kFront,
	};

public:
	float x, y, z;

	/// <summary>
	/// ベクトルをデバック表示する
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	void Printf(int x, int y) const;

	/// <summary>
	/// ベクトル長関数
	/// </summary>
	/// <returns>ベクトルの長さ</returns>
	float Length() const { return sqrtf((*this) * (*this)); }

	/// @brief 2乗ベクトル長関数
	/// @return ベクトル長
	float LengthSQ() const { return (*this) * (*this); }

	/// <summary>
	/// 正規化
	/// </summary>
	/// <returns>ベクトル長が1のベクトル</returns>
	Vector3 Nomalize() const
	{

		float Length = this->Length();
		if (Length != 0) {
			return *this / Length;
		}
		else {
			return zero();
		}
	}

	Vector3 operator+(const Vector3 &Second) const
	{
		return Vector3{ this->x + Second.x, this->y + Second.y, this->z + Second.z };
	}
	Vector3 operator-(const Vector3 &Second) const
	{
		return Vector3{ this->x - Second.x, this->y - Second.y, this->z - Second.z };
	}

	Vector3 &operator+=(const Vector3 &Second)
	{
		this->x += Second.x;
		this->y += Second.y;
		this->z += Second.z;
		return *this;
	}
	Vector3 &operator-=(const Vector3 &Second)
	{
		this->x -= Second.x;
		this->y -= Second.y;
		this->z -= Second.z;
		return *this;
	}

	Vector3 operator*(const float &Second) const
	{
		return Vector3{ this->x * Second, this->y * Second, this->z * Second };
	}
	Vector3 operator/(const float &Second) const
	{
		return Vector3{ this->x / Second, this->y / Second, this->z / Second };
	}

	Vector3 &operator*=(const float &Second)
	{
		this->x *= Second;
		this->y *= Second;
		this->z *= Second;
		return *this;
	}
	Vector3 &operator/=(const float &Second)
	{
		this->x /= Second;
		this->y /= Second;
		this->z /= Second;
		return *this;
	}

	float &operator[](uint32_t index) noexcept { return arr()[index]; }
	float operator[](uint32_t index) const noexcept { return arr()[index]; }

	// Vector3 operator*(const Matrix3x3& Second) const {}

	// Vector3 operator*=(const Matrix3x3& Second) {}

	inline const Vector3 &operator+() const { return *this; }
	// 逆ベクトル
	inline Vector3 operator-() const { return *this * -1; }

	// 内積
	inline float operator*(const Vector3 &v) const { return x * v.x + y * v.y + z * v.z; }
	// 外積(クロス積)
	[[nodiscard]] inline Vector3 cross(const Vector3 &v) const { return Vector3{ y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x }; }

	/// @brief 垂直ベクトル
	/// @return 90度回転したベクトル
	inline Vector3 Perpendicular() const
	{
		if (x != 0.f || y != 0.f)
			return Vector3{ -y, x, 0.f };
		return Vector3{ 0.f, -z, y };
	}

	static const Vector3 &zero() { static Vector3 item{}; return item; };

	static const Vector3 &right() { static Vector3 item{ .x = 1.f }; return item; };

	static const Vector3 &up() { static Vector3 item{ .y = 1.f }; return item; };

	static const Vector3 &front() { static Vector3 item{ .z = 1.f }; return item; };

	static const Vector3 &one() { static Vector3 item{ 1.f,1.f,1.f }; return item; };

	inline Vector3 Reflect(Vector3 normal) const { return (*this) - normal * 2 * ((*this) * normal); }

	inline bool operator==(const Vector3 &vec) const { return (this->x == vec.x) && (this->y == vec.y) && (this->z == vec.z); }

	/// @brief 暗黙的な配列への変換
	inline operator std::array<float, 3u> &() noexcept
	{
		return arr();
	}

	/// @brief 暗黙的な配列への変換
	inline operator const std::array<float, 3u> &() const noexcept
	{
		return arr();
	}

	inline std::array<float, 3u> &arr() noexcept
	{
		return *reinterpret_cast<std::array<float, 3u> *>(this);
	}
	inline const std::array<float, 3u> &arr() const noexcept
	{
		return *reinterpret_cast<const std::array<float, 3u> *>(this);
	}

	static uint32_t size() { return 3u; }

	float *const begin() { return &x; }
	const float *const begin() const { return &x; }
	const float *const cbegin() const { return &x; }

	float *const end() { return begin() + size(); }
	const float *const end() const { return begin() + size(); }
	const float *const cend() const { return begin() + size(); }

	float *const data() { return begin(); }
	const float *const data() const { return begin(); }
	const float *const cdata() const { return begin(); }

private:
};

inline Vector3 operator*(const float &left, const Vector3 &right)
{
	return right * left;
}
struct Quaternion final {
	Quaternion() = default;
	Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
	Quaternion(const Vector3 &vec, float w) : w(w) { this->vec() = vec; };

	float x, y, z;
	float w;

	/// @brief ベクトル部を取得する関数
	/// @return クォータニオンのベクトル部 [ 参照 ]
	inline Vector3 &vec() noexcept { return *reinterpret_cast<Vector3 *>(&x); }
	inline const Vector3 &vec() const noexcept { return *reinterpret_cast<const Vector3 *>(&x); }

	/// @brief 単位クォータニオン
	static const Quaternion &Identity() { static Quaternion val{ 0, 0, 0, 1 }; return val; };

	/// @brief 共役クォータニオン関数
	/// @return 共役クォータニオン
	inline Quaternion Conjugation() const;

	/// @brief 逆クォータニオン関数
	/// @return 逆クォータニオン
	inline Quaternion Inverse() const;

	/// @brief 二乗ノルム
	/// @return 二乗したクォータニオンの長さ
	inline float LengthSQ() const;

	/// @brief ノルム
	/// @return クォータニオンの長さ
	inline float Length() const;

	/// @brief 正規化関数
	/// @return 単位クォータニオン
	inline Quaternion Normalize() const;

	/// @brief 右方向のベクトル
	/// @return 三次元ベクトル
	Vector3 GetRight() const noexcept;

	/// @brief 上方向のベクトル
	/// @return 三次元ベクトル
	Vector3 GetUp() const noexcept;

	/// @brief 前方向のベクトル
	/// @return 三次元ベクトル
	Vector3 GetFront() const noexcept;

	static inline Vector3 RotateVector(const Vector3 &a, const Quaternion &b);
	inline Vector3 RotateVector(const Vector3 &v) const;

	static Quaternion Create(const Vector3 &euler);

	inline Quaternion AnyAxisRotation(const Vector3 &axis, float angle) {
		float halfAngle = angle / 2.f;
		return Quaternion{ axis * std::sin(halfAngle), std::cos(halfAngle) };
	}
};

Quaternion operator/(const Quaternion &left, const float right)
{
	return { left.x / right, left.y / right, left.z / right, left.w / right };
}

inline Quaternion operator*(const Quaternion &a, const Quaternion &b)
{
	Quaternion result;

	// ベクトル部の算出 ( 実数部は Vector3への代入時に切り捨て )
	result.vec() = a.vec().cross(b.vec()) + a.vec() * b.w + b.vec() * a.w;
	// 実数部の算出 ( ドット積で 実数部を切り捨て )
	result.w = a.w * b.w - a.vec() * (b.vec());

	return result;
}

inline Quaternion Quaternion::Conjugation() const
{
	Quaternion result;

	// 符号反転
	result.vec() = -vec();
	// 実数部を戻す
	result.w = this->w;

	return result;
}

inline Quaternion Quaternion::Inverse() const
{
	const float lengthSQ = this->LengthSQ();
	if (lengthSQ == 0.f) {
		return *this;
	}

	Quaternion result;

	result = this->Conjugation() / lengthSQ;

	return result;
}

inline Quaternion Quaternion::Normalize() const
{
	// 長さ
	float length = this->Length();
	// もし長さが0ならそのまま返す( 0なので )
	if (length == 0.f) {
		return *this;
	}

	Quaternion result;
	// ノルムで割る
	result = *this / length;
	return result;
}

inline Vector3 Quaternion::GetRight() const noexcept
{
	return Vector3{ w * w + x * x - y * y - z * z, 2.f * (x * y + w * z), 2.f * (x * z - w * y) };
}

inline Vector3 Quaternion::GetUp() const noexcept
{
	return Vector3{ 2.f * (x * y - w * z), w * w - x * x + y * y - z * z, 2.f * (y * z + w * x) };
}

inline Vector3 Quaternion::GetFront() const noexcept
{
	return Vector3{ 2.f * (x * z + w * y), 2.f * (y * z - w * x), w * w - x * x - y * y + z * z };
}

inline float Quaternion::LengthSQ() const
{
	//__m128 value = static_cast<__m128>(*this);
	return x * x + y * y + z * z + w * w;
}

inline float Quaternion::Length() const
{
	return std::sqrt(LengthSQ());
}

inline Vector3 Quaternion::RotateVector(const Vector3 &a, const Quaternion &b)
{

	return b.RotateVector(a);
}

inline Vector3 Quaternion::RotateVector(const Vector3 &v) const
{
	Quaternion result = *this * Quaternion{ v, 0.f } *this->Conjugation();

	return result.vec();
}

Quaternion Quaternion::Create(const Vector3 &euler) {
	enum SinCos {
		kSin,
		kCos
	};

	const std::array<float, 2u> tX = { std::sin(euler.x / 2.f), std::cos(euler.x / 2.f) };
	const std::array<float, 2u> tY = { std::sin(euler.y / 2.f), std::cos(euler.y / 2.f) };
	const std::array<float, 2u> tZ = { std::sin(euler.z / 2.f), std::cos(euler.z / 2.f) };

	Quaternion result{
		/* x */ tX[kCos] * tY[kSin] * tZ[kSin] + tX[kSin] * tY[kCos] * tZ[kCos],
		/* y */ -tX[kSin] * tY[kCos] * tZ[kSin] + tX[kCos] * tY[kSin] * tZ[kCos],
		/* z */ tX[kCos] * tY[kCos] * tZ[kSin] + tX[kSin] * tY[kSin] * tZ[kCos],
		/* w */ -tX[kSin] * tY[kSin] * tZ[kSin] + tX[kCos] * tY[kCos] * tZ[kCos]
	};

	/*for (uint32_t i = 0u; i < 3u; i++) {
		Vector3 buff{};
		(&buff.x)[2u - i] = 1.f;
		result *= Quaternion::AnyAxisRotation(buff, (&euler.x)[i]);
	}*/

	return result.Normalize();
}

struct Dice {
	enum  Direction {
		kNorth,
		kEast,
		kSouth,
		kWest,
	};

	std::array<uint32_t, 6u> faceNum_{};
	// 上を向いている面のインデックス
	Quaternion facing_ = Quaternion::Identity();

	Dice Move(Direction direction)
	{
		Dice result = *this;

		Vector3 rotate{};
		switch (direction % 2) {
		case 0:
			rotate.x = -hPI;
			break;
		case 1:
			rotate.z = hPI;
			break;
		default:
			break;
		}
		if (direction >= 2) {
			rotate *= -1;
		}

		result.facing_ = (result.facing_ * Quaternion::Create(rotate)).Normalize();

		/*Vector3 upVec = result.facing_.GetUp();
		std::cout << upVec.x << ' ' << upVec.y << ' ' << upVec.z << ' ' << result.GetFaceNum() << std::endl;*/

		return result;
	}

	uint32_t GetFaceNum() const
	{
		uint32_t index{};
		Vector3 upVec = facing_.GetUp();
		float buf{};
		uint32_t bufInd{};
		for (uint32_t i = 0; i < 3; i++) {
			if (buf < std::abs(upVec[i])) {
				buf = std::abs(upVec[i]);
				bufInd = i;
			}
		}
		switch (bufInd) {
		case 0:
			index = 2;
			break;
		case 1:
			index = 0;
			break;
		case 2:
			index = 4;
			break;
		default:
			break;
		}

		if ((upVec.x + upVec.y + upVec.z) < 0.f) {
			index = 5 - index;
		}

		return faceNum_[index];
	}
};

int main()
{

	// 面のデータを取得する
	Dice dice;
	for (auto &face : dice.faceNum_) {
		std::cin >> face;
	}
	// ダイスの操作
	std::string movement;
	std::cin >> movement;

	for (const char item : movement) {
		if (item == '\0') { break; }
		switch (item) {
		case 'N':
			dice = dice.Move(Dice::Direction::kNorth);
			break;
		case 'E':
			dice = dice.Move(Dice::Direction::kEast);
			break;
		case 'S':
			dice = dice.Move(Dice::Direction::kSouth);
			break;
		case 'W':
			dice = dice.Move(Dice::Direction::kWest);
			break;
		default:
			break;
		}


	}
	std::cout << dice.GetFaceNum() << std::endl;



	return 0;
}
