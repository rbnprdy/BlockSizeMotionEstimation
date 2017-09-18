//
//  vbsme.h
//  BlockSizeMotionEstimation
//
//  Created by Ruben Purdy on 9/15/17.
//  Copyright © 2017 arizona. All rights reserved.
//

#ifndef vbsme_h
#define vbsme_h

#include <stdio.h>

int* blockSizeMotionEstimation(int *asize, int *frame, int *window);

int sumAbsoluteDiffFrame(int *asize, int *frame, int *window, int yPos, int xPos);

int sumAbsoluteDiffPixel(int framePixel, int windowPixel);

#endif /* vbsme_h */
