#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <vector>

// 可変長行列
class ResizeableMatrix {
public:
    ResizeableMatrix(size_t y = 0u, size_t x = 0u)
        : x_(x), y_(y)
    {
        data_.resize(x * y);
    }
    ResizeableMatrix(const ResizeableMatrix &) = default;
    ResizeableMatrix(ResizeableMatrix &&) = default;
    ResizeableMatrix &operator=(const ResizeableMatrix &) = default;
    ResizeableMatrix &operator=(ResizeableMatrix &&) = default;

    size_t GetX() const { return x_; }
    size_t GetY() const { return y_; }
    size_t size() const { return data_.size(); }

    using iterator = std::vector<size_t>::iterator;
    using const_iterator = std::vector<size_t>::const_iterator;

    /// @brief 要素へのアクセス
    /// @return 要素
    size_t &at(size_t y, size_t x) { return data_[x + x_ * y]; }
    size_t at(size_t y, size_t x) const { return data_[x + x_ * y]; }

    /// @brief 各行の先頭イテレータを取得する
    iterator atLine(size_t y) { return data_.begin() + x_ * y; }
    const_iterator atLine(size_t y) const { return data_.begin() + x_ * y; }

    std::vector<size_t> GetLine(size_t y) const { return std::vector<size_t>(data_.begin() + x_ * y, data_.begin() + x_ * (y + 1)); }
    std::vector<size_t> GetVerticalLine(size_t x) const
    {
        std::vector<size_t> result(y_);
        for (size_t y = 0; y < y_; ++y) {
            result[y] = at(y, x);
        }
        return result;
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
        // 左辺を転置
        ResizeableMatrix left(other.x_, other.y_);
        {
            auto leftItr = left.data_.begin();
            for (size_t y = 0; y < other.y_; ++y) {
                for (size_t x = 0; x < other.x_; ++x) {
                    // 転置して代入
                    *leftItr++ = other.at(x, y);
                }
            }
        }
        ResizeableMatrix result(y_, other.x_);
        {
            auto resultItr = result.data_.begin();
            // 各行の要素をドット積で計算して、resultに代入
            for (size_t y = 0; y < result.y_; ++y) {
                const_iterator rightItr = this->atLine(y);
                for (size_t x = 0; x < result.x_; ++x) {
                    const_iterator leftItr = left.begin();
                    for (size_t inX = 0; inX < x_; ++inX) {
                        *resultItr += *rightItr++ * *leftItr++;
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
        auto itr = matrix.data_.begin();

        for (size_t y = 0; y < matrix.y_; ++y) {
            for (size_t x = 0; x < matrix.x_; ++x) {
                os << *itr++ << " ";
            }
            os << std::endl;
        }
        return os;
    }

    iterator begin() { return data_.begin(); }
    iterator end() { return data_.end(); }

    operator bool() const { return not x_ or not y_; }

private:
    size_t x_, y_;
    std::vector<size_t> data_;
};

// 行列同士の計算

int main(void)
{

    size_t x, y;
    std::cin >> y >> x;
	size_t totalSum = 0;

    ResizeableMatrix a(y, x);
    for (auto &itr : a) {
        std::cin >> itr;
    }
    // 各行ごとに表示
    for (uint16_t i = 0; i < a.GetY(); i++) {
        const auto &line = a.GetLine(i);
        for (const size_t item : line) {
            std::cout << item << " ";
        }
        size_t sum = std::accumulate(line.begin(), line.end(), 0);
        std::cout << sum << std::endl;
    }

    // 各行の合計値を返す
    for (uint16_t i = 0; i < a.GetX(); i++) {
        // 各列の合計値を返す
        const auto &itr = a.GetVerticalLine(i);
        size_t sum = std::accumulate(itr.begin(), itr.end(), 0);
        std::cout << sum << " ";
		totalSum += sum;
    }
	std::cout << totalSum << std::endl;
}