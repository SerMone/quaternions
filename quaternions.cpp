
#include "quaternions.hpp"
#include "in_out.hpp"

#include <iomanip>
#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>



double quaternions::set_rot_comp(double angle_deg) {

  double ang = ang_degree_to_first_round(angle_deg);

  if (ang == 180)
    return 0;
  else
    return std::cos(ang * M_PI / 180 / 2);
}

double quaternions::x() const { return comp[0]; }
double quaternions::y() const { return comp[1]; }
double quaternions::z() const { return comp[2]; }

// set components functions

void quaternions::set_components(const std::vector<double> &vec) { comp = vec; }

void quaternions::set_rotation_deg(double angle_deg) {
  rot_ang = set_rot_comp(angle_deg);
}

// print quaternion

std::ostream& operator<<(std::ostream &os, const quaternions q) {
  std::cout << std::setprecision(4) << "\n"
            << "[" << q.rot_ang << "; " << q.x() << "; " << q.y() << "; "
            << q.z() << "]  r_e = " << q.comp_err * 100 << " %" << std::endl;
  return os;
}

// operations with quaternions

quaternions quaternions::operator*(quaternions q) const {
  double a;
  std::vector<double> c(3);
  a = rot_ang * q.rot_ang - x() * q.x() - y() * q.y() - z() * q.z();

  c[0] = rot_ang * q.x() + x() * q.rot_ang + y() * q.z() - z() * q.y();

  c[1] = rot_ang * q.y() + y() * q.rot_ang + z() * q.x() - x() * q.z();

  c[2] = rot_ang * q.z() + z() * q.rot_ang + x() * q.y() - y() * q.x();
  return quaternions(c, a);
}

double quaternions::quat_module() {
  /*  std::cout << "modulo"
              << sqrt(rot_ang * rot_ang + x() * x() + y() * y() + z() * z())
              << std::endl;*/
  return std::sqrt(rot_ang * rot_ang + x() * x() + y() * y() + z() * z());
}

double quaternions::vector_module() {
  /*  std::cout << "modulo"
              << sqrt(x() * x() + y() * y() + z() * z())
              << std::endl;*/
  return std::sqrt(x() * x() + y() * y() + z() * z());
}

quaternions quaternions::normalize() {
  double norm_par;
  std::vector<double> vec(3);
  norm_par =
      std::sqrt((1 - rot_ang * rot_ang) / (x() * x() + y() * y() + z() * z()));
  //		std::cout << norm_par << std::endl;
  for (std::size_t i = 0; i < comp.size(); ++i) {
    vec[i] = comp[i] * norm_par;
  }
  return quaternions(vec, rot_ang, comp_err);
}

quaternions quaternions::conjugate() const {
  std::vector<double> c(3);
  for (std::size_t i = 0; i < comp.size(); ++i) {
    c[i] = -comp[i];
  }

  return quaternions(c, rot_ang, comp_err);
}

// rotation execution function

quaternions quaternions::execute_rot(quaternions axis) {
  quaternions ris;
  quaternions norm;
  norm = axis.normalize();
  ris = norm.conjugate() * (*this) * norm;

  std::cout << comp_err << std::endl;

  // relative computational error estimation
  ris.comp_err =
      (std::fabs(quat_module() - ris.quat_module())) / ris.quat_module() +
      comp_err;

  std::cout << ris.comp_err << std::endl;

  ris.rot_ang = 0;
  return ris;
}

// computation of the algorithm of Runge Kutta for the euler spinning top

// function outside of the class quaternions used to minimize the
// dimension of the runge kutta implementation functions
std::vector<double> euler_func(std::vector<double> ang_vel,
                               std::vector<double> inertia,
                               std::vector<double> torque) {

  std::vector<double> func{0, 0, 0};

  func[0] = (torque[0] - ang_vel[1] * ang_vel[2] * (inertia[2] - inertia[1])) /
            inertia[0];

  func[1] = (torque[1] - ang_vel[0] * ang_vel[2] * (inertia[0] - inertia[2])) /
            inertia[1];

  func[2] = (torque[2] - ang_vel[1] * ang_vel[0] * (inertia[1] - inertia[0])) /
            inertia[2];

  return func;
}


// call this function with the angular velocity
std::vector<std::vector<double>> 
quaternions::iteration(double dt, std::vector<double> inertia,
                       std::vector<double> torque = {0, 0, 0}) {

  std::vector<std::vector<double>> vec{comp, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  for (std::size_t j = 1; j < vec.size(); ++j) {

    vec[j] = euler_func(vec[j - 1], inertia, torque);

    for (std::size_t i = 0; i < vec[j].size(); ++i) {
      if (j == (vec.size() - 1))
        vec[j][i] = comp[i] + dt * vec[j][i];

      else
        vec[j][i] = comp[i] + dt * vec[j][i] / 2;
    }
  }
  return vec;
}

// call this function with the vector representing the object
quaternions quaternions::rot_spinning_top
                (double t, double n, std::vector<double> a_vel,
                 std::vector<double> inertia,
                 std::vector<double> torque = {0, 0, 0}) {
  double dt = t / n;
  std::vector<std::vector<double>> vec{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  quaternions ist_rot(a_vel);
  ist_rot.set_rotation_deg(ist_rot.vector_module() * 180 / M_PI * dt);
  quaternions obj(execute_rot(ist_rot));

  for (unsigned k = 1; k < n; ++k) {

    vec = ist_rot.iteration(dt, inertia, torque);
    for (size_t i = 0; i < vec.size(); ++i) {
      vec[i] = euler_func(vec[i], inertia, torque);
    }
    //	std::cout << "questo pure \n" << vector_of_vector_to_string(vec) <<
    //std::endl;
    for (size_t j = 0; j < vec[0].size(); ++j) {
      ist_rot.comp[j] =
          ist_rot.comp[j] +
          t / n / 6 * (vec[0][j] + 2 * vec[1][j] + 2 * vec[2][j] + vec[3][j]);
    }
    ist_rot.set_rotation_deg(ist_rot.vector_module() * 180 / M_PI * t / n);

    // std::cout << "\nquesto" << ist_rot << std::endl;

    obj = execute_rot(ist_rot);
    obj.comp_err = obj.comp_err + dt * dt * dt * dt * k / quat_module();
  }
  return obj;
}


