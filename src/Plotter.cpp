#include "Plotter.h"
#include <fstream>
#include <iostream>

Plotter::Plotter(const std::vector<std::vector<double>> &data) : data(data) {}

// Plot the pitch angle graph
void Plotter::plotPitchGraph() {
  // Write data to a temporary file
  std::ofstream tempDataFile("temp_data.txt");
  if (!tempDataFile.is_open()) {
    std::cerr << "Unable to open temporary data file!" << std::endl;
    return;
  }

  for (const auto &row : data) {
    tempDataFile << row[0] << ' ' << row[1] << std::endl;
  }

  tempDataFile.close();

  // Using a gnuplot script
  std::ofstream gpFile("plot_script.plt");
  if (!gpFile.is_open()) {
    std::cerr << "Unable to create gnuplot script file!" << std::endl;
    return;
  }

  gpFile << "set term x11 persist\n";
  gpFile << "set title 'The Pitch Angle Changing over Time'\n";
  gpFile << "set xlabel 'time(s)'\n";
  gpFile << "set ylabel 'pitch(degree)'\n";
  gpFile << "plot 'temp_data.txt' with lines title 'pitch'\n";

  gpFile.close();

  // Execute the gnuplot script
  system("gnuplot plot_script.plt");

  // Delete temporary files
  remove("temp_data.txt");
  remove("plot_script.plt");

  std::cout << "Press enter to continue..." << std::endl;
  std::cin.get();
}

// Plot the roll angle graph
void Plotter::plotRollGraph() {
  // Write data to a temporary file
  std::ofstream tempDataFile("temp_data.txt");
  if (!tempDataFile.is_open()) {
    std::cerr << "Unable to open temporary data file!" << std::endl;
    return;
  }

  for (const auto &row : data) {
    tempDataFile << row[0] << ' ' << row[2] << std::endl;
  }

  tempDataFile.close();

  // Using a gnuplot script
  std::ofstream gpFile("plot_script.plt");
  if (!gpFile.is_open()) {
    std::cerr << "Unable to create gnuplot script file!" << std::endl;
    return;
  }

  gpFile << "set term x11 persist\n";
  gpFile << "set title 'The Roll Angle Changing over Time'\n";
  gpFile << "set xlabel 'time(s)'\n";
  gpFile << "set ylabel 'roll(degree)'\n";
  gpFile << "plot 'temp_data.txt' with lines title 'Roll'\n";

  gpFile.close();

  // Execute the gnuplot script
  system("gnuplot plot_script.plt");

  // Delete temporary files
  remove("temp_data.txt");
  remove("plot_script.plt");

  std::cout << "Press enter to continue..." << std::endl;
  std::cin.get();
}

// Plot the yaw angle graph
void Plotter::plotYawGraph() {
  // Write data to a temporary file
  std::ofstream tempDataFile("temp_data.txt");
  if (!tempDataFile.is_open()) {
    std::cerr << "Unable to open temporary data file!" << std::endl;
    return;
  }

  for (const auto &row : data) {
    tempDataFile << row[0] << ' ' << row[3] << std::endl;
  }

  tempDataFile.close();

  // Using a gnuplot script
  std::ofstream gpFile("plot_script.plt");
  if (!gpFile.is_open()) {
    std::cerr << "Unable to create gnuplot script file!" << std::endl;
    return;
  }

  gpFile << "set term x11 persist\n";
  gpFile << "set title 'The Yaw Angle Changing over Time'\n";
  gpFile << "set xlabel 'time(s)'\n";
  gpFile << "set ylabel 'yaw(degree)'\n";
  gpFile << "plot 'temp_data.txt' with lines title 'yaw'\n";

  gpFile.close();

  // Execute the gnuplot script
  system("gnuplot plot_script.plt");

  // Delete temporary files
  remove("temp_data.txt");
  remove("plot_script.plt");

  std::cout << "Press enter to continue..." << std::endl;
  std::cin.get();
}
