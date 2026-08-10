#pragma once
#include <fstream>
#include "class_mesh.hpp"
#include "class_field.hpp"
#include "class_time_loop.hpp"


template<typename T>
class output_writer
{
    public :
        output_writer(mesh_1d<T> const& msh, std::string filename): mesh_(msh), radical_name_(filename){};

        ~output_writer(){};

        void write_solution(field<T> solution, std::string loop_counter);
        void write_solution(Vector<T> solution, std::string loop_counter);
        inline const mesh_1d<T>& mesh() const { return mesh_; };

    protected :
        mesh_1d<T> const& mesh_;
        std::string radical_name_;
};

// ===== Definitions ===== //
template<typename T>
void output_writer<T>::write_solution(field<T> solution, std::string loop_counter)
{
    std::string filename = radical_name_ + "_" + loop_counter + ".txt";
    std::ofstream my_file(filename);

    for(size_t ii = 0; ii < mesh_.n_cells() + 1; ii++)
    {
        my_file << mesh_.xv(ii) << " " << solution(ii) << std::endl;
    }
    
    my_file.close();
}

template<typename T>
void output_writer<T>::write_solution(Vector<T> solution, std::string loop_counter)
{
    std::string filename = radical_name_ + "_" + loop_counter + ".txt";
    std::ofstream my_file(filename);

    for(size_t ii = 0; ii < mesh_.n_cells() + 1; ii++)
    {
        my_file << mesh_.xv(ii) << " " << solution(ii) << std::endl;
    }
    
    my_file.close();
}