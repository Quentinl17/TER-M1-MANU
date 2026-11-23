#include "class_mesh.hpp"
#include "class_field.hpp"
#include "class_time_loop.hpp"
#include "class_output_writer.hpp"

int main()
{
    // needed initialization parameters
    double x_left = 0.;
    double x_right = 1.;
    size_t Ne = 100;
    size_t Nt = 100;
    double final_time = 1.;
    int CRENEAU = 0;
    int SIN_PULSE = 1;

    double nu = 0.1;
    double alpha = 5 * 1e-2;

    // mesh construction
    mesh_1d<double> msh(x_left, x_right, Ne);
    //msh.print();

    // initial field defined and initialized on mesh
    field<double> uh(SIN_PULSE, msh);

    // initialize time-loop
    time_loop<double> loop_in_time(msh, final_time, Nt, nu, alpha);

    // lauch time-loop
    loop_in_time.run(uh);

    output_writer<double> out_times(msh, "times");
    out_times.get_times(loop_in_time.get_times(), "times"); 

    return 0;
}