//
//  main.cpp
//  HandwritingRecognition
//
//  Created by Andrew Wang on 8/19/14.
//  Copyright (c) 2014 Andrew Wang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Model.h"
#include "KNNClassifier.h"
#include "SHLNeuralNetClassifier.h"

int main(int argc, const char * argv[]) {
    Model *trainingModel = new Model("smallset-labels", "smallset-images");
    Model *testingModel = new Model("smallset-labels", "smallset-images");
    
    //SHLNeuralClassifier classifier(trainingModel);
    KNNClassifier classifier(trainingModel, 5);
    std::cout << "Done learning.\n";
    
    int total = 0, successes = 0;
    int totalForDigit[10], successesForDigit[10];
    for (int i = 0; i < 10; i++) {
        totalForDigit[i] = 0;
        successesForDigit[i] = 0;
    }
    
    for (int i = 0; i < testingModel->numDataPoints; i++) {
        int actual = testingModel->labels[i];
        drawImage(testingModel->images[i], 28, 28);
        int prediction = classifier.classify(testingModel->images[i]);
        
        std::cout << "That looks like a " << prediction << std::endl;
        
        // update success/total for this digit
        if (prediction == actual) {
            successesForDigit[actual]++;
        }
        totalForDigit[actual]++;
        
        // update success/total
        if (prediction == actual) {
            successes++;
        }
        total++;
        
        // progress report
        if (i % 100 == 0) {
            //std::cout << 100 * i / testingModel->numDataPoints << "% complete." << std::endl;
        }
        
        std::string dummy;
        std::cin >> dummy;
    }
    
    std::cout << " -- Digit Recognition Results --\n";
    std::cout << "By digit:\n";
    for (int i = 0; i < 10; i++) {
        std::cout << "Digit: " << i << "\n";
        std::cout << "Correctly predicted " << successesForDigit[i] << " out of " << totalForDigit[i] << " times.\n";
        std::cout << "Accuracy: " << (float)successesForDigit[i] / totalForDigit[i] << "\n\n";
    }
    std::cout << "--------\n";
    std::cout << "Summary:\n";
    std::cout << "Correctly predicted " << successes << " out of " << total << " times.\n";
    std::cout << "Accuracy: " << (float)successes / total << "\n";
    
    return 0;
}
