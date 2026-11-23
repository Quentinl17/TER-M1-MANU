#pragma once
#include <fstream>
#include "class_mesh.hpp"
#include "class_field.hpp"


template<typename T>
class output_writer
{
    public :
        output_writer(mesh_1d<T> const& msh, std::string filename): mesh_(msh), radical_name_(filename){};

        ~output_writer(){};

        void write_solution(field<T> const& solution, std::string loop_counter);
        void get_times(Vector<T> const& times, std::string loop_counter);
        
        const mesh_1d<T>& mesh() const { return mesh_; };

    protected :
        mesh_1d<T> const& mesh_;
        std::string radical_name_;
};

// ----- Definitions ----- //
template<typename T>
void output_writer<T>::write_solution(field<T> const& solution, std::string loop_counter)
{
    std::string filename = radical_name_ + "_" + loop_counter + ".txt";
    std::ofstream my_file(filename);

    for(size_t ii = 0; ii < mesh_.n_vertices(); ii++)
    {
        my_file << mesh_.xv(ii) << " " << solution(ii) << std::endl;
    }
    
    my_file.close();
}

template<typename T>
void output_writer<T>::get_times(Vector<T> const& times, std::string loop_counter)
{
    std::string filename = radical_name_ + "_" + loop_counter + ".txt";
    std::ofstream my_file(filename);

    for(size_t ii = 0; ii < times.size(); ii++)
    {
        my_file << times[ii] << std::endl;
    }

    my_file.close();
}