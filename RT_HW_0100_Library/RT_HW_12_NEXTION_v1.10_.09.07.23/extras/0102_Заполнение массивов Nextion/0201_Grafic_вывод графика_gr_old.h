//=================================================================================================
//         1.ФУНКЦИЯ ВЫВОДА ГРАФИКА
//  Входные параметры:
//  grSize - длина графика на по оси x;
//  stepGrafic - кол-во заполняемых значений между смежными значащими точками;
//  16     - кол-во слов в массиве;
//  255    - высота графика   по оси Y; 
//  gr0:gr15 - 16 4-x байтовых слов с данными; 
//  Рабочие параметры:
//  
//  sys0   - текущее   выводимое значение;
//  sys1   - следующее выводимое значение; 
//  sys2   - шаг заполнения [-1,0,+1] для промежуточных точек;
//=======================Расчет шага графика=======================================================
stepGrafic=grSize/16
stepGrafic=grSize/4
if(stepGrafic>0)
{
 stepGrafic--
}
//=======================Очистка графика===========================================================
cle 9,0

//======Обработка 0-го слова [байты 0:3]===========================================================
valGrafic=gr0
limGrafic=gr1&0xFF //--Ограничение графика 0-байтом следующего слова
//-------------------------------------------------------------------------------------------------
for(idx=0;idx<4;idx++)
{
  if(idx==0)
  {
    sys0=valGrafic
    sys0=sys0&0xFF
    sys1=valGrafic>>8
    sys1=sys1&0xFF
  }
  if(idx==1)
  {
    sys0=valGrafic>>8
    sys0=sys0&0xFF
    sys1=valGrafic>>16
    sys1=sys1&0xFF
  }
  if(idx==2)
  {
    sys0=valGrafic>>16
    sys0=sys0&0xFF
    sys1=valGrafic>>24
    sys1=sys1&0xFF
  }
  if(idx==3)
  {
    sys0=valGrafic>>24
    sys0=sys0&0xFF
    sys1=limGrafic
  }
//-------------------------------------------------
  graficStep=

//------Определение направления изменения 0-го слова-----------------------------------------------
  sys2=0
  if(sys1>sys0)
  {
    sys2=1
  }
  if(sys1<sys0)
  {
    sys2=-1
  }
//------Вывод 0-го слова---------------------------------------------------------------------------  
  for(idx1=0;idx1<buf1;idx1++)
  {
    add 9,0,sys0
    sys0=sys0+sys2
	if(sys0>sys1)
	{
	 sys0=sys1	
	}
	if(sys0<sys1)
	{
	 sys0=sys1	
	}	
  }
}
//======Обработка 1-го слова [байты 4:7]===========================================================
valGrafic=gr1
limGrafic=gr2&0xFF //--Ограничение графика 0-байтом следующего слова
//-------------------------------------------------------------------------------------------------
for(idx=0;idx<4;idx++)
{
  if(idx==0)
  {
    sys0=valGrafic
    sys0=sys0&0xFF
    sys1=valGrafic>>8
    sys1=sys1&0xFF
  }
  if(idx==1)
  {
    sys0=valGrafic>>8
    sys0=sys0&0xFF
    sys1=valGrafic>>16
    sys1=sys1&0xFF
  }
  if(idx==2)
  {
    sys0=valGrafic>>16
    sys0=sys0&0xFF
    sys1=valGrafic>>24
    sys1=sys1&0xFF
  }
  if(idx==3)
  {
    sys0=valGrafic>>24
    sys0=sys0&0xFF
    sys1=limGrafic
  }
//------Определение направления изменения 1-го слова-----------------------------------------------
  sys2=0
  if(sys1>sys0)
  {
    sys2=1
  }
  if(sys1<sys0)
  {
    sys2=-1
  }
//------Вывод 1-го слова---------------------------------------------------------------------------  
  for(idx1=0;idx1<buf1;idx1++)
  {
    add 9,0,sys0
    sys0=sys0+sys2
	if(sys0>sys1)
	{
	 sys0=sys1	
	}
	if(sys0<sys1)
	{
	 sys0=sys1	
	}	
  }
}
//======Обработка 2-го слова [байты 8:11]=========================================================
valGrafic=gr2
limGrafic=gr3&0xFF //--Ограничение графика 0-байтом следующего слова
//-------------------------------------------------------------------------------------------------
for(idx=0;idx<4;idx++)
{
  if(idx==0)
  {
    sys0=valGrafic
    sys0=sys0&0xFF
    sys1=valGrafic>>8
    sys1=sys1&0xFF
  }
  if(idx==1)
  {
    sys0=valGrafic>>8
    sys0=sys0&0xFF
    sys1=valGrafic>>16
    sys1=sys1&0xFF
  }
  if(idx==2)
  {
    sys0=valGrafic>>16
    sys0=sys0&0xFF
    sys1=valGrafic>>24
    sys1=sys1&0xFF
  }
  if(idx==3)
  {
    sys0=valGrafic>>24
    sys0=sys0&0xFF
    sys1=limGrafic
  }
//------Определение направления изменения 2-го слова-----------------------------------------------
  sys2=0
  if(sys1>sys0)
  {
    sys2=1
  }
  if(sys1<sys0)
  {
    sys2=-1
  }
//------Вывод 2-го слова---------------------------------------------------------------------------  
  for(idx1=0;idx1<buf1;idx1++)
  {
    add 9,0,sys0
    sys0=sys0+sys2
	if(sys0>sys1)
	{
	 sys0=sys1	
	}
	if(sys0<sys1)
	{
	 sys0=sys1	
	}	
  }
}
//======Обработка 3-го слова [байты 12:15]=========================================================
valGrafic=gr3
limGrafic=gr4&0xFF //--Ограничение графика 0-байтом следующего слова
//-------------------------------------------------------------------------------------------------
for(idx=0;idx<4;idx++)
{
  if(idx==0)
  {
    sys0=valGrafic
    sys0=sys0&0xFF
    sys1=valGrafic>>8
    sys1=sys1&0xFF
  }
  if(idx==1)
  {
    sys0=valGrafic>>8
    sys0=sys0&0xFF
    sys1=valGrafic>>16
    sys1=sys1&0xFF
  }
  if(idx==2)
  {
    sys0=valGrafic>>16
    sys0=sys0&0xFF
    sys1=valGrafic>>24
    sys1=sys1&0xFF
  }
  if(idx==3)
  {
    sys0=valGrafic>>24
    sys0=sys0&0xFF
    sys1=limGrafic
  }
//------Определение направления изменения 3-го слова-----------------------------------------------
  sys2=0
  if(sys1>sys0)
  {
    sys2=1
  }
  if(sys1<sys0)
  {
    sys2=-1
  }
//------Вывод 3-го слова---------------------------------------------------------------------------  
  for(idx1=0;idx1<buf1;idx1++)
  {
    add 9,0,sys0
    sys0=sys0+sys2
	if(sys0>sys1)
	{
	 sys0=sys1	
	}
	if(sys0<sys1)
	{
	 sys0=sys1	
	}	
  }
}

//======Обработка 4-го слова [байты 16:19]=========================================================
valGrafic=gr4
limGrafic=gr5&0xFF //--Ограничение графика 0-байтом следующего слова
//-------------------------------------------------------------------------------------------------
for(idx=0;idx<4;idx++)
{
  if(idx==0)
  {
    sys0=valGrafic
    sys0=sys0&0xFF
    sys1=valGrafic>>8
    sys1=sys1&0xFF
  }
  if(idx==1)
  {
    sys0=valGrafic>>8
    sys0=sys0&0xFF
    sys1=valGrafic>>16
    sys1=sys1&0xFF
  }
  if(idx==2)
  {
    sys0=valGrafic>>16
    sys0=sys0&0xFF
    sys1=valGrafic>>24
    sys1=sys1&0xFF
  }
  if(idx==3)
  {
    sys0=valGrafic>>24
    sys0=sys0&0xFF
    sys1=limGrafic
  }
//------Определение направления изменения 4-го слова-----------------------------------------------
  sys2=0
  if(sys1>sys0)
  {
    sys2=1
  }
  if(sys1<sys0)
  {
    sys2=-1
  }
//------Вывод 4-го слова---------------------------------------------------------------------------  
  for(idx1=0;idx1<buf1;idx1++)
  {
    add 9,0,sys0
    sys0=sys0+sys2
	if(sys0>sys1)
	{
	 sys0=sys1	
	}
	if(sys0<sys1)
	{
	 sys0=sys1	
	}	
  }
}
//======Обработка 5-го слова [байты 20:23]=========================================================
valGrafic=gr5
limGrafic=gr6&0xFF //--Ограничение графика 0-байтом следующего слова
//-------------------------------------------------------------------------------------------------
for(idx=0;idx<4;idx++)
{
  if(idx==0)
  {
    sys0=valGrafic
    sys0=sys0&0xFF
    sys1=valGrafic>>8
    sys1=sys1&0xFF
  }
  if(idx==1)
  {
    sys0=valGrafic>>8
    sys0=sys0&0xFF
    sys1=valGrafic>>16
    sys1=sys1&0xFF
  }
  if(idx==2)
  {
    sys0=valGrafic>>16
    sys0=sys0&0xFF
    sys1=valGrafic>>24
    sys1=sys1&0xFF
  }
  if(idx==3)
  {
    sys0=valGrafic>>24
    sys0=sys0&0xFF
    sys1=limGrafic
  }
//------Определение направления изменения 5-го слова-----------------------------------------------
  sys2=0
  if(sys1>sys0)
  {
    sys2=1
  }
  if(sys1<sys0)
  {
    sys2=-1
  }
//------Вывод 1-го слова---------------------------------------------------------------------------  
  for(idx1=0;idx1<buf1;idx1++)
  {
    add 9,0,sys0
    sys0=sys0+sys2
	if(sys0>sys1)
	{
	 sys0=sys1	
	}
	if(sys0<sys1)
	{
	 sys0=sys1	
	}	
  }
}
//======Обработка 6-го слова [байты 24:27]=========================================================
valGrafic=gr6
limGrafic=gr7&0xFF //--Ограничение графика 0-байтом следующего слова
//-------------------------------------------------------------------------------------------------
for(idx=0;idx<4;idx++)
{
  if(idx==0)
  {
    sys0=valGrafic
    sys0=sys0&0xFF
    sys1=valGrafic>>8
    sys1=sys1&0xFF
  }
  if(idx==1)
  {
    sys0=valGrafic>>8
    sys0=sys0&0xFF
    sys1=valGrafic>>16
    sys1=sys1&0xFF
  }
  if(idx==2)
  {
    sys0=valGrafic>>16
    sys0=sys0&0xFF
    sys1=valGrafic>>24
    sys1=sys1&0xFF
  }
  if(idx==3)
  {
    sys0=valGrafic>>24
    sys0=sys0&0xFF
    sys1=limGrafic
  }
//------Определение направления изменения 6-го слова-----------------------------------------------
  sys2=0
  if(sys1>sys0)
  {
    sys2=1
  }
  if(sys1<sys0)
  {
    sys2=-1
  }
//------Вывод 6-го слова---------------------------------------------------------------------------  
  for(idx1=0;idx1<buf1;idx1++)
  {
    add 9,0,sys0
    sys0=sys0+sys2
	if(sys0>sys1)
	{
	 sys0=sys1	
	}
	if(sys0<sys1)
	{
	 sys0=sys1	
	}	
  }
}
//======Обработка 7-го слова [байты 28:31]=========================================================
valGrafic=gr7
limGrafic=gr8&0xFF //--Ограничение графика 0-байтом следующего слова
//-------------------------------------------------------------------------------------------------
for(idx=0;idx<4;idx++)
{
  if(idx==0)
  {
    sys0=valGrafic
    sys0=sys0&0xFF
    sys1=valGrafic>>8
    sys1=sys1&0xFF
  }
  if(idx==1)
  {
    sys0=valGrafic>>8
    sys0=sys0&0xFF
    sys1=valGrafic>>16
    sys1=sys1&0xFF
  }
  if(idx==2)
  {
    sys0=valGrafic>>16
    sys0=sys0&0xFF
    sys1=valGrafic>>24
    sys1=sys1&0xFF
  }
  if(idx==3)
  {
    sys0=valGrafic>>24
    sys0=sys0&0xFF
    sys1=limGrafic
  }
//------Определение направления изменения 7-го слова-----------------------------------------------
  sys2=0
  if(sys1>sys0)
  {
    sys2=1
  }
  if(sys1<sys0)
  {
    sys2=-1
  }
//------Вывод 7-го слова---------------------------------------------------------------------------  
  for(idx1=0;idx1<buf1;idx1++)
  {
    add 9,0,sys0
    sys0=sys0+sys2
	if(sys0>sys1)
	{
	 sys0=sys1	
	}
	if(sys0<sys1)
	{
	 sys0=sys1	
	}	
  }
}

//======Обработка 8-го слова [байты 32:35]=========================================================
valGrafic=gr8
limGrafic=gr9&0xFF //--Ограничение графика 0-байтом следующего слова
//-------------------------------------------------------------------------------------------------
for(idx=0;idx<4;idx++)
{
  if(idx==0)
  {
    sys0=valGrafic
    sys0=sys0&0xFF
    sys1=valGrafic>>8
    sys1=sys1&0xFF
  }
  if(idx==1)
  {
    sys0=valGrafic>>8
    sys0=sys0&0xFF
    sys1=valGrafic>>16
    sys1=sys1&0xFF
  }
  if(idx==2)
  {
    sys0=valGrafic>>16
    sys0=sys0&0xFF
    sys1=valGrafic>>24
    sys1=sys1&0xFF
  }
  if(idx==3)
  {
    sys0=valGrafic>>24
    sys0=sys0&0xFF
    sys1=limGrafic
  }
//------Определение направления изменения 8-го слова-----------------------------------------------
  sys2=0
  if(sys1>sys0)
  {
    sys2=1
  }
  if(sys1<sys0)
  {
    sys2=-1
  }
//------Вывод 8-го слова---------------------------------------------------------------------------  
  for(idx1=0;idx1<buf1;idx1++)
  {
    add 9,0,sys0
    sys0=sys0+sys2
	if(sys0>sys1)
	{
	 sys0=sys1	
	}
	if(sys0<sys1)
	{
	 sys0=sys1	
	}	
  }
}
//======Обработка 9-го слова [байты 36:39]=========================================================
valGrafic=gr9
limGrafic=gr10&0xFF //--Ограничение графика 0-байтом следующего слова
//-------------------------------------------------------------------------------------------------
for(idx=0;idx<4;idx++)
{
  if(idx==0)
  {
    sys0=valGrafic
    sys0=sys0&0xFF
    sys1=valGrafic>>8
    sys1=sys1&0xFF
  }
  if(idx==1)
  {
    sys0=valGrafic>>8
    sys0=sys0&0xFF
    sys1=valGrafic>>16
    sys1=sys1&0xFF
  }
  if(idx==2)
  {
    sys0=valGrafic>>16
    sys0=sys0&0xFF
    sys1=valGrafic>>24
    sys1=sys1&0xFF
  }
  if(idx==3)
  {
    sys0=valGrafic>>24
    sys0=sys0&0xFF
    sys1=limGrafic
  }
//------Определение направления изменения 9-го слова-----------------------------------------------
  sys2=0
  if(sys1>sys0)
  {
    sys2=1
  }
  if(sys1<sys0)
  {
    sys2=-1
  }
//------Вывод 9-го слова---------------------------------------------------------------------------  
  for(idx1=0;idx1<buf1;idx1++)
  {
    add 9,0,sys0
    sys0=sys0+sys2
	if(sys0>sys1)
	{
	 sys0=sys1	
	}
	if(sys0<sys1)
	{
	 sys0=sys1	
	}	
  }
}
//======Обработка 10-го слова [байты 40:43]========================================================
valGrafic=gr10
limGrafic=gr11&0xFF //--Ограничение графика 0-байтом следующего слова
//-------------------------------------------------------------------------------------------------
for(idx=0;idx<4;idx++)
{
  if(idx==0)
  {
    sys0=valGrafic
    sys0=sys0&0xFF
    sys1=valGrafic>>8
    sys1=sys1&0xFF
  }
  if(idx==1)
  {
    sys0=valGrafic>>8
    sys0=sys0&0xFF
    sys1=valGrafic>>16
    sys1=sys1&0xFF
  }
  if(idx==2)
  {
    sys0=valGrafic>>16
    sys0=sys0&0xFF
    sys1=valGrafic>>24
    sys1=sys1&0xFF
  }
  if(idx==3)
  {
    sys0=valGrafic>>24
    sys0=sys0&0xFF
    sys1=limGrafic
  }
//------Определение направления изменения 10-го слова-----------------------------------------------
  sys2=0
  if(sys1>sys0)
  {
    sys2=1
  }
  if(sys1<sys0)
  {
    sys2=-1
  }
//------Вывод 10-го слова---------------------------------------------------------------------------  
  for(idx1=0;idx1<buf1;idx1++)
  {
    add 9,0,sys0
    sys0=sys0+sys2
	if(sys0>sys1)
	{
	 sys0=sys1	
	}
	if(sys0<sys1)
	{
	 sys0=sys1	
	}	
  }
}
//======Обработка 11-го слова [байты 44:47]========================================================
valGrafic=gr11
limGrafic=gr12&0xFF //--Ограничение графика 0-байтом следующего слова
//-------------------------------------------------------------------------------------------------
for(idx=0;idx<4;idx++)
{
  if(idx==0)
  {
    sys0=valGrafic
    sys0=sys0&0xFF
    sys1=valGrafic>>8
    sys1=sys1&0xFF
  }
  if(idx==1)
  {
    sys0=valGrafic>>8
    sys0=sys0&0xFF
    sys1=valGrafic>>16
    sys1=sys1&0xFF
  }
  if(idx==2)
  {
    sys0=valGrafic>>16
    sys0=sys0&0xFF
    sys1=valGrafic>>24
    sys1=sys1&0xFF
  }
  if(idx==3)
  {
    sys0=valGrafic>>24
    sys0=sys0&0xFF
    sys1=limGrafic
  }
//------Определение направления изменения 11-го слова-----------------------------------------------
  sys2=0
  if(sys1>sys0)
  {
    sys2=1
  }
  if(sys1<sys0)
  {
    sys2=-1
  }
//------Вывод 11-го слова---------------------------------------------------------------------------  
  for(idx1=0;idx1<buf1;idx1++)
  {
    add 9,0,sys0
    sys0=sys0+sys2
	if(sys0>sys1)
	{
	 sys0=sys1	
	}
	if(sys0<sys1)
	{
	 sys0=sys1	
	}	
  }
}

//======Обработка 12-го слова [байты 48:51]========================================================
valGrafic=gr12
limGrafic=gr13&0xFF //--Ограничение графика 0-байтом следующего слова
//-------------------------------------------------------------------------------------------------
for(idx=0;idx<4;idx++)
{
  if(idx==0)
  {
    sys0=valGrafic
    sys0=sys0&0xFF
    sys1=valGrafic>>8
    sys1=sys1&0xFF
  }
  if(idx==1)
  {
    sys0=valGrafic>>8
    sys0=sys0&0xFF
    sys1=valGrafic>>16
    sys1=sys1&0xFF
  }
  if(idx==2)
  {
    sys0=valGrafic>>16
    sys0=sys0&0xFF
    sys1=valGrafic>>24
    sys1=sys1&0xFF
  }
  if(idx==3)
  {
    sys0=valGrafic>>24
    sys0=sys0&0xFF
    sys1=limGrafic
  }
//------Определение направления изменения 12-го слова-----------------------------------------------
  sys2=0
  if(sys1>sys0)
  {
    sys2=1
  }
  if(sys1<sys0)
  {
    sys2=-1
  }
//------Вывод 12-го слова---------------------------------------------------------------------------  
  for(idx1=0;idx1<buf1;idx1++)
  {
    add 9,0,sys0
    sys0=sys0+sys2
	if(sys0>sys1)
	{
	 sys0=sys1	
	}
	if(sys0<sys1)
	{
	 sys0=sys1	
	}	
  }
}
//======Обработка 13-го слова [байты 52:55]========================================================
valGrafic=gr13
limGrafic=gr14&0xFF //--Ограничение графика 0-байтом следующего слова
//-------------------------------------------------------------------------------------------------
for(idx=0;idx<4;idx++)
{
  if(idx==0)
  {
    sys0=valGrafic
    sys0=sys0&0xFF
    sys1=valGrafic>>8
    sys1=sys1&0xFF
  }
  if(idx==1)
  {
    sys0=valGrafic>>8
    sys0=sys0&0xFF
    sys1=valGrafic>>16
    sys1=sys1&0xFF
  }
  if(idx==2)
  {
    sys0=valGrafic>>16
    sys0=sys0&0xFF
    sys1=valGrafic>>24
    sys1=sys1&0xFF
  }
  if(idx==3)
  {
    sys0=valGrafic>>24
    sys0=sys0&0xFF
    sys1=limGrafic
  }
//------Определение направления изменения 13-го слова-----------------------------------------------
  sys2=0
  if(sys1>sys0)
  {
    sys2=1
  }
  if(sys1<sys0)
  {
    sys2=-1
  }
//------Вывод 13-го слова---------------------------------------------------------------------------  
  for(idx1=0;idx1<buf1;idx1++)
  {
    add 9,0,sys0
    sys0=sys0+sys2
	if(sys0>sys1)
	{
	 sys0=sys1	
	}
	if(sys0<sys1)
	{
	 sys0=sys1	
	}	
  }
}
//======Обработка 14-го слова [байты 56:59]========================================================
valGrafic=gr14
limGrafic=gr15&0xFF //--Ограничение графика 0-байтом следующего слова
//-------------------------------------------------------------------------------------------------
for(idx=0;idx<4;idx++)
{
  if(idx==0)
  {
    sys0=valGrafic
    sys0=sys0&0xFF
    sys1=valGrafic>>8
    sys1=sys1&0xFF
  }
  if(idx==1)
  {
    sys0=valGrafic>>8
    sys0=sys0&0xFF
    sys1=valGrafic>>16
    sys1=sys1&0xFF
  }
  if(idx==2)
  {
    sys0=valGrafic>>16
    sys0=sys0&0xFF
    sys1=valGrafic>>24
    sys1=sys1&0xFF
  }
  if(idx==3)
  {
    sys0=valGrafic>>24
    sys0=sys0&0xFF
    sys1=limGrafic
  }
//------Определение направления изменения 14-го слова-----------------------------------------------
  sys2=0
  if(sys1>sys0)
  {
    sys2=1
  }
  if(sys1<sys0)
  {
    sys2=-1
  }
//------Вывод 14-го слова---------------------------------------------------------------------------  
  for(idx1=0;idx1<buf1;idx1++)
  {
    add 9,0,sys0
    sys0=sys0+sys2
	if(sys0>sys1)
	{
	 sys0=sys1	
	}
	if(sys0<sys1)
	{
	 sys0=sys1	
	}	
  }
}
//======Обработка 15-го слова [байты 60:63]========================================================
valGrafic=gr15
limGrafic=grEnd&0xFF //--Ограничение графика 0-байтом следующего слова
//-------------------------------------------------------------------------------------------------
for(idx=0;idx<4;idx++)
{
  if(idx==0)
  {
    sys0=valGrafic
    sys0=sys0&0xFF
    sys1=valGrafic>>8
    sys1=sys1&0xFF
  }
  if(idx==1)
  {
    sys0=valGrafic>>8
    sys0=sys0&0xFF
    sys1=valGrafic>>16
    sys1=sys1&0xFF
  }
  if(idx==2)
  {
    sys0=valGrafic>>16
    sys0=sys0&0xFF
    sys1=valGrafic>>24
    sys1=sys1&0xFF
  }
  if(idx==3)
  {
    sys0=valGrafic>>24
    sys0=sys0&0xFF
    sys1=limGrafic
  }
//------Определение направления изменения 15-го слова-----------------------------------------------
  sys2=0
  if(sys1>sys0)
  {
    sys2=1
  }
  if(sys1<sys0)
  {
    sys2=-1
  }
//------Вывод 15-го слова---------------------------------------------------------------------------  
  for(idx1=0;idx1<buf1;idx1++)
  {
    add 9,0,sys0
    sys0=sys0+sys2
	if(sys0>sys1)
	{
	 sys0=sys1	
	}
	if(sys0<sys1)
	{
	 sys0=sys1	
	}	
  }
}




//==================================