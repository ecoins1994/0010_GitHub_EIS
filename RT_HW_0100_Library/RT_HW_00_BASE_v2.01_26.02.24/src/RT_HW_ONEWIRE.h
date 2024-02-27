
#ifndef RT_HW_ONEWIRE_h
#define RT_HW_ONEWIRE_h
//-------------------------------------------------------------------------------------------------
#include "RT_HW_BASE.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class RT_HW_ONEWIRE{
//----Приватные переменные-------------------------------------------------------------------------
private:
unsigned char ROM_NO[8];
uint8_t LastDiscrepancy;
uint8_t LastFamilyDiscrepancy;
bool    LastDeviceFlag;
//----Глобальные переменные------------------------------------------------------------------------
public:
uint8_t pin;
RT_HW_ONEWIRE() {}						//--Конструктор без параметров;
RT_HW_ONEWIRE(uint8_t _pin){begin(_pin);}	//--Конструктор с номером пина шины 1-Wire;
//=================================================================================================
//								1.Базовые функции ввода/вывода
//
// Определение в функциях параметров порта и бит используются 
// для увеличения быстродействия функции и обеспечения более точного времени её работы.
//
// Если параметр power=1, то шина удерживается на высоком уровне, конец для устройств с паразитным питанием
// и шина отключается от питания  командой depower() или другой командой записи или чтения с параметром power=1;
//=================================================================================================
//-------------------------------------------------------------------------------------------------
// 							1.1.Запись бита.
// Шина всегда остается запитанной в конце, следует иметь это ввиду при команде write().
//-------------------------------------------------------------------------------------------------
void write_bit(uint8_t v){
volatile RT_HW_PIN_ONEWIRE_ID id; RT_HW_PIN_ONEWIRE_SET_ID(id,pin); 
if(v&1){RT_HW_PIN_ONEWIRE_MODE_OUTPUT_LOW(id);  delayMicroseconds(10);
		RT_HW_PIN_ONEWIRE_WRITE_HIGH(id);       delayMicroseconds(55);}
else   {RT_HW_PIN_ONEWIRE_MODE_OUTPUT_LOW(id);  delayMicroseconds(65);
		RT_HW_PIN_ONEWIRE_WRITE_HIGH(id);       delayMicroseconds(5);}
};
//-------------------------------------------------------------------------------------------------
// 							1.2.Запись байта. 
// Если параметр power=1, то шина удерживается на высоком уровне, конец для устройств с паразитным питанием
// и шина отключается от питания  командой depower() или другой командой записи или чтения с параметром power=1;
// Код записи использует активные драйверы для повышения
// высокий уровень, если вам нужно питание после записи (например, DS18S20 в
// режим паразитного питания), затем установите 'power' в 1, иначе вывод будет
// переходим в три состояния в конце записи, чтобы избежать перегрева при коротком замыкании или
// другая неудача.
//RT_HW_PIN_ONEWIRE_MODE_INPUT_LOW(id)
//-------------------------------------------------------------------------------------------------
void write(uint8_t v, uint8_t power=0) {
volatile RT_HW_PIN_ONEWIRE_ID id; RT_HW_PIN_ONEWIRE_SET_ID(id,pin); 
uint8_t bitMask;
for(bitMask=0x01; bitMask;	bitMask<<=1) {write_bit( (bitMask & v)?1:0);}
if (!power) {RT_HW_PIN_ONEWIRE_MODE_INPUT_LOW(id);} 
};
//-------------------------------------------------------------------------------------------------
// 							1.3.Запись count байтов из буфера buf 
//-------------------------------------------------------------------------------------------------
void write_bytes(const uint8_t *buf, uint16_t count, bool power=0) {
volatile RT_HW_PIN_ONEWIRE_ID id; RT_HW_PIN_ONEWIRE_SET_ID(id,pin); 
for(uint16_t i=0; i<count; i++) {write(buf[i]);}
if (!power) {RT_HW_PIN_ONEWIRE_MODE_INPUT_LOW(id);} 
};
//-------------------------------------------------------------------------------------------------
// 							1.4.Чтение бита.
//-------------------------------------------------------------------------------------------------
uint8_t read_bit(void){
uint8_t r;
volatile RT_HW_PIN_ONEWIRE_ID id; RT_HW_PIN_ONEWIRE_SET_ID(id,pin);
  RT_HW_PIN_ONEWIRE_MODE_OUTPUT_LOW(id);  delayMicroseconds(3);
  RT_HW_PIN_ONEWIRE_MODE_INPUT(id);       delayMicroseconds(10);
r=RT_HW_PIN_ONEWIRE_READ(id);             delayMicroseconds(53);
return r;}               				
		 	
//-------------------------------------------------------------------------------------------------
// 							1.5.Чтение байта.
//-------------------------------------------------------------------------------------------------
uint8_t read() {
uint8_t bitMask; uint8_t r=0;
for(bitMask=0x01; bitMask; bitMask<<=1){if (read_bit()) r |= bitMask;}
return r;}
//-------------------------------------------------------------------------------------------------
// 							1.6.Чтение count байт в буфер buf.
//-------------------------------------------------------------------------------------------------
void read_bytes(uint8_t *buf, uint16_t count) {for(uint16_t i=0; i<count; i++) {buf[i]=read();}}

//=================================================================================================
//								2.Базовые функции управления
//=================================================================================================
//-------------------------------------------------------------------------------------------------
//                             2.1.Настройка номера пина шины 1-Wire;	
//-------------------------------------------------------------------------------------------------
void begin(uint8_t _pin){
//RT_HW_PIN_DIR_SET_ID(id,pin); 		//--Настройка ID пина; 
//RT_HW_PIN_ONEWIRE_MODE_INPUT(id);	//--Настройка пина на чтение;
pin=_pin;
pinMode(pin, INPUT); 
//bitmask = RT_HW_ONEWIRE_PIN_TO_BITMASK(pin); 
//baseReg = RT_HW_ONEWIRE_PIN_TO_BASEREG(pin);
reset_search();}
//-------------------------------------------------------------------------------------------------
// 							  2.2.Выполнение цикла сброса 1-Wire. 
// Возвращает 1, если устройство отвечаетс импульсом присутствия. 
// Возвращает 0, если устройство отсутствует или шина закорочена или 
//           иным образом удерживается на низком уровне более 250 мкс;
//-------------------------------------------------------------------------------------------------
uint8_t reset(void){					//--Выполнение цикла сброса 1-Wire. 
uint8_t r; uint8_t retries = 125;
volatile RT_HW_PIN_ONEWIRE_ID id; RT_HW_PIN_ONEWIRE_SET_ID(id,pin); 
RT_HW_PIN_ONEWIRE_MODE_INPUT(id);                                                                 //--Перевод на чтение;
do{if(--retries == 0) {return 0;}      delayMicroseconds(2);} while(!RT_HW_PIN_ONEWIRE_READ(id)); //--Ожидание высокого уровня на шине не более 250мкс;
RT_HW_PIN_ONEWIRE_MODE_OUTPUT_LOW(id); delayMicroseconds(480);                                    //--Шина переводится в низкий уровень на вывод;
RT_HW_PIN_ONEWIRE_MODE_INPUT(id);      delayMicroseconds(70);                                     //--Перевод на чтение, 70 мкс для нормализация состояния на шине; 
r = !RT_HW_PIN_ONEWIRE_READ(id);       delayMicroseconds(410);                                    //--Чтениесостояния шины с последующей задержкой 410 мкс;
return r;
}
//-------------------------------------------------------------------------------------------------
// 							2.3.Выбор устройтва по адресу.
// Перед данной командой требуется выполните команду reset(); Do a ROM select
//-------------------------------------------------------------------------------------------------
void select(const uint8_t rom[8]){uint8_t i;
write(0x55);  for(i=0; i<8; i++) write(rom[i]);}
//-------------------------------------------------------------------------------------------------
// 							2.4.Команда пропуск адреса (0xCC)
// (адресация ко всем устройствам на шине) Do a ROM skip
//-------------------------------------------------------------------------------------------------
void skip(){write(0xCC);}
//-------------------------------------------------------------------------------------------------
// 							2.5.Отключение питания на шине 1-Wire.
// Функцию следует применить в том случае, если использовали флаг power=1 для write() 
// или использовался вызов write_bit() и не планируется делать еще одно чтение или запись. 
// Это команда защищает шину 1-Wiree от случайных коротких замыканий на шине. 
//-------------------------------------------------------------------------------------------------
void depower(){
volatile RT_HW_PIN_ONEWIRE_ID id; RT_HW_PIN_ONEWIRE_SET_ID(id,pin); 	
RT_HW_PIN_ONEWIRE_MODE_INPUT(id);}


//=================================================================================================
//								3.Функции поиска устройств
//=================================================================================================
//-------------------------------------------------------------------------------------------------
// 								3.1.Очистка параметров поиска.
// Выполняется перед поиском нового устройства.
// You need to use this function to start a search again from the beginning.
// You do not need to do it for the first search, though you could.
//-------------------------------------------------------------------------------------------------
void reset_search(){
LastDiscrepancy=0; LastDeviceFlag=false; LastFamilyDiscrepancy=0;
for(int i=7; ; i--) {ROM_NO[i] = 0; if (i==0) break;}}
//-------------------------------------------------------------------------------------------------
// 								3.2.Настройка целевой поиск с типом устройства family_code 
// при последующем поиске устройства с новым адресом
// Setup the search to find the device type 'family_code' on the next call
// to search(*newAddr) if it is present.
// set the search state to find SearchFamily type devices
//-------------------------------------------------------------------------------------------------
void target_search(uint8_t family_code){
ROM_NO[0] = family_code;
for(uint8_t i=1; i<8; i++) {ROM_NO[i]=0;}
LastDiscrepancy = 64; LastFamilyDiscrepancy = 0; LastDeviceFlag = false;}

//-------------------------------------------------------------------------------------------------
// 							3.3.Поиск следующее устройство. 
// Возвращается 1, если был возвращен новый адрес. 
// Взовращает   0, если шина закорочена, нет устройств, или уже получиены все адреса на шины. 
// Полезно проверить CRC, чтобы убедиться, что был получен не случайный мусор. 
// Порядок поиска детерминирован и будут получены те же устройства в том же порядке.
//-------------------------------------------------------------------------------------------------	 
bool search(uint8_t *newAddr, bool search_mode=1){
uint8_t id_bit_number=1;   uint8_t last_zero=0; uint8_t rom_byte_number=0; bool search_result=false;
unsigned char rom_byte_mask=1; 
uint8_t id_bit; uint8_t cmp_id_bit;
unsigned char search_direction;
//----Если последний поиск был не последним
if(!LastDeviceFlag){
	//----Сброс шины перед поиском устрйотсва
	if (!reset()){LastDiscrepancy = 0; LastDeviceFlag = false; LastFamilyDiscrepancy = 0; return false;} //--Выход, если ошибка сброса;
    //----Команда поиска устройства
	if (search_mode == true) {write(0xF0);}   // NORMAL SEARCH
    else 					 {write(0xEC);}   // CONDITIONAL SEARCH
	//----Цикл для поиска устройства
    do{
        //----Чтение бита и его дополнения
        id_bit=read_bit(); cmp_id_bit=read_bit();
        //----Проверка отсутствия устройства на 1-wire
        if ((id_bit==1)&&(cmp_id_bit==1)){break;} 
		else {if(id_bit!= cmp_id_bit) {search_direction=id_bit;}  //--Если все подключенные устройства имеют 0 или 1, сохраняется бит записи значения для поиска;
              else{         //--Если это несоответствие если перед последним несоответствием,в предыдущем следующем, выберается то же, что и в прошлый раз;
                   if(id_bit_number<LastDiscrepancy){search_direction=((ROM_NO[rom_byte_number] & rom_byte_mask) > 0);}
                   else {   //--Если равен последнему выбору 1, если нет, то выбор 0;
                         search_direction = (id_bit_number == LastDiscrepancy);}
               // if 0 was picked then record its position in LastZero
               if (search_direction==0){last_zero=id_bit_number; if (last_zero<9){LastFamilyDiscrepancy=last_zero;}} //--Если равен последнему выбору 1, если нет, то выбор 0  с проверкой несоответствие в in family;                                         
                  }
            //--Установка или сброс бита в ROM byte rom_byte_number с маской rom_byte_mask
            if (search_direction==1){ROM_NO[rom_byte_number] |= rom_byte_mask;}
            else				    {ROM_NO[rom_byte_number] &= ~rom_byte_mask;}
            //--Бит записи направления поиска серийного номера
            write_bit(search_direction);
            // increment the byte counter id_bit_number
            // and shift the mask rom_byte_mask
            id_bit_number++;
            rom_byte_mask <<= 1;

            // if the mask is 0 then go to new SerialNum byte rom_byte_number and reset mask
            if (rom_byte_mask == 0) {rom_byte_number++; rom_byte_mask = 1;}
         }
      }
      while(rom_byte_number < 8);  // loop until through all ROM bytes 0-7
    //----if the search was successful then
      // search successful so set LastDiscrepancy,LastDeviceFlag,search_result
	  if (!(id_bit_number < 65)) {LastDiscrepancy=last_zero;
								  if(LastDiscrepancy==0) {LastDeviceFlag = true;}// check for last device
								  search_result = true;}
   }

//----Если устройство не найдено, сброс счетчиков для следующего поиска;
if(!search_result || !ROM_NO[0]){LastDiscrepancy = 0; LastDeviceFlag = false; LastFamilyDiscrepancy = 0; search_result = false;} 
else 							{for (int i = 0; i < 8; i++) newAddr[i] = ROM_NO[i];}
//----Выход;
return search_result;}



//=================================================================================================
//								4.Функции расчета CRC
//=================================================================================================
//-------------------------------------------------------------------------------------------------	
// 								4.1.Вычисление 8-битный CRC Dallas Semiconductor.
// Используется ПЗУ и регистры оперативной памяти.
// Compute a Dallas Semiconductor 8 bit CRC. These show up in the ROM
// and the registers.  (Use tiny 2x16 entry CRC table)
//-------------------------------------------------------------------------------------------------
uint8_t crc8(const uint8_t *addr, uint8_t len){
uint8_t crc=0;
while(len--){crc = *addr++ ^ crc;  // just re-using crc as intermediate
			 crc = pgm_read_byte(RT_HW_PGM_TABLE_CRC8_2X16 + (crc & 0x0f)) ^
			       pgm_read_byte(RT_HW_PGM_TABLE_CRC8_2X16 + 16 + ((crc >> 4) & 0x0f));}
return crc;}
//-------------------------------------------------------------------------------------------------	
// 								4.2.Вычисление 16-битный CRC Dallas Semiconductor.
// Это необходимо для проверки целостность данных, полученных от многих устройств 1-Wire. 
// Вычисленный здесь CRC "не тот", что принимается из 1-Wire, по двум причинам:
// 	1) CRC передается с побитовой инверсией.
//  2) в зависимости от порядка байтов вашего процессора двоичное представление двухбайтового возвращаемого значения 
//     может иметь другой порядок байтов, чем два байта, которые принимаются от 1-Wire.
// Параметры:   
//		input - Массив байтов для контрольной суммы.
// 		len   — сколько байтов использовать.
// 		crc   — начальное значение crc (необязательно)
// Возвращает CRC16 - определенный Dallas Semiconductor.
//-------------------------------------------------------------------------------------------------	
uint16_t crc16(const uint8_t* input, uint16_t len, uint16_t crc){
#if defined(__AVR__)
for (uint16_t i = 0 ; i < len ; i++) {crc = _crc16_update(crc, input[i]);}
#else
static const uint8_t oddparity[16] ={ 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0 };
for(uint16_t i=0; i<len; i++) {uint16_t cdata=input[i]; cdata=(cdata^crc)&0xff; crc >>= 8;
							   if(oddparity[cdata&0x0F]^oddparity[cdata>>4])   {crc ^= 0xC001;}
							   cdata <<= 6; crc ^= cdata; cdata <<= 1; crc ^= cdata;}
#endif
return crc;}
//-------------------------------------------------------------------------------------------------	
// Вычисление 1-Wire CRC16 и сравнение его с полученным CRC.
// Пример использования: - чтение DS2408:
// Для работы функции необходимо разместить входные данные uint8_t buf[13]:
//    buf[0] = 0xF0;    // Read PIO Registers
//    buf[1] = 0x88;    // LSB address
//    buf[2] = 0x00;    // MSB address
//    WriteBytes(net,buf,  3);    // Write 3 cmd bytes
//    ReadBytes(net, buf+3,10);   // Read 6 data bytes, 2 0xFF, 2 CRC16
//    if (!CheckCRC16(buf, 11, &buf[11])) { Handle error.}     
// Входные параметры:          
// input - массив данных для расчета CRC16;
// len -   кол-во обрабатываемых байт;
// inverted_crc - The two CRC16 bytes in the received data. This should just point into the received data, *not* at a 16-bit integer.
// crc - CRC16 для сравнения;
// Возвращает при совпадение CRC16.
//-------------------------------------------------------------------------------------------------	
bool check_crc16(const uint8_t* input, uint16_t len, const uint8_t* inverted_crc, uint16_t crc){
crc = ~crc16(input, len, crc); return (crc & 0xFF) == inverted_crc[0] && (crc >> 8) == inverted_crc[1];}
//=================================================================================================
}; //--END class RT_HW_OneWire{
#endif // RT_HW_ONEWIRE_h


