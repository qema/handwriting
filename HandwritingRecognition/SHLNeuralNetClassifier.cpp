//
//  SHLNeuralNetClassifier.cpp
//  HandwritingRecognition
//
//  Created by Andrew Wang on 8/20/14.
//  Copyright (c) 2014 Andrew Wang. All rights reserved.
//

#include "SHLNeuralNetClassifier.h"
#include "Neural.h"
#include <iostream>
#include <assert.h>
#include <math.h>

const int HIDDEN_LAYER_SIZE = 300;
const double LEARNING_RATE = 0.3;

SHLNeuralClassifier::SHLNeuralClassifier(Model *trainingModel) : inputSize(trainingModel->imageWidth * trainingModel->imageHeight), hiddenLayer(HIDDEN_LAYER_SIZE, LogisticPerceptron(inputSize)), outputLayer(trainingModel->getAllPossibleLabels().size(), LogisticPerceptron(HIDDEN_LAYER_SIZE)) {
    
    model = trainingModel;
    int index = 0;
    for (auto label : model->getAllPossibleLabels()) {
        indexToLabel[index++] = label;
    }
    
    //std::cout << "hiddenlayer weigths has size " << hiddenLayer[0].weights.size() << "\n";
    
    // train
    backPropagateTrain();
}

void SHLNeuralClassifier::backPropagateTrain() {
    // clear weights
    for (int hiddenIndex = 0; hiddenIndex < hiddenLayer.size(); hiddenIndex++) {
        for (int inputIndex = 0; inputIndex < inputSize; inputIndex++) {
            hiddenLayer[hiddenIndex].weights[inputIndex] = (double)(rand() % 100) / 1000 - .05;   // small random number
        }
    }
    for (int outputIndex = 0; outputIndex < outputLayer.size(); outputIndex++) {
        for (int hiddenIndex = 0; hiddenIndex < hiddenLayer.size(); hiddenIndex++) {
            outputLayer[outputIndex].weights[hiddenIndex] = (double)(rand() % 100) / 1000 - .05;  // small random number
        }
    }
    
    for (int epoch = 0; epoch < 100000; epoch++) {
        if (epoch % 100 == 0)
            std::cout << "Epoch " << epoch << std::endl;
        /* // #OLD
        inputToHiddenWeights.clear();
        hiddenToOutputWeights.clear();
        for (int i = 0; i < inputSize; i++) {
            for (int j = 0; j < hiddenLayer.size(); j++) {
                inputToHiddenWeights[std::make_pair(i, j)] = 0; // small random number
            }
        }
        for (int i = 0; i < hiddenLayer.size(); i++) {
            for (int j = 0; j < outputLayer.size(); j++) {
                hiddenToOutputWeights[std::make_pair(i, j)] = 0;    // small random number
            }
        }*/
        
        double MSE = 0;
        for (int i = 0; i < model->numDataPoints; i++) {
            // convert image to vector
            std::vector<double> input;
            for (int row = 0; row < model->imageHeight; row++) {
                for (int col = 0; col < model->imageWidth; col++) {
                    //std::cout << row << ", " << col << ": " << i << "\n";
                    input.push_back(getPixel(model->images[i], row, col, model->imageWidth) / 255.0);
                }
            }
            
            // -- forward propagation --
            // 1. input layer to hidden layer
            for (int hiddenIndex = 0; hiddenIndex < hiddenLayer.size(); hiddenIndex++) {
                hiddenLayer[hiddenIndex].predict(input);
            }
            
            // vectorize hidden nodes that are connected to this output node
            std::vector<double> hiddenValues;
            for (int hiddenIndex = 0; hiddenIndex < hiddenLayer.size(); hiddenIndex++) {
                hiddenValues.push_back(hiddenLayer[hiddenIndex].value);
            }
            
            // 2. hidden layer to output layer
            for (int outputIndex = 0; outputIndex < outputLayer.size(); outputIndex++) {
                outputLayer[outputIndex].predict(hiddenValues);
            }
            
            // -- backward propagation of deltas --
            // 1. output layer to hidden layer
            std::vector<double> outputDeltas;
            for (int outputIndex = 0; outputIndex < outputLayer.size(); outputIndex++) {
                int actual = (indexToLabel[outputIndex] == model->labels[i]) ? 1 : 0;
                outputDeltas.push_back(outputLayer[outputIndex].gradient(hiddenValues) * (actual - outputLayer[outputIndex].value));
                MSE += pow(actual - outputLayer[outputIndex].value, 2);
            }
            // 2. hidden layer to input layer
            std::vector<double> hiddenDeltas;
            for (int hiddenIndex = 0; hiddenIndex < hiddenLayer.size(); hiddenIndex++) {
                double weightedDeltasSum = 0;
                for (int outputIndex = 0; outputIndex < outputLayer.size(); outputIndex++) {
                    weightedDeltasSum += outputLayer[outputIndex].weights[hiddenIndex + 1] * outputDeltas[outputIndex];
                }
                hiddenDeltas.push_back(hiddenLayer[hiddenIndex].gradient(input) * weightedDeltasSum);
                //std::cout << hiddenLayer[hiddenIndex].gradient(input) << ", " << weightedDeltasSum << " -> " << hiddenLayer[hiddenIndex].gradient(input) * weightedDeltasSum << " but the actual is " << hiddenDeltas[hiddenDeltas.size()-1] << std::endl;
            }
            
            // -- update weights --
            // 1. hidden->output weights
            for (int outputIndex = 0; outputIndex < outputLayer.size(); outputIndex++) {
                outputLayer[outputIndex].weights[0] += LEARNING_RATE * outputDeltas[outputIndex];
                for (int hiddenIndex = 0; hiddenIndex < hiddenLayer.size(); hiddenIndex++) {
                    outputLayer[outputIndex].weights[hiddenIndex + 1] += LEARNING_RATE * hiddenLayer[hiddenIndex].value * outputDeltas[outputIndex];
                }
            }
            // 2. input->hidden weights
            for (int hiddenIndex = 0; hiddenIndex < hiddenLayer.size(); hiddenIndex++) {
                hiddenLayer[hiddenIndex].weights[0] += LEARNING_RATE * hiddenDeltas[hiddenIndex];
                for (int inputIndex = 0; inputIndex < inputSize; inputIndex++) {
                    hiddenLayer[hiddenIndex].weights[inputIndex + 1] += LEARNING_RATE * input[inputIndex] * hiddenDeltas[hiddenIndex];
                    //std::cout << input[inputIndex] << ", " << hiddenDeltas[hiddenIndex] << std::endl;
                    //assert(hiddenLayer[hiddenIndex].weights[hiddenIndex] > -1000000);
                }
            }
        }
        //std::cout << "MSE: " << MSE << std::endl;
    }
}

int SHLNeuralClassifier::classify(unsigned char *image) {
    // convert image to vector
    std::vector<double> input;
    for (int row = 0; row < model->imageHeight; row++) {
        for (int col = 0; col < model->imageWidth; col++) {
            //std::cout << row << ", " << col << ": " << i << "\n";
            input.push_back(getPixel(image, row, col, model->imageWidth) / 255.0);
        }
    }
    
    // 1. input layer to hidden layer
    for (int hiddenIndex = 0; hiddenIndex < hiddenLayer.size(); hiddenIndex++) {
        hiddenLayer[hiddenIndex].predict(input);
    }
    
    // vectorize hidden nodes that are connected to this output node
    std::vector<double> hiddenValues;
    for (int hiddenIndex = 0; hiddenIndex < hiddenLayer.size(); hiddenIndex++) {
        hiddenValues.push_back(hiddenLayer[hiddenIndex].value);
    }
    
    // 2. hidden layer to output layer
    int argmax = -1;
    double maxPrediction = -1;
    for (int outputIndex = 0; outputIndex < outputLayer.size(); outputIndex++) {
        double prediction = outputLayer[outputIndex].predict(hiddenValues);
        if (prediction > maxPrediction) {
            maxPrediction = prediction;
            argmax = outputIndex;
        }
        //std::cout << "Label: " << indexToLabel[outputIndex] << " Prediction: " << outputLayer[outputIndex].value << std::endl;
    }
    return argmax;
}