#ifndef IN_OUT_HPP
#define IN_OUT_HPP

#include <string>
#include <vector>

double ang_degree_to_first_round(double angle_deg);

// read components functions
double read_angle();

std::vector<double> read_components();

std::vector<double> read_ang_vel();

double read_time();

std::vector<double> read_inertial_mom();

std::vector<double> read_torque();

std::string vector_to_string(std::vector<double> vec);

std::string vector_of_vector_to_string(std::vector<std::vector<double>> vec);
#endif
