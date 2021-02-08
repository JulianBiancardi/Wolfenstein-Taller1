#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_RANDOMIZER_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_RANDOMIZER_H_

#include <cmath>
#include <random>
#include <type_traits>

template <class T>
using uniform_distribution = typename std::conditional<
    std::is_floating_point<T>::value, std::uniform_real_distribution<T>,
    typename std::conditional<std::is_integral<T>::value,
                              std::uniform_int_distribution<T>,
                              void>::type>::type;

template <class T>
class Randomizer {
 public:
  Randomizer() {}
  T operator()(T start_range, T end_range) {
    std::random_device rd;     // Creo la semilla (toma info aleatoria del SO)
    std::mt19937_64 mt(rd());  // Genero un valor pseudo-aleatorio de 64 bits.
    uniform_distribution<T> rand_num(start_range, end_range);
    return (rand_num(mt));  // It was the ERROR
  }
};

#endif  // WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_RANDOMIZER_H_
