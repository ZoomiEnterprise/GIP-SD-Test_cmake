#ifndef SD_H
#define SD_H

#include "ff.h"
#include <stdint.h>
#include <stdio.h>

typedef 

struct {
    FATFS fs;
    FIL file;
    FRESULT result;
    UINT br, bw;
} sdcard_t;

void SDCard(sdcard_t* card);

void deleteFile(sdcard_t* card, char* path);

void mkdir(sdcard_t* card, char* path);

void touch(sdcard_t* card, char* path);

void readBytes(sdcard_t* card, char* path, uint8_t* buffer, unsigned long bufLength, unsigned long offset, int noFile);

void writeBytes(sdcard_t* card, char* path, uint8_t* buffer, unsigned long bufLength, unsigned long offset);

void appendBytes(sdcard_t* card, char* path, uint8_t* buffer, unsigned long bufLength);

#endif