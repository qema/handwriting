//
//  KNNClassifier.h
//  HandwritingRecognition
//
//  Created by Andrew Wang on 8/19/14.
//  Copyright (c) 2014 Andrew Wang. All rights reserved.
//

#ifndef __HandwritingRecognition__KNNClassifier__
#define __HandwritingRecognition__KNNClassifier__

#include <stdio.h>
#include "Classifier.h"
#include "Model.h"

class KNNClassifier : Classifier {
public:
    KNNClassifier(Model *trainingModel, int numNearest);
    int classify(unsigned char *image);
    
    int numNearest;
private:
    Model *model;
};

#endif /* defined(__HandwritingRecognition__KNNClassifier__) */
