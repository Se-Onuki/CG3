#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <vector>

// 可変長行列
class ResizeableMatrix {
public:
	using T = size_t;

	ResizeableMatrix(size_t y = 0u, size_t x = 0u)
		: x_(x), y_(y)
	{
		data_ = std::make_unique<T[]>(x * y);
	}
	ResizeableMatrix(const ResizeableMatrix &) = default;
	ResizeableMatrix(ResizeableMatrix &&) = default;
	ResizeableMatrix &operator=(const ResizeableMatrix &) = default;
	ResizeableMatrix &operator=(ResizeableMatrix &&) = default;

	size_t GetX() const { return x_; }
	size_t GetY() const { return y_; }
	size_t size() const { return x_ * y_; }

	using iterator = T *;
	using const_iterator = const T *;

	/// @brief 要素へのアクセス
	/// @return 要素
	T &at(size_t y, size_t x) { return data_[x + x_ * y]; }
	T at(size_t y, size_t x) const { return data_[x + x_ * y]; }

	/// @brief 各行の先頭イテレータを取得する
	iterator atLine(size_t y) { return data_.get() + x_ * y; }
	const_iterator atLine(size_t y) const { return data_.get() + x_ * y; }

	std::unique_ptr<T[]> GetLine(size_t y) const {
		std::unique_ptr<T[]> result = std::make_unique<T[]>(x_);

		std::copy(this->begin() + x_ * y, this->begin() + x_ * (y + 1), result.get());

		return std::move(result);
	}
	std::unique_ptr<T[]> GetVerticalLine(size_t x) const
	{
		std::unique_ptr<T[]> result = std::make_unique<T[]>(y_);
		for (size_t y = 0; y < y_; ++y) {
			result[y] = at(y, x);
		}
		return std::move(result);
	}

	/// @brief 行列の積
	/// @param other 別の行列
	/// @return 行列
	ResizeableMatrix operator*(const ResizeableMatrix &other) const
	{
		// もし行列のサイズが異なる場合はエラー
		if (x_ != other.y_) {
			return ResizeableMatrix{};
		}
		// 右辺を転置
		ResizeableMatrix right(other.x_, other.y_);
		{
			auto rightItr = right.begin();
			for (size_t y = 0; y < right.y_; ++y) {
				for (size_t x = 0; x < right.x_; ++x) {
					// 転置して代入
					*rightItr++ = other.at(x, y);
				}
			}
		}
		ResizeableMatrix result(y_, other.x_);
		{
			auto resultItr = result.begin();

			// 各行の要素をドット積で計算して、resultに代入
			for (size_t y = 0; y < y_; ++y) {
				const_iterator rightItr = right.begin();
				for (size_t i = 0; i < right.GetY(); ++i) {
					const_iterator leftItr = this->atLine(y);
					for (size_t inX = 0; inX < x_; ++inX) {
						*resultItr += *leftItr++ * *rightItr++;
					}
					resultItr++;
				}
			}
		}

		return result;
	}

	/// @brief 文字列化
	/// @param os 出力ストリーム
	/// @param matrix 入力
	/// @return ストリーム
	friend std::ostream &operator<<(std::ostream &os, const ResizeableMatrix &matrix)
	{
		auto itr = matrix.begin();

		for (T y = 0; y < matrix.y_; ++y) {
			for (T x = 0; x < matrix.x_; ++x) {
				os << *itr++;
				if (x < matrix.x_ - 1) {
					os << ' ';
				}
			}
			//if (y < matrix.y_ - 1) {
			os << std::endl;
			//}
		}
		return os;
	}

	iterator begin() { return data_.get(); }
	iterator end() { return data_.get() + size(); }

	const_iterator begin() const { return data_.get(); }
	const_iterator end() const { return data_.get() + size(); }

	operator bool() const { return not x_ or not y_; }

private:
	size_t x_, y_;
	std::unique_ptr<T[]> data_;
};

// 行列同士の計算

int main(void)
{

	size_t n, m, l;
	std::cin >> n >> m >> l;

	ResizeableMatrix a(n, m);
	ResizeableMatrix b(m, l);
	for (auto &itr : a) {
		std::cin >> itr;
	}
	for (auto &itr : b) {
		std::cin >> itr;
	}
	std::cout << a * b;

	return 0;
}