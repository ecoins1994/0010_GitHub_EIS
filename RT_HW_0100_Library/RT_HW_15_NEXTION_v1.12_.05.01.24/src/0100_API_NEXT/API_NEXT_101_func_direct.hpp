//=================================================================================================
//						   Настройка параметров устройства							
//=================================================================================================
void setDeviceID(RT_HW_STRUCT_NEXT_DEVICE &z, 	    //==Настройка параметров;
            uint8_t *arrByte,  uint16_t *arrWord,   uint32_t *arrLong, 
            uint8_t lenArrByte,uint8_t  lenArrWord, uint8_t lenArrLong){
//------------Настройка параметров главной управляющей функции-------------------------------------
if(z.custom!=0) {return;}								//--Выход, если устройство ужже инициализирован;
z.num=z.ddr=z.blink=z.ready=z.readyRead=0;				//--clear registers;
if(!RT_HW_Base.uartCheckNum(z.uart)) {z.codeErr=60;}	//--check allow num UART;
if(z.codeErr==0){z.num=RT_HW_Base.setFistFreeDevice(hive.set,RT_HW_NEXT_MAX_DEVICE);	//--getting number free device;
			     if(z.num==0) 		 {z.codeErr=61;}}	//--check number getting free device;
if(z.codeErr==0){
ptr[z.num]=&z;														//--reservation pointer ID;
z.ptrArrByte=arrByte; 	 z.ptrArrWord=arrWord;	  z.ptrArrLong=arrLong;		//--reservation pointer array;  
z.lenArrByte=lenArrByte; z.lenArrWord=lenArrWord; z.lenArrLong=lenArrLong;	//--reservation size    array;  
z.busy=0;  				//--Флаг занятости;						
z.custom=1;  return;}	//--Успешный выход;
z.custom=90; return;	//--Выход при ошибке настройкиж
};
//=================================================================================================
//						    Nextion	управление							
//=================================================================================================
void direct   (RT_HW_STRUCT_NEXT_DEVICE &z){		
//---------------------------Тактирующий генератор 50ms--------------------------------------------
if(RT_HW_Base.shed.ready){z.blink=RT_HW_Base.shed.blink50;}					        //--Тактирующие меандры от диспетчера задач;
else                     {if(RT_HW_Base.periodMs(z.timeBeginGen,50)){z.blink^=1;};} //--Тактирующие меандры от внутреннего генератора;
//---------------------------Сторожевой таймер-----------------------------------------------------
if(z.agoBlink!=z.blink){z.agoBlink=z.blink; 								//--Фиксация такта генератора;
						if(z.busy){if(++z.wdBusy>3){z.wdBusy=0; z.busy=0;}} //--Сторожевой таймер
                        else			    {       z.wdBusy=0;}}          //                 busy;
//---------------------------Настройка UART--------------------------------------------------------
if(z.ddr==0){if(z.custom!=1){return;} 										//--Ожидание настройки ID;
             if(z.ready==0) {RT_HW_Base.uartBegin(z.uart);}  z.ddr=1;} 	    //--Инициализация UART;		  
if(z.ddr==1){if(!RT_HW_Base.uartSerial(z.uart)){return;}		            //--Ожидание готовности UART;
             z.ready=1; z.step=0; z.ddr=2;}									//--Переход на рабочий режим;
//---------------------------Прием транзакций------------------------------------------------------
if(z.ddr==2){getFromNxt(z);}   												//--Прием транзакций;          
};
//=================================================================================================
//						              Сервисные функции								
//=================================================================================================
uint8_t getBlink   (uint8_t num){return ptr[num]->blink;}		//==Возвращает меандр тактирующего генератора; 
uint8_t checkReady (uint8_t num){return ptr[num]->ready;}		//==Проверка настройки UART;
uint8_t checkBusy  (uint8_t num){return ptr[num]->busy;}		//==Проверка допустимости номера устройства;
void    setBusy    (uint8_t num){ptr[num]->busy=1;}			    //==Установка флага занятости с фиксацией времени для watchdog; 
void    clrBusy    (uint8_t num){ptr[num]->busy=0;}			    //==Очистка флага занятости с фиксацией времени для watchdog; 
//=================================================================================================
//								Функции для работы с массивами данных		
//================================================================================================= 
bool     checkNum  (uint8_t num){						    //==check доступности устройства с номером num;
 if((num==0) || (num>RT_HW_NEXT_MAX_DEVICE)){return 0;} else {return 1;}}
uint32_t getPtrArr (uint8_t num, char mode){			    //==getting address pointer array; 
if(checkNum(num)){
if(mode=='B'){return (uint32_t)ptr[num]->ptrArrByte;}
if(mode=='W'){return (uint32_t)ptr[num]->ptrArrWord;}
if(mode=='L'){return (uint32_t)ptr[num]->ptrArrLong;}
if(mode=='Z'){return (uint32_t)ptr[num];}} 
              return (uint32_t)ptr[0]->ptrArrLong;}	
uint8_t  getLenArr (uint8_t num, char mode){ 			    //==getting len array;
if(checkNum(num)){
if((num==0) || (num>RT_HW_NEXT_MAX_DEVICE)){return 0;} 	
if(mode=='B'){return ptr[num]->lenArrByte;}
if(mode=='W'){return ptr[num]->lenArrWord;}
if(mode=='L'){return ptr[num]->lenArrLong;}
if(mode=='Z'){return ptr[num]->lenArrLong;}} return 0;}
//---------------------------------------------------------------------------------------------------
//  						Функция чтения из байтового массива
//---------------------------------------------------------------------------------------------------
uint32_t getVarArr (uint8_t num, uint8_t index){ //==getting value from array;
if(checkNum(num)){if(index>=getLenArr(num,'B')) {return 0;} else {uint8_t  *arr=ptr[num]->ptrArrByte; return arr[index];}}
return 0;};
//---------------------------------------------------------------------------------------------------
//  						Функция чтения из разных массивов (со временем наверное уберется)
//---------------------------------------------------------------------------------------------------
uint32_t getVarArr (uint8_t num, char mode, uint8_t index){ //==getting value from array;
if(checkNum(num)){
if(mode=='B'){if(index>=getLenArr(num,'B')) {return 0;} else {uint8_t  *arr=ptr[num]->ptrArrByte; return arr[index];}}
if(mode=='W'){if(index>=getLenArr(num,'W')) {return 0;} else {uint16_t *arr=ptr[num]->ptrArrWord; return arr[index];}}
if(mode=='L'){if(index>=getLenArr(num,'L')) {return 0;} else {uint32_t *arr=ptr[num]->ptrArrLong; return arr[index];}}} return 0;}
//---------------------------------------------------------------------------------------------------
void     setVarArr (uint8_t num, char mode, uint8_t index, uint32_t val){ //==setting value to array;
if(checkNum(num)){
if(mode=='B'){if(index>=getLenArr(num,'B')) {return;} else {uint8_t  *arr=ptr[num]->ptrArrByte; arr[index]= (uint8_t)val;}}
if(mode=='W'){if(index>=getLenArr(num,'W')) {return;} else {uint16_t *arr=ptr[num]->ptrArrWord; arr[index]=(uint16_t)val;}}
if(mode=='L'){if(index>=getLenArr(num,'L')) {return;} else {uint32_t *arr=ptr[num]->ptrArrLong; arr[index]=(uint32_t)val;}}}}
//=================================================================================================
//								Getting system 		
//=================================================================================================
uint8_t  getSystem (uint8_t num, char mode){
if(checkNum(num)){
if(mode=='P'){return ptr[num]->vPage;}
if(mode=='S'){return ptr[num]->vSleep;}
if(mode=='W'){return ptr[num]->vWeek;}
if(mode=='D'){return ptr[num]->vDay;}
if(mode=='M'){return ptr[num]->vMonth;}
if(mode=='Y'){return ptr[num]->vYear;}
if(mode=='h'){return ptr[num]->vHour;}
if(mode=='m'){return ptr[num]->vMin;}
if(mode=='s'){return ptr[num]->vSec;}
}
return 0;};


uint8_t  getTest (uint8_t num, char mode){if(checkNum(num)){
if(mode=='E'){return ptr[num]->codeErr;}
return 0;}}

//=================================================================================================


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//					Прием транзакций из Nextion 
// Транзакции принимаются в фоновом режиме.
// Формат транзакций для данных (uint8_t):
//   head[0]=0x3A; 
//   func[1]-функции приема-0x6,0x16,0x26,0x36,0x46,0x56 в массив prt.
//   adr[2]
//   qnt[3]
//   qntByte[4]    
// Формат транзакции для номера страницы: 0x66 page 0xFF 0xFF 0xFF
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void getFromNxt(RT_HW_STRUCT_NEXT_DEVICE &z){
//-------------------------------------------------------------------------------------------------
//						Очистка параметров 
//-------------------------------------------------------------------------------------------------
if(z.step==0) {z.index=z.codeErr=z.step=0;	 
               for(uint8_t i=0; i<RT_HW_NEXT_BUFF_REG_SIZE; i++){z.buff[i]=0;}	//--Clearing buff;
			   z.step++; return;}												//--goto next step;
//-------------------------------------------------------------------------------------------------
//				Ожидание заголовка принимаемой транзакции
//-------------------------------------------------------------------------------------------------
if(z.step==1) {if(!RT_HW_Base.uartAvailable(z.uart)){return;}//-waiting first code head;
			   z.head=z.buff[z.index]=RT_HW_Base.uartRead(z.uart);
			   z.codeErr=z.step=z.index=0;					//--clear index;
               z.timeGet=millis();
               z.index++;				//--store first code head;
               if(z.head==0x3A){z.step= 2;}	//--Переход на обработку транзакции с данными в формате ~~ModBus;
			   if(z.head==0x66){z.step=10;} //--Переход на обработку транзакции с номером страницы;
			   if(z.head==0x86){z.step=20;} //--Переход на обработку кода "Дисплей перешел в спящий  режим";
			   if(z.head==0x87){z.step=20;} //--Переход на обработку кода "Дисплей вышел из  спящего режима";
			   if(z.step==0)   {return;}	//--Возврат если неопознанный код заголовка			   
			   
			   //RT_HW_Base.consoleTest(String(F("Head")),z.head,';','H');
			   //RT_HW_Base.consoleTest(String(F(" step")),z.step);
}			   
//-------------------------------------------------------------------------------------------------
//				Обработка заголовка принимаемой транзакции (func,qnt,qntByte)
//-------------------------------------------------------------------------------------------------
if(z.step==2) {do{
			      if(RT_HW_Base.uartAvailable(z.uart))
				  {
			       z.buff[z.index]=RT_HW_Base.uartRead(z.uart); z.timeGet=millis();	
				   if(z.index==1) {z.func=z.buff[z.index]; 
				                   if((z.func!=0x06)&&(z.func!=0x16)&&(z.func!=0x26)&&(z.func!=0x46)&&(z.func!=0x56)) 
								                                   {z.codeErr=51; z.step=0;  return;}} //--check code func;	
				   if(z.index==2) {z.adr=z.buff[z.index];}
				   if(z.index==3) {z.qnt=z.buff[z.index];}
				   if(z.index==4) {z.qntByte=z.buff[z.index];
								   if(z.func==0x06){if(z.qntByte!=z.qnt) 	{z.codeErr=60;} else {if((z.adr+z.qnt)> z.lenArrByte) {z.codeErr=61;}}}
                                   if(z.func==0x16){if(z.qntByte!=(z.qnt*2)){z.codeErr=62;} else {if((z.adr+z.qnt)> z.lenArrWord) {z.codeErr=63;}}}	
	                               if(z.func==0x26){if(z.qntByte!=(z.qnt*4)){z.codeErr=64;} else {if((z.adr+z.qnt)> z.lenArrLong) {z.codeErr=65;}}}
								   if(z.func==0x46){if(z.qntByte!=z.qnt)    {z.codeErr=66;}}
								   if(z.func==0x56){if(z.qntByte!=z.qnt)    {z.codeErr=67;}}
				// RT_HW_Base.consoleTest(String(F("Nxt read step=2,4 codeErr")),z.codeErr);			   
	                               if(z.codeErr!=0){z.step=0; return;}
	                               if(z.qntByte>32){z.step=0; return;}}
                                   z.index++;
								   if(z.index>4){z.step++; break;}}
				  if(RT_HW_Base.getPastMs(z.timeGet)>z.timeOutGetByte)      {z.codeErr=70; z.step=0; return;}
				 } while(1);			 

			//RT_HW_Base.consoleTest(String(F(" head")),z.head,',');
			//RT_HW_Base.consoleTest(String(F(" func")),z.func,',');	
			//RT_HW_Base.consoleTest(String(F(" adr")), z.adr,',');
			//RT_HW_Base.consoleTest(String(F(" qnt")), z.qnt,',');
			//RT_HW_Base.consoleTest(String(F(" qntByte")), z.qntByte,',');			
			//RT_HW_Base.consoleTest(String(F(" index")),   z.index);
			
			 }
//-------------------------------------------------------------------------------------------------
//				Обработка данных транзакций + crc + end
//-------------------------------------------------------------------------------------------------
if(z.step==3) {do{	
               if(RT_HW_Base.uartAvailable(z.uart)){
		          z.buff[z.index]=RT_HW_Base.uartRead(z.uart); z.timeGet=millis();
				  if(z.index==z.qntByte+5) {z.crc=z.buff[z.index];}
		          z.index++;
		          if(z.index>(z.qntByte+5)){z.step++; break;}}
		          if(RT_HW_Base.getPastMs(z.timeGet)>z.timeOutGetByte) 		{z.codeErr=71; z.step=0; return;}	//--check time-out transaction;	
				 } while(1);
				 //RT_HW_Base.consoleTest(String(F("Nxt read step=3,x codeErr")),z.codeErr);
				 
				 }   
//-------------------------------------------------------------------------------------------------
//				Обработка целостности транзакций
//-------------------------------------------------------------------------------------------------
if(z.step==4) {z.crcCalc=0; z.readyRead=1; z.cntGetPackAll++;
			   for(uint8_t i=0;i<=(z.qntByte+4); i++){z.crcCalc=z.crcCalc+z.buff[i];}			   
			   z.crcCalc=z.crcCalc&0xFF;
               z.crcCalc=0xFF-z.crcCalc;	
			   z.crcCalc++;
               if(z.crcCalc!=z.crc)  {z.codeErr=85; z.step=0; return;} 
			   if(z.func==0x56) {z.vYear=z.buff[5]; z.vMonth=z.buff[6]; z.vDay=z.buff[7]; 
							     z.vHour=z.buff[8]; z.vMin  =z.buff[9]; z.vSec=z.buff[10]; z.vWeek=z.buff[11]; 							 
								 //z.vRsv1=z.buff[12]; z.vRsv2 =z.buff[13];						
								 }	
			   for(uint8_t i=0; i<z.qnt;i++){
			       if(z.func==0x06) {uint8_t  bf= z.buff[i+5]; 		
				   //RT_HW_Base.consoleVar(bf,' ',0,'H');
				   setVarArr(z.num,'B',(z.adr+i),bf);}
	               if(z.func==0x16) {uint16_t bf=(z.buff[i*2+1+5]<<8)+z.buff[i*2+5]; i+=1; setVarArr(z.num,'W',(z.adr+i),bf);}
                   if(z.func==0x26) {uint32_t bf=(z.buff[i*4+1+5]<<8)+z.buff[i*4+5]; i+=3; setVarArr(z.num,'L',(z.adr+i),bf);}
				   //if(z.func==0x46) {uint8_t  bf=(z.buff[i+5]                              setValArr(z.num,'L',(z.adr+i),bf);}			   
				   }
                   //RT_HW_Base.consoleCR();
				   
				//RT_HW_Base.consoleTest(String(F("Nxt func")),z.func,',');
				//RT_HW_Base.consoleTest(String(F(" qnt")),z.qnt,':');
				//for(uint8_t i=0; i<z.qnt; i++){uint8_t  bf=getVarArr(z.num,'B',i); RT_HW_Base.consoleVar(bf,'_');}
				//RT_HW_Base.consoleCR();
				
               z.cntGetPackOk++; z.codeErr=0; z.step=0; return;}  	
//-------------------------------------------------------------------------------------------------
//				Обработка транзакциии с номером страницы
//-------------------------------------------------------------------------------------------------
if(z.step==10) {do{
			      if(RT_HW_Base.uartAvailable(z.uart))
				  {
			       z.buff[z.index]=RT_HW_Base.uartRead(z.uart); z.timeGet=millis();	
				   if(z.index==1) {if(z.buff[z.index]>=64)   {z.codeErr=90+z.index; z.step=0; return;}} 				             
				   if(z.index==2) {if(z.buff[z.index]!=0xFF) {z.codeErr=90+z.index; z.step=0; return;}}
				   if(z.index==3) {if(z.buff[z.index]!=0xFF) {z.codeErr=90+z.index; z.step=0; return;}}				   
				   if(z.index==4) {if(z.buff[z.index]!=0xFF) {z.codeErr=90+z.index; z.step=0; return;}
								   else                      {z.vPage=z.buff[1];    z.step=0; return;}}
				  z.index++;
				  }
				  if(RT_HW_Base.getPastMs(z.timeGet)>z.timeOutGetByte){z.codeErr=99; z.step=0; return;}
				 } while(1);
			  }
//-------------------------------------------------------------------------------------------------
//				Обработка транзакциии с кодом входа/выхода спящего режима
//-------------------------------------------------------------------------------------------------
if(z.step==20) {do{
			      if(RT_HW_Base.uartAvailable(z.uart))
				  {
			       z.buff[z.index]=RT_HW_Base.uartRead(z.uart); z.timeGet=millis();					             
				   if(z.index==1) {if(z.buff[z.index]!=0xFF) {z.codeErr=90+z.index; z.step=0; return;}}
				   if(z.index==2) {if(z.buff[z.index]!=0xFF) {z.codeErr=90+z.index; z.step=0; return;}}				   
				   if(z.index==3) {if(z.buff[z.index]!=0xFF) {z.codeErr=90+z.index; z.step=0; return;}
				                   else                      {if(z.head==0x86){z.vSleep=1;} 
								                              if(z.head==0x87){z.vSleep=0;} 
								                                                    z.step=0; return;}}
				  z.index++;
				  }
				  if(RT_HW_Base.getPastMs(z.timeGet)>z.timeOutGetByte){z.codeErr=99; z.step=0; return;}
				 } while(1);
			  }			  
//=================================================================================================
};	//++++END getFromNxt)

/*
//=================================================================================================
//						    Nextion								
//=================================================================================================
void setID    (RT_HW_STRUCT_NEXT_DEVICE &z, 	    //==Настройка параметров;
            uint8_t *arrByte,  uint16_t *arrWord,   uint32_t *arrLong, 
            uint8_t lenArrByte,uint8_t  lenArrWord, uint8_t lenArrLong){
//------------Настройка параметров главной управляющей функции-------------------------------------
if(z.custom==0) {													//--to avoid re-initialization;
z.num=z.ddr=z.blink=z.ready=z.readyRead=0;							//--clear registers;
if(!RT_HW_Base.uartCheckNum(z.uart)) {z.custom=90; return;}			//--check allow num UART;
z.num=RT_HW_Base.setFistFreeDevice(hive.set,RT_HW_NEXT_MAX_DEVICE);	//--getting number free device;
if(z.num==0) 		                 {z.custom=91; return;}			//--check number getting free device;
ptr[z.num]=&z;														//--reservation pointer ID;
z.ptrArrByte=arrByte; 												//--reservation pointer byte array;  
z.ptrArrWord=arrWord; 												//--reservation pointer word array;    
z.ptrArrLong=arrLong; 												//--reservation pointer long array; 
z.lenArrByte=lenArrByte; 											//--reservation size    byte array;  
z.lenArrWord=lenArrWord;											//--reservation size    word массива;    
z.lenArrLong=lenArrLong;											//--reservation size    long массива; 
//z.cntGetPackAll=z.cntGetPackOk=0;
z.busy=0;  															//--Флаг занятости;
//z.durationByte=((1000000UL/z.speed)+1)*8;							//--Длительность приема/передачи одного байта;
z.custom=1;}};
*/





