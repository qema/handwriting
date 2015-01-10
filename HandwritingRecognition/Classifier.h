//
//  Classifier.h
//  HandwritingRecognition
//
//  Created by Andrew Wang on 8/19/14.
//  Copyright (c) 2014 Andrew Wang. All rights reserved.
//

#ifndef __HandwritingRecognition__Classifier__
#define __HandwritingRecognition__Classifier__

#include <stdio.h>

class Classifier {
public:
    virtual int classify(unsigned char *image) { return -1; }
};

#endif /* defined(__HandwritingRecognition__Classifier__) */
