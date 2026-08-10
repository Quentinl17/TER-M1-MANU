#pragma once
#include <cmath>
#include "class_mesh.hpp"

// ----- Definitions of functions -----
// --- Initial ---
double creneau(double xx)
{
    return 1.;
}

// donnée oscillante à hautes fréquences
double sin_pulse(double xx)
{
    return sin(3.14 * xx); //+ sin(3.14 * 10. * xx);
};

// --- Second member ---
double pression_cte(double xx)
{
    return -1.;
};


// ----- Definition of class field -----
template<typename T>
class field
{
    public :
        field(int test_label, mesh_1d<T> const& msh);

        ~field(){};

        inline const size_t n_cells() const { return n_cells_; };
        inline const Vector<T>& operator()() const { return values_; };
        inline T operator()(size_t ii) const { return values_[ii]; };
        inline T& operator()(size_t ii){ return values_[ii]; };

    protected :
        size_t n_cells_{0};
        Vector<T> values_;
};

// ----- Definitions -----
template<typename T>
field<T>::field(int test_label, mesh_1d<T> const& msh): n_cells_(msh.n_cells() + 1), values_(n_cells_)
{
    if(test_label == 0)
    {
        for(size_t ii = 0; ii < n_cells_; ii++)
        {
            values_[ii] = creneau(msh.xv(ii));
        }
    }

    if(test_label == 1)
    {
        for(size_t ii = 0; ii < n_cells_; ii++)
        {
            values_[ii] = sin_pulse(msh.xv(ii));
        }
    }
}