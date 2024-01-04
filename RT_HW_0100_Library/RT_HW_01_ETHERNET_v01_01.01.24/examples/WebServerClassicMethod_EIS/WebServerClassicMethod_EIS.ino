#include "flprogEthernet.h"
#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif
uint32_t timeBegin; uint8_t timeEvent=0;
int16_t arr[10];
/*
  -------------------------------------------------------------------------------------------------
        Создание интерфейса для работы с чипом W5100(W5200,W5500)
        Шина SPI и пин CS берутся из  RT_HW_Base.device.spi.busETH и RT_HW_Base.device.spi.csETH
  -------------------------------------------------------------------------------------------------
*/
FLProgWiznetInterface WiznetInterface;

/*
  -------------------------------------------------------------------------------------------------
        Второй вариант cоздания интерфейса для работы с чипом W5100(W5200,W5500).
        С непосредственной привязкой  пину.
        Пин CS - 10
        Шина SPI берётся из RT_HW_Base.device.spi.busETH
  -------------------------------------------------------------------------------------------------
*/
// FLProgWiznetInterface WiznetInterface(10);

/*
  -------------------------------------------------------------------------------------------------
      Третий вариант cоздания интерфейса для работы с чипом W5100(W5200,W5500).
      С непосредственной привязкой  пину и шине.
      Пин CS - 10
      Шина SPI - 0
  -------------------------------------------------------------------------------------------------
*/
// FLProgWiznetInterface WiznetInterface(10, 0);

/*
  -------------------------------------------------------------------------------------------------
          Создание объекта сервера  с привязкой к интерфейсу
  -------------------------------------------------------------------------------------------------
*/
FLProgEthernetServer server(&WiznetInterface, 80);

/*
  -----------------------------------------------------------------------------------------
          Определение рабочих параметров и функций
  -----------------------------------------------------------------------------------------
*/

uint8_t ethernetStatus = 255;
uint8_t ethernetError = 255;

uint8_t serverStatus = 255;
uint8_t serverError = 255;

uint32_t blinkStartTime = 0;
uint8_t cntConnect=0, cntDisConnect=0;

bool isNeedSendConnectMessage = true;
bool isNeedSendDisconnectMessage = true;

//=================================================================================================
void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
  }

  flprog::printConsole(" Тест проверки WizNet Web сервера по классической схеме ");

  Serial.print("CS - ");
  Serial.println(WiznetInterface.pinCs());
  Serial.print("SPI BUS - ");
  Serial.println(WiznetInterface.spiBus());

  WiznetInterface.mac(0x78, 0xAC, 0xC0, 0x2C, 0x3E, 0x40); //--Установка MAC-адрес контроллера
  // WiznetInterface.localIP(192, 168, 199, 155);
  // WiznetInterface.resetDhcp();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

//=================================================================================================
void loop()
{
  WiznetInterface.pool();
  printStatusMessages();
  blinkLed();
  workServer();
//-------------------------------------------------------------------------------------------------
  if(millis()-timeBegin>=1000){timeBegin=millis();
  arr[0]++;
  for(uint8_t i=1; i<8; i++){++arr[i]; arr[i]+=(i*2);}}
//-------------------------------------------------------------------------------------------------  
}

//=================================================================================================
void workServer(){
  if (!server.connected()){return;}
  if (!server.available()){return;}
  
  RT_HW_Base.consoleBlank('+',10);
  RT_HW_Base.consoleCurrentTime(); RT_HW_Base.consoleTest(String(F(" Подключение клиента cnt")),++cntConnect,'E','U');
  bool currentLineIsBlank = true;
  uint32_t timeBegin=micros();
  while (server.connected()){
    if  (server.available()){char c = server.read();  
                             RT_HW_Base.consoleChar(c);
                             //Serial.write(c);
                             if(c == '\n' && currentLineIsBlank){
                                  //--Отправка стандартного HTTP заголовка ответа
                                  server.println("HTTP/1.1 200 OK");
                                  server.println("Content-Type: text/html");
                                  server.println("Connection: close");
                                  server.println("Refresh: 5");
                                  server.println();
                                  server.println("<!DOCTYPE HTML>");
                                  server.println("<html>");
                                  //--Вывод переменных
                                  
                                  for (int i = 0; i < 6; i++){
                                  server.print("counter ");
                                  server.print(i);
                                  server.print(" is ");
                                  server.print(arr[i]);
                                  server.println("<br />");
                                                              }      
                                  server.println("</html>");
                                  break;
                                                                }
                             if (c == '\n'){currentLineIsBlank = true;}
                        else if (c != '\r'){currentLineIsBlank = false;}
                              }
                             }
  server.stopConnection();
  RT_HW_Base.consoleBlank('-',10);
  RT_HW_Base.consoleCurrentTime(); RT_HW_Base.consoleTest(String(F(" Отключение  клиента cnt")),++cntDisConnect,'~','U');
  RT_HW_Base.consoleTest(String(F(" time(mcs)")),RT_HW_Base.getPastMcs(timeBegin),'E','U');
}
//============================================================================================
void blinkLed(){if (flprog::isTimer(blinkStartTime,500)) {blinkStartTime = millis(); digitalWrite(LED_BUILTIN, !(digitalRead(LED_BUILTIN)));}}

void printStatusMessages(){
  if (WiznetInterface.getStatus() != ethernetStatus)
  {
    ethernetStatus = WiznetInterface.getStatus();
    Serial.println();
    Serial.print("Статус интерфейса - ");
    Serial.println(flprog::flprogStatusCodeName(ethernetStatus));
  }
  if (WiznetInterface.getError() != ethernetError)
  {
    ethernetError = WiznetInterface.getError();
    if (ethernetError != FLPROG_NOT_ERROR)
    {
      Serial.println();
      Serial.print("Ошибка интерфейса - ");
      Serial.println(flprog::flprogErrorCodeName(ethernetError));
    }
  }
  if (server.getStatus() != serverStatus)
  {
    serverStatus = server.getStatus();
    Serial.println();
    Serial.print("Статус сервера - ");
    Serial.println(flprog::flprogStatusCodeName(serverStatus));
  }
  if (server.getError() != serverError)
  {
    serverError = server.getError();
    if (serverError != FLPROG_NOT_ERROR)
    {
      Serial.println();
      Serial.print("Ошибка сервера - ");
      Serial.println(flprog::flprogErrorCodeName(serverError));
    }
  }
  printConnectMessages();
  printDisconnectMessages();
}

void printConnectMessages()
{
  if (!WiznetInterface.isReady())
  {
    return;
  }
  if (!isNeedSendConnectMessage)
  {
    return;
  }
  Serial.println("Ethernet подключён!");
  Serial.print("Ip - ");
  Serial.println(WiznetInterface.localIP());
  Serial.print("DNS - ");
  Serial.println(WiznetInterface.dns());
  Serial.print("Subnet - ");
  Serial.println(WiznetInterface.subnet());
  Serial.print("Gateway - ");
  Serial.println(WiznetInterface.gateway());
  isNeedSendConnectMessage = false;
  isNeedSendDisconnectMessage = true;
}

void printDisconnectMessages()
{
  if (WiznetInterface.isReady())
  {
    return;
  }
  if (isNeedSendConnectMessage)
  {
    return;
  }
  if (!isNeedSendDisconnectMessage)
  {
    return;
  }
  Serial.println("Ethernet отключён!");
  isNeedSendConnectMessage = true;
  isNeedSendDisconnectMessage = false;
}
