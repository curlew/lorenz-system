#include <fstream>

struct vector3 {
    double x, y, z;

    vector3 &operator+=(const vector3 &rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        return *this;
    }

    // scalar multiplication
    vector3 operator*(double rhs) const {
        return vector3{this->x * rhs, this->y * rhs, this->z * rhs};
    }
};

class lorenz_system {
    const double m_sigma, m_rho, m_beta;

public:
    lorenz_system(double sigma, double rho, double beta) : m_sigma{sigma}, m_rho{rho}, m_beta{beta} {}

    vector3 operator()(const vector3 &s) const {
        // Lorenz model ordinary differential equations
        return vector3{
            .x = m_sigma * (s.y - s.x),
            .y = m_rho * s.x - s.x * s.z - s.y,
            .z = s.x * s.y - m_beta * s.z,
        };
    }
};

int main() {
    // System parameters
    const double sigma = 10;
    const double rho = 28;
    const double beta = 8.0 / 3.0;

    // Initial conditions
    vector3 state = {.x = 1, .y = 1, .z = 1};

    lorenz_system lorenz(sigma, rho, beta);

    const double step = 0.001;
    const double time_end = 75;

    std::ofstream points_file("points.txt");
    points_file << state.x << "," << state.y << "," << state.z << "\n";
    // solve ODEs w/ Euler's method
    for (int i = 1; i < time_end / step; ++i) {
        vector3 change = lorenz(state) * step;
        state += change;
        points_file << state.x << "," << state.y << "," << state.z << "\n";
    }
}
