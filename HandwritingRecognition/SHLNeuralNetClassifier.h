//
//  SHLNeuralNetClassifier.h
//  HandwritingRecognition
//
//  Created by Andrew Wang on 8/20/14.
//  Copyright (c) 2014 Andrew Wang. All rights reserved.
//

#ifndef __HandwritingRecognition__SHLNeuralNetClassifier__
#define __HandwritingRecognition__SHLNeuralNetClassifier__

#include <stdio.h>
#include "Classifier.h"
#include "Model.h"
#include "Neural.h"
#include <vector>
#include <map>

// single hidden layer
class SHLNeuralClassifier : Classifier {
public:
    SHLNeuralClassifier(Model *trainingModel);
    int classify(unsigned char *image);
    
private:
    void backPropagateTrain();
    void forwardPropagate(unsigned char *image);
    
    Model *model;
    
    int inputSize;
    
    //std::vector<Perceptron> inputLayer;
    std::vector<LogisticPerceptron> hiddenLayer;
    std::vector<LogisticPerceptron> outputLayer;
    
    std::map<int, int> indexToLabel;
    
    //std::map<std::pair<int, int>, double> inputToHiddenWeights;
    //std::map<std::pair<int, int>, double> hiddenToOutputWeights;
};

#endif /* defined(__HandwritingRecognition__SHLNeuralNetClassifier__) */
