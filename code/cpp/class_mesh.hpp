#pragma once
#include <iostream>
#include <Eigen/Dense>

template<typename T>
using Vector = Eigen::Matrix<T, Eigen::Dynamic, 1>;

template<typename T>
class mesh_1d
{
    public :
        mesh_1d(T x_left, T x_right, size_t n_cells);

        ~mesh_1d(){};

        inline const size_t n_vertices() const { return n_vertices_ ;};
        inline const size_t n_cells() const { return n_cells_; };
        inline const T dx() const { return dx_; };
        inline T xv(size_t ii) const { return vertices_coordinates_[ii]; };

        void print();

    protected :
        Vector<T> vertices_coordinates_;
        size_t n_vertices_{0};
        size_t n_cells_{0};
        T dx_;
};

// ===== Definitions ===== //
template<typename T>
mesh_1d<T>::mesh_1d(T x_left, T x_right, size_t n_cells) : n_cells_(n_cells), n_vertices_(n_cells + 1), vertices_coordinates_(n_cells + 1)
{   
    if(x_left == x_right)
    {
        std::cout << "Error : x_left and x_right must be different !" << std::endl;
        abort();
    }

    if(n_cells == 0)
    {
        std::cout << "Error : number of cells must be strictly positive !" << std::endl;
        abort();
    }

    dx_ = (x_right - x_left) / n_cells;

    for(size_t ii = 0; ii < n_vertices_; ii++)
    {
        vertices_coordinates_[ii] = x_left +  ii * dx_;
    }
}

template<typename T>
void mesh_1d<T>::print()
{
    std::cout << "The meshes definitions :" << std::endl;

    std::cout << "- Number of cells : " << n_cells_ << std::endl;
    std::cout << "- Number of vertices : " << n_vertices_ << std::endl;
    std::cout << "- Step : " << dx_ << std::endl;

    std::cout << "- Vertices coordinates : [";
    for(size_t ii = 0; ii < n_vertices_ - 1; ii++)
    {
        std::cout << vertices_coordinates_[ii] << ", ";
    }
    std::cout << vertices_coordinates_[n_vertices_ - 1] << "]" << std::endl;
}