/*
 * readBMP.h
 *
 *  Created on: 2026
 *      Author: Kateryna Deren
 */
#include "BMP_types.h".
#include <stdint.h>
int processBMP(void);
bool readButton();
void drawCompresedImage(RGBQUAD* palette, uint32_t w, uint32_t h);
void drawImage8(int w, int h,int biClrUsed);
void drawImage24(uint32_t w, uint32_t h);
void drawImage24Lines(uint32_t w, uint32_t h);
void drawImage8Lines(int w, int h,int biClrUsed);