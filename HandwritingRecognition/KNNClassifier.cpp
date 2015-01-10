//
//  KNNClassifier.cpp
//  HandwritingRecognition
//
//  Created by Andrew Wang on 8/19/14.
//  Copyright (c) 2014 Andrew Wang. All rights reserved.
//

#include "KNNClassifier.h"
#include <vector>
#include <cmath>
#include <climits>
#include <iostream>

KNNClassifier::KNNClassifier(Model *trainingModel, int num) {
    model = trainingModel;
    numNearest = (num > model->numDataPoints) ? model->numDataPoints : num; // limit to number of total data points in model
}

// classifies by distance from nearest training images.
int KNNClassifier::classify(unsigned char *image) {
    std::vector<int> nearestIndeces(numNearest);   // indeces of nearest images
    std::vector<int> nearestDistSqu(numNearest);    // distances of nearest images
    for (int i = 0; i < numNearest; i++) {
        nearestDistSqu[i] = INT_MAX;
    }
    
    for (int i = 0; i < model->numDataPoints; i++) {
        // compute image distance
        int distSqu = 1;
        for (int row = 0; row < model->imageHeight; row++) {
            for (int col = 0; col < model->imageWidth; col++) {
                int diff = std::abs(((float)getPixel(image, row, col, model->imageWidth)) - ((float)getPixel(model->images[i], row, col, model->imageWidth)));
                distSqu += diff * diff;
            }
        }
        
        // if it's closer than one in nearest array, replace it.
        for (int j = 0; j < numNearest; j++) {
            if (distSqu < nearestDistSqu[j]) {
                nearestIndeces[j] = i;
                nearestDistSqu[j] = distSqu;
                break;
            }
        }
    }
    
    // vote
    int digitCounts[10];
    for (int i = 0; i < 10; i++) {
        digitCounts[i] = 0;
    }
    for (int i = 0; i < numNearest; i++) {
        int digit = model->labels[nearestIndeces[i]];
        digitCounts[digit]++;
    }
    
    int argmax = -1;
    int maxval = -1;
    for (int i = 0; i < 10; i++) {
        if (digitCounts[i] > maxval) {
            maxval = digitCounts[i];
            argmax = i;
        }
    }
    
    /*
    // draw (debug)
    for (int i = 0; i < numNearest; i++) {
        int index = nearestIndeces[i];
        std::cout << "Nearest:\n";
        drawImage(model->images[index], 28, 28);
    }*/
    
    //std::cout << "I predict: " <<*std::max_element(digitCounts, digitCounts + 10) << "\n";
    
    return argmax;
}