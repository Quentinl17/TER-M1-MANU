#pragma once
#include <filesystem>
#include "class_mesh.hpp"
#include "class_field.hpp"
#include "class_output_writer.hpp"
#include "class_rsmatrix.hpp"

template<typename T>
class time_loop
{
    public :
        time_loop(mesh_1d<T> const& msh, T final_time, size_t Nt, T nu, T alpha)
            : mesh_(msh), 
              final_time_(final_time), 
              n_time_(Nt),
              RSmatrix_(msh, nu, alpha),
              times_(Nt + 1)
              {};

        ~time_loop(){};

        const T final_time() const { return final_time_; };
        const Vector<T>& get_times() const { return times_; };
        void run(field<T>& uh);

    protected :
        size_t n_time_{0};
        T dt_{0.};
        T final_time_{0.};

        mesh_1d<T> const& mesh_;
        rsmatrix<T> RSmatrix_;

        Vector<T> times_;
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

    std::filesystem::remove_all("RS_solutions");
    std::filesystem::create_directories("RS_solutions");
    output_writer<T> out_stream(mesh_, "RS_solutions/solution");

    out_stream.write_solution(uh, std::to_string(0));

    dt_ = final_time_ / n_time_;
    RSmatrix_.assemble(dt_);

    // Conditions de Dirichlet homogènes
    uh(0) = 0.;
    uh(mesh_.n_cells()) = 0.;

    // "Vectorisation" pour le type des calculs 
    Vector<T> u(mesh_.n_cells() - 1);
    for(size_t ii = 0; ii < mesh_.n_cells() - 1; ii++)
    {
        u(ii) = uh(ii + 1);
    }

    times_[0] = static_cast<T>(0);
    for(size_t kk = 1; kk <= n_time_; kk++)
    {
        // Stockage des temps
        times_[kk] = dt_ * kk;
        // Calcul de la solution à chaque temps
        u = RSmatrix_.acces_Ainv() * (RSmatrix_.acces_B() * u + dt_ * RSmatrix_.acces_F());
        // Passage en type field
        for(size_t ii = 0; ii < mesh_.n_cells() - 1; ii++)
        {
            uh(ii + 1) = u(ii);
        }
        // Affichage des solutions à chaque pas de temps
        out_stream.write_solution(uh, std::to_string(kk));
    }
}