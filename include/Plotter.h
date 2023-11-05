#ifndef PLOTTER_H
#define PLOTTER_H

#include <vector>

class Plotter {
public:
  Plotter(const std::vector<std::vector<double>> &data);
  void plotPitchGraph();
  void plotRollGraph();
  void plotYawGraph();

private:
  std::vector<std::vector<double>> data;
};

#endif 
