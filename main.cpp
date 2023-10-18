#include <iostream>
#include <stdint.h>

template <typename T1, typename T2>
class ValuePair
{
public:
	ValuePair(T1 a, T2 b);
	~ValuePair() = default;

	const T1 &Min() const {
		return std::min<T1>(a_, static_cast<T1>(b_));
	}

	friend std::ostream &operator<<(std::ostream &os, const ValuePair<T1, T2> &obj) {
		os << "ValuePair<" << typeid(T1).name() << ", " << typeid(T2).name() << ">: " << obj.a_ << ", " << obj.b_ << " => Min<" << typeid(T1).name() << ">(" << obj.Min() << ")";
		return os;
	}

private:
	T1 a_;
	T2 b_;

};
template <typename T1, typename T2>
ValuePair<T1, T2>::ValuePair(T1 a, T2 b) : a_(a), b_(b) {}

int main(void) {
	std::cout << ValuePair{ 1, 5.f } << std::endl;
	std::cout << ValuePair{ 153, 325.0 } << std::endl;

	std::cout << ValuePair{ 8.f, 5 } << std::endl;
	std::cout << ValuePair{ 153.f, 325.0 } << std::endl;

	std::cout << ValuePair{ 1.0, 5 } << std::endl;
	std::cout << ValuePair{ 8.0, 5.f } << std::endl;

	return 0;
}