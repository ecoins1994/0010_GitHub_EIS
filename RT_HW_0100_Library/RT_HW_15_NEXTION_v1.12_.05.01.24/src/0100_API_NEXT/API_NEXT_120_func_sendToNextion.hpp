//=================================================================================================
//				Настройка для блока отправки транзакций в Nextion (выход custom=1)
//=================================================================================================
void setVarID (RT_HW_STRUCT_NEXT_WRITE_VAR &id, uint8_t num, char modeTask, uint16_t periodLimit=0, uint16_t periodTask=0){
if(id.custom!=0)  {return;}
if(!checkNum(num)){return;}			//--Выход, если недопустимый номер устройства;
id.num=num;							//--Сохранение номера устройства;
id.blink=getBlink(id.num);			//--Синхронизация с тактирующим генератором;
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
uint8_t directTask(RT_HW_STRUCT_NEXT_WRITE_VAR &id){
//-------------------------------------------------------------------------------------------------
id.run=0;													//--Сброс команды управления;
id.blink=getBlink(id.num);									//--Прием значения от тактирующего генератора;
if(!id.extEN)  {id.first=1; id.run=0;                           return id.run;} 
if(id.first==1){id.first=0; id.run=1; id.agoBlink=id.blink; id.agoEN=id.extEN; 
                                      id.cntLimit=id.cntTask=0; return id.run;} 
//-------------------------------------------------------------------------------------------------
if(id.modeTask=='F'){          return id.run;} 															        //--Обнократное вывод по изменению extEN 0->1;
if(id.modeTask=='E'){id.run=1; return id.run;} //--Выполняется в каждом цикле;
if(id.modeTask=='Q'){id.run=2; return id.run;} //--Выполняется в каждом цикле при изменении во внешней функции; 
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

void setSendINXX(RT_HW_STRUCT_NEXT_WRITE_VAR  &id, uint8_t nxt, char mode='A', uint16_t periodLimit=100, uint16_t periodTask=2500){
if(id.custom==0){setVarID(id,nxt,mode,periodLimit,periodTask);}
};
void directSendINXX(RT_HW_STRUCT_NEXT_WRITE_VAR  &id,uint16_t numReg, int32_t v){
(void)numReg;
directTask(id); if(id.run>0){id.var=v;} 	sendINXX(id);}; 

//=================================================================================================
//							Отправка данных  в формате "in"+String(id.numReg)+"="+String(id.agoVar)
//=================================================================================================
void    sendINXX (RT_HW_STRUCT_NEXT_WRITE_VAR &id){sendV(id);}
void    sendV (RT_HW_STRUCT_NEXT_WRITE_VAR &id){
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
//							Отправка инструкции + число с контролем номера страницы
//=================================================================================================
void    sendU (RT_HW_STRUCT_NEXT_WRITE_VAR &id, String instr){
if(id.ddr==0){	//++++Проверка условий для отправки транзакции (id.run,id.num,dv.ready,dv.busy)----
if(!id.run){return;} 
if((ptr[id.num]->vPage==id.page)||(id.page>=99)){id.cmdRun=id.run; id.ddr=1;} //--Контроль номера страницы
else {return;}   	
}	//---------------------------------------------------------------------------------------------
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
RT_HW_Base.uartPrint(instr,            				ptr[id.num]->uart); 	//--Отправка "in";					
RT_HW_Base.uartWrite(0x3D,             				ptr[id.num]->uart); //--Отправка '=';	
RT_HW_Base.uartPrint(String(id.agoVar),				ptr[id.num]->uart);	//--Отправка значения;			
for(uint8_t i=0;i<3;i++){RT_HW_Base.uartWrite(0xFF,	ptr[id.num]->uart);}	//--Отправка 0xFF 0xFF 0xFF;
id.cmdRun=0; ptr[id.num]->busy=0; id.ddr=0; 				//--Сброс флага занятости UART;
}															//--Переход на следующй этап;						
}; //--END sendU(); 
//=================================================================================================
//							Отправка инструкции + числа без контроля номера страницы
//=================================================================================================
void    sendN (RT_HW_STRUCT_NEXT_WRITE_VAR &id, String instr){
if(id.ddr==0){	//++++Проверка условий для отправки транзакции (id.run,id.num,dv.ready,dv.busy)----
if(!id.run){return;} id.cmdRun=id.run; id.ddr=1;
//if((ptr[id.num]->vPage==id.page)||(id.page>=99)){id.cmdRun=id.run; id.ddr=1;} //--Контроль номера страницы
//else {return;}   	
}	//---------------------------------------------------------------------------------------------
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
RT_HW_Base.uartPrint(instr,            				ptr[id.num]->uart); 				//--Отправка "in";					
RT_HW_Base.uartWrite(0x3D,             				ptr[id.num]->uart);				//--Отправка '=';	
RT_HW_Base.uartPrint(String(id.agoVar),				ptr[id.num]->uart);	//--Отправка значения;			
for(uint8_t i=0;i<3;i++){RT_HW_Base.uartWrite(0xFF,	ptr[id.num]->uart);}	//--Отправка 0xFF 0xFF 0xFF;
id.cmdRun=0; ptr[id.num]->busy=0; id.ddr=0; 				//--Сброс флага занятости UART;
}															//--Переход на следующй этап;						
}; //--END sendN(); 
//=================================================================================================
//							Отправка инструкции без контроля номера страницы
//=================================================================================================
void    sendF (RT_HW_STRUCT_NEXT_WRITE_VAR &id, String instr){
if(id.ddr==0){	//++++Проверка условий для отправки транзакции (id.run,id.num,dv.ready,dv.busy)----
if(!id.run){return;} id.cmdRun=id.run; id.ddr=1;
//if((ptr[id.num]->vPage==id.page)||(id.page>=99)){id.cmdRun=id.run; id.ddr=1;} //--Контроль номера страницы
//else {return;}   	
}	//---------------------------------------------------------------------------------------------
if(id.ddr==1){id.cntLimit=id.cntTask=0;
	          id.agoVar=id.var;      id.ddr++;}	//
if(id.ddr==2){if(!checkNum  (id.num)) {return;}	//--Проверка инциализации устройства с номером num;
              if(!ptr[id.num]->ready) {return;}	//--Проверка настройки UART [uartBegin()];
              if( ptr[id.num]->busy)  {return;}	//--Проверка занятости UART;   
              ptr[id.num]->busy=1;              //--Захват   занятости UART;
              if(!ptr[id.num]->busy)  {return;}	//--Повторная проверка занятости UART (для устранения конфликтов с другими задачами);    
              id.ddr++;}  						//--Переход на следующй этап;
//------Отправка транзакции------------------------------------------------------------------------ 
if(id.ddr==3){
RT_HW_Base.uartPrint(instr, 						ptr[id.num]->uart); 				//--Отправка "in";							
for(uint8_t i=0;i<3;i++){RT_HW_Base.uartWrite(0xFF,	ptr[id.num]->uart);}	//--Отправка 0xFF 0xFF 0xFF;
id.cmdRun=0; ptr[id.num]->busy=0; id.ddr=0; 				//--Сброс флага занятости UART;
}															//--Переход на следующй этап;						
}; //--END sendF(); 

//=================================================================================================
//							Отправка инструкции с контролем номера страницы
//=================================================================================================
void    sendT (RT_HW_STRUCT_NEXT_WRITE_VAR &id, String instr, String &agoTxt, String varTxt){
if(id.ddr==0){	//++++Проверка условий для отправки транзакции (id.run,id.num,dv.ready,dv.busy)----
if(!id.run){return;} 
if((ptr[id.num]->vPage==id.page)||(id.page>=99)){id.cmdRun=id.run; id.ddr=1;} //--Контроль номера страницы
else {return;}   	
}	//---------------------------------------------------------------------------------------------
if(id.ddr==1){if(id.cmdRun==2){if(agoTxt==varTxt){id.cmdRun=0; id.ddr=0; return;}} //--Выход если нет изменений;
			  id.cntLimit=id.cntTask=0;
			  agoTxt=varTxt;      id.ddr++;}	//
if(id.ddr==2){if(!checkNum  (id.num)) {return;}	//--Проверка инциализации устройства с номером num;
              if(!ptr[id.num]->ready) {return;}	//--Проверка настройки UART [uartBegin()];
              if( ptr[id.num]->busy)  {return;}	//--Проверка занятости UART;   
              ptr[id.num]->busy=1;              //--Захват   занятости UART;
              if(!ptr[id.num]->busy)  {return;}	//--Повторная проверка занятости UART (для устранения конфликтов с другими задачами);    
              id.ddr++;}  						//--Переход на следующй этап;
//------Отправка транзакции------------------------------------------------------------------------ 
if(id.ddr==3){
RT_HW_Base.uartPrint(instr, 						ptr[id.num]->uart); 		        //--Отправка "in";					
RT_HW_Base.uartWrite(0x3D,  						ptr[id.num]->uart);				//--Отправка '=';	
RT_HW_Base.uartWrite(0x22,  						ptr[id.num]->uart); 				//--Отправка кавычек;	
RT_HW_Base.uartPrint(agoTxt,						ptr[id.num]->uart); 		    //--Отправка текста;	
RT_HW_Base.uartWrite(0x22,  						ptr[id.num]->uart); 				//--Отправка кавычек;			
for(uint8_t i=0;i<3;i++){RT_HW_Base.uartWrite(0xFF,	ptr[id.num]->uart);}	//--Отправка 0xFF 0xFF 0xFF;
id.cmdRun=0; ptr[id.num]->busy=0; id.ddr=0; 				//--Сброс флага занятости UART;
}															//--Переход на следующй этап;						
}; //--END sendU(); 

//=================================================================================================
//							Отправка данных  в формате "in"+String(id.numReg)+"="+String(id.agoVar)
//=================================================================================================
void    sendPageInstrVar (RT_HW_STRUCT_NEXT_WRITE_VAR &id, String instr){
//------Проверка условий для отправки транзакции (id.run,id.num,dv.ready,dv.busy)------------------
if(id.ddr==0){
if(!id.run){return;} 
if((ptr[id.num]->vPage==id.page)|| (id.page>=99)) {id.cmdRun=id.run; id.ddr=1;}
else                                                      {return;}
}   		//--Ожидание  флага запуска отправки транзакции;
//-------------------------------------------------------------------------------------------------
if(id.ddr==1){
if(id.cmdRun==2){if(id.agoVar==id.var){id.cmdRun=0; id.ddr=0; return;}} //--Выход если нет изменений;
id.cntLimit=id.cntTask=0;
id.agoVar=id.var; id.ddr=2;
}
//-------------------------------------------------------------------------------------------------
if(id.ddr==2){
if(!checkNum  (id.num)) {return;}   //--Проверка инциализации устройства с номером num;
if(!ptr[id.num]->ready) {return;}   //--Проверка настройки UART [uartBegin()];
if( ptr[id.num]->busy)  {return;}	//--Проверка занятости UART;   
ptr[id.num]->busy=1;              	//--Захват   занятости UART;
if(!ptr[id.num]->busy)  {return;}	//--Повторная проверка занятости UART (для устранения конфликтов с другими задачами);    
id.ddr=3;
}  						//--Переход на следующй этап;
//------Отправка транзакции------------------------------------------------------------------------ 
if(id.ddr==3){			
RT_HW_Base.uartPrint(instr,							ptr[id.num]->uart);				//--Отправка инструкции;
RT_HW_Base.uartWrite(0x3D, 			    			ptr[id.num]->uart);				//--Отправка символа '='(равно);
RT_HW_Base.uartPrint(String(id.agoVar), 			ptr[id.num]->uart);	//--Отправка значения;			
for(uint8_t i=0;i<3;i++){RT_HW_Base.uartWrite(0xFF,	ptr[id.num]->uart);}	//--Отправка 0xFF 0xFF 0xFF;
id.cmdRun=0; ptr[id.num]->busy=0; id.ddr=0; 				//--Сброс флага занятости UART;
}															//--Переход на следующй этап;						
}; //--END sendINXX(); 

//=================================================================================================
//							Отправка данных  в формате "in"+String(id.numReg)+"="+String(id.agoVar)
//=================================================================================================
void    sendInstrVar (RT_HW_STRUCT_NEXT_WRITE_VAR &id, String instr){
//------Проверка условий для отправки транзакции (id.run,id.num,dv.ready,dv.busy)------------------
if(id.ddr==0){
if(!id.run){return;} 
id.cmdRun=id.run; id.ddr=1;}   		//--Ожидание  флага запуска отправки транзакции;
//-------------------------------------------------------------------------------------------------
if(id.ddr==1){
if(id.cmdRun==2){
if(id.agoVar==id.var){id.cmdRun=0; id.ddr=0; return;}} //--Выход если нет изменений;
id.cntLimit=id.cntTask=0;
id.agoVar=id.var; id.ddr=2;}
//-------------------------------------------------------------------------------------------------
if(id.ddr==2){
if(!checkNum  (id.num)) {return;}   //--Проверка инциализации устройства с номером num;
if(!ptr[id.num]->ready) {return;}   //--Проверка настройки UART [uartBegin()];
if( ptr[id.num]->busy)  {return;}	//--Проверка занятости UART;   
ptr[id.num]->busy=1;              	//--Захват   занятости UART;
if(!ptr[id.num]->busy)  {return;}	//--Повторная проверка занятости UART (для устранения конфликтов с другими задачами);    
id.ddr=3;}  						//--Переход на следующй этап;
//------Отправка транзакции------------------------------------------------------------------------ 
if(id.ddr==3){			
RT_HW_Base.uartPrint(instr,							ptr[id.num]->uart);				//--Отправка инструкции;
RT_HW_Base.uartWrite(0x3D, 							ptr[id.num]->uart);				//--Отправка символа '='(равно);
RT_HW_Base.uartPrint(String(id.agoVar),            	ptr[id.num]->uart);	//--Отправка значения;			
for(uint8_t i=0;i<3;i++){RT_HW_Base.uartWrite(0xFF,	ptr[id.num]->uart);}	//--Отправка 0xFF 0xFF 0xFF;
id.cmdRun=0; ptr[id.num]->busy=0; id.ddr=0; 				//--Сброс флага занятости UART;
}															//--Переход на следующй этап;						
}; //--END sendINXX(); 


//=================================================================================================
//							Отправка данных  в формате "inst"
//=================================================================================================
void	sendInstr(RT_HW_STRUCT_NEXT_WRITE_VAR &id, String instr){
//------Проверка условий для отправки транзакции (id.run,id.num,dv.ready,dv.busy)------------------
if(id.ddr==0){      	
if(!id.run){return;} id.run=0;   	//--Ожидание  флага запуска отправки транзакции;
if(!checkNum  (id.num)) {return;}   //--Проверка инциализации устройства с номером num;
if(!ptr[id.num]->ready) {return;}   //--Проверка настройки UART [uartBegin()];
if( ptr[id.num]->busy)  {return;}	//--Проверка занятости UART;   
    ptr[id.num]->busy=1;            //--Захват   занятости UART;
if(!ptr[id.num]->busy)  {return;}	//--Повторная проверка занятости UART (для устранения конфликтов с другими задачами);    
id.ddr++;} 							//--Переход на следующй этап;	
//------Отправка транзакции------------------------------------------------------------------------
if(id.ddr==1){
RT_HW_Base.uartPrint(instr,                        ptr[id.num]->uart); //--Отправка инструкции;								
for(uint8_t i=0;i<3;i++){RT_HW_Base.uartWrite(0xFF,ptr[id.num]->uart);}	//--Отправка 0xFF 0xFF 0xFF;
ptr[id.num]->timeBeginBusy=micros(); 						//--Фиксация времени для динамической задержки;
id.ddr++;}													//--Переход на следующй этап;	
//------Динамическая задержка и сброс занятости UART-----------------------------------------------
if(id.ddr==2){     
if(RT_HW_Base.getPastMcs(ptr[id.num]->timeBeginBusy)<=3500){return;} //--Динамическая пауза 800mcs;
ptr[id.num]->busy=0;  				//--Сброс флага занятости UART;
id.ddr=0; return;}  				//--Передача управления на начало:
}; //--END sendNameVal(); 




/*
//=================================================================================================
//                          Отправка данных  в формате "inst"
//							Запись байта со сдвигом данных
//  Формат транзакции: String->"headD=0xYY" + завершающая посылка 0xFF 0xFF 0xFF  
//=================================================================================================
void	sendGrafic(RT_HW_STRUCT_NEXT_WRITE_VAR &id, String name, int32_t var){
//------Проверка условий для отправки транзакции (id.run,id.num,dv.ready,dv.busy)------------------
if(id.ddr==0){      	
if(!id.run){return;} id.run=0;   	//--Ожидание  флага запуска отправки транзакции;
if(!checkNum  (id.num)) {return;}   //--Проверка инциализации устройства с номером num;
if(!ptr[id.num]->ready) {return;}   //--Проверка настройки UART [uartBegin()];
if( ptr[id.num]->busy)  {return;}	//--Проверка занятости UART;   
    ptr[id.num]->busy=1;            //--Захват   занятости UART;
if(!ptr[id.num]->busy)  {return;}	//--Повторная проверка занятости UART (для устранения конфликтов с другими задачами);    
id.ddr++;} 							//--Переход на следующй этап;	
//------Отправка транзакции------------------------------------------------------------------------
if(id.ddr==1){
RT_HW_Base.uartPrint(ptr[id.num]->uart,(name+String(var,HEX)));         //--							
for(uint8_t i=0;i<3;i++){RT_HW_Base.uartWrite(ptr[id.num]->uart,0XFF);}	//--Отправка 0xFF 0xFF 0xFF;
ptr[id.num]->timeBeginBusy=micros(); 						//--Фиксация времени для динамической задержки;
id.ddr++;}													//--Переход на следующй этап;	
//------Динамическая задержка и сброс занятости UART-----------------------------------------------
if(id.ddr==2){     
if(RT_HW_Base.getPastMcs(ptr[id.num]->timeBeginBusy)<=1500){return;} //--Динамическая пауза 800mcs;
ptr[id.num]->busy=0;  				//--Сброс флага занятости UART;
id.ddr=0; return;}  				//--Передача управления на начало:
}; //--END sendGrafic(); 
*/

//=================================================================================================

/*
//=================================================================================================
void writeInt32(RT_HW_STRUCT_NEXT_WRITE_VAR &id, uint8_t adr, int32_t var, uint8_t EN){
directSend(id,EN);
if(id.run==1){                   id.agoVar=var;  id.run=5;}  //--Запуск периодически;
if(id.run==2){if(id.agoVar!=var){id.agoVar=var;  id.run=5;}}
sendAdrVal(id,adr);
}; 

//=================================================================================================
void writeFloat(RT_HW_STRUCT_NEXT_WRITE_VAR &id, uint8_t adr, float var,   uint8_t EN){
directSend(id,EN);
if(id.run==1){                                  id.agoVar=(int32_t)(var*100);  id.run=1;}  //--Запуск периодически;
if(id.run==2){if(id.agoVar!=(int32_t)(var*100)){id.agoVar=(int32_t)(var*100);  id.run=1;}}
sendAdrVal(id,adr);
};

//=================================================================================================
void writeNameVar(RT_HW_STRUCT_NEXT_WRITE_VAR &id, String name, int32_t var,uint8_t EN){
directSend(id,EN);
if(id.state==1){                   id.agoVal=val;  id.run=1;}  //--Запуск периодически;
if(id.state==2){if(id.agoVal!=val){id.agoVal=val;  id.run=1;}}
sendNameVal(id,name,val);
};
//=================================================================================================
void writeInstr(RT_HW_STRUCT_NEXT_WRITE_VAR &id, String &agoInstr, String instr, uint8_t EN){
directSend(id,EN);
if(id.state==1){                    agoInstr=instr;  id.run=1;}  //--Запуск периодически;
if(id.state==2){if(agoInstr!=instr){agoInstr=instr;  id.run=1;}}
sendInstr(id,agoInstr);
};
*/



//=================================================================================================
//							Управление измерением
//=================================================================================================
//										Управление вызовом задач
// Функция setTaskId устанавливает периоды обработки события 10,25,50,100,250,500 или 1000 ms.
// id - вектор запуска задач;
// gen - меандр  внешнего генератора с полупериодом равным tick, 
//       который был применен в функции настройки вектора запуска задач.
//=================================================================================================
/*
uint8_t directTask (RT_HW_STRUCT_NEXT_WRITE_VAR_ID &id, uint8_t stanGen=0){
//-------------------------------------------------------------------------------------------------
id.run=0;
if((!RT_HW_Base.shed.ready) || (0)) {if(RT_HW_Base.period(id.timeBegin,millis(),id.tick)){id.gen=!id.gen;}} //--Автономный генератор при не работающием диспетчере;
else {if(id.tick==10) {id.gen=shed.blink10;}  if(id.tick==25) {id.gen=shed.blink25;}  if(id.tick==50){id.gen=shed.blink50;} 
      if(id.tick==100){id.gen=shed.blink100;} if(id.tick==250){id.gen=shed.blink250;}}
if(!id.extEN)  {id.first=1; return id.run;}
if(id.first==1){id.first=0; id.run=1; id.agoGen=id.gen; id.agoEN=id.extEN; return id.run;}  
if(id.mode=='F'){           return id.run;} 															   //--Выполняется однократно по first=1;
if(id.mode=='E'){id.run=1;  return id.run;} //--Выполняется в каждом цикле;
if(id.mode=='Q'){id.run=2;  return id.run;} //--Выполняется в каждом цикле при изменении во внешней функции;
//-------------------------------------------------------------------------------------------------
if(id.agoGen!=id.gen){id.agoGen=id.gen;
if(id.mode=='C'){if(++id.cntLimit>=id.periodLimit){id.cntLimit=0;				id.run=2;} return id.run;} //--По изменению во внешней функции;
if(id.mode=='P'){if(++id.cntTask >=id.periodTask) {id.cntTask=0; 				id.run=1;} return id.run;} //--Периодически;
if(id.mode=='T'){if(++id.cntTask >=id.periodTask) {id.cntTask=0; 				id.run=2;} return id.run;} //--Периодически и по изменению во внешней функции: 
if(id.mode=='A'){if(++id.cntLimit>=id.periodLimit){id.cntLimit=0;id.cntTask=0;  id.run=2;}          	   //--По изменению во внешней функции
                 if(++id.cntTask >=id.periodTask) {id.cntTask=0; id.cntLimit=0; id.run=1;} return id.run;} //                       или периодически; 
}
return id.run;
};	//++++END directTask 
*/



/*
//=================================================================================================
//				Настройка для блока отправки транзакций в Nextion 
//=================================================================================================
uint8_t setValID (RT_HW_STRUCT_NEXT_WRITE_VAL &id, uint8_t num, char mode, uint16_t periodLimit=0, uint16_t periodTask=0){
if(!checkNum(num)){return 0;}			//--Выход, если недопустимый номер устройства;
id.num=num;								//--Сохранение номера устройства;
id.blink=getBlink(id.num);				//--Синхронизация с тактирующим генератором;
id.mode=mode;							//--Режим управления задачей [C,P,T,A,E,S,F,N];
id.periodLimit=RT_HW_Base.timeToTick(periodLimit,50);	//--Расчет минимального периода в тиках;
id.periodTask =RT_HW_Base.timeToTick(periodTask, 50);	//--Расчет основного    периода в тиках;
if(id.periodTask<id.periodLimit){id.periodTask=id.periodLimit;} //--Нормализация периодов в тиках;
id.cntLimit=id.cntTask=0;	                 	//--Очистка счетчиков;
id.agoEN=0; id.run=0; 
id.custom=1;
return 1;};
*/
/*
//=================================================================================================
//							Управление измерением
//=================================================================================================
uint8_t directSend(RT_HW_STRUCT_NEXT_WRITE_VAL &id, uint8_t extEN=1){
//-------------------------------------------------------------------------------------------------
id.state=0;																						//--Сброс регистра состояния;
if(id.agoEN!=extEN){id.agoEN=extEN; if(extEN){id.cntLimit=id.cntTask=0; id.state=1; return 1;}}	//--Безусловный вывод по изменению extEN 0->1;
//-------------------------------------------------------------------------------------------------
if(id.mode=='F'){return 0;} 															        //--Обнократное вывод по изменению extEN 0->1;
if(id.blink!=getBlink(id.num)){id.blink=getBlink(id.num);										//--Проверка изменения тактирующего генератора;
if(id.mode=='C'){if(++id.cntLimit>=id.periodLimit){id.cntLimit=0;       id.state=2;} return 1;} //--Вывод по изменению выводимой переменной;
if(id.mode=='P'){if(++id.cntTask >=id.periodTask) {id.cntTask=0; 		id.state=1;} return 1;} //--Вывод периодический;
if(id.mode=='T'){if(++id.cntTask >=id.periodTask) {id.cntTask=0; 		id.state=2;} return 1;} //--Вывод периодический при изменении внешней переменной; 
if(id.mode=='A'){if(++id.cntLimit>=id.periodLimit){id.cntLimit=0;       id.state=2;}   			//--Вывод по изменению выводимой переменной 
         if(++id.cntTask >=id.periodTask) {id.cntTask=0; id.cntLimit=0; id.state=1;} return 1;} //                      или периодический вывод; 
} //--END if(id.blink!=getBlink(id.num);
return 0;};
*/
/*
//=================================================================================================
//							Отправка данных  в формате "in"+"адрес"="val"
//=================================================================================================
void    sendAdrVal (RT_HW_STRUCT_NEXT_WRITE_VAL &id, uint8_t adr){
//------Проверка условий для отправки транзакции (id.run,id.num,dv.ready,dv.busy)------------------
if(id.ddr==0){      	
if(!id.run){return;} id.run=0;   	//--Ожидание  флага запуска отправки транзакции;
if(!checkNum  (id.num)) {return;}   //--Проверка инциализации устройства с номером num;
if(!ptr[id.num]->ready) {return;}   //--Проверка настройки UART [uartBegin()];
if( ptr[id.num]->busy)  {return;}	//--Проверка занятости UART;   
    ptr[id.num]->busy=1;            //--Захват   занятости UART;
if(!ptr[id.num]->busy)  {return;}	//--Повторная проверка занятости UART (для устранения конфликтов с другими задачами);    
id.ddr++;}  						//--Переход на следующй этап;
//------Отправка транзакции------------------------------------------------------------------------ 
if(id.ddr==1){
RT_HW_Base.uartPrint(ptr[id.num]->uart,String("in")); 		//--Отправка "in";				
RT_HW_Base.uartPrint(ptr[id.num]->uart,String(adr)); 		//--Отправка "номера переменных";	
RT_HW_Base.uartWrite(ptr[id.num]->uart,0x3D);				//--Отправка '=';	
RT_HW_Base.uartPrint(ptr[id.num]->uart,String(id.agoVal));	//--Отправка значения;			
for(uint8_t i=0;i<3;i++){RT_HW_Base.uartWrite(ptr[id.num]->uart,0XFF);}	//--Отправка 0xFF 0xFF 0xFF;
ptr[id.num]->timeBeginBusy=millis(); 						//--Фиксация времени для динамической задержки;
id.ddr++;
}													//--Переход на следующй этап;						
//------Динамическая задержка и сброс занятости UART-----------------------------------------------
if(id.ddr==2){     
//if(RT_HW_Base.getPastMs(ptr[id.num]->timeBeginBusy)<=2){return;} //--Динамическая пауза 800mcs;
ptr[id.num]->busy=0;  				//--Сброс флага занятости UART;
id.ddr=0; return;}  				//--Передача управления на начало:
}; //--END sendVal(); 

*/

/*
//=================================================================================================
//							Отправка данных  в формате "name"="val"
//=================================================================================================
void	sendNameVal(RT_HW_STRUCT_NEXT_WRITE_VAL &id, String name, int32_t val){
//------Проверка условий для отправки транзакции (id.run,id.num,dv.ready,dv.busy)------------------
if(id.ddr==0){      	
if(!id.run){return;} id.run=0;   	//--Ожидание  флага запуска отправки транзакции;
if(!checkNum  (id.num)) {return;}   //--Проверка инциализации устройства с номером num;
if(!ptr[id.num]->ready) {return;}   //--Проверка настройки UART [uartBegin()];
if( ptr[id.num]->busy)  {return;}	//--Проверка занятости UART;   
    ptr[id.num]->busy=1;            //--Захват   занятости UART;
if(!ptr[id.num]->busy)  {return;}	//--Повторная проверка занятости UART (для устранения конфликтов с другими задачами);    
id.ddr++;} 							//--Переход на следующй этап;
//------Отправка транзакции------------------------------------------------------------------------ 	
if(id.ddr==1){
RT_HW_Base.uartPrint(ptr[id.num]->uart,name); 				//--Отправка заголовка;			
RT_HW_Base.uartWrite(ptr[id.num]->uart,0x3D);				//--Отправка '=';
RT_HW_Base.uartPrint(ptr[id.num]->uart,String(val));		//--Отправка значения;					
for(uint8_t i=0;i<3;i++){RT_HW_Base.uartWrite(ptr[id.num]->uart,0XFF);}	//--Отправка 0xFF 0xFF 0xFF;
ptr[id.num]->timeBeginBusy=micros(); 						//--Фиксация времени для динамической задержки;
id.ddr++;}													//--Переход на следующй этап;	
//------Динамическая задержка и сброс занятости UART-----------------------------------------------
if(id.ddr==2){     
if(RT_HW_Base.getPastMcs(ptr[id.num]->timeBeginBusy)<=2500){return;} //--Динамическая пауза 800mcs;
ptr[id.num]->busy=0;  				//--Сброс флага занятости UART;
id.ddr=0; return;}  				//--Передача управления на начало:
}; //--END sendNameVal(); 
*/

