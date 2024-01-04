//=================================================================================================
//				Настройка для блока отправки транзакций (выход custom=1)
//=================================================================================================
void setVarID (RT_HW_STRUCT_MODBUS_WRITE_VAR &id, uint8_t num, char modeTask, uint16_t periodLimit=0, uint16_t periodTask=0){
if(id.custom!=0)  {return;}
if(!checkNum(num)){return;}					//--Выход, если недопустимый номер устройства;
id.num=num;									//--Сохранение номера устройства;
id.blink=getBlink(id.num);					//--Синхронизация с тактирующим генератором;
id.modeTask=modeTask;						//--Режим управления задачей [C,P,T,A,E,Q,F];
id.periodLimit=RT_HW_Base.timeToTick(periodLimit,50);	//--Расчет минимального периода в тиках;
id.periodTask =RT_HW_Base.timeToTick(periodTask, 50);	//--Расчет основного    периода в тиках;
if(id.periodTask<id.periodLimit){id.periodTask=id.periodLimit;} //--Нормализация периодов в тиках;
id.cntLimit=id.cntTask=0;	        //--Очистка счетчиков;
id.agoEN=0; id.run=0; id.custom=1;
};
//=================================================================================================
//							Управление записью (выход run=0,1,2)
//=================================================================================================
uint8_t directTask(RT_HW_STRUCT_MODBUS_WRITE_VAR &id){
//-------------------------------------------------------------------------------------------------
id.run=0;													//--Сброс команды управления;
id.blink=getBlink(id.num);									//--Прием значения от тактирующего генератора;
if(!id.extEN)  {id.first=1; id.run=0;                           return id.run;} 
if(id.first==1){id.first=0; id.run=1; id.agoBlink=id.blink; id.agoEN=id.extEN; 
                                      id.cntLimit=id.cntTask=0; return id.run;} 
//-------------------------------------------------------------------------------------------------
if(id.modeTask=='F'){          return id.run;} 				//--Обнократное вывод по изменению extEN 0->1;
if(id.modeTask=='E'){id.run=1; return id.run;} 				//--Выполняется в каждом цикле;
if(id.modeTask=='Q'){id.run=2; return id.run;} 				//--Выполняется в каждом цикле при изменении во внешней функции; 
//-------------------------------------------------------------------------------------------------
if(id.agoBlink==id.blink){return id.run;} id.agoBlink=id.blink;
if(id.modeTask=='C'){if(++id.cntLimit>=id.periodLimit){id.cntLimit=0;       id.run=2;} return id.run;} //--Вывод по изменению выводимой переменной;
if(id.modeTask=='P'){if(++id.cntTask >=id.periodTask) {id.cntTask=0; 		id.run=1;} return id.run;} //--Вывод периодический;
if(id.modeTask=='T'){if(++id.cntTask >=id.periodTask) {id.cntTask=0; 		id.run=2;} return id.run;} //--Вывод периодический при изменении внешней переменной; 
if(id.modeTask=='A'){if(++id.cntLimit>=id.periodLimit){id.cntLimit=0;       id.run=2;}   			   //--Вывод по изменению выводимой переменной 
                 if(++id.cntTask >=id.periodTask) {id.cntTask=0; id.cntLimit=0; id.run=1;} return id.run;} //                      или периодический вывод; 
return id.run;
}; //--END directTask();
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//							Отправка данных  в формате 
//=================================================================================================
void    sendV (RT_HW_STRUCT_MODBUS_WRITE_VAR &id){
//------Проверка условий для отправки транзакции (id.run,id.num,dv.ready,dv.busy)------------------
if(id.ddr==0){if(!id.run){return;} id.cmdRun=id.run; 
              id.ddr++;}   	//--Ожидание  флага запуска отправки транзакции;
if(id.ddr==1){if(id.cmdRun==2){if(id.agoVar==id.var){id.cmdRun=0; id.ddr=0; return;}} //--Выход если нет изменений;
			  id.cntLimit=id.cntTask=0;
			  id.agoVar=id.var;      id.ddr++;}	//
if(id.ddr==2){if(!checkNum  (id.num)) {return;}	//--Проверка инциализации устройства с номером num;
              if(!ptr[id.num]->ready) {return;}	//--Проверка настройки UART [uartBegin()];
              if( ptr[id.num]->busy)  {return;}	//--Проверка занятости UART;   
              ptr[id.num]->busy=1;              //--Захват   занятости UART;
              if(!ptr[id.num]->busy)  {return;}	//--Повторная проверка занятости UART (для устранения конфликтов с другими задачами);    
              id.ddr++;}  						//--Переход на следующй этап;
//------Отправка транзакции------------------------------------------------------------------------ 
if(id.ddr==3){
RT_HW_Base.uartPrint(String("in"),     				ptr[id.num]->uart); 		//--Отправка "in";				
RT_HW_Base.uartPrint(String(id.numReg),				ptr[id.num]->uart);  //--Отправка "номера переменных";	
RT_HW_Base.uartWrite(0x3D,             				ptr[id.num]->uart);				//--Отправка '=';	
RT_HW_Base.uartPrint(String(id.agoVar),				ptr[id.num]->uart);	//--Отправка значения;			
for(uint8_t i=0;i<3;i++){RT_HW_Base.uartWrite(0xFF,	ptr[id.num]->uart);}	//--Отправка 0xFF 0xFF 0xFF;
id.cmdRun=0; ptr[id.num]->busy=0; id.ddr=0; 				//--Сброс флага занятости UART;
}															//--Переход на следующй этап;						
}; //--END sendINXX(); 

//=================================================================================================
