#include "sd.h"
#include "ff.h"
#include <stdio.h>

void SDCard(sdcard_t* card) {
    printf("Mounting card;\n");
    card->result = f_mount(&(card->fs), "", 1);
    if (card->result != FR_OK)
        printf("Mount Error\n");
}

void deleteFile(sdcard_t *card, char *path) { // werkt nog niet
    if (card == NULL) { // check of de sdcard_t valid is
        printf("Card is NULL;\n");
        return;
    }

    card->result = f_unlink(path);
    if (card->result != FR_OK) {
        printf("File could not be deleted;\n");
        return;
    }
}

void readBytes(sdcard_t* card, char* path, uint8_t* buffer, unsigned long bufLength, unsigned long offset) {
    if (card == NULL) { // check of de sdcard_t valid is
        printf("Card is NULL;\n");
        return;
    }

    // open het bestand
    card->result = f_open(&card->file, path, FA_READ);
    if (card->result != FR_OK){ // fout
        printf("Open Error\n");
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
        printf("File could not be opened/created;\n");
        return;
    }

    card->result = f_lseek(&(card->file), offset);
    if (card->result != FR_OK) { // fout
        printf("Seek Error;\n");
        f_close(&(card->file));
        return;
    }

    card->result = f_write(&(card->file), buffer, bufLength, &(card->bw));
    if (card->result != FR_OK) {
        printf("Write Error;\n");
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
        printf("File could not be opened/created;\n");
        return;
    }

    card->result = f_lseek(&(card->file), card->file.fsize);
    if (card->result != FR_OK) { // fout
        printf("Seek Error;\n");
        f_close(&(card->file));
        return;
    }

    card->result = f_write(&(card->file), buffer, bufLength, &(card->bw));
    if (card->result != FR_OK) {
        printf("Write Error;\n");
    }
    f_close(&(card->file));
}