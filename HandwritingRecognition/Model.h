//
//  Model.h
//  HandwritingRecognition
//
//  Created by Andrew Wang on 8/19/14.
//  Copyright (c) 2014 Andrew Wang. All rights reserved.
//

#ifndef __HandwritingRecognition__Model__
#define __HandwritingRecognition__Model__

#include <stdio.h>
#include <string>
#include <vector>
#include <set>

unsigned char getPixel(unsigned char *image, int row, int col, int imageWidth);
void drawImage(unsigned char *image, int imageWidth, int imageHeight);

class Model {
public:
    Model(std::string labelFile, std::string imageFile);
    Model(const Model &model);
    ~Model();
    std::set<int> getAllPossibleLabels();
    
    // data
    int numDataPoints;
    int imageWidth, imageHeight;
    std::vector<int> labels;
    std::vector<unsigned char*> images;  // each image is stored in row-major order
    
private:
    void loadLabels(std::string labelFile);
    void loadImages(std::string imageFile);
    
    std::set<int> allPossibleLabels;
};

#endif /* defined(__HandwritingRecognition__Model__) */
