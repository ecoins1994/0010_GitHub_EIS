
//--------------namespace flprog-------------------------

uint32_t difference32(uint32_t start, uint32_t end){
if(end>=start){return end - start;}
               return (0xfFFFFFFF - start) + end;}

uint8_t isTimer(uint32_t startTime, uint32_t period){
return (difference32(startTime, (millis()))) >= period;}

uint8_t isTimerMicros(uint32_t startTime, uint32_t period){
return (difference32(startTime, (micros()))) >= period;}

uint32_t timeBack(uint32_t value){
 static uint32_t current=millis();
 if(value<current){return (current-value);}
                   return ((0xFFFFFFFF-value)+current);}

uint32_t speedFromCode(uint8_t code){
switch (code){
  case RT_HW_SPEED_300: 	return    300;	break;
  case RT_HW_SPEED_600:		return    600;	break;
  case RT_HW_SPEED_1200:	return   1200;	break;
  case RT_HW_SPEED_2400:	return   2400;	break;
  case RT_HW_SPEED_4800:	return   4800;  break;
  case RT_HW_SPEED_9600:	return   9600;  break;
  case RT_HW_SPEED_14400:	return  14400;	break;
  case RT_HW_SPEED_19200:	return  19200;	break;
  case RT_HW_SPEED_28800:	return  28800;	break;
  case RT_HW_SPEED_38400:	return  38400;	break;
  case RT_HW_SPEED_57600:	return  57600; 	break;
  case RT_HW_SPEED_115200:	return 115200;  break;
  default:					return   9600;	break;
}}

uint8_t codeFromSpeed(uint32_t speed){
switch (speed){
  case 300:		return RT_HW_SPEED_300;	break;
  case 600:		return RT_HW_SPEED_600;	break;
  case 1200:	return RT_HW_SPEED_1200;   break;
  case 2400:	return RT_HW_SPEED_2400;	break;
  case 4800:	return RT_HW_SPEED_4800;	break;
  case 9600:	return RT_HW_SPEED_9600;	break;
  case 14400:	return RT_HW_SPEED_14400;	break;
  case 19200:	return RT_HW_SPEED_19200;	break;
  case 28800:	return RT_HW_SPEED_28800;	break;
  case 38400:	return RT_HW_SPEED_38400;	break;
  case 57600:	return RT_HW_SPEED_57600;	break;
  case 115200:	return RT_HW_SPEED_115200;	break;
  default:		return RT_HW_SPEED_9600;
}}

uint16_t serialCodeForParametrs(byte portDataBits, byte portStopBits, byte portParity){
  static int code = 0;
  if(portStopBits==2){code=code+8;}
  if(portDataBits==6){code=code+2;}
  if(portDataBits==7){code=code+4;}
  if(portDataBits==8){code=code+6;}
  if(portParity  ==1){code=code+32;}
  if(portParity  ==2){code=code+48;}
return code;}

bool applyMac(uint8_t m0, uint8_t m1, uint8_t m2, uint8_t m3, uint8_t m4, uint8_t m5, uint8_t *target){
  static bool result; 
  result = false;
  if(m0!=target[0]){target[0]=m0;	result=true;}
  if(m1!=target[1]){target[1]=m1;	result=true;}
  if(m2!=target[2]){target[2]=m2;	result=true;}
  if(m3!=target[3]){target[3]=m3;   result=true;}
  if(m4!=target[4]){target[4]=m4;   result=true;}
  if(m5!=target[5]){target[5]=m5;	result=true;}
return result;}

bool checkMacAddres(uint8_t *target){
    static bool result = 0;
    for (uint8_t i = 0; i < 6; i++)
    {
        if (target[i] == 255)
        {
            return false;
        }
        if (target[i] > 0)
        {
            result = true;
        }
    }
    return result;
}

void parseMacAddressString(String value, uint8_t *array)
{
    int index;
    uint8_t buffer[6] = {255, 255, 255, 255, 255, 255};
    uint8_t raz = 0;
    String tempString;
    while ((value.length() > 0) && (raz <= 6))
    {
        index = value.indexOf(":");
        if (index == -1)
        {
            tempString = value;
            value = "";
        }
        else
        {
            tempString = value.substring(0, index);
            value = value.substring(index + 1);
        }
        buffer[raz] = byte(hexStrToInt(tempString));
        raz++;
    }
    if (checkMacAddres(buffer))
    {
        for (byte i = 0; i < 6; i++)
        {
            array[i] = buffer[i];
        }
    }
}

uint32_t hexStrToInt(String str){
    uint8_t len = str.length();
    if (len == 0)
        return 0;
    int result = 0;
    for (uint8_t i = 0; i < 8; i++) // только первые 8 цифр влезутв uint32
    {
        char ch = str[i];
        if (ch == 0)
            break;
        result <<= 4;
        if (isdigit(ch))
            result = result | (ch - '0');
        else
            result = result | (ch - 'A' + 10);
    }
    return result;
}
