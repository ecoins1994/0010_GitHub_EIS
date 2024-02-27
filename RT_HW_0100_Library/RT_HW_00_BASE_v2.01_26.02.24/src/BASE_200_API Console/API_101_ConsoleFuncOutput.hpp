
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//							1.ОСНОВНЫЕ ФУНКЦИЯ ВЫВОДА ЧЕРЕЗ структуру RT_HW_STRUCT_MESS
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//								1.1.Вывод сообщения id
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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								2.ФУНКЦИИ ВЫВОДА ПРОСТЫХ СООБЩЕНИЙ 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//								2.1.Простые функции вывода
// Суффикс: '~'-не выводится, G-пробел, L-перевод строки, E-';'+перевод строки, S-вывод ';', V-вывод',' или вывод любого иного символа;	
//=================================================================================================
  void consoleSuff (RT_HW_STRUCT_MESS &id,             char suff='~'){if(consoleRun()){messSuff(id, suff);    if(id.lenSuff){consoleWrite(id.suff);} if(id.lenCR){consoleWrite('\n');}}};	//++++Вывод суффикса; 
  void consoleChar (RT_HW_STRUCT_MESS &id, char v=' ', char suff='~'){if(consoleRun()){consoleWrite(v);                      consoleSuff(id,suff);}};										//++++Вывод символа с суффиксом;
  void consoleCR   (RT_HW_STRUCT_MESS &id,             uint8_t sz=1) {if(consoleRun()){id.size=sz;        for(console.idx=0; console.idx<sz; console.idx++){consoleWrite('\n');}}};		//++++Вывод переводoв строки;
  void consoleBlank(RT_HW_STRUCT_MESS &id,             uint8_t sz)   {if(consoleRun()){id.size=sz;        for(console.idx=0; console.idx<sz; console.idx++){consoleWrite((uint8_t)(id.blank));}}};//+++Вывод sz пробелов;
  void consoleBlank(RT_HW_STRUCT_MESS &id, char v,     uint8_t sz)   {if(consoleRun()){consoleSuff(id,v); for(console.idx=0; console.idx<sz; console.idx++){consoleWrite((uint8_t)v);}}};	//+++Вывод sz заполнителей=v;	 															//++++Вывод sz заполнителей=v с суффиксом; 
  void consoleLine (RT_HW_STRUCT_MESS &id, char v='=', uint8_t sz=80){if(consoleRun()){id.size=sz;        for(console.idx=0; console.idx<sz; console.idx++){consoleWrite((uint8_t)v);} consoleWrite('\n');}};//++Вывод линии;
//-------------------------------------------------------------------------------------------------

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								3. ФУНКЦИИ ВЫВОДА ПЕРЕМЕННЫХ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//								4.1. Вывод переменных с возможностью вывода заголовка
//=================================================================================================
  void consoleVar(int8_t   v, char suff='~',uint8_t sz=0, char mode='Z',String hd="~") {if(consoleRun()){varToMess(mess,v,suff,sz,mode,hd); consoleMess(mess);}}; //--int8_t  [mode:P,A,C,B,*,H,U,I,0,1,2,3,Z,z,X];
  void consoleVar(uint8_t  v, char suff='~',uint8_t sz=0, char mode='Z',String hd="~") {if(consoleRun()){varToMess(mess,v,suff,sz,mode,hd); consoleMess(mess);}}; //--uint8_t [mode:P,A,C,B,*,H,U,I,0,1,2,3,Z,z,X];
  void consoleVar(int16_t  v, char suff='~',uint8_t sz=0, char mode='Z',String hd="~") {if(consoleRun()){varToMess(mess,v,suff,sz,mode,hd); consoleMess(mess);}}; //--int16_t [mode:B,*,H,U,I,0,1,2,3,Z,z];
  void consoleVar(uint16_t v, char suff='~',uint8_t sz=0, char mode='Z',String hd="~") {if(consoleRun()){varToMess(mess,v,suff,sz,mode,hd); consoleMess(mess);}}; //--uint16_t[mode:B,*,H,U,I,0,1,2,3,Z,z];
  void consoleVar(int32_t  v, char suff='~',uint8_t sz=0, char mode='Z',String hd="~") {if(consoleRun()){varToMess(mess,v,suff,sz,mode,hd); consoleMess(mess);}}; //--int32_t [mode:B,*,H,U,I,0,1,2,3,Z,z];
  void consoleVar(uint32_t v, char suff='~',uint8_t sz=0, char mode='Z',String hd="~") {if(consoleRun()){varToMess(mess,v,suff,sz,mode,hd); consoleMess(mess);}}; //--uint32_t[mode:B,*,H,U,I,0,1,2,3,Z,z];
  void consoleVar(float    v, char suff='~',uint8_t sz=0, char mode='2',String hd="~") {if(consoleRun()){varToMess(mess,v,suff,sz,mode,hd); consoleMess(mess);}}  //--float   [mode:0,1,2,3,Z,z];
  void consoleVar(String   v, char suff='~',uint8_t sz=0, char mode='S',String hd="~") {if(consoleRun()){varToMess(mess,v,suff,sz,mode,hd); consoleMess(mess);}}; //--String  [mode:N,U,L];
  void consoleVar(char     v, char suff='~',uint8_t sz=0, char mode='N',String hd="~") {if(consoleRun()){varToMess(mess,v,suff,sz,mode,hd); consoleMess(mess);}}; //--char    [mode:N,U,L];
  void consoleVar(bool     v, char suff='~',uint8_t sz=0, char mode='1',String hd="~") {if(consoleRun()){varToMess(mess,v,suff,sz,mode,hd); consoleMess(mess);}}; //--bit     [mode:0 0/1,1 -+,2  *,3  #,4 -|,5 <>,6 _+,7 _*,8 _+;
//=================================================================================================
//			 					2.2. Вывод тестовой переменной (впереди переменной заголовок) !!! Изменить вывод как в 2.1
//=================================================================================================
  void consoleTest(String str, int8_t   v, char suff='E', char mode='Z') {if(consoleRun()){consoleVar(str,'='); consoleVar(v,suff,0,mode);}};
  void consoleTest(String str, uint8_t  v, char suff='E', char mode='Z') {if(consoleRun()){consoleVar(str,'='); consoleVar(v,suff,0,mode);}};
  void consoleTest(String str, int16_t  v, char suff='E', char mode='Z') {if(consoleRun()){consoleVar(str,'='); consoleVar(v,suff,0,mode);}};
  void consoleTest(String str, uint16_t v, char suff='E', char mode='Z') {if(consoleRun()){consoleVar(str,'='); consoleVar(v,suff,0,mode);}};
  void consoleTest(String str, int32_t  v, char suff='E', char mode='Z') {if(consoleRun()){consoleVar(str,'='); consoleVar(v,suff,0,mode);}};
  void consoleTest(String str, uint32_t v, char suff='E', char mode='Z') {if(consoleRun()){consoleVar(str,'='); consoleVar(v,suff,0,mode);}};
  void consoleTest(String str, float    v, char suff='E', char mode='Z') {if(consoleRun()){consoleVar(str,'='); consoleVar(v,suff,0,mode);}};
  void consoleTest(String str, String   v, char suff='E', char mode='Z') {if(consoleRun()){consoleVar(str,'='); consoleVar(v,suff,0,mode);}};
  void consoleTest(String str, char     v, char suff='E', char mode='Z') {if(consoleRun()){consoleVar(str,'='); consoleVar(v,suff,0,mode);}};
  void consoleTest(String str, bool     v, char suff='E', char mode='Z') {if(consoleRun()){consoleVar(str,'='); consoleVar(v,suff,0,mode);}};
//=================================================================================================
//		   						2.3. Вывод тестовых переменной при изменении (впереди переменной заголовок) !!! Изменить вывод как в 2.1
//=================================================================================================
  void consoleChange(String str, uint8_t  &ago, uint8_t  v, char suff='E', char mode='z') {if(consoleRun()){if(ago!=v){ago=v; consoleVar(str,'='); consoleVar(v,suff,0,mode);}}}
  void consoleChange(String str, int8_t   &ago, int8_t   v, char suff='E', char mode='Z') {if(consoleRun()){if(ago!=v){ago=v; consoleVar(str,'='); consoleVar(v,suff,0,mode);}}}
  void consoleChange(String str, int16_t  &ago, int16_t  v, char suff='E', char mode='Z') {if(consoleRun()){if(ago!=v){ago=v; consoleVar(str,'='); consoleVar(v,suff,0,mode);}}}
  void consoleChange(String str, uint16_t &ago, uint16_t v, char suff='E', char mode='Z') {if(consoleRun()){if(ago!=v){ago=v; consoleVar(str,'='); consoleVar(v,suff,0,mode);}}}
  void consoleChange(String str, int32_t  &ago, int32_t  v, char suff='E', char mode='Z') {if(consoleRun()){if(ago!=v){ago=v; consoleVar(str,'='); consoleVar(v,suff,0,mode);}}}
  void consoleChange(String str, uint32_t &ago, uint32_t v, char suff='E', char mode='Z') {if(consoleRun()){if(ago!=v){ago=v; consoleVar(str,'='); consoleVar(v,suff,0,mode);}}}
  void consoleChange(String str, float    &ago, float    v, char suff='E', char mode='Z') {if(consoleRun()){if(ago!=v){ago=v; consoleVar(str,'='); consoleVar(v,suff,0,mode);}}}
  void consoleChange(String str, String   &ago, String   v, char suff='E', char mode='Z') {if(consoleRun()){if(ago!=v){ago=v; consoleVar(str,'='); consoleVar(v,suff,0,mode);}}}
  void consoleChange(String str, char     &ago, char     v, char suff='E', char mode='Z') {if(consoleRun()){if(ago!=v){ago=v; consoleVar(str,'='); consoleVar(v,suff,0,mode);}}}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								3.ФУНКЦИИ ВЫВОДА МАССИВОВ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//								3.1. Вывод массивов
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
//			 					3.2. Вывод тестовых массивов (впереди массива заголовок)
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
//		   						3.3.Вывод массивов при их изменении
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


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								4.ФУНКЦИИ ВЫВОДА ЗАГОЛОВКА
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void consoleHead(String  v,char bl='-',  uint8_t sz=80, char mode='S'){
//static char _alig; static char _blank;
if(consoleRun()){
mess.agoAlig=mess.alig;   mess.alig='C';	//--Сохранение предущего и установка нового значения alig;
mess.agoBlank=mess.blank; mess.blank=bl;	//--Сохранение предущего и установка нового значения blank;	
consoleVar(v,'L',sz,mode); 					//--Вывод заголовка;
mess.alig =mess.agoAlig;   					//--Восстановления предущего значения alig;
mess.blank=mess.agoBlank; 					//--Восстановления предущего значения blank;		
}};

