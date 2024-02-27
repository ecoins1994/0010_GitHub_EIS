//=================================================================================================
//				Функции нормализации значений ADC,PWW,DAC до системного значения 
//=================================================================================================	
  uint16_t maxBitDepthSys (){return ((1<<board.depth)-1);};		 //-return	max var разрядности 1:16 для системной разрядности;
  uint16_t maxBitDepth (uint8_t &depth){if(depth>=16) {return 0xFFFF;} if(depth==0){return 0;} return ((1<<depth)-1);}; //-return	max var разрядности 1:16;
  uint16_t normADC(uint16_t v){return map(v,0,maxBitDepth(device.adc.depth),0,maxBitDepth(board.depth));}; //--нормализация для ADC;
  uint16_t normPWM(uint16_t v){return map(v,0,maxBitDepth(device.pwm.depth),0,maxBitDepth(board.depth));}; //--нормализация для PWM;
#if defined(RT_HW_PERMIT_DAC)
  uint16_t normDAC(uint16_t v){return map(v,0,maxBitDepth(device.dac.depth),0,maxBitDepth(board.depth));}; //--нормализация для DAC;
#endif

//=================================================================================================
//				Функции нормализации 
//=================================================================================================
  uint16_t normDepth(uint16_t v,uint8_t depth){
	if(depth>16){depth=16;} 									 //--нормализация системного сигнала SYS ;
    return map(v,0,maxBitDepth(board.depth),0,maxBitDepth(depth));};			   			

//=================================================================================================
//				Функции нормализации 
//=================================================================================================
  uint16_t normDepthFull(uint16_t v,uint8_t inDepth, uint8_t outDepth){
	if(inDepth>16){inDepth=16;} if(outDepth>16){outDepth=16;}	//--универсальный норматизатор;  
	return map(v,0,maxBitDepth(inDepth),0,maxBitDepth(outDepth));};;