//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							1.Function cosoleBegin, consoleEN, consoleWrite
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//							1.1.CONSOLE: Basic console setup
//=================================================================================================
bool consoleBegin(){
if(console.dir==4) {return console.ok;}				//--Empty console entry;
//-------------------------------------------------------------------------------------------------
if(console.dir==0) {								//--Waiting for an external trigger signal;	
   console.run=console.ok=console.head=console.all=0; 			//--Reset states;	
   uartBegin(console.numUart);						//--Console initialization;							  	
   messDefault();									//--Setting default parameters;
   console.dir++;   return console.ok;}									//--Goto dir=1;
//-------------------------------------------------------------------------------------------------
if(console.dir==1) {								//--Waiting for console to be ready;
 //if(!Serial){return console.ok;}
 if(uartSerial(console.numUart)==0) {return console.ok;} //--Waiting for console to be ready;
	console.run=console.head=1;			//--Set ok,head;   
	consoleBlank(10);     consoleCR();	//--Cleaning the console panel(the Arduino IDE cleanup code could not be found);	   
	console.dir++; return console.ok;}	//--Goto dir=2; 				
//-------------------------------------------------------------------------------------------------
if(console.dir==2) {console.head=0; console.ok=1; console.dir++; return console.ok;}
//-------------------------------------------------------------------------------------------------
if(console.dir==3) {							
   console.head=0; console.all=1;					//--Clear head, set all; 
   console.dir=3;} 								//--Goto dir=3;
//-------------------------------------------------------------------------------------------------
return console.ok;};
//=================================================================================================
uint8_t consoleOk(){
if(!console.run){consoleBegin();}
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_RP2040)
if(console.ok & Serial){return 1;}
//-------------------------------------------------------------------------------------------------
#else
if(console.ok)         {return 1;} 
#endif
//-------------------------------------------------------------------------------------------------
return 0;}
//=================================================================================================
uint8_t consoleHead(){
if(!console.run){consoleBegin();}
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_RP2040)
if(console.head & Serial){return 1;} 
//-------------------------------------------------------------------------------------------------
#else
if(console.head)         {return 1;} 
#endif
//-------------------------------------------------------------------------------------------------
return 0;}
//=================================================================================================
uint8_t consoleRun(){
if(!console.run){consoleBegin();}
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_RP2040)
if(console.run & Serial){return 1;} 
//-------------------------------------------------------------------------------------------------
#else
if(console.run)         {return 1;} 
#endif
//-------------------------------------------------------------------------------------------------
return 0;}

//=================================================================================================
//							1.2.CONSOLE: Configuring the console for use in external functions
//=================================================================================================
uint8_t consoleEN(uint8_t &run, uint8_t &agoEN, bool extEN){
if(agoEN!=extEN){agoEN=extEN; if(extEN){run=1;}}
if(run==1)      {if(consoleBegin()){run=2;}}
return run;}
//=================================================================================================
// 							1.3.CONSOLE: MAIN OUTPUT FUNCTION - byte (character) output
// 										[temporary patch for RP2040!!!]
//=================================================================================================
uint8_t consoleWrite(uint8_t v){
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_RP2040)
//if(!console.run){return 0;}
if(console.run & Serial){Serial.print(char(v)); return 1;}
#else
if(console.run)  {uartWrite(v,console.numUart); return 1;} 	
#endif
return 0;}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								2.Function output
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=================================================================================================
//								2.1.OUTPUT simple functions
// Suffix: '~'-nothing is output, G-space, L-line translation, E-';'+line translation, S-';', V-',' or any other character;	
//=================================================================================================
void consoleSuff (RT_HW_STRUCT_MESS &id,             char suff='~'){if(consoleRun()){messSuff(id, suff);    if(id.lenSuff){consoleWrite(id.suff);} if(id.lenCR){consoleWrite('\n');}}};	//++++Вывод суффикса; 
void consoleChar (RT_HW_STRUCT_MESS &id, char v=' ', char suff='~'){if(consoleRun()){consoleWrite(v);                      consoleSuff(id,suff);}};										//++++Вывод символа с суффиксом;
void consoleCR   (RT_HW_STRUCT_MESS &id,             uint8_t sz=1) {if(consoleRun()){id.size=sz;        for(console.idx=0; console.idx<sz; console.idx++){consoleWrite('\n');}}};		//++++Вывод переводoв строки;
void consoleBlank(RT_HW_STRUCT_MESS &id,             uint8_t sz)   {if(consoleRun()){id.size=sz;        for(console.idx=0; console.idx<sz; console.idx++){consoleWrite((uint8_t)(id.blank));}}};//+++Вывод sz пробелов;
void consoleBlank(RT_HW_STRUCT_MESS &id, char v,     uint8_t sz)   {if(consoleRun()){consoleSuff(id,v); for(console.idx=0; console.idx<sz; console.idx++){consoleWrite((uint8_t)v);}}};	//+++Вывод sz заполнителей=v;	 															//++++Вывод sz заполнителей=v с суффиксом; 
void consoleLine (RT_HW_STRUCT_MESS &id, char v='=', uint8_t sz=80){if(consoleRun()){id.size=sz;        for(console.idx=0; console.idx<sz; console.idx++){consoleWrite((uint8_t)v);} consoleWrite('\n');}};//++Вывод линии;
//-------------------------------------------------------------------------------------------------
void consoleSuff (char suff)                {if(consoleRun()){messSuff(mess,suff); if(mess.lenSuff){consoleWrite(mess.suff);} if(mess.lenCR){consoleWrite('\n');}}};	//++++Вывод суффикса; 
void consoleChar (char v=' ', char suff='~'){if(consoleRun()){consoleWrite(v); consoleSuff(suff);}};																	//++++Вывод символа с суффиксом [G,L,E,S,V,~];
void consoleCR   (uint8_t sz=1)             {if(consoleRun()){for(console.idx=0; console.idx<sz; console.idx++){consoleWrite('\n');}}};									//++++Вывод нескольких переводoв строки;
void consoleBlank(            uint8_t sz)   {if(consoleRun()){for(console.idx=0; console.idx<sz; console.idx++){consoleWrite((uint8_t)(mess.blank));}}};				//++++Вывод sz пробелов;
void consoleBlank(char v,     uint8_t sz)   {if(consoleRun()){for(console.idx=0; console.idx<sz; console.idx++){consoleWrite((uint8_t)v);};}};							//++++Вывод sz заполнителей=v;	 															//++++Вывод sz заполнителей=v с суффиксом; 
void consoleLine (char v='=', uint8_t sz=80){if(consoleRun()){for(console.idx=0; console.idx<sz; console.idx++){consoleWrite((uint8_t)v);} consoleWrite('\n');}}; 		//++++Вывод горизонтальной линии;					   
//=================================================================================================
//								2.2.OUTPUT of generated message mess.str
//=================================================================================================	
void consoleMess(RT_HW_STRUCT_MESS &id, uint8_t qntArr=0){
if(id.lenBegin){for(id.idx=0; id.idx<id.lenBegin;id.idx++){consoleWrite(id.blank);}}//--Вывод заполнителей перед значением;
//-------------------------------------------------------------------------------------------------
if(id.lenVar){																		//--Вывод если lenVar>0;
if(id.modeVar=='S'){																//--Вывод для переменных String;
const char * data=id.str.c_str(); 													//--Установка указателя на начало строки;	
     for(id.idx=0;id.idx<id.qnt;   id.idx++){consoleWrite(data[id.idx]);}}			//--Вывод текста длиной qnt;	
else{for(id.idx=0;id.idx<id.lenVar;id.idx++){consoleWrite(id.str.charAt(id.idx));}}}//--Вывод для остальных переменных;
//-------------------------------------------------------------------------------------------------
if(qntArr){
if((id.adx+1)<qntArr){consoleWrite((uint8_t)id.separator);							//--Вывод разделителя между элементами массива;
if(id.lenEnd) {for(id.idx=0; id.idx<id.lenEnd; id.idx++){consoleWrite(id.blank);}}return;}}//--Вывод заполнителей после элемента массива;
//-------------------------------------------------------------------------------------------------
if(id.lenSuff){consoleWrite((uint8_t)id.suff);}									 	//--Вывод суффикса;
if(id.lenEnd) {for(id.idx=0; id.idx<id.lenEnd; id.idx++){consoleWrite(id.blank);}}	//--Вывод заполнителей после;
if(id.lenCR)  {consoleWrite('\n');}													//--Вывод перевода строки;				
};
//=================================================================================================
//								2.3.OUTPUT header
//=================================================================================================	
void consoleHead(String  v,char bl='-',  uint8_t sz=80, char mode='S'){
static char _alig; static char _blank;
if(consoleRun()){
_alig=mess.alig;   mess.alig='C';		//--Сохранение предущего и установка нового значения alig;
_blank=mess.blank; mess.blank=bl;		//--Сохранение предущего и установка нового значения alig;	
consoleVar(v,'L',sz,mode); 				//--Вывод заголовка;
mess.alig =_alig;   					//--Восстановления предущего значения alig;
mess.blank=_blank; 						//--Восстановления предущего значения alig;		
}};
//=================================================================================================
//								2.4.OUTPUT of variables
//=================================================================================================
void consoleVar( int8_t  v,char suff='~',uint8_t sz=0,char mode='Z',String head="~"){if(consoleRun()){varToMess(mess,v,suff,sz,mode,head);	consoleMess(mess);}}; //--int8_t  [mode:P,A,C,B,*,H,U,I,0,1,2,3,Z,z,X];
void consoleVar(uint8_t  v,char suff='~',uint8_t sz=0,char mode='Z',String head="~"){if(consoleRun()){varToMess(mess,v,suff,sz,mode,head);	consoleMess(mess);}}; //--uint8_t [mode:P,A,C,B,*,H,U,I,0,1,2,3,Z,z,X];
void consoleVar( int16_t v,char suff='~',uint8_t sz=0,char mode='Z')				{if(consoleRun()){varToMess(mess,v,suff,sz,mode);     	consoleMess(mess);}}; //--int16_t [mode:B,*,H,U,I,0,1,2,3,Z,z];
void consoleVar(uint16_t v,char suff='~',uint8_t sz=0,char mode='Z')				{if(consoleRun()){varToMess(mess,v,suff,sz,mode);    	consoleMess(mess);}}; //--uint16_t[mode:B,*,H,U,I,0,1,2,3,Z,z];
void consoleVar( int32_t v,char suff='~',uint8_t sz=0,char mode='Z')				{if(consoleRun()){varToMess(mess,v,suff,sz,mode); 		consoleMess(mess);}}; //--int32_t [mode:B,*,H,U,I,0,1,2,3,Z,z];
void consoleVar(uint32_t v,char suff='~',uint8_t sz=0,char mode='Z')				{if(consoleRun()){varToMess(mess,v,suff,sz,mode); 		consoleMess(mess);}}; //--uint32_t[mode:B,*,H,U,I,0,1,2,3,Z,z];
void consoleVar(float    v,char suff='~',uint8_t sz=0,char mode='2')				{if(consoleRun()){varToMess(mess,v,suff,sz,mode); 		consoleMess(mess);}}  //--float   [mode:0,1,2,3,Z,z];
void consoleVar(String   v,char suff='~',uint8_t sz=0,char mode='S')				{if(consoleRun()){varToMess(mess,v,suff,sz,mode); 		consoleMess(mess);}}; //--String  [mode:N,U,L];
void consoleVar(char     v,char suff='~',uint8_t sz=0,char mode='N')				{if(consoleRun()){varToMess(mess,v,suff,sz,mode); 		consoleMess(mess);}}; //--char    [mode:N,U,L];
void consoleVar(bool     v,char suff='~',uint8_t sz=0,char mode='1')				{if(consoleRun()){varToMess(mess,v,suff,sz,mode); 		consoleMess(mess);}}; //--bit     [mode:0 0/1,1 -+,2  *,3  #,4 -|,5 <>,6 _+,7 _*,8 _+;
//=================================================================================================
//								2.5.OUTPUT of formatted array
//=================================================================================================
void consoleArr( int8_t  *arr, char suff, uint8_t sz, char mode, uint8_t qnt)		{for(mess.adx=0; mess.adx<qnt; mess.adx++){varToMess(mess,arr[mess.adx],suff,sz,mode); consoleMess(mess,qnt);}};
void consoleArr(uint8_t  *arr, char suff, uint8_t sz, char mode, uint8_t qnt)		{for(mess.adx=0; mess.adx<qnt; mess.adx++){varToMess(mess,arr[mess.adx],suff,sz,mode); consoleMess(mess,qnt);}};
void consoleArr( int16_t *arr, char suff, uint8_t sz, char mode, uint8_t qnt)		{for(mess.adx=0; mess.adx<qnt; mess.adx++){varToMess(mess,arr[mess.adx],suff,sz,mode); consoleMess(mess,qnt);}};
void consoleArr(uint16_t *arr, char suff, uint8_t sz, char mode, uint8_t qnt)		{for(mess.adx=0; mess.adx<qnt; mess.adx++){varToMess(mess,arr[mess.adx],suff,sz,mode); consoleMess(mess,qnt);}};
void consoleArr( int32_t *arr, char suff, uint8_t sz, char mode, uint8_t qnt)		{for(mess.adx=0; mess.adx<qnt; mess.adx++){varToMess(mess,arr[mess.adx],suff,sz,mode); consoleMess(mess,qnt);}};
void consoleArr(uint32_t *arr, char suff, uint8_t sz, char mode, uint8_t qnt)		{for(mess.adx=0; mess.adx<qnt; mess.adx++){varToMess(mess,arr[mess.adx],suff,sz,mode); consoleMess(mess,qnt);}};
void consoleArr(float    *arr, char suff, uint8_t sz, char mode, uint8_t qnt)		{for(mess.adx=0; mess.adx<qnt; mess.adx++){varToMess(mess,arr[mess.adx],suff,sz,mode); consoleMess(mess,qnt);}};
void consoleArr(String   *arr, char suff, uint8_t sz, char mode, uint8_t qnt)		{for(mess.adx=0; mess.adx<qnt; mess.adx++){varToMess(mess,arr[mess.adx],suff,sz,mode); consoleMess(mess,qnt);}};
void consoleArr(bool     *arr, char suff, uint8_t sz, char mode, uint8_t qnt)		{for(mess.adx=0; mess.adx<qnt; mess.adx++){varToMess(mess,arr[mess.adx],suff,sz,mode); consoleMess(mess,qnt);}};
void consoleArr(char     *arr, char suff, uint8_t sz, char mode, uint8_t qnt)		{for(mess.adx=0; mess.adx<qnt; mess.adx++){varToMess(mess,arr[mess.adx],suff,sz,mode); consoleMess(mess,qnt);}};
//=================================================================================================
//			 					2.6.OUTPUT of test variables
//=================================================================================================
void consoleTest(String str,  int8_t  v, char suff='E', char mode='Z') 				{if(consoleRun()){consoleVar(str,'='); consoleVar(v,suff,0,mode);}};
void consoleTest(String str, uint8_t  v, char suff='E', char mode='Z') 				{if(consoleRun()){consoleVar(str,'='); consoleVar(v,suff,0,mode);}};
void consoleTest(String str,  int16_t v, char suff='E', char mode='Z') 				{if(consoleRun()){consoleVar(str,'='); consoleVar(v,suff,0,mode);}};
void consoleTest(String str, uint16_t v, char suff='E', char mode='Z') 				{if(consoleRun()){consoleVar(str,'='); consoleVar(v,suff,0,mode);}};
void consoleTest(String str,  int32_t v, char suff='E', char mode='Z') 				{if(consoleRun()){consoleVar(str,'='); consoleVar(v,suff,0,mode);}};
void consoleTest(String str, uint32_t v, char suff='E', char mode='Z') 				{if(consoleRun()){consoleVar(str,'='); consoleVar(v,suff,0,mode);}};
void consoleTest(String str, float    v, char suff='E', char mode='Z') 				{if(consoleRun()){consoleVar(str,'='); consoleVar(v,suff,0,mode);}};
void consoleTest(String str, String   v, char suff='E', char mode='Z') 				{if(consoleRun()){consoleVar(str,'='); consoleVar(v,suff,0,mode);}};
void consoleTest(String str, char     v, char suff='E', char mode='Z') 				{if(consoleRun()){consoleVar(str,'='); consoleVar(v,suff,0,mode);}};
void consoleTest(String str, bool     v, char suff='E', char mode='Z') 				{if(consoleRun()){consoleVar(str,'='); consoleVar(v,suff,0,mode);}};
//=================================================================================================
//			 					2.6.OUTPUT of test variables
//=================================================================================================
void consoleTestArr(String str, int8_t  *arr,char suff, char mode, uint8_t qnt) 	{if(consoleRun()){consoleVar(str,'='); consoleArr(arr,suff,0,mode,qnt);}};
void consoleTestArr(String str,uint8_t  *arr,char suff, char mode, uint8_t qnt) 	{if(consoleRun()){consoleVar(str,'='); consoleArr(arr,suff,0,mode,qnt);}};
void consoleTestArr(String str, int16_t *arr,char suff, char mode, uint8_t qnt) 	{if(consoleRun()){consoleVar(str,'='); consoleArr(arr,suff,0,mode,qnt);}};
void consoleTestArr(String str,uint16_t *arr,char suff, char mode, uint8_t qnt) 	{if(consoleRun()){consoleVar(str,'='); consoleArr(arr,suff,0,mode,qnt);}};
void consoleTestArr(String str, int32_t *arr,char suff, char mode, uint8_t qnt) 	{if(consoleRun()){consoleVar(str,'='); consoleArr(arr,suff,0,mode,qnt);}};
void consoleTestArr(String str,uint32_t *arr,char suff, char mode, uint8_t qnt) 	{if(consoleRun()){consoleVar(str,'='); consoleArr(arr,suff,0,mode,qnt);}};
void consoleTestArr(String str, float   *arr,char suff, char mode, uint8_t qnt) 	{if(consoleRun()){consoleVar(str,'='); consoleArr(arr,suff,0,mode,qnt);}};
void consoleTestArr(String str, char    *arr,char suff, char mode, uint8_t qnt) 	{if(consoleRun()){consoleVar(str,'='); consoleArr(arr,suff,0,mode,qnt);}};
//=================================================================================================
//		   						2.7.OUTPUT of test variables when changing
//=================================================================================================
void consoleChange(String str, uint8_t  &ago, uint8_t  v, char sf='E', char md='z')	{if(consoleRun()){if(ago!=v){ago=v; consoleVar(str,'=');consoleVar(v,sf,0,md);}}}
void consoleChange(String str, int8_t   &ago, int8_t   v, char sf='E', char md='Z')	{if(consoleRun()){if(ago!=v){ago=v; consoleVar(str,'=');consoleVar(v,sf,0,md);}}}
void consoleChange(String str, int16_t  &ago, int16_t  v, char sf='E', char md='Z') {if(consoleRun()){if(ago!=v){ago=v; consoleVar(str,'=');consoleVar(v,sf,0,md);}}}
void consoleChange(String str, uint16_t &ago, uint16_t v, char sf='E', char md='Z') {if(consoleRun()){if(ago!=v){ago=v; consoleVar(str,'=');consoleVar(v,sf,0,md);}}}
void consoleChange(String str, int32_t  &ago, int32_t  v, char sf='E', char md='Z') {if(consoleRun()){if(ago!=v){ago=v; consoleVar(str,'=');consoleVar(v,sf,0,md);}}}
void consoleChange(String str, uint32_t &ago, uint32_t v, char sf='E', char md='Z') {if(consoleRun()){if(ago!=v){ago=v; consoleVar(str,'=');consoleVar(v,sf,0,md);}}}
void consoleChange(String str, float    &ago, float    v, char sf='E', char md='Z') {if(consoleRun()){if(ago!=v){ago=v; consoleVar(str,'=');consoleVar(v,sf,0,md);}}}
void consoleChange(String str, String   &ago, String   v, char sf='E', char md='Z') {if(consoleRun()){if(ago!=v){ago=v; consoleVar(str,'=');consoleVar(v,sf,0,md);}}}
void consoleChange(String str, char     &ago, char     v, char sf='E', char md='Z') {if(consoleRun()){if(ago!=v){ago=v; consoleVar(str,'=');consoleVar(v,sf,0,md);}}}
//=================================================================================================
//		   						2.8.OUTPUT of test array when changing
//=================================================================================================
//----------------------------------int16_t  arr[]-------------------------------------------------
void consoleChangeArr(String str, int8_t   *ago, int8_t   *v, char suff, uint8_t sz, char mode, uint8_t qnt) {
 if(consoleRun()){ 
for(console.idx=0; console.idx<qnt; console.idx++){if(ago[console.idx]!=v[console.idx]){console.idxOk=1; ago[console.idx]=v[console.idx];}}
 if(console.idxOk){console.idxOk=0; consoleVar(str,'=');  consoleArr(ago,suff,sz,mode,qnt);}}};	
//----------------------------------uint8_t  arr[]-------------------------------------------------
void consoleChangeArr(String str, uint8_t  *ago, uint8_t  *v, char suff, uint8_t sz, char mode, uint8_t qnt) {
 if(consoleRun()){
for(console.idx=0; console.idx<qnt; console.idx++){if(ago[console.idx]!=v[console.idx]){console.idxOk=1; ago[console.idx]=v[console.idx];}}
 if(console.idxOk){console.idxOk=0; consoleVar(str,'=');  consoleArr(ago,suff,sz,mode,qnt);}}};	
//----------------------------------int16_t  arr[]-------------------------------------------------
void consoleChangeArr(String str, int16_t  *ago, int16_t  *v, char suff, uint8_t sz, char mode, uint8_t qnt) {
 if(consoleRun()){ 
for(console.idx=0; console.idx<qnt; console.idx++){if(ago[console.idx]!=v[console.idx]){console.idxOk=1; ago[console.idx]=v[console.idx];}}
 if(console.idxOk){console.idxOk=0; consoleVar(str,'=');  consoleArr(ago,suff,sz,mode,qnt);}}};	
//----------------------------------uint16_t arr[]-------------------------------------------------
void consoleChangeArr(String str, uint16_t *ago,uint16_t  *v, char suff, uint8_t sz, char mode, uint8_t qnt) {
 if(consoleRun()){
for(console.idx=0; console.idx<qnt; console.idx++){if(ago[console.idx]!=v[console.idx]){console.idxOk=1; ago[console.idx]=v[console.idx];}}
 if(console.idxOk){console.idxOk=0; consoleVar(str,'=');  consoleArr(ago,suff,sz,mode,qnt);}}};	
//----------------------------------int32_t  arr[]-------------------------------------------------
void consoleChangeArr(String str, int32_t  *ago, int32_t  *v, char suff, uint8_t sz, char mode, uint8_t qnt) {
if(consoleRun()){
for(console.idx=0; console.idx<qnt; console.idx++){if(ago[console.idx]!=v[console.idx]){console.idxOk=1; ago[console.idx]=v[console.idx];}}
 if(console.idxOk){console.idxOk=0; consoleVar(str,'=');  consoleArr(ago,suff,sz,mode,qnt);}}};	
//----------------------------------uint32_t arr[]-------------------------------------------------
void consoleChangeArr(String str, uint32_t *ago, uint32_t *v, char suff, uint8_t sz, char mode, uint8_t qnt) {
 if(consoleRun()){ 
for(console.idx=0; console.idx<qnt; console.idx++){if(ago[console.idx]!=v[console.idx]){console.idxOk=1; ago[console.idx]=v[console.idx];}}
 if(console.idxOk){console.idxOk=0; consoleVar(str,'=');  consoleArr(ago,suff,sz,mode,qnt);}}};
//----------------------------------float    arr[]-------------------------------------------------
void consoleChangeArr(String str, float    *ago, float    *v, char suff, uint8_t sz, char mode, uint8_t qnt) {
 if(consoleRun()){
for(console.idx=0; console.idx<qnt; console.idx++){if(ago[console.idx]!=v[console.idx]){console.idxOk=1; ago[console.idx]=v[console.idx];}}
 if(console.idxOk){console.idxOk=0; consoleVar(str,'=');  consoleArr(ago,suff,sz,mode,qnt);}}};
//----------------------------------String    arr[]-------------------------------------------------
void consoleChangeArr(String str, String   *ago, String   *v, char suff, uint8_t sz, char mode, uint8_t qnt) {
 if(consoleRun()){
for(console.idx=0; console.idx<qnt; console.idx++){if(ago[console.idx]!=v[console.idx]){console.idxOk=1; ago[console.idx]=v[console.idx];}}
 if(console.idxOk){console.idxOk=0; consoleVar(str,'=');  consoleArr(ago,suff,sz,mode,qnt);}}};
//----------------------------------char    arr[]-------------------------------------------------
void consoleChangeArr(String str, char     *ago, char     *v, char suff, uint8_t sz, char mode, uint8_t qnt) {
 if(consoleRun()){
for(console.idx=0; console.idx<qnt; console.idx++){if(ago[console.idx]!=v[console.idx]){console.idxOk=1; ago[console.idx]=v[console.idx];}}
 if(console.idxOk){console.idxOk=0; consoleVar(str,'=');  consoleArr(ago,suff,sz,mode,qnt);}}};
//==================================================================================================
//=================================СИСТЕМНЫЕ ФУНКЦИИ===============================================
//=================================================================================================
//							Вывод значений из массивов заданного типа [kind]
//=================================================================================================
void consoleArrPGM(uint8_t kind){
 uint8_t len;
 uint8_t  qntLine; uint8_t endLine;
//-------------------------------------------------------------------------------------------------
if(kind>RT_HW_PGM_QNT_ID){return;}								//--Выход по несуществующему типу массива; 
len=getLenPosPGM(kind);											//--Получение кол-ва доступных пинов;
if(len==0)				 {return;}								//--Выход если нет выводимых элементов;					
mess.alig='L'; consoleVar(getNameKindPin(kind),'[',4); 			//--Вывод имени массива + '[';
mess.alig='R'; consoleVar(len,']',3,'U'); consoleChar(':',' ');	//--Вывод кол-ва доступных пинов + ']';
//-------------------------------------------------------------------
uint8_t indexPin=0;	 
qntLine=24; 
#if defined(RT_HW_CORE_STM32)
if(mess.modePin=='A'){qntLine=8;} else{qntLine=16;}
#endif
//-------------------------------------------------------------------
len=getLenFullPGM(kind);										//--
 endLine=0;
for(uint8_t i=0; i<len; i++){uint8_t pin=getFromArrPGM(kind,i); if(pin!=255){
//---------------------------------------------------------------------------------
if(endLine){endLine=0; consoleBlank(9);}
    if((++indexPin>=qntLine) || ((i+1)>=len))   {consoleVar(pin,'E',mess.lenPin,'P'); indexPin=0; endLine=1;}
     else                       {consoleVar(pin,',',mess.lenPin,'P'); }}
//---------------------------------------------------------------------------------------
}
if(indexPin>0) {consoleSuff('L');}
//------------------------------------------------------------------
//mess.alig=alig; mess.modePin=modePin;
};

//===================================================================

//=================================================================================================
//							КОНСОЛЬ: ВЫВОД массива сообщения mess.str
//=================================================================================================	
//void consoleArrMess(RT_HW_STRUCT_MESS &id){
//if(id.lenBegin){for(id.idx=0;id.idx<id.lenBegin;id.idx++){consoleWrite(id.blank);}}//--Вывод заполнителей перед значением;
//-------------------------------------------------------------------------------------------------
//if(id.lenVar){																		//--Вывод если lenVar>0;
//if(id.modeVar=='S'){																//--Вывод для переменных String;
//const char * data=id.str.c_str(); 													//--Установка указателя на начало строки;	
//     for(id.idx=0;id.idx<id.qnt;   id.idx++){consoleWrite(data[id.idx]);}}			//--Вывод текста длиной qnt;	
//else{for(id.idx=0;id.idx<id.lenVar;id.idx++){consoleWrite(id.str.charAt(id.idx));}}}//--Вывод для остальных переменных;
//-------------------------------------------------------------------------------------------------
//if((id.idx+1)<id.qnt){consoleWrite((uint8_t)id.separator);							//--Вывод разделителя между элементами массива;
//if(id.lenEnd)  {for(id.idx=0; id.idx<id.lenEnd; id.idx++){consoleWrite(id.blank);}} return;} //--Вывод заполнителей после элемента массива;
///-------------------------------------------------------------------------------------------------
//if(id.lenSuff) {consoleWrite((uint8_t)id.suff);} 									//--Вывод суффикса в конце массива; 
//if(id.lenEnd)  {for(id.idx=0; id.idx<id.lenEnd; id.idx++){consoleWrite(id.blank);}}	//--Вывод заполнителей в конце сообщения;
//if(id.lenCR)   {consoleWrite('\n');}												//--Вывод перевода строки;
//};
