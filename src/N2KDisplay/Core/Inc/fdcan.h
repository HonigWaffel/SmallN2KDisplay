/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    fdcan.h
  * @brief   This file contains all the function prototypes for
  *          the fdcan.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FDCAN_H__
#define __FDCAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include <stdint.h>
#include <stdbool.h>
/* USER CODE END Includes */

extern FDCAN_HandleTypeDef hfdcan1;

/* USER CODE BEGIN Private defines */

/* Linker-Symbol importieren */
extern uint32_t FLASH_PERSISTENT_ORIGIN;
extern uint32_t FLASH_PERSISTENT_SIZE;

/* Adresse als Zahl */
#define FLASH_PERSISTENT_ADDR   ((uint32_t)&FLASH_PERSISTENT_ORIGIN)
#define FLASH_PAGE_SIZE   0x2000U
#define FLASH_BASE_ADDR   0x08000000U

#define FLASH_PERSISTENT_PAGE \
    ((FLASH_PERSISTENT_ADDR - FLASH_BASE_ADDR) / FLASH_PAGE_SIZE)


typedef enum
{
	fdcan_n2k_speed = 0,
	fdcan_n2k_depth,
	fdcan_n2k_nmode,
	fdcan_n2k_quan
}fdcan_enn2kDATA_t;

typedef enum
{
	fdcan_SEL_SCREEN1 = 0,
	fdcan_SEL_SPEED,
	fdcan_SEL_DEPTH,
	fdcan_SEL_MENUS,
	fdcan_SEL_QUAN     ///< last entry, never change!!
}fdcan_enSEL_SCREEN_t;

typedef struct {
    bool 	boNewData;
    float 	fData;
} fdcan_stN2KData_t;

typedef struct{
	uint32_t u32Init;
	uint32_t u32SelScreen;
	uint32_t reserved[2];   // Padding → 16 Byte
}fdcan_stSCREEN_SEL_t;

extern fdcan_stSCREEN_SEL_t fdcan_stSCREEN_SEL_RAM;
extern fdcan_stN2KData_t fdcan_stN2KData[];
extern fdcan_enSEL_SCREEN_t enSelArrow;

extern bool boMenuActive;
/* USER CODE END Private defines */

void MX_FDCAN1_Init(void);

/* USER CODE BEGIN Prototypes */

//void fdcan_vParserTask(void);
void fdcan_vScreenSel_Save(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __FDCAN_H__ */

