#include "curves.h"

namespace curves {
	template<std::floating_point K>
	std::ostream& operator<<(std::ostream& out, const Point<K>& p)
	{
		return out << "{" << p.x << ", " << p.y << ", " << p.z << "}";
	}

	template struct Point<long double>;
	template struct Point<double>;
	template struct Point<float>;
	template std::ostream& operator<<(std::ostream& os, const Point<long double>& other);
	template std::ostream& operator<<(std::ostream& os, const Point<double>& other);
	template std::ostream& operator<<(std::ostream& os, const Point<float>& other);

	template<std::floating_point T>
	Helix<T>::Helix(T _a, T _b, T _step) : a(std::abs(_a)), b(std::abs(_b)), step(_step) { }

	template<std::floating_point T>
	Helix<T>::Helix(T _a, T _step) : Helix(_a, _a, _step) { }

	template<std::floating_point T>
	Point<T> Helix<T>::C(T t) {
		return { a * std::cos(t), b * std::sin(t), step * t / T(2.0) / std::numbers::pi_v<T> };
	}

	template<std::floating_point T>
	Point<T> Helix<T>::dC(T t) {
		return { -a * std::sin(t), b * std::cos(t), step / T(2.0) / std::numbers::pi_v<T> };
	}

	template<std::floating_point T>
	Helix<T>::~Helix() {}

	template class Helix<long double>;
	template class Helix<double>;
	template class Helix<float>;

	template<std::floating_point T>
	Ellipse<T>::Ellipse(T _a, T _b) : Helix<T>(_a, _b, 0.0) { }

	template<std::floating_point T>
	Ellipse<T>::~Ellipse() {}

	template class Ellipse<long double>;
	template class Ellipse<double>;
	template class Ellipse<float>;

	template<std::floating_point T>
	Circle<T>::Circle(T _a) : Ellipse<T>(_a, _a) { }

	template<std::floating_point T>
	Circle<T>::~Circle() {}

	template class Circle<long double>;
	template class Circle<double>;
	template class Circle<float>;
}