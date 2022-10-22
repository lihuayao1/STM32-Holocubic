#ifndef __SD_FS_PP_H
#define	__SD_FS_PP_H

#include "stm32f10x.h"
#include "diskio.h"

void Sd_fs_test(void);
void Sd_fs_init(void);
void SDIO_NVIC_Configuration(void);
int Sdfs_new(BYTE *new_file_name, BYTE *write_buffer, BYTE buffer_size);
int Sdfs_write(BYTE *write_file_name, BYTE *write_buffer, BYTE buffer_size);
int Sdfs_read(BYTE *read_file_name, BYTE *save_buffer);
//int GetGBKCode_from_sd(unsigned char* pBuffer,const unsigned char * c);
int GetGBKCode_from_sd ( uint8_t * pBuffer, uint16_t c);

#endif /* __SD_FS_PP_H */
