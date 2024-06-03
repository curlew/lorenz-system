#include <fstream>

struct vector3 {
    double x, y, z;

    // scalar multiplication
    vector3 operator*(double rhs) const {
        return {x * rhs, y * rhs, z * rhs};
    };

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

int main(int argc, char *argv[]) {
    std::ofstream points("points.csv");
    points << "x,y,z\n";

    lorenz_system lorenz;

    // initial conditions
    vector3 state = {1.0, 1.0, 1.0};

    const double step = 0.001;

    points << state << "\n";
    for (int n = 1; n < std::ceil(75 / step); ++n) {
        // solve with Euler's method
        vector3 change = lorenz(state) * step;
        state += change;
        points << state << "\n";
    }
}
