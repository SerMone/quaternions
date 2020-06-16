
#include "in_out.hpp"
#include "str.hpp"

#include <iostream>

double ang_degree_to_first_round(double angle_deg) {

  while (angle_deg >= 360)
    angle_deg -= 360;

  while (angle_deg < 0)
    angle_deg += 360;

  return angle_deg;
}


double read_angle() {

  double phi = 0;
  double phi_corrected = 0;

  while (phi_corrected == 0) {

    std::cout << "\ninsert the degree angle of rotation" << std::endl;
    std::cin >> phi;

    phi_corrected = ang_degree_to_first_round(phi);

    if (phi_corrected == 0) {
      std::cout << "\nthe trasformation is degenerate and gives back the "
                   "starting vector,\ninsert another degree angle"
                << std::endl;
    }
  }

  return phi_corrected;
}


std::vector<double> read_components() {
  std::cout
      << "\nit is necessary a tridimensional non null vector to proceed:\n";
  std::vector<double> vec{0, 0, 0};
  do {
    for (std::size_t i = 0; i < vec.size(); ++i) {
      std::cout << "write the " << i + 1
                << " component of the tridimensional vector" << std::endl;
      std::cin >> vec[i];
    }
    if (0 == (vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2])) {
      std::cout << "\nit is a null vector, insert another" << std::endl;
    }
  } while (0 == (vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]));
  return vec;
}


std::vector<double> read_ang_vel() {
  std::cout << "\nit is necessary a tridimensional non null angular velocity "
               "to proceed: ";
  std::vector<double> vec{0, 0, 0};
  do {
    for (std::size_t i = 0; i < vec.size(); ++i) {
      std::cout << "\nwrite the " << i + 1
                << " component of the tridimensional angular velocity"
                << std::endl;
      std::cin >> vec[i];
    }
    if (0 == (vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2])) {
      std::cout << "\nit is a null vector, insert another vector" << std::endl;
    }
  } while (0 == (vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]));
  return vec;
}


double read_time() {
  double t = 0;
  do {
    std::cout << "\ninsert the positive, non null time at witch calculate the "
                 "rotation"
              << std::endl;
    std::cin >> t;
    if (t <= 0) {
      std::cout << "\nthe time is either null or negative, insert another value"
                << std::endl;
    }
  } while (t <= 0);

  return t;
}


std::vector<double> read_inertial_mom() {
  std::cout << "\nit is necessary a tridimensional inertial momentum with "
               "positive components "
               "to proceed: ";
  std::vector<double> vec{0, 0, 0};

  for (std::size_t i = 0; i < vec.size(); ++i) {
    do {
      std::cout << "\nwrite the " << i + 1
                << " component of the tridimensional inertial momentum"
                << std::endl;
      std::cin >> vec[i];

      if (vec[i] <= 0) {
        std::cout
            << "\nit is a null or negative component, insert another component"
            << std::endl;
      }
    } while (vec[i] <= 0);
  }
  return vec;
}


std::vector<double> read_torque() {
  std::cout << "\nit is necessary a tridimensional torque "
               "to proceed: ";
  std::vector<double> vec{0, 0, 0};
  for (std::size_t i = 0; i < vec.size(); ++i) {
    std::cout << "\nwrite the " << i + 1
              << " component of the tridimensional torque" << std::endl;
    std::cin >> vec[i];
  }
  return vec;
}


std::string vector_to_string(std::vector<double> vec) {
  return join(vec.begin(), vec.end());
}


std::string vector_of_vector_to_string(std::vector<std::vector<double>> vec) {
  std::vector<std::string> str(4);
  for (unsigned i = 0; i < vec.size(); ++i) {
    str[i] = join(vec[i].begin(), vec[i].end());
  }
  return join(str.begin(), str.end(), "]\n[");
}
