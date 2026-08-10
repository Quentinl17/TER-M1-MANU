#pragma once
#include "class_mesh.hpp"
#include "class_field.hpp"
#include "class_rsmatrix.hpp"

template<typename T>
class time_loop
{
    public :
        time_loop(mesh_1d<T> const& msh, T final_time, size_t Nt, T nu, T alpha)
            : mesh_(msh), 
              final_time_(final_time), 
              n_time_(Nt),
              RSmatrix_(msh, nu, alpha)
              {};

        ~time_loop(){};

        inline const T final_time() const { return final_time_; };
        inline const Matrix<T>& intermediate_solutions() const { return intermediate_solutions_; };
        void run(field<T>& uh);

    protected :
        size_t n_time_{0};
        T dt_{0.};
        T final_time_{0.};

        mesh_1d<T> const& mesh_;
        rsmatrix<T> RSmatrix_;

        Matrix<T> intermediate_solutions_;
};

// ----- Definitions -----
template<typename T>
void time_loop<T>::run(field<T>& uh)
{
    if(n_time_ == 0)
    {
        std::cout << "Error : no time subdivision !" << std::endl;
        abort();
    }

    dt_ = final_time_ / n_time_;
    RSmatrix_.assemble(dt_);
    intermediate_solutions_ = Matrix<T>::Zero(mesh_.n_cells() + 1, 4);

    // Calculs des temps à stocker
    std::vector<size_t> save_times;
    for(size_t kk = 0; kk < 4; kk++)    
    {
        save_times.push_back((kk + 1) * n_time_ / 8);
    }

    // Conditions de Dirichlet homogènes
    uh(0) = 0.;
    uh(mesh_.n_cells()) = 0.;

    // "Vectorisation" pour le type des calculs 
    Vector<T> u(mesh_.n_cells() - 1);
    for(size_t ii = 0; ii < mesh_.n_cells() - 1; ii++)
    {
        u(ii) = uh(ii + 1);
    }

    // Calcul de la solution
    for(size_t tt = 1; tt <= n_time_; tt++)
    {
        u = RSmatrix_.acces_Ainv() * (RSmatrix_.acces_B() * u + dt_ * RSmatrix_.acces_F());
        
        for(size_t ii = 0; ii < 4; ii++)
        {
            if(tt == save_times[ii])
            {
                intermediate_solutions_.col(ii).segment(1, mesh_.n_cells() - 1) = u;
            }
        }

    }

    // Passage en type field
    for(size_t ii = 0; ii < mesh_.n_cells() - 1; ii++)
    {
        uh(ii + 1) = u(ii);
    }
}