//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//            					PAJ7620U2 (Сенсор жестов)
// В сенсор PAC7620 встроена функция распознавания жестов с интерфейсов i2c(SPI).
// Это аналитическая сенсорная система изображения, разпознавать 9 видов жестов рук, такие как
// движение вверх, вниз, влево, вправо,вперед, назад, вращение по/против часовой стрелке, взмахи.
// Он также может обнаруживать приближающейся или удаляющейся объекта от датчика. 
// PAJ7620 подходит для низких
// PAJ7620 это законченный комплексное сенсорное решение со встроенным ИК-светодиодом и оптическим объективом.
//
// Информация по 9-ти видам движения доступна через чтения регистра через шину i2c. 
// Нормальный диапазон обнаружения жестов от 5 до 15 см от сенсора через рабочий угол обзора по диагонали 60° соответственно. 
// Кроме того, PAC7620можно настроить как обычный режим (скорость жестов от 60°/с до 600°/с) 
// или игровой режим (скорость жестов от 60°/с до 1200°/с) для различных приложений. 
// PAC7620 также предлагает встроенное обнаружение приближения, перемещения уходящего объекта.
//
// Через SPI реализуется режим получения изображения с типичной частотой отчета 120 Гц 
// с размером изображения 30x30(режим вычитания кадров, WOI) или 30x30(режим необработанных данных, WOI).
// Глубина данных пикселя составляет 9 бит и выводится через шину SPI. 
// Скорость SCK шины SPI равна на внешний тактовый вход SPI в диапазоне от 22 до 48 МГц (режим вычитания кадров) 
// или от 44 до 48 МГц (режим необработанных данных).
//
// При изменение угла размещения сенсора, потребуется переобозначить 
//    маску флага прерывания обнаружения тестов(Bank0 Address=0x41)
//        и флаг  прерывания обнаружения жестов(Bank0 Address=0x43).
//
// ИНИЦИАЛИЗАЦИЯ: 
// 1.После включения подождать >T1=700мкс, пока PAJ7620U2 не стабилизируется.
// 2.Записть идентификатор подчиненного устройства (0x73) для обработки пробуждения I2C.П
// 3.Подождать >T2=400мкс. 
// 4.Запишисаьб начальные настройки и различные настройки режимов для PAJ7620U2. 
// 5.Включить PAJ7620U2, записав в регистр Bank1, Addr0x72 значение 0x01.
// 6.Доступ к данным жестов теперь можно получить через шину I2C.
//
// ОБНАРУЖЕНИЕ ЖЕСТОВ (в состояние работы):
// 1.Частота обновления жестов составляет 120 Гц для нормального режима и 240 Гц для игрового режима. 
// 2.К результату жеста доступ можно получить доступ с помощью механизма прерывания или путем 
//   опроса флага прерывания обнаружения жеста (Bank 0, Address=0x43).

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++