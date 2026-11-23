#pragma once
#include <cmath>

// ----- Definitions of functions -----
// --- Initial ---
// fonction porte
template<typename T>
T creneau(T xx)
{
    return static_cast<T>(1);
}

// donnée oscillante à hautes fréquences
template<typename T>
T sin_pulse(T xx)
{
    return sin(3.14 * xx) + sin(3.14 * 10. * xx);
};

// --- Second member ---
template<typename T>
T pression_cte(T xx)
{
    return static_cast<T>(-1);
};