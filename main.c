/**
  ******************************************************************************
  * file           : main.c
  * brief          : Main program body
  *                  Calls target system initialization then loop in main.
  ******************************************************************************
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "mx_usart2.h"
#include "stdio.h"
#include "fat_sd_spi.h"
#include "stm32c5xx_hal_spi.h"
#include "mx_spi1.h"
#include "stm32c5xx_hal_uart.h"
#include "sd.h"
#include <stdlib.h>
#include <time.h>

sdcard_t card;
uint8_t buffer[512];

/* Serial Port */
int _write(int file, char *ptr, int len)
{
    // ST-approved way to retrieve the modern static handle pointer in CubeMX2
    hal_uart_handle_t *p_huart2 = mx_usart2_uart_gethandle(); 

    if (p_huart2 != NULL) {
        // Transmit your print data using the validated handle pointer
        HAL_UART_Transmit(p_huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
    }
    return len;
}

int main(void)
{
  if (mx_system_init() != SYSTEM_OK)
    return (-1);

  SDCard(&card);

  // stream read test
  printf("ShadowAssasin.mp3 Reading...\n");
  unsigned long offset = 0;
  int eof = 0;

  f_open(&(card.file), "songs/ShadowAssasin.mp3", FA_READ);

  while(eof==0) {
    f_read(&(card.file), buffer, 512, &(card.br));
    //printf(buffer);
    if (card.br < 512)
      eof = 1;
  }

  f_close(&(card.file));
  printf("\nFile played; EOF\n");

  while (1) {
    HAL_Delay(1000);
  }
} /* end main */