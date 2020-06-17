#ifndef QUATERNIONS_H
#define QUATERNIONS_H
#include "in_out.hpp"
#include <vector>


class quaternions {
  std::vector<double> comp;
  double rot_ang;
  double comp_err;

  static double set_rot_comp(double angle_deg);

public:
  double x() const;
  double y() const;
  double z() const;

  // constructors

  quaternions(double a_deg, std::vector<double> vec = {0, 0, 0}, double err = 0)
      : comp(vec), rot_ang(set_rot_comp(a_deg)), comp_err(err) {}

  quaternions(std::vector<double> vec = {0, 0, 0}, double rot = 0,
              double err = 0)
      : comp(vec), rot_ang(rot), comp_err(err) {}

  quaternions(const quaternions &q)
      : comp(q.comp), rot_ang(q.rot_ang), comp_err(q.comp_err) {}

  // set components functions

  void set_components(const std::vector<double> &vec);

  void set_rotation_deg(double angle_deg);

  // print components functions

  friend std::ostream &operator<<(std::ostream &os, const quaternions q);

  // operations with quaternions

  quaternions operator*(quaternions q) const;

  double quat_module() const;

  double vector_module() const;

  quaternions normalize() const;

  quaternions conjugate() const;

  // rotation execution function

  quaternions execute_rot(quaternions axis);

  // computation of the algorithm of Runge Kutta for the euler spinning top

  // call this function with the angular velocity
  std::vector<std::vector<double>>
  iteration(double dt, std::vector<double> inertia,
            std::vector<double> torque);

  quaternions rot_spinning_top(double t, double n, std::vector<double> a_vel,
                               std::vector<double> inertia,
                               std::vector<double> torque);

}; // end class


#endif
