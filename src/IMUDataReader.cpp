#include "IMUDataReader.h"
#include <fstream>
#include <iostream>
#include <sstream>

IMUDataReader::IMUDataReader(const std::string &filename) : filename(filename) {}

// Read the file
bool IMUDataReader::readDataFile() {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Unable to open file." << std::endl;
    return false;
  }

  std::string line;
  while (std::getline(file, line)) {
    processLine(line);
  }

  file.close();
  return true;
}

// Store the required data in a two-dimensional array
void IMUDataReader::processLine(const std::string &line) {
  std::istringstream iss(line);
  std::string token;
  std::string prevToken;

  while (std::getline(iss, token, ',')) {
    if (token == "00000077") {
      std::vector<double> values;

      if (!prevToken.empty()) {
        values.push_back(std::stod(prevToken));
      }

      while (std::getline(iss, token, ',')) {
        if (token.find('*') != std::string::npos) {
          token = token.substr(0, token.find('*'));
          values.push_back(std::stod(token));
          break;
        }
        values.push_back(std::stod(token));
      }
      rawData.push_back(values);
      break;
    }

    prevToken = token;
  }
}

// Calculate the average of the observed array over the entire static period
void IMUDataReader::calculateAverages() {
  if (rawData.empty()) {
    std::cerr << "Error: No data to process." << std::endl;
    return;
  }

  int numEntries = rawData.size();
  int numValues = rawData[0].size();
  averages.resize(numValues, 0.0);

  for (const auto &entry : rawData) {
    for (int i = 0; i < numValues; ++i) {
      averages[i] += entry[i];
    }
  }

  for (double &average : averages) {
    average /= numEntries;
  }
}

std::vector<double> IMUDataReader::getAverages() {
  return averages;
}

// Data preprocessing
void IMUDataReader::applyTransformations() {
  if (rawData[0].size() != 7) {
    std::cerr << "Error: No data to process." << std::endl;
    return;
  }

  for (auto &entry : rawData) {
    for (int i = 1; i < 4; ++i) {
      entry[i] *= (accScale * 100.0);
    }

    for (int i = 4; i < 7;++i) {
      entry[i] *= (gyoScale * 100.0);
    }

    entry[2] = -entry[2];
    entry[5] = -entry[5];
  }
}

std::vector<std::vector<double>> IMUDataReader::getRawData() {
  return rawData;
}

// Calculate the average of the observation array for each second
std::vector<std::vector<double>> IMUDataReader::secondAverages() {
  std::vector<std::vector<double>> secondAverage;

  if (rawData.empty()) {
    return secondAverage;
  }

  double currentSecond = rawData[0][0];
  double sumA = 0.0, sumB = 0.0, sumC = 0.0, sumD = 0.0, sumE = 0.0, sumF = 0.0;
  int count = 0;

  for (const auto &row : rawData) {
    if (row[0] - currentSecond >= 1.0) {
      // A new second begins
      secondAverage.push_back({currentSecond + 0.5, sumA / count, sumB / count, sumC / count, sumD / count, sumE / count, sumF / count});

      // Reset variables
      currentSecond = row[0];
      sumA = sumB = sumC = sumD = sumE = sumF = 0.0;
      count = 0;
    }

    sumA += row[1];
    sumB += row[2];
    sumC += row[3];
    sumD += row[4];
    sumE += row[5];
    sumF += row[6];
    count++;
  }

  return secondAverage;
}