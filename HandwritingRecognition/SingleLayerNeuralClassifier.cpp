//
//  SingleLayerNeuralClassifier.cpp
//  HandwritingRecognition
//
//  Created by Andrew Wang on 8/20/14.
//  Copyright (c) 2014 Andrew Wang. All rights reserved.
//

#include "SingleLayerNeuralClassifier.h"
/*
SingleLayerNeuralClassifier::SingleLayerNeuralClassifier(Model *trainingModel) {
    model = trainingModel;
    
    std::set<int> labels = trainingModel->getAllPossibleLabels();
    for (std::set<int>::iterator it = labels.begin(); it != labels.end(); it++) {
        int label = *it;
        std::vector<std::vector<Perceptron>> perceptronGrid;
        for (int row = 0; row < trainingModel->imageHeight; row++) {
            std::vector<Perceptron> perceptronRow;
            for (int col = 0; col < trainingModel->imageWidth; col++) {
                Perceptron perceptron(1);
                perceptronRow.push_back(perceptron);
            }
            perceptronGrid.push_back(perceptronRow);
        }
        perceptrons[label] = perceptronGrid;
    }
    
    trainPerceptrons();
}

void SingleLayerNeuralClassifier::trainPerceptrons() {
    for (auto pair : perceptrons) {
        int label = pair.first;
        std::vector<std::vector<Perceptron>> &grid = pair.second;
        for (int row = 0; row < model->imageHeight; row++) {
            for (int col = 0; col < model->imageWidth; col++) {
                trainPerceptron(grid[row][col], label);
            }
        }
    }
}

void SingleLayerNeuralClassifier::trainPerceptron(Perceptron &perceptron, int label) {
    
}

int SingleLayerNeuralClassifier::classify(unsigned char *image) {
    int argmax = -1;
    double maxScore = -1;
    for (int label : model->getAllPossibleLabels()) {
        
    }
}*/