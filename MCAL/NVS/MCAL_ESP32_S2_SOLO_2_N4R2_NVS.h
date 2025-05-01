/******************************************************************************************************************************
 File Name      : MCAL_ESP32_S2_SOLO_2_N4R2_NVS.C
 Description    : This file as Header for (NVS)
 Author         : Omar Sameh
 Tester         : 
 Device(s)      : ESP32_S2_SOLO_2_N4R2
 Creation Date  : 17/08/2024
 Testing Date   : 
 @COPYRIGHT 2016 El-ARABY Research and development center.
 all rights reserved
*********************************************************************************************************************************/
#ifndef MCAL_ESP32_S2_SOLO_2_N4R2_NVS_H_
#define MCAL_ESP32_S2_SOLO_2_N4R2_NVS_H_

#include "../ESP32_S2_SOLO_2_N4R2_Main.h"
#include "nvs_flash.h"
#include "nvs.h"

#define NVS_NAMESPACE "storage"

void NVS_Init(void);
void NVS_Write_Int(const tsbyte *key, tsword value);
void NVS_Read_Int(const tsbyte *key, tsword *out_value);
void NVS_Write_Array(const tsbyte *key, tsword *data, size_t length);
void NVS_Read_Array(const tsbyte *key, tsword *data, size_t length);
void NVS_Write_String(const tsbyte *key, const tsbyte *value);
void NVS_Read_String(const tsbyte *key, tsbyte *out_value, size_t max_length);
void NVS_Erase_Key(const tsbyte *key);

#endif /* MCAL_ESP32_S2_SOLO_2_N4R2_NVS_H_ */
