/*
 * readBMP.h
 *
 *  Created on: 2026
 *      Author: Kateryna Deren
 */
#include "BMP_types.h"
#include <stdint.h>
int processBMP(void);
void drawCompresedImage(RGBQUAD* palette, uint32_t w);
void drawImage8(int w, int h,int biClrUsed);
void drawImage24(uint32_t w, uint32_t h);
