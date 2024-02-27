//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//										ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//					Проверка на изменения значения с сохранением в буферe
//-------------------------------------------------------------------------------------------------
bool checkChangeVar(int8_t   &ago, int8_t   val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar(uint8_t  &ago, uint8_t  val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar( int16_t &ago, int16_t  val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar(uint16_t &ago, uint16_t val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar(int32_t  &ago, int32_t  val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar(uint32_t &ago, uint32_t val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar(String   &ago, String   val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar(float    &ago, float    val) {if(ago!=val) {ago=val;  return 1;} return 0;}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=================================================================================================
//					Ограничение переменных установленными границами mode[L,A,N]
// mode: 
// 'A' - всегда;
// 'L' - Если верхняя граница !=0 для верхней границы и если нижняя граница !=0 для нижней границы;
//-------------------------------------------------------------------------------------------------
uint8_t limitationVar(uint8_t  cur, uint8_t highLimit, uint8_t lowLimit, char mode='L'){
if(mode=='L'){if((highLimit!=0) && (cur>highLimit)){cur=highLimit;} if((lowLimit !=0) && (cur<lowLimit)) {cur=lowLimit;}	return cur;}
if(mode=='A'){                   if(cur>highLimit) {cur=highLimit;}                    if(cur<lowLimit)  {cur=lowLimit;}	return cur;}
return cur;}
//--------------------------------------------------------------------------------------------------
int16_t limitationVar(int16_t  cur, int16_t highLimit, int16_t lowLimit, char mode='L'){
if(mode=='L'){if((highLimit!=0) && (cur>highLimit)){cur=highLimit;} if((lowLimit !=0) && (cur<lowLimit)) {cur=lowLimit;}	return cur;}
if(mode=='A'){                   if(cur>highLimit) {cur=highLimit;}                    if(cur<lowLimit)  {cur=lowLimit;}	return cur;}
return cur;}
//-------------------------------------------------------------------------------------------------
int32_t limitationVar(int32_t  cur, int32_t highLimit, int32_t lowLimit, char mode='L'){
if(mode=='L'){if((highLimit!=0) && (cur>highLimit)){cur=highLimit;} if((lowLimit !=0) && (cur<lowLimit)) {cur=lowLimit;}	return cur;}
if(mode=='A'){                   if(cur>highLimit) {cur=highLimit;}                    if(cur<lowLimit)  {cur=lowLimit;}	return cur;}
return cur;}
//-------------------------------------------------------------------------------------------------
float limitationVar(float  cur, float highLimit, float lowLimit, char mode='L'){
if(mode=='L'){if((highLimit!=0) && (cur>highLimit)){cur=highLimit;} if((lowLimit !=0) && (cur<lowLimit)) {cur=lowLimit;}	return cur;}
if(mode=='A'){                   if(cur>highLimit) {cur=highLimit;}                    if(cur<lowLimit)  {cur=lowLimit;}	return cur;}
return cur;}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
