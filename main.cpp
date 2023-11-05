#include <iostream>
#include "IMUDataReader.h"
#include "EulerAnglesCalculator.h"
#include "Plotter.h"

int main() {
  std::vector<double> averageData, secondData, epochData;

  // Read data
  IMUDataReader staticData("/home/akui/Downloads/imu_231008/imu_static_data/alignment.ASC");

  // The average observation over the entire time period
  if (staticData.readDataFile()) {
    staticData.applyTransformations();
    staticData.calculateAverages();
    averageData = staticData.getAverages();
  }

  // The attitude angles computed from the averaged static data over the entire duration
  EulerAnglesCalculator averageEuler(averageData);
  averageEuler.calculateMatrix();
  averageEuler.calculateEulerAngles();
  std::cout << "The attitude angles computed from the averaged static data over the entire duration:" << std::endl
            << "Pitch:" << averageEuler.getPitch() << std::endl
            << "Roll:" << averageEuler.getRoll() << std::endl
            << "Yaw:" << averageEuler.getYaw() << std::endl;

  // Attitude angles computed for each epoch
  std::vector<std::vector<double>> epochResult;
  std::vector<std::vector<double>> Data = staticData.getRawData();
  for (int i = 0; i < Data.size();++i) {
    epochData = Data[i];
    EulerAnglesCalculator epochEuler(epochData);
    epochEuler.calculateMatrix();
    epochEuler.calculateEulerAngles();
    double pitch = epochEuler.getPitch();
    double roll = epochEuler.getRoll();
    double yaw = epochEuler.getYaw();
    epochResult.push_back({epochData[0], pitch, roll, yaw});
  }

  // Plotting the Attitude Angle Curve
  Plotter plot_epoch(epochResult);
  plot_epoch.plotPitchGraph();
  plot_epoch.plotRollGraph();
  plot_epoch.plotYawGraph();

  // The attitude angles calculated after averaging static data every second
  std::vector<std::vector<double>> secondResult;
  std::vector<std::vector<double>> DataSecond = staticData.secondAverages();
  for (int i = 0; i < DataSecond.size(); ++i) {
    secondData = DataSecond[i];
    EulerAnglesCalculator secondEuler(secondData);
    secondEuler.calculateMatrix();
    secondEuler.calculateEulerAngles();
    double pitch = secondEuler.getPitch();
    double roll = secondEuler.getRoll();
    double yaw = secondEuler.getYaw();
    secondResult.push_back({secondData[0], pitch, roll, yaw});
  }

  // Plotting the Attitude Angle Curve
  Plotter plot_second(secondResult);
  plot_second.plotPitchGraph();
  plot_second.plotRollGraph();
  plot_second.plotYawGraph();

  return 0;
}
