//
//  Neural.cpp
//  HandwritingRecognition
//
//  Created by Andrew Wang on 8/20/14.
//  Copyright (c) 2014 Andrew Wang. All rights reserved.
//

#include "Neural.h"
#include <numeric>
#include <cmath>
#include <iostream>
#include <assert.h>
#include <math.h>

Perceptron::Perceptron(int numFeatures) : weights(numFeatures + 1, 0), value(0) {
}

LogisticPerceptron::LogisticPerceptron(int numFeatures) : Perceptron(numFeatures), weights(numFeatures + 1, 0), value(0) {
    
}

double LogisticPerceptron::predict(std::vector<double> features) {
    double dotProduct = std::inner_product(++weights.begin(), weights.end(), features.begin(), 0);
    dotProduct += weights[0];
    
    //std::cout << "<DP " << dotProduct << ">\n";
    
    double prediction = (double)1.0 / (1.0 + exp(-dotProduct));
    //std::cout << "I predict " << prediction << "\n";
    
    value = prediction;
    
    return prediction;
}

double LogisticPerceptron::gradient(std::vector<double> input) {/*
    int dotProduct = std::inner_product(++weights.begin(), weights.end(), input.begin(), 0);
    //assert(weights.size() == input.size() + 1);
    dotProduct += weights[0];
    
    double expX = exp(dotProduct);
    
    //assert(abs(expX / ((1 + expX) * (1 + expX))) < 10000000);
    std::cout << "My gradient is " << expX << " for input " << dotProduct << std::endl;
    return expX / (1 + expX) / (1 + expX);*/
    double g = predict(input);
    return (1 - g) * g;
}