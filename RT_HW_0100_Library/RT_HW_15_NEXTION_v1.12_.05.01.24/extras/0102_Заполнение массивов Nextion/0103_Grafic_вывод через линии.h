//=================================================================================================
//         1.ФУНКЦИЯ ВЫВОДА ГРАФИКА ЧЕРЕЗ ЛИНИИ
//  Входные параметры:
//  grBeginX=5:  начальная кородината X
//  grBeginY=350: начальная кородината Y
//  grStep=8:    кол-во пикселей между точками 0масштабирование по оси X);
//  grKY=10:     коэффициент для масштабирования по оси Y;
//  grSize - длина графика на по оси x;
//  stepGrafic - кол-во пикселей между выводимыми значениями;
//  16     - кол-во слов в массиве;
//  255    - высота графика   по оси Y; 
//  gr0:gr15 - 16 4-x байтовых слов с данными; 
//  Рабочие параметры:
//  
//  sys0   - текущее   выводимое значение;
//  sys1   - следующее выводимое значение; 
//  sys2   - шаг заполнения [-1,0,+1] для промежуточных точек;
//=======================Расчет шага графика=======================================================
//xbGrafic=grBeginX
//xyGrafic=grBeginY
stepGrafic=grStep
scaleGrafic=grScale
colorGrafic=grColor
//=======================Очистка графика===========================================================
cle 9,0
//======Обработка 16-ти слова в цикле==============================================================
for(idx=0;idx<16;idx++)
{
//======Обработка 4 x-байт(каждого из 16-ти слова) в цикле=========================================
 for(idx1=0;idx1<4;idx1++)
 {	 
//------Выбор текущего и следующего слова----------------------------------------------------------
  if(idx==0)
  {
   valGrafic=gr0
   limGrafic=gr1
  }	
  if(idx==1)
  {
   valGrafic=gr1
   limGrafic=gr2
  }	
  if(idx==2)
  {
   valGrafic=gr2
   limGrafic=gr3
  }	
  if(idx==3)
  {
   valGrafic=gr3
   limGrafic=gr4
  }
   if(idx==4)
  {
   valGrafic=gr4
   limGrafic=gr5
  }	
  if(idx==5)
  {
   valGrafic=gr5
   limGrafic=gr6
  }	
  if(idx==6)
  {
   valGrafic=gr6
   limGrafic=gr7
  }	
  if(idx==7)
  {
   valGrafic=gr7
   limGrafic=gr8
  }	
  if(idx==8)
  {
   valGrafic=gr8
   limGrafic=gr9
  }	
  if(idx==9)
  {
   valGrafic=gr9
   limGrafic=gr10
  }	
  if(idx==10)
  {
   valGrafic=gr10
   limGrafic=gr11
  }	
  if(idx==11)
  {
   valGrafic=gr11
   limGrafic=gr12
  }
   if(idx==12)
  {
   valGrafic=gr12
   limGrafic=gr13
  }	
  if(idx==13)
  {
   valGrafic=gr13
   limGrafic=gr14
  }	
  if(idx==14)
  {
   valGrafic=gr14
   limGrafic=gr15
  }	
  if(idx==15)
  {
   valGrafic=gr15
   limGrafic=gr15
  }	
//------Расчет координат X выводимой линии---------------------------------------------
   sys0=idx*4+idx1
   sys1=sys0*stepGrafic
   xbGrafic=sys0
   xeGrafic=sys0
   if(sys0<64)
   {   
    xeGrafic+=stepGrafic 
   }   
//------Расчет координат  Y  выводимой линии---------------------------------------------
   if(idx1==0)
   {
    sys0=valGrafic
	sys0&=0xFF
    ybGrafic=sys0
	sys0=valGrafic>>8
	sys0&=0xFF
	yeGrafic=sys0
   }	   
//-------------------------------------------------------------------------------------------------
   if(idx1==1)
   {
    sys0=valGrafic>>8
	sys0&=0xFF
    ybGrafic=sys0
	sys0=valGrafic>>16
	sys0&=0xFF
	yeGrafic=sys0
   }
//-------------------------------------------------------------------------------------------------
   if(idx1==2)
   {
    sys0=valGrafic>>16
	sys0&=0xFF
    ybGrafic=sys0
	sys0=valGrafic>>24
	sys0&=0xFF
	yeGrafic=sys0
   }
//-------------------------------------------------------------------------------------------------
   if(idx1==3)
   {
    sys0=valGrafic>>24
	sys0&=0xFF
    ybGrafic=sys0	
	sys0=limGrafic
	sys0&=0xFF
	yeGrafic=sys0
   }   
//------Привязка координат к полю вывода графика---------------------------------------------------
   xbGrafic=grBeginX+xbGrafic
   xeGrafic=grBeginX+xeGrafic
   ybGrafic=grBeginY-ybGrafic
   yeGrafic=grBeginY-yeGrafic 
//------ВЫВОД ЛИНИИ--------------------------------------------------------------------------------
   line xbGrafic,ybGrafic,xeGrafic,yeGrafic,colorGrafic
 }//======END for(idx1=0;idx1<4;idx1++)
} //======END for(idx=0;idx<16;idx++)==============================================================
//=================================================================================================