#ifndef RANDOM_GEN_HPP
#define RANDOM_GEN_HPP

#include <random>
#include <limits>

namespace rng {

inline std::mt19937 engine;

/// @brief Initialize randomgenerator
inline void InitializeRng() {
    std::random_device dev;
    rng::engine = std::mt19937{dev()};
}

/// @brief Get int in range [min, max] (inclusive)
inline unsigned int RandomInt(unsigned int min = 0, int max = std::numeric_limits<unsigned int>::max()) {
    std::uniform_int_distribution<std::default_random_engine::result_type> d(min, max);
    return d(engine);
}

/// @brief Get random float between 0.0F and 1.0F
inline float RandomF() {
    std::uniform_real_distribution<float> f(0.0F, 1.0F);
    return f(engine);
}


}


#endif
