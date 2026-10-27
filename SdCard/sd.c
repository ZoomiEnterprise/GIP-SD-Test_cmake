#include "sd.h"
#include "ff.h"
#include <stdio.h>

void SDCard(sdcard_t* card) {
    card->result = f_mount(&(card->fs), "", 1);
    if (card->result != FR_OK)
        printf("Mount Error; %d\n", card->result);
}

void deleteFile(sdcard_t *card, char *path) { // werkt nog niet
    if (card == NULL) { // check of de sdcard_t valid is
        printf("Card is NULL;\n");
        return;
    }

    card->result = f_unlink(path);
    if (card->result != FR_OK) {
        printf("File could not be deleted; %d\n", card->result);
        return;
    }
}

void mkdir(sdcard_t* card, char* path) {
    if (card == NULL) { // check of de sdcard_t valid is
        printf("Card is NULL;\n");
        return;
    }

    card->result = f_mkdir(path);
    if (card->result != FR_OK){ // fout
        printf("Create Error; %d\n", card->result);
        return;
    }
    f_close(&(card->file));
}

void touch(sdcard_t* card, char* path) {
if (card == NULL) { // check of de sdcard_t valid is
        printf("Card is NULL;\n");
        return;
    }

    card->result = f_open(&(card->file), path, FA_OPEN_ALWAYS);
    if (card->result != FR_OK){ // fout
        printf("Create Error; %d\n", card->result);
        return;
    }
    f_close(&(card->file));
}

void readBytes(sdcard_t* card, char* path, uint8_t* buffer, unsigned long bufLength, unsigned long offset) {
    if (card == NULL) { // check of de sdcard_t valid is
        printf("Card is NULL;\n");
        return;
    }

    // open het bestand
    card->result = f_open(&card->file, path, FA_READ);
    if (card->result != FR_OK){ // fout
        printf("Open Error; %d\n", card->result);
        return;
    }

    // zoek de offset
    card->result = f_lseek(&card->file, offset);
    if (card->result != FR_OK) { // fout
        printf("Seek Error: %d\n", card->result);
        f_close(&card->file); // sluit het bestand als de fout optreed
        return;
    }

    card->result = f_read(&(card->file), buffer, bufLength, &(card->br)); // lees een sector
    if (card->result != FR_OK) { // fout
        printf("Read Error: %d\n", card->result); // het bestand moet hier niet vroegtijdig gesloten worden omdat dat ongeacht het resultaat al gebeurt.
    }
    f_close(&(card->file));
}

void writeBytes(sdcard_t* card, char* path, uint8_t* buffer, unsigned long bufLength, unsigned long offset) {
    if (card == NULL) { // check of de sdcard_t valid is
        printf("Card is NULL;\n");
        return;
    }

    card->result = f_open(&(card->file), path,  FA_OPEN_ALWAYS|FA_READ|FA_WRITE); // FA_OPEN_ALWAYS zorgt er voor dat de file aangemaakt word als die nog niet bestaat;
    if (card->result != FR_OK) { // fout
        printf("Open Error; %d\n", card->result);
        return;
    }

    card->result = f_lseek(&(card->file), offset);
    if (card->result != FR_OK) { // fout
        printf("Seek Error; %d\n", card->result);
        f_close(&(card->file));
        return;
    }

    card->result = f_write(&(card->file), buffer, bufLength, &(card->bw));
    if (card->result != FR_OK) {
        printf("Write Error; %d\n", card->result);
    }
    f_close(&(card->file));
}


void appendBytes(sdcard_t* card, char* path, uint8_t* buffer, unsigned long bufLength) {
    if (card == NULL) { // check of de sdcard_t valid is
        printf("Card is NULL;\n");
        return;
    }

    card->result = f_open(&(card->file), path,  FA_OPEN_ALWAYS|FA_READ|FA_WRITE); // FA_OPEN_ALWAYS zorgt er voor dat de file aangemaakt word als die nog niet bestaat;
    if (card->result != FR_OK) { // fout
        printf("Open Error; %d\n", card->result);
        return;
    }

    card->result = f_lseek(&(card->file), card->file.fsize);
    if (card->result != FR_OK) { // fout
        printf("Seek Error; %d\n", card->result);
        f_close(&(card->file));
        return;
    }

    card->result = f_write(&(card->file), buffer, bufLength, &(card->bw));
    if (card->result != FR_OK) {
        printf("Write Error; %d\n", card->result);
    }
    f_close(&(card->file));
}