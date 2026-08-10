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
    double alpha = 5 * 1e-4;

    // mesh construction
    mesh_1d<double> msh(x_left, x_right, Ne);
    //msh.print();

    // initial field defined and initialized on mesh
    field<double> uh(SIN_PULSE, msh);

    // initialize writer
    output_writer<double> out_stream(msh, "SIN_PULSE");

    // write initial field
    out_stream.write_solution(uh, "initial");

    // initialize time-loop
    time_loop<double> loop_in_time(msh, final_time, Nt, nu, alpha);

    // lauch time-loop
    loop_in_time.run(uh);

    // write final field
    const Matrix<double>& inter = loop_in_time.intermediate_solutions();
    for(auto ii = 0; ii < 4; ii++)
    {
        out_stream.write_solution(inter.col(ii), "step_" + std::to_string(ii + 1));
    }
    out_stream.write_solution(uh, "final");

    return 0;
}