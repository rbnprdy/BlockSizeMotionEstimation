//
//  vbsme.c
//  BlockSizeMotionEstimation
//
//  Created by Ruben Purdy on 9/15/17.
//  Copyright © 2017 arizona. All rights reserved.
//

#include "vbsme.h"

int* blockSizeMotionEstimation(int *asize, int *frame, int *window) {
    
    static int coords[2] = {0,0}; // Row, Column (v0, v1)
    
    int minSum = 100000;
    
    int frameHeight = asize[0];
    int frameLength = asize[1];
    int windowHeight = asize[2];
    int windowLength = asize[3];
    
    int top = 0;
    int bottom = frameHeight - windowHeight;
    
    int left = 0;
    int right = frameLength - windowLength;
    
    int dir = 0;
    
    while (!(top > bottom) || !(left > right)) {
        int i = 0;
        if (dir == 0) {
            // Iterate from left to right
            for (i = left; i <= right; i++) {
                int tempSum = sumAbsoluteDiffFrame(asize, frame, window, top, i);
                if (tempSum < minSum) {
                    minSum = tempSum;
                    coords[0] = top;
                    coords[1] = i;
                }
            }
            top++;
            dir = 1;
        } else if (dir == 1) {
            // Iterate from top to bottom
            for (i = top; i <= bottom; i++) {
                int tempSum = sumAbsoluteDiffFrame(asize, frame, window, i, right);
                if (tempSum < minSum) {
                    minSum = tempSum;
                    coords[0] = i;
                    coords[1] = right;
                }
            }
            right--;
            dir = 2;
        } else if (dir == 2) {
            // Iterate from right to left
            for (i = right; i >= left; i--) {
                int tempSum = sumAbsoluteDiffFrame(asize, frame, window, bottom, i);
                if (tempSum < minSum) {
                    minSum = tempSum;
                    coords[0] = bottom;
                    coords[1] = i;
                }
            }
            bottom--;
            dir = 3;
        } else {
            // Iterate from bottom to top
            for (i = bottom; i >= top; i--) {
                int tempSum = sumAbsoluteDiffFrame(asize, frame, window, i, left);
                if (tempSum < minSum) {
                    minSum = tempSum;
                    coords[0] = i;
                    coords[1] = left;
                }
            }
            left++;
            dir = 0;
        }
    }
    
    return coords;
}

int sumAbsoluteDiffFrame(int *asize, int *frame, int *window, int yPos, int xPos) {
    
    int sum = 0;
    int i, j;
    int frameLength = asize[1];
    int windowHeight = asize[2];
    int windowLength = asize[3];
    
    int frameOffset = yPos*frameLength + xPos;
    int windowOffset = 0;
    
    // Iterate through the height of the window
    for (i = 0; i < windowHeight; i++) {
        // Iterates through the length of the window
        for (j = 0; j < windowLength; j++) {
            // j stores x pos, i stores y pos (must multiply by length to get position in 1d array)
            sum += sumAbsoluteDiffPixel(frame[frameOffset], window[windowOffset]);
            frameOffset++;
            windowOffset++;
        }
        frameOffset += frameLength - windowLength;
    }
    return sum;
}

int sumAbsoluteDiffPixel(int framePixel, int windowPixel) {
    if (framePixel > windowPixel) {
        return framePixel - windowPixel;
    } else {
        return windowPixel - framePixel;
    }
}
