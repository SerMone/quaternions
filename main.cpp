#include "quaternions.hpp"


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
// main function

int main(int argc, char **argv) {
  /*  std::cout << "\nfunction and rotation test:" << std::endl;
    quaternions q_test(read_components());
    std::vector<double> c{1, 0, 0};
    quaternions rot_test(180, c);
    std::cout << "\ntest rotation of 180 degrees around x axis" <<
    q_test.execute_rot(rot_test)
              << std::endl;
    c = {0,1,0};
    rot_test.set_components(c);
    std::cout << "\ntest rotation of 180 degrees around y axis" <<
    q_test.execute_rot(rot_test)
              << std::endl;
    c = {0,0,1};
    rot_test.set_components(c);
    std::cout << "\ntest rotation of 180 degrees around z axis" <<
    q_test.execute_rot(rot_test)
              << std::endl;*/
  std::vector<double> ang_vel{2, 1, 1};
  //  ang_vel = read_ang_vel();

  std::vector<double> inertia{1, 3, 1};
  //  inertia = read_inertial_mom();

  std::vector<double> torque{1, 2, 3};
  //  torque = read_torque();

  double t, n, dt;
  t = 2;
  n = 2;
  dt = t / n;
  std::cout << "ang vel = " << vector_to_string(ang_vel) << std::endl;
  std::cout << "inertia = " << vector_to_string(inertia) << std::endl;
  std::cout << "torque = " << vector_to_string(torque) << std::endl;
  std::cout << "time = " << t << "  dt = " << dt << std::endl;
  quaternions q_ang_vel(ang_vel);
  std::cout << vector_of_vector_to_string(
      q_ang_vel.iteration(dt, inertia, torque));
  std::vector<double> objk{2, 2, 1};

  quaternions obj(objk);
  std::cout << "1\n" << obj << std::endl;

  std::cout << "2\n"
            << obj.rot_spinning_top(t, n, ang_vel, inertia, torque)
            << std::endl;
  /*  std::vector<double> components1{3.4, 3.1, 1.2};
  quaternions q(1, components1);

  //  double angle_deg = read_angle();
  double angle_deg = read_angle();
  angle_deg = 120;
  q.set_rotation_deg(angle_deg);

  std::vector<double> components2{2.1, 3.5, 3.2};
  components2 = read_components();
  q.set_components(components2);

  std::cout << q;

  q.normalize();

  std::cout << q << std::endl;
  std::cout << q.conjugate();

  quaternions q2(std::vector<double>{3, 4, 5});
  std::cout << q2;

  std::cout << q2.execute_rot(q);
  std::cout << q2.module() << std::endl;
  std::cout << q2.execute_rot(q).module() << std::endl;

  //  std::cout << ( q2.module() - q2.execute_rot(q).module() ) /
  q2.execute_rot(q).module();
  // 	    << std::endl;*/
}
