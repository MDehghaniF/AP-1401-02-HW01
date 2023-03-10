#ifndef HW1_H
#define HW1_H
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// function prototype

double sigmoid(double);
std::vector<double> train(std::vector<std::shared_ptr<std::vector<double>>>, double, int);
std::vector<std::shared_ptr<std::vector<double>>> read_csv(std::string);
double predict(std::vector<double>, std::vector<double>);
double accuracy();

// end function prototype

#endif
