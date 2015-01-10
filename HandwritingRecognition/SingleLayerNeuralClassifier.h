//
//  SingleLayerNeuralClassifier.h
//  HandwritingRecognition
//
//  Created by Andrew Wang on 8/20/14.
//  Copyright (c) 2014 Andrew Wang. All rights reserved.
//

#ifndef __HandwritingRecognition__SingleLayerNeuralClassifier__
#define __HandwritingRecognition__SingleLayerNeuralClassifier__

#include <stdio.h>
#include "Classifier.h"
#include "Model.h"
#include "Neural.h"
#include <vector>
#include <map>

class SingleLayerNeuralClassifier : Classifier {
public:
    SingleLayerNeuralClassifier(Model *trainingModel);
    int classify(unsigned char *image);
    
private:
    void trainPerceptrons();
    void trainPerceptron(Perceptron &perceptron, int label);
    
    Model *model;
    std::map<int, std::vector<std::vector<Perceptron>>> perceptrons;  // maps label it's trying to classify to grid of (row, then col)
};

#endif /* defined(__HandwritingRecognition__SingleLayerNeuralClassifier__) */
