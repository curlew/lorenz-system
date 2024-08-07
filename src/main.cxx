#include <cmath>
#include <fstream>

struct vector3 {
    double x, y, z;

    vector3 &operator+=(const vector3 &rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const vector3 &v) {
        return os << v.x << "," << v.y << "," << v.z;
    }
};

vector3 operator*(double scalar, const vector3 &v) {
    return {scalar * v.x, scalar * v.y, scalar * v.z};
}
vector3 operator+(const vector3 &lhs, const vector3 &rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}


class lorenz_system {
    // system parameters
    const double m_sigma, m_rho, m_beta;

public:
    lorenz_system(double sigma = 10, double rho = 28, double beta = 8.0 / 3.0)
        : m_sigma{sigma}
        , m_rho{rho}
        , m_beta{beta} { }

    vector3 operator()(const vector3 &s) const {
        return {
            .x = m_sigma * (s.y - s.x),
            .y = m_rho * s.x - s.x * s.z - s.y,
            .z = s.x * s.y - m_beta * s.z
        };
    }
};

class rossler_system {
    const double m_a, m_b, m_c;

public:
    rossler_system(double a = 0.1, double b = 0.1, double c = 14)
        : m_a{a}
        , m_b{b}
        , m_c{c} { }

    vector3 operator()(const vector3 &s) const {
        return {
            .x = -s.y - s.z,
            .y = s.x + m_a * s.y,
            .z = m_b + s.z * (s.x - m_c)
        };
    }
};

int main(int argc, char *argv[]) {
    std::ofstream points("points.csv");
    points << "x,y,z\n";

    lorenz_system lorenz;

    // initial conditions
    vector3 state = {1.0, 1.0, 1.0};

    const double step = 0.01;

    points << state << "\n";
    for (int n = 1; n < std::ceil(100 / step); ++n) {
        // RK4
        vector3 k1 = lorenz(state);
        vector3 k2 = lorenz(state + step * 0.5 * k1);
        vector3 k3 = lorenz(state + step * 0.5 * k2);
        vector3 k4 = lorenz(state + step * k3);
        vector3 change = (step / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
        state += change;
        points << state << "\n";
    }
}
