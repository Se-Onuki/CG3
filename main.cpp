#include <iostream>
#include <stdint.h>

template <typename T>
class ValuePair
{
public:
	ValuePair(T a, T b);
	~ValuePair() = default;

	const T &Min() const {
		return std::min<T>(a_, b_);
	}

	friend std::ostream &operator<<(std::ostream &os, const ValuePair<T> &obj) {
		os << "ValuePair<" << typeid(T).name() << ">: " << obj.a_ << ", " << obj.b_ << " => Min(" << obj.Min() << ")";
		return os;
	}

private:
	T a_;
	T b_;

};
template <typename T>
ValuePair<T>::ValuePair(T a, T b) : a_(a), b_(b) {}

int main(void) {
	std::cout << ValuePair{ 1, 5 } << std::endl;
	std::cout << ValuePair{8.f, 5.f} << std::endl;
	std::cout << ValuePair{153.0, 325.0} << std::endl;

	return 0;
}