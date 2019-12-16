//
//  imageProc.cpp
//
//  Created by Michael Grierson on 13/11/2017.
//    Updated by Michael Zbyszynski on 12/11/2019.
//

#include "imageProc.hpp"

// Assumes RBG

ofPixels imageProc::threshRBG(ofPixels pixIn, ofPixels pixOut, int thresh) {
    
    for (int i = 0; i < pixIn.getWidth() * pixIn.getHeight() * pixIn.getNumChannels(); ++i) {
        if (pixIn[i] > thresh) {
            pixOut[i] = pixIn[i];
        }
        else {
            pixOut[i] = 0;
        }
    }
    
    return pixOut;
}

ofPixels imageProc::iThreshRBG(ofPixels pixIn, ofPixels pixOut, int thresh) {
    
    for (int i = 0; i < pixIn.getWidth() * pixIn.getHeight() * pixIn.getNumChannels(); ++i) {
        if (pixIn[i] < thresh) {
            pixOut[i] = pixIn[i];
        }
        else {
            pixOut[i] = 0;
        }
    }
    
    return pixOut;
}

// Assumes RGB
// 0.2126*R + 0.7152*G + 0.0722*B
ofPixels imageProc::threshGreyscale(ofPixels pixIn, ofPixels pixOut, int thresh) {
    
    for (int i = 0; i < pixIn.getWidth() * pixIn.getHeight() * pixIn.getNumChannels(); i += pixIn.getNumChannels()) {
        // we're not resizing, so there's lots of reduntant data
        pixOut[i] = pixOut[i + 1] = pixOut[i + 2] = (pixIn[i] * 0.2126) + (pixIn[i + 1] * 0.7152) + (pixIn[i + 2] * 0.0722);
        
        if (pixOut[i] < thresh) {
            pixOut[i] = pixOut[i + 1] = pixOut[i + 2] = 0;
        }
    }
    
    return pixOut;
}

// Assumes RGB
// 0.2126*R + 0.7152*G + 0.0722*B
ofPixels imageProc::iThreshGreyscale(ofPixels pixIn, ofPixels pixOut, int thresh) {
    
    for (int i = 0; i < pixIn.getWidth() * pixIn.getHeight() * pixIn.getNumChannels(); i += pixIn.getNumChannels()) {
        // we're not resizing, so there's lots of reduntant data
        pixOut[i] = pixOut[i + 1] = pixOut[i + 2] = (pixIn[i] * 0.2126) + (pixIn[i + 1] * 0.7152) + (pixIn[+2] * 0.0722);
        
        if (pixOut[i] > thresh) {
            pixOut[i] = pixOut[i + 1] = pixOut[i + 2] = 0;
        }
    }
    
    return pixOut;
}


// Assumes RGB
// 0.2126*R + 0.7152*G + 0.0722*B
ofPixels imageProc::greyscale(ofPixels pixIn, ofPixels pixOut) {
    
    for (int i = 0; i < pixIn.getWidth() * pixIn.getHeight() * pixIn.getNumChannels(); i += pixIn.getNumChannels()) {
        // we're not resizing, so there's lots of reduntant data
        pixOut[i] = pixOut[i + 1] = pixOut[i + 2] = (pixIn[i] * 0.2126) + (pixIn[i + 1] * 0.7152) + (pixIn[+2] * 0.0722);
    }
    
    return pixOut;
}

ofPixels imageProc::motionBlur(ofPixels pixIn, ofPixels pixOut, float blur) {
    
    for (int i = 0; i < pixIn.getWidth() * pixIn.getHeight() * pixIn.getNumChannels(); ++i) {
        pixOut[i] = lastVals[i % 3] + blur * (pixIn[i] - lastVals[i % 3]);
        lastVals[i % 3] = pixOut[i];
    }
    
    return pixOut;
}

ofPixels imageProc::simpleHighPass(ofPixels pixIn, ofPixels pixOut, float blur) {
    
    for (int i = 0; i < pixIn.getWidth() * pixIn.getHeight() * pixIn.getNumChannels(); ++i) {
        pixOut[i] = lastVals[i % 3] + blur * (pixIn[i] - lastVals[i % 3]);
        lastVals[i % 3] = pixOut[i];
        pixOut[i] = pixIn[i] - pixOut[i];
    }
    
    return pixOut;
}

ofPixels imageProc::simpleEdgeDetect(ofPixels pixIn, ofPixels pixOut, float edge) {
    
    for (int i = 0; i < pixIn.getWidth() * pixIn.getHeight() * pixIn.getNumChannels(); ++i) {
        pixOut[i] = lastVals[i % 3] + edge * (pixIn[i] - lastVals[i % 3]);
        lastVals[i % 3] = pixOut[i];
        pixOut[i] = pixIn[i] - pixOut[i];
    }
    
    return pixOut;
}

ofPixels imageProc::resizeX(ofPixels pixIn, ofPixels pixOut, float resize) {
    
    for (int i = 0; i < pixIn.getHeight() * pixIn.getWidth() * pixIn.getNumChannels(); i += pixIn.getWidth() * pixIn.getNumChannels()) {
        for (int j = 0; j < pixIn.getWidth(); j++) {
            pixOut[i + (j * 3)] = pixIn[i + (floor(j * resize) * 3)];
            pixOut[i + (j * 3) + 1] = pixIn[i + (floor(j * resize) * 3) + 1];
            pixOut[i + (j * 3) + 2] = pixIn[i + (floor(j * resize) * 3) + 2];
        }
    }
    
    return pixOut;
}

ofPixels imageProc::resizeY(ofPixels pixIn, ofPixels pixOut, float resize) {
    
    int totalSize = pixIn.getHeight() * pixIn.getWidth() * pixIn.getNumChannels();
    
    for (int i = 0; i < pixIn.getHeight(); i++) {
        int coll = i * pixIn.getWidth() * pixIn.getNumChannels();
        int resizedY = floor(i * resize) * pixIn.getWidth() * pixIn.getNumChannels();
        
        for (int j = 0; j < pixIn.getWidth(); j++) {
            pixOut[coll + (j * 3)] = pixIn[fmod(resizedY + (j * 3), totalSize)];
            pixOut[coll + (j * 3) + 1] = pixIn[fmod(resizedY + (j * 3) + 1, totalSize)];
            pixOut[coll + (j * 3) + 2] = pixIn[fmod(resizedY + (j * 3) + 2, totalSize)];
        }
        
    }
    
    return pixOut;
}

ofPixels imageProc::resize(ofPixels pixIn, ofPixels pixOut, float resize) {
    
    int totalSize = pixIn.getHeight() * pixIn.getWidth() * pixIn.getNumChannels();
    
    for (int i = 0; i < pixIn.getHeight(); i++) {
        int coll = i * pixIn.getWidth() * pixIn.getNumChannels();
        int resizedY = floor(i * resize) * pixIn.getWidth() * pixIn.getNumChannels();
        
        for (int j = 0; j < pixIn.getWidth(); j++) {
            pixOut[coll + (j * 3)] = pixIn[fmod(resizedY + (floor(j * resize) * 3), totalSize)];
            pixOut[coll + (j * 3) + 1] = pixIn[fmod(resizedY + (floor(j * resize) * 3) + 1, totalSize)];
            pixOut[coll + (j * 3) + 2] = pixIn[fmod(resizedY + (floor(j * resize) * 3) + 2, totalSize)];
            
        }
    }
    return pixOut;
}

ofPixels imageProc::resizeXY(ofPixels pixIn, ofPixels pixOut, float resizeX, float resizeY) {
    
    int totalSize = pixIn.getHeight() * pixIn.getWidth() * pixIn.getNumChannels();
    
    for (int i = 0; i < pixIn.getHeight(); i++) {
        
        int coll = i * pixIn.getWidth() * pixIn.getNumChannels();
        int resizedY = floor(i * resizeY) * pixIn.getWidth() * pixIn.getNumChannels();
        
        for (int j = 0; j < pixIn.getWidth(); j++) {
            
            pixOut[coll + (j * 3)] = pixIn[fmod(resizedY + (floor(j * resizeX) * 3), totalSize)];
            pixOut[coll + (j * 3) + 1] = pixIn[fmod(resizedY + (floor(j * resizeX) * 3) + 1, totalSize)];
            pixOut[coll + (j * 3) + 2] = pixIn[fmod(resizedY + (floor(j * resizeX) * 3) + 2, totalSize)];
            
        }
        
    }
    
    return pixOut;
}

ofPixels imageProc::resizeXY(ofPixels pixIn, ofPixels pixOut, float resizeX, float resizeY, float anchorX, float anchorY) {
    
    int totalSize = pixIn.getHeight() * pixIn.getWidth() * pixIn.getNumChannels();
    
    for (int i = 0; i < pixIn.getHeight(); i++) {
        
        int coll = i * pixIn.getWidth() * pixIn.getNumChannels();
        int resizedY = floor((i + anchorY) * resizeY) * pixIn.getWidth() * pixIn.getNumChannels();
        
        for (int j = 0; j < pixIn.getWidth(); j++) {
            
            pixOut[coll + (j * 3)] = pixIn[fmod(resizedY + (floor((j + anchorX) * resizeX) * 3), totalSize)];
            pixOut[coll + (j * 3) + 1] = pixIn[fmod(resizedY + (floor((j + anchorX) * resizeX) * 3) + 1, totalSize)];
            pixOut[coll + (j * 3) + 2] = pixIn[fmod(resizedY + (floor((j + anchorX) * resizeX) * 3) + 2, totalSize)];
            
        }
        
    }
    
    return pixOut;
}

ofPixels imageProc::rotate(ofPixels pixIn, ofPixels pixOut, float theta) {
    
    int numChannels = pixIn.getNumChannels();
    int totalSize = pixIn.getHeight() * pixIn.getWidth() * numChannels;
    
    theta = fmod(theta, TWO_PI);
    
    for (int i = 0; i < pixIn.getHeight(); i++) {
        
        for (int j = 0; j < pixIn.getWidth(); j++) {
            
            // basic rotation. Note the output is int.
            // otherwise you get weird distortion.
            int x = floor((cos(theta) * j) - (sin(theta) * i));
            int y = floor((sin(theta) * j) + (cos(theta) * i));
            
            int coll = i * pixIn.getWidth() * numChannels;
            
            if (x * y >= 0 && x * y <= pixIn.getHeight() * pixIn.getWidth() * numChannels) {
                
                pixOut[coll + (j * numChannels)] = pixIn[(y * pixIn.getWidth() * numChannels) + x * numChannels];
                pixOut[coll + (j * numChannels) + 1] = pixIn[(y * pixIn.getWidth() * numChannels) + (x * numChannels) + 1];
                pixOut[coll + (j * numChannels) + 2] = pixIn[(y * pixIn.getWidth() * numChannels) + (x * numChannels) + 2];
                
            }
            
        }
        
    }
    
    return pixOut;
}

ofPixels imageProc::rotate(ofPixels pixIn, ofPixels pixOut, float theta, int anchorX, int anchorY, int offsetX, int offsetY, float zoomX, float zoomY) {
    
    int numChannels = pixIn.getNumChannels();
    int totalSize = pixIn.getHeight() * pixIn.getWidth() * numChannels;
    
    theta = fmod(theta, TWO_PI);
    
    for (int i = 0; i < pixIn.getHeight(); i++) {
        
        for (int j = 0; j < pixIn.getWidth(); j++) {
            
            // Full Rotation code, including offset, anchor and zoom
            
            int x = floor((cos(theta) / zoomX) * (j - (offsetX + anchorX)) - (sin(theta) / zoomY) * (i - (offsetY + anchorY))) + anchorX;
            int y = floor((sin(theta) / zoomX) * (j - (offsetX + anchorX)) + (cos(theta) / zoomY) * (i - (offsetY + anchorY))) + anchorY;
            
            int coll = i * pixIn.getWidth() * numChannels;
            
            if ((y * pixIn.getWidth() * numChannels) + x * numChannels >= 0 && (y * pixIn.getWidth() * numChannels) + x * numChannels <= pixIn.getHeight() * pixIn.getWidth() * numChannels) {
                
                pixOut[coll + (j * numChannels)] = pixIn[(y * pixIn.getWidth() * numChannels) + x * numChannels];
                pixOut[coll + (j * numChannels) + 1] = pixIn[(y * pixIn.getWidth() * numChannels) + (x * numChannels) + 1];
                pixOut[coll + (j * numChannels) + 2] = pixIn[(y * pixIn.getWidth() * numChannels) + (x * numChannels) + 2];
                
            }
            else {
                pixOut[coll + (j * numChannels)] = 0;
                pixOut[coll + (j * numChannels) + 1] = 0;
                pixOut[coll + (j * numChannels) + 2] = 0;
                
            }
            
        }
        
    }
    
    return pixOut;
}

ofPixels imageProc::convolve(ofPixels pixIn, ofPixels pixOut, float kernel[9]) {
    
    for (int i = 1; i < pixIn.getHeight() - 1; i++) {
        
        int collm1 = (i - 1) * pixIn.getWidth() * pixIn.getNumChannels();
        int coll = i * pixIn.getWidth() * pixIn.getNumChannels();
        int collp1 = (i + 1) * pixIn.getWidth() * pixIn.getNumChannels();
        for (int j = 1; j < pixIn.getWidth() - 1; j++) {
            
            pixOut[coll + (j * 3)] = ((pixIn[collm1 + ((j - 1) * 3)] * kernel[0]) + (pixIn[collm1 + ((j) * 3)] * kernel[1]) + (pixIn[collm1 + ((j + 1) * 3)] * kernel[2]) + (pixIn[coll + ((j - 1) * 3)] * kernel[3]) + (pixIn[coll + ((j) * 3)] * kernel[4]) + (pixIn[coll + ((j + 1) * 3)] * kernel[5]) + (pixIn[collp1 + ((j - 1) * 3)] * kernel[6]) + (pixIn[coll + ((j) * 3)] * kernel[7]) + (pixIn[collp1 + ((j + 1) * 3)] * kernel[8]));
            pixOut[coll + (j * 3) + 1] = ((pixIn[collm1 + ((j - 1) * 3) + 1] * kernel[0]) + (pixIn[collm1 + ((j) * 3) + 1] * kernel[1]) + (pixIn[collm1 + ((j + 1) * 3) + 1] * kernel[2]) + (pixIn[coll + ((j - 1) * 3) + 1] * kernel[3]) + (pixIn[coll + ((j) * 3) + 1] * kernel[4]) + (pixIn[coll + ((j + 1) * 3) + 1] * kernel[5]) + (pixIn[collp1 + ((j - 1) * 3) + 1] * kernel[6]) + (pixIn[coll + ((j) * 3) + 1] * kernel[7]) + (pixIn[collp1 + ((j + 1) * 3) + 1] * kernel[8]));
            pixOut[coll + (j * 3) + 2] = ((pixIn[collm1 + ((j - 1) * 3) + 2] * kernel[0]) + (pixIn[collm1 + ((j) * 3) + 2] * kernel[1]) + (pixIn[collm1 + ((j + 1) * 3) + 2] * kernel[2]) + (pixIn[coll + ((j - 1) * 3) + 2] * kernel[3]) + (pixIn[coll + ((j) * 3) + 2] * kernel[4]) + (pixIn[coll + ((j + 1) * 3) + 2] * kernel[5]) + (pixIn[collp1 + ((j - 1) * 3) + 2] * kernel[6]) + (pixIn[coll + ((j) * 3) + 2] * kernel[7]) + (pixIn[collp1 + ((j + 1) * 3) + 2] * kernel[8]));
            
        }
        
    }
    
    return pixOut;
    
}




