//=================================================================================================
// В библиотеке Picture загрузить первыми четыре изображения для аннимации живучести
//
// 		                         СОЗДАЕТСЯ НА КАЖДОЙ СТРАНИЦЕ
// 1.Создается функция оператором Timer:   objname=Main;  tim=100;
// 2.Создается вспомогательный объект (X)Variable: objname=vSTR; sta=String; txt=строка; txt_maxl=40;
// 3.Создается функция оператором Timer:   objname=Quick; tim= 50;  //--Оперативные действия;
// 4.Создается функция оператором Timer:   objname=Fast;  tim= 250; //--Быстрые действия;
// 5.Создается функция оператором Timer:   objname=Slow;  tim=1000; //--Медленные действия;
// 6.Создается функция оператором Timer:   objname=toMCU; tim=100;  //--Отправка транзакций виз Nextion в MCU;
// 7.Создается функция оператором Timer:   objname=Clock; tim=100;  //--Работа с часами Nextion(если требуется);
//-------------------------------------------------------------------------------------------------
// 8.На странице создается объект Picture: objname=blink; pic=0;  (для мерцания(аннимации) = живучесть дисплея)
//-------------------------------------------------------------------------------------------------

//=================================================================================================
//  Периодическое (400мс) мерцание(анимация) индикатором живучести Nextion
//=================================================================================================
cntBlink++
if(cntBlink>=4)
{
  cntBlink=0
  if(numBlink==0)
  {
    blink.pic=0
  }
  if(numBlink==1)
  {
    blink.pic=1
  }
  if(numBlink==2)
  {
    blink.pic=2
  }
  if(numBlink==3)
  {
    blink.pic=3
  }
  numBlink++
  if(numBlink>3)
  {
    numBlink=0
  }
}
//=================================================================================================
//  Вывод номера страницы по изменению(100mc) или периодически (1сек)
//=================================================================================================
sys0=0
if(vPage!=dp)
{
  sys0=1
  cntPage=0
  vPage=dp
}
if(cntPage==0)
{
  sys0=1
}
cntPage++
if(cntPage>=10)
{
  cntPage=0
}
if(sys0>0)
{
  sendme
}
//=================================================================================================
