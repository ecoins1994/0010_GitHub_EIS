//=================================================================================================
//						   1.16.Генератор случайного MAC-адреса(3 младших байта).
//=================================================================================================
void genMacAddr(uint8_t b0=0x78, uint8_t b1=0xAC, uint8_t b2=0xC0){
genRandom(0,24); 
buff.mac[0]=b0; 						buff.mac[1]=b1; 						buff.mac[2]=b2;
buff.mac[3]=(buff.vRandom>>16)&0xFF;	buff.mac[4]=(buff.vRandom>> 8)&0xFF;	buff.mac[5]= buff.vRandom&0xFF;};
