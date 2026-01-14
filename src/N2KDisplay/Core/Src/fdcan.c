/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    fdcan.c
  * @brief   This file provides code for the configuration
  *          of the FDCAN instances.
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
/* Includes ------------------------------------------------------------------*/
#include "fdcan.h"

/* USER CODE BEGIN 0 */
#include "main.h"
#include "cmsis_os2.h"
#include <stdio.h>

typedef enum
{
	fdcan_msg_speed = 0,  ///< 0 Speed
	fdcan_msg_depth,      ///< 1 Deep
	fdcan_msg_nmode,      ///< 2 Nightmode enable/disable
	fdcan_msg_quan
} fdcan_enMSG_t;
typedef struct
{
	uint32_t u32pgn;
	uint32_t u32Data[8];
} fdcan_stCANMMSG_t;
fdcan_stCANMMSG_t fdcan_stCanMgs[fdcan_msg_quan]=
{
		[fdcan_msg_speed] = {128259, 0u},
		[fdcan_msg_depth] = {128267, {0u, 0xFFu,0xFFu}},
		[fdcan_msg_nmode] = {123451, 0xFFFFFFFFu}
};

fdcan_stN2KData_t fdcan_stN2KData[fdcan_n2k_quan] =
{
		[fdcan_n2k_speed] = {false, 0.0},
		[fdcan_n2k_depth] = {false, 0.0},
		[fdcan_n2k_nmode] = {false, 0.0}
};

fdcan_enSEL_SCREEN_t enSelArrow = fdcan_SEL_SCREEN1;

__attribute__((section(".persistent_flash")))
fdcan_stSCREEN_SEL_t fdcan_stSCREEN_SEL_FLASH =
{
		.u32Init = 0xCAFEBABE,
		.u32SelScreen = (uint32_t)fdcan_SEL_SCREEN1
};


fdcan_stSCREEN_SEL_t fdcan_stSCREEN_SEL_RAM;

bool boMenuActive = false;

static void fdcan_vScreenSel_Load(void);

/* USER CODE END 0 */

FDCAN_HandleTypeDef hfdcan1;

/* FDCAN1 init function */
void MX_FDCAN1_Init(void)
{

  /* USER CODE BEGIN FDCAN1_Init 0 */
	// Initialize the screen selection
  fdcan_vScreenSel_Load();
  /* USER CODE END FDCAN1_Init 0 */

  /* USER CODE BEGIN FDCAN1_Init 1 */

  /* USER CODE END FDCAN1_Init 1 */
  hfdcan1.Instance = FDCAN1;
  hfdcan1.Init.ClockDivider = FDCAN_CLOCK_DIV2;
  hfdcan1.Init.FrameFormat = FDCAN_FRAME_FD_BRS;
  hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan1.Init.AutoRetransmission = DISABLE;
  hfdcan1.Init.TransmitPause = DISABLE;
  hfdcan1.Init.ProtocolException = DISABLE;
  hfdcan1.Init.NominalPrescaler = 10;
  hfdcan1.Init.NominalSyncJumpWidth = 1;
  hfdcan1.Init.NominalTimeSeg1 = 13;
  hfdcan1.Init.NominalTimeSeg2 = 2;
  hfdcan1.Init.DataPrescaler = 1;
  hfdcan1.Init.DataSyncJumpWidth = 1;
  hfdcan1.Init.DataTimeSeg1 = 1;
  hfdcan1.Init.DataTimeSeg2 = 1;
  hfdcan1.Init.StdFiltersNbr = 0;
  hfdcan1.Init.ExtFiltersNbr = 1;
  hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN1_Init 2 */
  // Global filters: akzeptiere ALLE Standard- und Extended-Frames in FIFO0
  HAL_FDCAN_ConfigGlobalFilter(&hfdcan1,
      FDCAN_ACCEPT_IN_RX_FIFO0,      // Standard IDs
      FDCAN_ACCEPT_IN_RX_FIFO0,      // Extended IDs
      DISABLE,                       // Reject remote std
      DISABLE                        // Reject remote ext
  );

  // Interrupt aktivieren
  HAL_FDCAN_ActivateNotification(&hfdcan1,
      FDCAN_IT_RX_FIFO0_NEW_MESSAGE,
      0);

  // FDCAN starten
  HAL_FDCAN_Start(&hfdcan1);
  /* USER CODE END FDCAN1_Init 2 */

}

void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef* fdcanHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(fdcanHandle->Instance==FDCAN1)
  {
  /* USER CODE BEGIN FDCAN1_MspInit 0 */

  /* USER CODE END FDCAN1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_FDCAN1;
    PeriphClkInit.Fdcan1ClockSelection = RCC_FDCAN1CLKSOURCE_PLL1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* FDCAN1 clock enable */
    __HAL_RCC_FDCAN1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**FDCAN1 GPIO Configuration
    PB9     ------> FDCAN1_TX
    PB8     ------> FDCAN1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* FDCAN1 interrupt Init */
    HAL_NVIC_SetPriority(FDCAN1_IT0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
  /* USER CODE BEGIN FDCAN1_MspInit 1 */

  /* USER CODE END FDCAN1_MspInit 1 */
  }
}

void HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef* fdcanHandle)
{

  if(fdcanHandle->Instance==FDCAN1)
  {
  /* USER CODE BEGIN FDCAN1_MspDeInit 0 */

  /* USER CODE END FDCAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_FDCAN1_CLK_DISABLE();

    /**FDCAN1 GPIO Configuration
    PB9     ------> FDCAN1_TX
    PB8     ------> FDCAN1_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_9|GPIO_PIN_8);

    /* FDCAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(FDCAN1_IT0_IRQn);
  /* USER CODE BEGIN FDCAN1_MspDeInit 1 */

  /* USER CODE END FDCAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
	if (RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE)
	{
		FDCAN_RxHeaderTypeDef rxHeader;
		uint8_t data[8];
		if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &rxHeader, data) == HAL_OK)
		{
			uint32_t id = rxHeader.Identifier; // 29-bit Extended ID
			uint8_t len = rxHeader.DataLength;
			// === HIER: Verarbeitung ===
			uint32_t u32pgn = (id >> 8)&0x1FFFF;
			fdcan_enMSG_t enIndex = (fdcan_enMSG_t)0;

			while( (enIndex < fdcan_msg_quan)
				  &&(u32pgn != fdcan_stCanMgs[enIndex].u32pgn))
			{
				enIndex++;
			}
			if (enIndex != fdcan_msg_quan)
			{
				for(uint8_t u8i = 0; u8i < len; u8i++)
				{
					fdcan_stCanMgs[enIndex].u32Data[u8i] = data[u8i];
				}
			}
		}
	}
}

void fdcan_vParserTask(void)
{
	fdcan_enMSG_t enIndex;
	while(1)
	{
		uint32_t u32RawSpeed;
		uint32_t u32RawDepth;
		uint32_t u32NightMode;
		uint32_t u32RawWind;
		for(enIndex = (fdcan_enMSG_t)0; enIndex < fdcan_msg_quan; enIndex++)
		{
			switch (enIndex)
			{
			case fdcan_msg_speed:
				u32RawSpeed = fdcan_stCanMgs[enIndex].u32Data[1];
				u32RawSpeed += (fdcan_stCanMgs[enIndex].u32Data[2] << 8);

				fdcan_stN2KData[fdcan_n2k_speed].fData = ((float)u32RawSpeed/100.0)*1.94384;
				fdcan_stN2KData[fdcan_n2k_speed].boNewData = true;
				break;

			case fdcan_msg_depth:
				u32RawDepth = fdcan_stCanMgs[enIndex].u32Data[1];
				u32RawDepth += (fdcan_stCanMgs[enIndex].u32Data[2] << 8);

				fdcan_stN2KData[fdcan_n2k_depth].fData = ((float)u32RawDepth/100.0);
				fdcan_stN2KData[fdcan_n2k_depth].boNewData = true;
				break;

			case fdcan_msg_nmode:
				u32NightMode = fdcan_stCanMgs[enIndex].u32Data[0];
				u32NightMode += (fdcan_stCanMgs[enIndex].u32Data[1] << 8);
				u32NightMode += (fdcan_stCanMgs[enIndex].u32Data[2] << 16);
				u32NightMode += (fdcan_stCanMgs[enIndex].u32Data[3] << 24);

				fdcan_stN2KData[fdcan_n2k_nmode].fData = (float)u32NightMode;
				fdcan_stN2KData[fdcan_n2k_nmode].boNewData = true;
				break;

			default:
				break;
			}
		}
		osDelay(10);
	}
}

static void fdcan_vScreenSel_Load(void)
{
    if (fdcan_stSCREEN_SEL_FLASH.u32Init == 0xCAFEBABE)
    {
        fdcan_stSCREEN_SEL_RAM = fdcan_stSCREEN_SEL_FLASH;
    }
    else
    {
        fdcan_stSCREEN_SEL_RAM.u32Init = 0xCAFEBABE;
        fdcan_stSCREEN_SEL_RAM.u32SelScreen = (uint32_t)fdcan_SEL_SCREEN1;
    }
}

void fdcan_vScreenSel_Save(void)
{
    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef erase = {
        .TypeErase = FLASH_TYPEERASE_PAGES,
        .Page = FLASH_PERSISTENT_PAGE,
        .NbPages = 1
    };

    uint32_t error;
    HAL_FLASHEx_Erase(&erase, &error);

    HAL_FLASH_Program(
        FLASH_TYPEPROGRAM_QUADWORD,
        FLASH_PERSISTENT_ADDR,
        (uint32_t)&fdcan_stSCREEN_SEL_RAM   // <-- WICHTIG
    );

    HAL_FLASH_Lock();
}


/* USER CODE END 1 */
