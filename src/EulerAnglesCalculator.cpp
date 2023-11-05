#include "EulerAnglesCalculator.h"
#include <cmath>

// Matrix initialization
EulerAnglesCalculator::EulerAnglesCalculator(const std::vector<double> &data) {
  g_b = Eigen::MatrixXd(3, 1);
  omega_b = Eigen::MatrixXd(3, 1);
  C = Eigen::MatrixXd(3, 3);

  g_b(0, 0) = -data[2];
  g_b(1, 0) = -data[3];
  g_b(2, 0) = data[1];
  omega_b(0, 0) = data[5];
  omega_b(1, 0) = data[6];
  omega_b(2, 0) = -data[4];

  C.fill(0);

  g_n = Eigen::MatrixXd(3, 1);
  omega_n = Eigen::MatrixXd(3, 1);
  g_n.fill(0);
  g_n(2, 0) = g;
  omega_n(1, 0) = 0;
  omega_n(0, 0) = omega_e * cos(phi);
  omega_n(2, 0) = -omega_e * sin(phi);
}

// Computing the cross product
Eigen::MatrixXd EulerAnglesCalculator::CrossProduct(const Eigen::MatrixXd &mat1, const Eigen::MatrixXd &mat2) {
  Eigen::MatrixXd temp(3, 3);
  temp.fill(0);
  temp(0, 1) = -mat1(2, 0);
  temp(0, 2) = mat1(1, 0);
  temp(1, 0) = mat1(2, 0);
  temp(1, 2) = -mat1(0, 0);
  temp(2, 0) = -mat1(1, 0);
  temp(2, 1) = mat1(0, 0);

  return temp * mat2;
}

// Solve for the attitude matrix
void EulerAnglesCalculator::calculateMatrix() {
  Eigen::MatrixXd v_g = g_n / Magnitude(g_n);
  Eigen::MatrixXd v_w = CrossProduct(g_n, omega_n) / Magnitude(CrossProduct(g_n, omega_n));
  Eigen::MatrixXd v_gw = CrossProduct(CrossProduct(g_n, omega_n), g_n) / Magnitude(CrossProduct(CrossProduct(g_n, omega_n), g_n));

  Eigen::MatrixXd w_g = g_b / Magnitude(g_b);
  Eigen::MatrixXd w_w = CrossProduct(g_b, omega_b) / Magnitude(CrossProduct(g_b, omega_b));
  Eigen::MatrixXd w_gw = CrossProduct(CrossProduct(g_b, omega_b), g_b) / Magnitude(CrossProduct(CrossProduct(g_b, omega_b), g_b));

  Eigen::MatrixXd V(3, 3), W(3, 3);
  V << v_g, v_w, v_gw;
  W << w_g, w_w, w_gw;
  C = V * W.transpose();
}

// Calculate the magnitude of the vector
double EulerAnglesCalculator::Magnitude(const Eigen::MatrixXd &mat) {
  return sqrt(mat(0, 0) * mat(0, 0) + mat(1, 0) * mat(1, 0) + mat(2, 0) * mat(2, 0));
}

// Calculate Euler angles
void EulerAnglesCalculator::calculateEulerAngles() {
  pitch = atan2(-C(2, 0), sqrt(C(2, 1) * C(2, 1) + C(2, 2) * C(2, 2))) * 180.0 / pi;
  roll = atan2(C(2, 1), C(2, 2)) * 180.0 / pi;
  yaw = atan2(C(1, 0), C(0, 0)) * 180.0 / pi;
}

double EulerAnglesCalculator::getRoll() const {
  return roll;
}

double EulerAnglesCalculator::getPitch() const {
  return pitch;
}

double EulerAnglesCalculator::getYaw() const {
  return yaw;
}
