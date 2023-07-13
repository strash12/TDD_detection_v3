#ifndef defined PARAM_STORAGE
#define PARAM_STORAGE

#include "../../TDD_detection/header.h"
#include <string>


namespace param_store
{
    struct _parametrs
        {
            int fftsize,cp,cp1,Nrb,fs,cyclic,windowing,band,PSS_number,CellId,shift_mark,delay,refsamples,first;
	        int shift_second_cor_start  = -500;// окна корреляции 
            int shift_second_cor_stop   = 500;// окна корреляции
            int shift = 50;// сдвиг для расчета примерного расположения первого символа. 
	        std::string path_first_part[3],path_second_part[3];
            uint32_t MMCM, MMCM_2,adreses;
            int Ns = 20;
	
        } ;
        
    class parametrs
    {
        private:
             _parametrs Norm_cp(int);
             _parametrs Ext_cp(int);
        public:
            parametrs();
            ~parametrs();
            _parametrs set_param(tch::FullTusurCommonConfig _config);
    };
} //namespace param


#endif //PARAM_STORAGE