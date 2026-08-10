#pragma once
#include "class_mesh.hpp"

template<typename T>
using Matrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;

template<typename T>
class rsmatrix
{
    public :
        rsmatrix(mesh_1d<T> const& mesh, T nu, T alpha)
            : A_inv_(Matrix<T>::Zero(mesh.n_cells() - 1, mesh.n_cells() - 1)), 
              B_(Matrix<T>::Zero(mesh.n_cells() - 1, mesh.n_cells() - 1)), 
              F_(mesh.n_cells() - 1), 
              mesh_(mesh), 
              nu_(nu), 
              alpha_(alpha)
              {};

        ~rsmatrix(){};

        inline const Matrix<T>& acces_Ainv() const { return A_inv_; };
        inline const Matrix<T>& acces_B() const { return B_; };
        inline const Vector<T>& acces_F() const { return F_; };
        inline const T nu() const { return nu_; };
        inline const T alpha() const { return alpha_; };
        const mesh_1d<T>& mesh() const { return mesh_; };

        void assemble(T dt);

    protected :
        Matrix<T> A_inv_;
        Matrix<T> B_;
        Vector<T> F_;

        mesh_1d<T> const& mesh_;

        T nu_;
        T alpha_;
};

// ----- Definitions -----
template<typename T>
void rsmatrix<T>::assemble(T dt)
{
    std::size_t n = mesh_.n_cells() - 1;
    T dx = mesh_.dx();

    Matrix<T> I = Matrix<T>::Identity(n, n);
    Matrix<T> Laplacian = Matrix<T>::Zero(n, n);

    for(std::size_t ii = 0; ii < n ; ii++)
    {
        Laplacian(ii, ii) = - 2. / (dx * dx);

        if(ii > 0)
        {
            Laplacian(ii, ii - 1) = 1. / (dx * dx);
        }
        if(ii < n - 1)
        {
            Laplacian(ii, ii + 1) = 1. / (dx * dx);
        }
    }

    A_inv_ = (I - (nu_ * dt + alpha_) * Laplacian).inverse();
    B_ = I - alpha_ * Laplacian;

    for(std::size_t ii = 0; ii < n; ii++)
    {
        // F_[ii] = pression_cte(mesh_.xv(ii));
        F_[ii] = 0.;
    }
}