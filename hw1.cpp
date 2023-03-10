// Mojtaba Dehghani Firouzabadi 9923027
// Asvanced Programming Dr. Amir Jahanshahi
// 1401/12/17 eydeton mobark =)))

#include "hw1.h"

// function prototype

double sigmoid(double z) // sigmoid function
{
    return (1 / (1 + std::exp(-1 * z)));
} // end sigmoid function

std::vector<std::shared_ptr<std::vector<double>>> read_csv(std::string filename) // red_csv function
{
    std::ifstream ifs { filename };
    size_t cnt {};
    std::string line;
    std::vector<std::shared_ptr<std::vector<double>>> data;
    while (!ifs.eof()) {
        auto tmp { std::make_shared<std::vector<double>>() };
        data.push_back(tmp);
        std::getline(ifs, line);
        std::istringstream iss { line };
        double x, y, lable;
        char ch;
        iss >> x >> ch >> y >> ch >> lable;
        data[cnt]->push_back(x);
        data[cnt]->push_back(y);
        data[cnt++]->push_back(lable);
    }
    ifs.close();
    return data;

} // end read_csv function

std::vector<double> train(std::vector<std::shared_ptr<std::vector<double>>> train_data, double learning_rate, int num_iter) // train function
{
    std::vector<double> weights, weights_tmp;
    for (size_t i {}; i < (*train_data[0]).size(); i++) {
        weights.push_back(0);
        weights_tmp.push_back(0);
    }

    for (int m {}; m < num_iter; m++) {
        for (size_t i {}; i < train_data.size(); i++) {
            for (size_t j {}; j < weights.size(); j++)
                weights_tmp.push_back(weights[j]);
            weights_tmp[0] += learning_rate * ((*train_data[i])[(*train_data[i]).size() - 1] - predict(*train_data[i], weights));
            for (size_t j {}; j < (*train_data[i]).size(); j++) {
                weights_tmp[j + 1] += learning_rate * ((*train_data[i])[(*train_data[i]).size() - 1] - predict(*train_data[i], weights)) * (*train_data[i])[j];
            }
            for (size_t j {}; j < weights.size(); j++)
                weights[j] = weights_tmp[j];
            weights_tmp.clear();
        }
    }
    return weights;
} // end train function

double predict(std::vector<double> train_data, std::vector<double> weights) // predict function
{
    double sum { weights[0] };
    for (size_t j {}; j < train_data.size() - 1; j++) {
        sum += weights[j + 1] * train_data[j];
    }
    sum = sigmoid(sum);
    if (sum < 0.5)
        return 0.0;
    else
        return 1.0;
} // end predict function

double accuracy() // accuracy function
{
    std::vector<std::shared_ptr<std::vector<double>>> data { read_csv("data.csv") };
    std::vector<std::shared_ptr<std::vector<double>>> moons { read_csv("moons.csv") };
    std::vector<double> weights;
    weights = train(data, .5, 500);
    double correct {};
    double all {};
    for (size_t i {}; i < moons.size(); i++) {
        all++;
        if (predict(*moons[i], weights) == (*moons[i])[moons[i]->size() - 1])
            correct++;
    }
    return (correct / all) * 100;
} // end accuracy function