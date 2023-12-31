//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//           					ADS1256
//
//=================================================================================================

//=================================================================================================
//							ПЕРЕЧЕНЬ РЕГИСТРОВ
// Работа ADS1255/6 контролируется с помощью набора регистров. 
// В совокупности регистры содержат всю информацию необходимые для настройки детали, такие как 
// скорость передачи данных, настройки мультиплексора, настройки PGA, калибровка и т. д.			
//=================================================================================================
// STATUS(00h): Регистр состояния, значение после сброса=01h;
//   Биты 7–4 ID3,ID2,ID1,ID0: идентификационные биты(только чтение);
//   Бит 3   	ORDER: порядок битов вывода данных: 0 = сначала старший бит (по умолчанию); 1 = сначала младший бит;
//            	Входные данные всегда сначала сдвигаются по наиболее значимому байту и биту. 
//            	Выходные данные всегда смещаются в сторону наиболее значимых значений первого байт. 
//            	Бит ORDER управляет только порядком битов выходных данных в байте.
//   Бит 2    	ACAL: автоматическая калибровка
//			  	0 = автокалибровка отключена (по умолчанию); 1 = автокалибровка включена;
//				Когда автокалибровка включена, самокалибровка начинается после завершения команды WREG, 
//                  которая изменяет PGA(биты 0–2 регистра ADCON), DR(биты 7–0 регистра DRATE) или BUFEN(бит 1 регистра STATUS);
//   Бит 1  	BUFEN: включение буфера аналогового входа. 0 = буфер отключен (по умолчанию); 1 = буфер включен.
//   Бит 0      DRDY: данные готовы(только чтение). Этот бит дублирует состояние вывода DRDY.
//-------------------------------------------------------------------------------------------------
// MUX(01h): Регистр управления входным мультиплексором, значение после сброса=01h;
//   Биты 7–4	PSEL3, PSEL2, PSEL1, PSEL0: выбор положительного входного канала (AINP), AIN2-AIN7 только для ADS1256:
//     			0000=AIN0, 0001=AIN1, 0010=AIN2, 0011=AIN3, 0100=AIN4, 0101=AIN5, 0110=AIN6, 0111=AIN7, 1xxx=AINCOM(GND)(PSEL3 = 1, PSEL2, PSEL1, PSEL0 «не важно»);
//	 Биты 3–0 	NSEL3, NSEL2, NSEL1, NSEL0: выбор отрицательного входного канала (AINP),
//              0000=AIN0, 0001=AIN1, 0010=AIN2, 0011=AIN3, 0100=AIN4, 0101=AIN5, 0110=AIN6, 0111=AIN7, 1xxx=AINCOM(GND)(NSEL3 = 1, NSEL2, NSEL1, NSEL0 «не важно»);
//              При использовании ADS1255 обязательно выбирать только доступные входы.
//-------------------------------------------------------------------------------------------------
// ADCON(02h): Регистр аналогово-цифрового управления, значение после сброса=20h;
//   Бит 7   	Зарезервировано, всегда 0 (только чтение);
//   Биты 6–5 	CLK1, CLK0: установка скорости тактового сигнала D0/CLKOUT.
//             	00 = Выход часов ВЫКЛ;                     01 = Частота тактового сигнала = fCLKIN (по умолчанию)
//            	10 = Частота тактового сигнала = fCLKIN/2; 11 = Частота тактового сигнала = fCLKIN/4
//            	Если CLKOUT не используется, рекомендуется его отключить. Эти биты можно сбросить только с помощью вывода RESET.
//  Биты 4–2 	SDCS1, SCDS0: датчик обнаруживает источники тока. Источники тока обнаружения датчиков можно активировать 
//                            для проверки целостности внешнего датчика, подающего сигнал на ADS1255/6. 
//                            Закороченный датчик выдает очень слабый сигнал, тогда как датчик разомкнутой цепи выдает очень сильный сигнал.
//              00 = Обнаружение датчика ВЫКЛ (по умолчанию); 01 = Ток обнаружения датчика = 0,5 мкА;
//				10 = Ток обнаружения датчика = 2 мкА;         11 = Ток обнаружения датчика = 10  мкА;
//  Биты 2–0 	PGA2, PGA1, PGA0: настройка усилителя с программируемым коэффициентом усиления.
//              000 = 1 (по умолчанию); 001 = 2;  010 = 4; 	011 = 8;
//              100 = 16;               101 = 32; 110 = 64; 111 = 64;
//-------------------------------------------------------------------------------------------------
// DRATE(03h): Скорость передачи данных аналого-цифрового преобразования, значение после сброса=01h;
//             Ниже показаны 16 допустимых настроек скорости передачи данных. 
//             Следует выбрать допустимую настройку, поскольку неверные настройки могут привести к непредсказуемым результатам.
//   Биты 7–0 DR[7: 0]: Настройка скорости передачи данных(1) для fCLKIN = 7,68 МГц. Скорость передачи данных линейно масштабируется с помощью fCLKIN.
//             11110000 = 30 000SPS (по умолчанию); 11100000 = 15000SPS; 11010000 = 7500SPS; 11000000 = 3750SPS;
//             10110000 =   2000SPS;                10100001 =  1000SPS; 10010010 =  500SPS; 10000010 =  100SPS;
//             01110010 =     60SPS;                01100011 =    50SPS; 01010011 =   30SPS; 01000011 =   25SPS;
//             00110011 =     15SPS;                00100011 =    10SPS; 00010011 =    5SPS; 00000011 =  2,5SPS;
//-------------------------------------------------------------------------------------------------
// I/O(04h):   Регистр управления GPIO, значение после сброса=E0h;
//             Состояния этих битов управляют работой выводов цифрового ввода/вывода общего назначения. 
//             ADS1256 имеет 4 контакта ввода/вывода: D3, D2,D1 и D0/CLKOUT. 
//             ADS1255 имеет 2 контакта ввода/вывода:        D1 и D0/CLKOUT. 
//             При использовании ADS1255 регистр биты DIR3, DIR2, DIO3 и DIO2 могут быть прочитаны и записаны, но не имеют никакого эффекта.
//	Бит 7      DIR3, направление цифрового ввода-вывода для контакта D3 цифрового ввода-вывода. 0 = D3 — выход,1 = D3 является входом (по умолчанию);
//	Бит 6      DIR2, направление цифрового ввода-вывода для контакта D2 цифрового ввода-вывода. 0 = D2 — выход,1 = D2 является входом (по умолчанию);
//	Бит 5      DIR1, направление цифрового ввода-вывода для контакта D1 цифрового ввода-вывода. 0 = D1 — выход,1 = D1 является входом (по умолчанию);
//	Бит 4      DIR0, направление цифрового ввода-вывода для контакта D0 цифрового ввода-вывода. 0 = D0 — выход,1 = D0 является входом (по умолчанию);
//  Биты 3–0   DI0[3:0]: состояние контактов цифрового пинов D3, D2, D1, D0/CLKOUT.
//			   Чтение этих битов покажет состояние соответствующего пина, независимо от того, настроен ли пин как ввод или вывод по DIR3-DIR0. 
//             Когда пин настроен как выход с помощью бита DIR, запись в соответствующий бит DIO установит состояние выхода. 
//             Когда пин настроен как вход с помощью бита DIR, запись в соответствующий бит DIO не будет иметь никакого эффекта. 
//             Когда DO/CLKOUT настроен как выход и CLKOUT включен (с использованием битов CLK1, CLK0 в регистре ADCON), запись в DIO0 не будет иметь никакого эффекта.
//-------------------------------------------------------------------------------------------------
// OFC0(05h): Байт калибровки смещения 0, младший байт. Значение сброса зависит от результатов калибровки. 
// OFC1(06h): Байт калибровки смещения 1.               Значение сброса зависит от результатов калибровки. 
// OFC2(07h): Байт калибровки смещения 2.               Значение сброса зависит от результатов калибровки. 
// FSC0(08h): Полномасштабный калибровочный байт 0, байт калибровки смещения 2, старший байт. Значение сброса зависит от результатов калибровки. 
// FSC1(09h): Полномасштабный калибровочный байт 1, байт калибровки смещения 1.               Значение сброса зависит от результатов калибровки. 
// FSC0(0Ah): Полномасштабный калибровочный байт 2, байт калибровки смещения 1.               Значение сброса зависит от результатов калибровки. 
//
//
//=================================================================================================
//							ПЕРЕЧЕНЬ КОМАНД
// Команды управляют работой ADS1255/6. 
// Все команды автономны за исключением чтения и записи регистра (RREG, WREG), для которых требуется второй командный байт плюс данные. 
// Дополнительные байты команды и данных могут быть вставлены без задержки после первого байта команды. 
// Бит ORDER в регистре STATUS устанавливает порядок битов в выходных данных. 
// Пин CS должен оставаться на низком уровне в течение всей последовательности команд.
//-------------------------------------------------------------------------------------------------
//  WAKEUP: 0x00; Завершает синхронизацию и выходит из режима ожидания;
//  RDATA:  0x01; Чтение данных. Эту команду можно применять для чтения одиночного результата, когда DRDY=LOW. 
//                После чтения 24 бит, устанавливается DRDY=HIGH;
//                Нет необходимости считывать повторно все 24 бита, но тогда DRDY не вернет высокий уровень.
//                См. временные характеристики, чтобы узнать необходимую задержку между окончанием команды RDATA 
//                                                                       и начало смещения данных на DOUT: t6=50.
//  RDATAC: 0x03; Непрерывное чтение данных. Эту команду можно применять для непрерывного чтения результата, когда DRDY = LOW. 
// 			      Этот режим позволяет непрерывный вывод новых данных на каждый DRDY без необходимости выдачи последующих команд чтения. 
//                После чтения 24 бит, устанавливается DRDY=HIGH; 
//                Нет необходимости считывать повторно все 24 бита, но тогда DRDY не вернет высокий уровень.
//                Этот режим может быть прекращен командой SDATAC (Stop Read Data Continuous =0Fh). 
// 				  Не используйте этот режим, если DIN и DOUT соединены вместе.
//  SDATAC:0x0F;  Прекращает непрерывное чтение данных и завершает режим непрерывного вывода данных. 
//                Команда должна быть подана после того, как DRDY станет низким и завершается до того, как DRDY достигнет высокого уровня.
//  RREG:  0001 rrrr, 0000 nnnn; Чтение из регистров. 
//                Читаются данные из 11 регистров, начиная с адреса регистра, указанного как часть команды.
//                Число прочитанных регистров будет равно одному плюс второй байт команды. 
//                Если счетчик превышает оставшиеся регистры, адреса вернутся к началу.
//                1-й командный байт: 0001 rrrr, где rrrr — адрес первого регистра для чтения.
//                2-й командный байт: 0000 nnnn, где nnnn — количество байтов для чтения – 1. 
//                См. временные характеристики для требуемая задержка между окончанием команды RREG и началом сдвига данных на DOUT: t6.
// WREG:  0101 rrrr, 0000 xxxx;  Запись регистров, начиная с регистра, указанного в команде. 
//                Количество регистров, которые будет записано равно единице плюс значение второго байта в команде.
//                1-й командный байт: 0101 rrrr, где rrrr — адрес первого записываемого регистра.
//                2-й командный байт: 0000 nnnn, где nnnn — количество записываемых байтов — 1.
//                Байты данных: данные, которые будут записаны в регистры. 
//-------------------------------------------------------------------------------------------------
