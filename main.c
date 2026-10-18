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
#include "ff.h"
#include "fat_sd_spi.h"
#include "stm32c5xx_hal_spi.h"
#include "mx_spi1.h"
#include "stm32c5xx_hal_uart.h"

FATFS fs;
FIL file;
FRESULT fresult;
UINT br, bw;

static char read_data[256];

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
  {
    return (-1);
  }
  else
  {
    printf("Mounting...\n");
    fresult = f_mount(&fs, "", 1);

    if (fresult == FR_OK) {
      printf("Mounted...\n");
      printf("Opening...\n");
      fresult = f_open(&file, "index.txt", FA_READ);
    
      if (fresult == FR_OK) {

        printf("Opened...\n");
        f_read(&file, read_data, sizeof(read_data)-1, &br);
        printf("Read %u bytes...\n", br);
        read_data[br] = '\0'; // Always null-terminate strings
        printf("Closed String...\n");
        f_close(&file);
        printf("Closed file...\n");

        printf("%s\n", read_data);
      }
    } else {
      printf("No mounty\n");
    }

    while (1) {
      HAL_Delay(1000);
    }
  }
} /* end main */

