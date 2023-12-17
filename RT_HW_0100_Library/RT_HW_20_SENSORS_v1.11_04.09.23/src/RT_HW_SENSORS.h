//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//            			SENSORS
//  ecoins@mail.ru
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef   RT_HW_SENSORS_h
#define   RT_HW_SENSORS_h
#define   RT_HW_SENSORS_VER 		 10		//--Library version number;
#include "RT_HW_BASE.h"						//--Connecting the base library;
//-------------------------------------------------------------------------------------------------
#include "Sensors_i2c/RT_HW_AHTxx.h"
#include "Sensors_i2c/RT_HW_SHT3x.h"	
#include "Sensors_i2c/RT_HW_HTU21.h"
#include "Sensors_i2c/RT_HW_BH1750.h"
#include "Sensors_i2c/RT_HW_BME280.h"
#include "Sensors_i2c/RT_HW_BMP180.h"
#include "Sensors_i2c/RT_HW_PAJ7620U2.h"
//-------------------------------------------------------------------------------------------------	
#include "Sensors_pin/RT_HW_DHT22.hpp"					
#include "Sensors_pin/RT_HW_DS1820.h"
#include "Sensors_pin/RT_HW_SR04.h"
//-------------------------------------------------------------------------------------------------
#include "Sensors_SPI/RT_HW_MAX6675.h"					
//=================================================================================================
#endif
//=================================================================================================