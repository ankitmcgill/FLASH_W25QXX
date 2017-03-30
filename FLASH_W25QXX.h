/*************************************************************************
* WINBOND W25QXX FLASH CHIP LIBRARY
*
*	SUPPORT FOR ONLY NORMAL SPI MODE (NO BI/QUAD SPI)
* SPI DATA FORMAT : 8 BITS, MSB FIRST
*
* THIS LIBRARY DOES NOT CONTROL THE SPI CS LINE. THATS THE REPSONSIBILITY
* OF THE USER APPLICATION
*
* THE EXCEPTION IS WHEN READING STATUS REGISTER FOR THE BUSY BIT. SINCE
* THIS SHOULD BE DONE BEFORE EXECUTING ANY OPERATION ON THE FLASH AND THE FACT
* THAT W25QXX DEVICE CANNOT DO COMMAND CHAINING (AFTER SENDING STATUS READ
* REGISTER COMMAND, THE CS LINE NEEDS TO BE TOGGLED BEFORE SENDING THE
* ACTUAL COMMAND, THE LIBRARY DOES NEED ACCESS TO CS LINE CONTROL FUNCTIONS
* THIS IS THE ONLY INSTANCE WHERE THE LIBRARY CONTROLS THE CS LINE
*
* FLASH MEMORY GETS ERASED WITH ALL 1 BITS (DEFAULT STATE)
*
* MARCH 27 2017
* ANKIT BHATNAGAR
* ANKIT.BHATNAGARINDIA@GMAIL.COM
*
* ***********************************************************************/


#ifndef _FLASH_W25QXX_
#define	_FLASH_W25QXX_

#define FLASH_W25QXX_COMMAND_NOP								0x00
#define FLASH_W25QXX_COMMAND_ENABLE_RESET				0x66
#define FLASH_W25QXX_COMMAND_RESET							0x99
#define FLASH_W25QXX_COMMAND_MANUFACTURER_ID		0x90
#define FLASH_W25QXX_COMMAND_UNIQUE_ID					0x4B
#define FLASH_W25QXX_COMMAND_JEDEC_ID						0x9F
#define FLASH_W25QXX_COMMAND_READ_STATUS_REG_1	0x05
#define FLASH_W25QXX_COMMAND_READ_STATUS_REG_2	0x35
#define FLASH_W25QXX_COMMAND_WRITE_STATUS_REGS	0x01
#define FLASH_W25QXX_COMMAND_WRITE_ENABLE				0x06
#define FLASH_W25QXX_COMMAND_WRITE_DISABLE			0x04
#define FLASH_W25QXX_COMMAND_SECTOR_ERASE_4KB		0x20
#define FLASH_W25QXX_COMMAND_BLOCK_ERASE_32KB		0x52
#define FLASH_W25QXX_COMMAND_BLOCK_ERASE_64KB		0xD8
#define FLASH_W25QXX_COMMAND_CHIP_ERASE					0xC7
#define FLASH_W25QXX_COMMAND_READ_DATA					0x03
#define FLASH_W25QXX_COMMAND_FAST_READ_DATA     0x0B

#include <stdint.h>
#include "ARM_STM32_SPI.h"

static uint16_t (*spi_send_get_function)(uint16_t);
static void (*spi_cs_low_function)(void);
static void (*spi_cs_high_function)(void);

void FLASH_W25QXX_Enable_Reset(void);
void FLASH_W25QXX_Do_Reset(void);
uint8_t FLASH_W25QXX_Get_Status_Register(uint8_t register_num);
uint8_t FLASH_W25QXX_Get_Busy_Status(void);

void FLASH_W25QXX_Write_Enable(void);
void FLASH_W25QXX_Write_Disable(void);

uint16_t FLASH_W25QXX_Get_Manufacturer_Id(void);
void FLASH_W25QXX_Get_Unique_Id(uint8_t* ret_ptr);
void FLASH_W25QXX_Get_Jedec_Id(uint8_t* ret_ptr);

uint8_t FLASH_W25QXX_Read_Data_Byte(uint32_t add);
void FLASH_W25QXX_Read_Data_Block(uint32_t add, uint8_t* data_ptr, uint32_t read_len);

void FLASH_W25QXX_Write_Status_Registers(uint8_t val_stat_reg_1, uint8_t val_stat_reg_2);

void FLASH_W25QXX_Sector_Erase_4kb(uint32_t add_sector);
void FLASH_W25QXX_Block_Erase_32Kb(uint32_t add_block);
void FLASH_W25QXX_Block_Erase_64Kb(uint32_t add_block);
void FLASH_W25QXX_Chip_Erase(void);



#endif
