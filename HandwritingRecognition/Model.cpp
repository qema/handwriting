//
//  Model.cpp
//  HandwritingRecognition
//
//  Created by Andrew Wang on 8/19/14.
//  Copyright (c) 2014 Andrew Wang. All rights reserved.
//

#include "Model.h"
#include <fstream>
#include <iostream>
#include <assert.h>

// utility
unsigned char getPixel(unsigned char *image, int row, int col, int imageWidth) {
    return image[row * imageWidth + col];
}

void drawImage(unsigned char *image, int imageWidth, int imageHeight) {
    for (int i = 0; i < imageHeight; i++) {
        for (int j = 0; j < imageWidth; j++) {
            char c = getPixel(image, i, j, imageWidth) > 127 ? '*' : ' ';
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

// ints are stored in high endian in the buffer.
unsigned long get32BitInt(unsigned char buffer[], int start) {
    unsigned long num = (buffer[start] << 24) + (buffer[start+1] << 16) + (buffer[start+2] << 8) + buffer[start+3];
    return num;
}

Model::Model(std::string labelFile, std::string imageFile) {
    loadLabels(labelFile);
    loadImages(imageFile);
}

Model::Model(const Model &model) : labels(model.labels) {
    numDataPoints = model.numDataPoints;
    imageWidth = model.imageWidth;
    imageHeight = model.imageHeight;
    
    for (int i = 0; i < model.numDataPoints; i++) {
        unsigned char *image = new unsigned char[imageWidth * imageHeight];
        std::memcpy(image, model.images[i], imageWidth * imageHeight * sizeof(unsigned char));
        images.push_back(image);
    }
}

std::set<int> Model::getAllPossibleLabels() {
    return allPossibleLabels;
}

void Model::loadLabels(std::string labelFile) {
    std::ifstream fin(labelFile, std::ios::binary | std::ios::ate);
    long long length = fin.tellg();
    fin.seekg(std::ios::beg);
    
    unsigned char *buffer = new unsigned char[length];
    
    fin.read((char *)buffer, length);
    fin.close();
    
    unsigned long sig = get32BitInt(buffer, 0);
    assert(sig == 2049);    // must match signature
    
    unsigned long numLabels = get32BitInt(buffer, 4);
    numDataPoints = (int)numLabels;
    
    for (int i = 0; i < numLabels; i++) {
        int label = buffer[8 + i];
        allPossibleLabels.insert(label);
        labels.push_back(label);
    }
    
    delete [] buffer;
}

void Model::loadImages(std::string imageFile) {
    std::ifstream fin(imageFile, std::ios::binary | std::ios::ate);
    long long length = fin.tellg();
    fin.seekg(std::ios::beg);
    
    unsigned char *buffer = new unsigned char[length];
    fin.read((char *)buffer, length);
    fin.close();
    
    unsigned long sig = get32BitInt(buffer, 0);
    assert(sig == 2051);    // must match signature
    
    unsigned long numImages = get32BitInt(buffer, 4);
    
    int numRows = (int)get32BitInt(buffer, 8);
    imageWidth = numRows;
    int numCols = (int)get32BitInt(buffer, 12);
    imageHeight = numCols;
    
    long long index = 16;
    for (int i = 0; i < numImages; i++) {
        unsigned char *image = new unsigned char[numRows*numCols];
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
                image[row*numRows+col] = buffer[index++];
            }
        }
        images.push_back(image);
    }
    
    delete [] buffer;
}

Model::~Model() {
    for (int i = 0; i < images.size(); i++) {
        delete [] images[i];
    }
}