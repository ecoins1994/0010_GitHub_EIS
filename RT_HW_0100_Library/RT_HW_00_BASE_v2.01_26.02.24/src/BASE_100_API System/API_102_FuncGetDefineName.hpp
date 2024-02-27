//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//				1.ФУНКЦИИ ПОЛУЧЕНИЕ СТРОКОВЫХ ПАРАМЕТРОВ КОНТРОЛЛЕРА (из Selectt_xxx.hpp & etc.)
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void vVerName(){				 //--Имя версии;	
#if defined(RT_HW_BASE_VER_NAME) 					
    mess.str=RT_HW_BASE_VER_NAME;  
#else
	mess.str="";
#endif
};

//-------------------------------------------------------------------------------------------------
void vBoardName(){						//--Имя платы;	
#if defined(RT_HW_BOARD_NAME) 					
    mess.str=RT_HW_BOARD_NAME;  
#else
	mess.str="";
#endif
};
//-------------------------------------------------------------------------------------------------
void vArchName(){						//--Имя архитектуры;	
#if defined(RT_HW_ARCH_NAME) 					
    mess.str=RT_HW_ARCH_NAME;  
#else
	mess.str="";
#endif
};
//-------------------------------------------------------------------------------------------------
void vCoreName(){						//--Имя ядра(CORE);	
#if defined(RT_HW_CORE_NAME) 					
   mess.str=RT_HW_CORE_NAME;  
#else
   mess.str="";
#endif
};
//-------------------------------------------------------------------------------------------------
void vBoardSelect(){					//--Наименование выбранной платы;	
#if defined(RT_HW_BOARD_SELECT) 					
   mess.str=RT_HW_BOARD_SELECT;  
#else
   mess.str="";
#endif
};
//-------------------------------------------------------------------------------------------------
void vBoardMemory(){					//--Наименование выбранной платы;	
#if defined(RT_HW_BOARD_MEMORY) 					
   mess.str=RT_HW_BOARD_MEMORY;  
#else
   mess.str="";
#endif
};