//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//								1.КОДИРОВЩИКИ, ДЕШИФРАТОРЫ
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//================================================================================================= 
//							 1.1.Кодировщик числа в номер бита
//================================================================================================= 
uint8_t  coder8 (uint8_t  v) {if((v==0) || (v>8)) {return 0;} uint8_t  dc=0; bitSet(dc,(v-1)); return dc;};  //-- 8-разрядный;
uint16_t coder16(uint16_t v) {if((v==0) || (v>16)){return 0;} uint16_t dc=0; bitSet(dc,(v-1)); return dc;};  //--16-разрядный;
//=================================================================================================
//							 1.2.Дешифраторы
//=================================================================================================
uint8_t  dc8 (uint8_t v){if((v>0) && (v<= 8)){return (uint8_t)1 <<(v-1);} return 0;} //-- 8-разрядный дешифратор;
uint16_t dc16(uint8_t v){if((v>0) && (v<=16)){return (uint16_t)1<<(v-1);} return 0;} //--16-разрядный дешифратор;
uint32_t dc24(uint8_t v){if((v>0) && (v<=24)){return (uint32_t)1<<(v-1);} return 0;} //--24-разрядный дешифратор;
uint32_t dc32(uint8_t v){if((v>0) && (v<=32)){return (uint32_t)1<<(v-1);} return 0;} //--32-разрядный дешифратор;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//										2.СЧЕТЧИКИ
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//							 3.1.СБРОС СЧЕТЧИКА 
//=================================================================================================
void counterReset(RT_HW_COUNTER_ID &id){
id.step=1; id.top=100; id.bottom=0; id.begin=0;          
id.cnt=id.begin; id.direct=0; id.var=0; id.reset=0;}
//-------------------------------------------------------------------------------------------------
void counterReset(RT_HW_COUNTER_ID &id,int16_t top, int16_t bottom, int16_t step, int16_t begin=0){
id.begin=begin; id.step=step; id.top=top; id.bottom=bottom; id.begin=begin;
id.cnt=id.begin; id.direct=0;  id.var=0; id.reset=0;}
//=================================================================================================
//							3.2.СЧЕТЧИК ПИЛА
//=================================================================================================
int16_t counterS(RT_HW_COUNTER_ID &id, uint8_t EN=1){
if(EN){
if( id.step>=0){if(id.cnt==id.top)   {id.var=id.bottom;} 
                else                 {id.var+=id.step; if(id.var>id.top)    {id.var=id.top;}}}
else           {if(id.cnt==id.bottom){id.cnt=id.top;} 
                else                 {id.var+=id.step; if(id.var<id.bottom) {id.var=id.bottom;}}}
id.cnt=(int16_t)id.var;} 
return id.cnt;};				
//=================================================================================================
//							3.3.СЧЕТЧИК ТРЕУГОЛЬНИК
//=================================================================================================
int16_t counterT(RT_HW_COUNTER_ID &id, uint8_t EN=1){
if(EN){
//-------------------------------------------------------------------------------------------------
if(id.step>=0){if(id.cnt==id.top)   {id.direct=1;} 
               if(id.cnt==id.bottom){id.direct=0;}
//-------------------------------------------------------------------------------------------------
			   if(id.direct==0){id.var+=id.step; if(id.var>id.top)    {id.var=id.top;}}
               else            {id.var-=id.step; if(id.var<id.bottom) {id.var=id.bottom;}}}
//-------------------------------------------------------------------------------------------------
else          {if(id.cnt==id.top)   {id.direct=0;} 
               if(id.cnt==id.bottom){id.direct=1;}
//-------------------------------------------------------------------------------------------------
			   if(id.direct==0){id.var+=id.step; if(id.var<id.bottom) {id.var=id.bottom;}}
			   if(id.direct==1){id.var-=id.step; if(id.var>id.top)    {id.var=id.top;}}}
id.cnt=(int16_t)id.var;} 
return id.cnt;};
//=================================================================================================
//							3.4.СЧЕТЧИК ЛИМИТ
//=================================================================================================
int16_t counterL(RT_HW_COUNTER_ID &id, uint8_t EN=1) {
if(EN){
if(id.step>=0) {if(id.cnt<id.top)   {id.var=id.cnt; id.var+=id.step; if(id.var>id.top)    {id.var=id.top;}}}
else           {if(id.cnt>id.bottom){id.var=id.cnt; id.var+=id.step; if(id.var<id.bottom) {id.var=id.bottom;}}}
id.cnt=(int16_t)id.var;} 
return id.cnt;};
//=================================================================================================
//							3.5.СЧЕТЧИК РЕВЕРСИВНЫЙ
//=================================================================================================
int16_t counterR(RT_HW_COUNTER_ID &id, uint8_t ENP=1, uint8_t ENM=0){
if(ENP){
if(id.step>=0) {id.var+=id.step; if(id.var>id.top)    {id.var=id.top;}}
else           {id.var+=id.step; if(id.var<id.bottom) {id.var=id.bottom;}}
id.cnt=(int16_t)id.var; return id.cnt;};
if(ENM){
if(id.step>=0) {id.var-=id.step; if(id.var<id.bottom) {id.var=id.bottom;}}
else           {id.var-=id.step; if(id.var>id.top)    {id.var=id.top; }}}
id.cnt=(int16_t)id.var; return id.cnt;};
//=================================================================================================

/*
//=================================================================================================
//									xxx.Обработка значения от защиты "дребезга" 
//									(будет убрана);
//=================================================================================================
bool chatterDIN(RT_HW_CHATTER_DIN &id, uint8_t var, uint16_t period){
if(id.dir==0) {if(id.ago!=var){id.timeBegin=RT_HW_MILLIS; id.dir++;}               return id.ago;}
if(id.dir==1) {if((getPastMs  (id.timeBegin)< period) && (id.ago==var)) {id.dir=0; return id.ago;} 
               if( getPastMs  (id.timeBegin)> period)    {id.ago=var;	 id.dir=0; return id.ago;}}}
*/
