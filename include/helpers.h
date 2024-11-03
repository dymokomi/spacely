#include <cmath>
namespace spacely {
    inline double linear_to_gamma(double linear_component, double gamma = 2.2) {   
        if (linear_component > 0)
            return std::pow(linear_component, (1.0/gamma));

        return 0;
    }
}