#include "RT_HW_LCD44780.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//									Конструктор
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
RT_HW_LCD44780:: RT_HW_LCD44780(){
hive.set=0x00; hive.qnt=0;
};
//=================================================================================================	
RT_HW_LCD44780 RT_HW_lcd44780; //--Создание объекта LCD типа HD44780
//=================================================================================================
 