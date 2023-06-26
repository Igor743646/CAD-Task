#include <iostream>
#include "curves.h"
#include <vector>
#include <random>
#include <memory>
#include <algorithm>

using namespace std;
using namespace curves;
using test_type = long double;
using container_type = shared_ptr<Curve<test_type>>;
constexpr test_type pi = numbers::pi_v<test_type>;

template<floating_point T>
T floating_rand(T low, T high) {
    return low + static_cast<T>(rand()) / (static_cast<T>(RAND_MAX / (high - low)));
}

int main()
{
    srand((unsigned int)time(nullptr));
        
    vector<container_type> v;

    const size_t vector_len = 10;

    for (size_t i = 0; i < vector_len; i++) {
        int r_type = rand() % 3;
        test_type a = floating_rand<test_type>(-1000, 1000);
        test_type b = floating_rand<test_type>(-1000, 1000);
        test_type step = floating_rand<test_type>(-1000, 1000);

        switch (r_type) {
        case 0:
            v.push_back(make_shared<Helix<test_type>>(a, step));
            break;
        case 1:
            v.push_back(make_shared<Ellipse<test_type>>(a, b));
            break;
        case 2:
            v.push_back(make_shared<Circle<test_type>>(a));
            break;
        }
    }

    for (size_t i = 0; i < vector_len; i++) {
        cout << "[" << i << "] point: " << v[i]->C(0.25 * pi) 
            << " derivative: " << v[i]->dC(0.25 * pi) << endl;
    }

    vector<container_type> v_only_circles;

    for (auto& elem_p : v) {
        if (dynamic_cast<Circle<test_type>*>(elem_p.get())) {
            v_only_circles.push_back(elem_p);
        }
    }

    sort(begin(v_only_circles), end(v_only_circles), [](const container_type& a, const container_type& b) {
        return dynamic_cast<Circle<test_type>*>(a.get())->a < dynamic_cast<Circle<test_type>*>(b.get())->a;
    });

    test_type total_sum = test_type(0.0);

    for (auto& elem_p : v_only_circles) {
        test_type r = dynamic_cast<Circle<test_type>*>(elem_p.get())->a;
        total_sum += r;
    }

    cout << "Total sum of radii of all circles : " << total_sum << endl;

    return 0;
}