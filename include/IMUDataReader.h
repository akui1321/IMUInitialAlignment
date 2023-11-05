#ifndef IMU_DATA_READER_H
#define IMU_DATA_READER_H

#include <string>
#include <vector>

class IMUDataReader {
public:
  IMUDataReader(const std::string &filename);

  bool readDataFile();

  void calculateAverages();

  std::vector<double> getAverages();

  void applyTransformations();

  std::vector<std::vector<double>> getRawData();

  std::vector<std::vector<double>> secondAverages();
private:
  std::string filename;
  std::vector<std::vector<double>> rawData;
  std::vector<double> averages;

  double accScale = 1.5258789063e-6;
  double gyoScale = 1.0850694444e-7;

  void processLine(const std::string &line);
};

#endif 
