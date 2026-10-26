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

sdcard_t card;

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

  // read test
  printf("\nRead Test;\n");
  uint8_t* data = malloc(128*sizeof(uint8_t));
  readBytes(&card, "index.txt", data, 127, 0);
  data[card.br] = '\n';
  data[card.br+1] = '\0';
  printf((char*)data);
  readBytes(&card, "index.txt", data, 127, 127);
  data[card.br] = '\n';
  data[card.br+1] = '\0';
  printf((char*)data);

  // write test
  printf("\nWrite Test;\n");
  uint8_t* wdata = "La di dada la ti dada la ti dada day, ladidada day!";
  writeBytes(&card, "day.txt", wdata, 52, 0);

  //append test
  printf("\nAppend Test;\n");
  uint8_t* adata = "\ncuz i may not have a home, but that's way okay.";
  appendBytes(&card, "day.txt", adata, 48);

  // delete test
  printf("\nDelete Test;\n");
  deleteFile(&card, "dayNOF.txt");

  //append test - no file
  printf("\nAppend Test; NOF\n");
  appendBytes(&card, "dayNOF.txt", adata, 48);

  while (1) {
    HAL_Delay(1000);
  }
} /* end main */