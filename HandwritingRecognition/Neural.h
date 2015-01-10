//
//  Neural.h
//  HandwritingRecognition
//
//  Created by Andrew Wang on 8/20/14.
//  Copyright (c) 2014 Andrew Wang. All rights reserved.
//

#ifndef __HandwritingRecognition__Neural__
#define __HandwritingRecognition__Neural__

#include <stdio.h>
#include <vector>

typedef struct {
    std::vector<int> input;
    int output;
} Example;

class Perceptron {
public:
    Perceptron(int numFeatures);
    virtual double predict(std::vector<double> features) { return -1; }
    virtual double gradient(std::vector<double> input) { return -1; }

    // 0th weight is for "dummy" feature. Features are numbered 1 through numFeatures
    std::vector<double> weights;
    double value;
};

class LogisticPerceptron : Perceptron {
public:
    LogisticPerceptron(int numFeatures);
    double predict(std::vector<double> features);
    double gradient(std::vector<double> input);
    
    std::vector<double> weights;
    double value;
};

#endif /* defined(__HandwritingRecognition__Neural__) */
