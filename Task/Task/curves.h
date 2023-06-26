#pragma once

#include <concepts>
#include <cmath>
#include <numbers>
#include <iostream>

namespace curves {

	/// <summary>
	/// Point struct {x, y, z}
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<std::floating_point T>
	struct Point {
		T x, y, z;

		template<std::floating_point K>
		friend std::ostream& operator<<(std::ostream&, const Point<K>&);
	};

	/// <summary>
	/// Abstract class curve with methods C(t) and dC(t)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<std::floating_point T>
	class Curve {
		public:
			virtual Point<T> C(T t) = 0;
			virtual Point<T> dC(T t) = 0;
	};

	/// <summary>
	/// Helix curve {a, b, step} (a == b)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<std::floating_point T>
	class Helix : public Curve<T> {
		public:
			T a, b, step;

		protected:
			Helix(T, T, T);

		public:
			Helix(T, T);
			Point<T> C(T) override;
			Point<T> dC(T) override;
			virtual ~Helix();
	};

	/// <summary>
	/// Ellipse curve (step == 0)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<std::floating_point T>
	class Ellipse : public Helix<T> {
		public:
			Ellipse(T, T);
			~Ellipse();
	};

	/// <summary>
	/// Circle curve (a == b, step == 0)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<std::floating_point T>
	class Circle : public Ellipse<T> {
		public:
			Circle(T);
			~Circle();
	};
}

