//#define       UPHONE_HVGA                  ///<  �ֱ���ΪHVGA 
#define UPHONE_WVGA                 ///<  �ֱ���ΪWVGA 
   
#if defined(UPHONE_HVGA)  
#include "Res_HVGA/app_kaixin_res_def.h"  
#elif defined(UPHONE_WVGA)  
#include "Res_WVGA/app_kaixin_res_def.h"  
#else  
#error resolution  
#endif 