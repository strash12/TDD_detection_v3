/*из параметров установленных пользователем на вэб интерфейсе, формируется кейс, 
котороый в дальнейшем будет использоваться ыо всей программе*/

#include "header.h"

namespace param_store
{
    param_store::parametrs::parametrs(){}
    param_store::parametrs::~parametrs(){}

    
    _parametrs parametrs::Ext_cp(int band)
    {
    _parametrs param;
    param.cyclic        = 2; // тип циклического префикса 1- нормальный 2 - расширенный    
    switch (band)
    {
    case 1:
        param.fftsize       = 1024;  // размер Фурье
        param.band          = 4;    // номер бэнда
        param.cp1           = 256;  // длинна циклического префикса 
        param.cp            = 256;  // длина циклического префикса первого OFDM символа в слоте  
        param.fs            = 15.36e6; // частота дискретизации
        param.Nrb           = 50;      // число ресурсных блоков                                
        param.adreses       = 0x000401D2; // адресс согласно отчету по fpga
        param .MMCM         = 0x00000010; // адресс согласно отчету по fpga
        param .MMCM_2       = 0x00002004; // адресс согласно отчету по fpga
        param.shift_mark                = param.fs/100-param.fs/1000-param.fftsize; // сдвиг для установки метки времени
        param.path_first_part   [0]        = "./signal_storage/SSS_array_B4.txt"; // массив SSS для первой половины
        param.path_second_part  [0]       = "./signal_storage/SSS_array_B4_n2.txt"; // массив SSS для второй половины
        param.windowing     = 5092;
        param.refsamples    = 18933; // примерное расположение первого символа
	param.correct       =   1398;    
    break;

    case 3:
        param.fftsize        = 256;
        param.band           = 2;
        param.cp1            = 64;
        param.cp             = 64;
        param.fs             = 3.84e6;
        param.Nrb            = 15;                                    
        param.adreses        = 0x000200D2;
        param .MMCM          = 0x00000040;
        param .MMCM_2        = 0x00002004;
        param.shift_mark                    = param.fs/100-param.fs/1000-4 * param.fftsize;
        param.path_first_part   [0]         = "./signal_storage/SSS_array_B2.txt";
        param.path_second_part  [0]         = "./signal_storage/SSS_array_B2_n2.txt";
        param.windowing     = 1242;
        param.refsamples    = 4636;
        param.correct       = -470;
        
    break;

    case 7:
        param.fftsize       = 512;
        param.band          = 3;
        param.cp1           = 128;
        param.cp            = 128;
        param.fs            = 7.68e6;
        param.Nrb           = 25;                                     
        param.adreses       = 0x00030136;
        param .MMCM         = 0x00000020;
        param .MMCM_2       = 0x00002004;
        param.shift_mark                = param.fs/100-param.fs/1000- 4 * param.fftsize;
        param.path_first_part   [0]     = "./signal_storage/SSS_array_B3.txt";
        param.path_second_part  [0]     = "./signal_storage/SSS_array_B3_n2.txt";
        param.windowing     = 2528;
        param.refsamples    = 10487;
        param.correct       = 122;
    break;

    case 15:
        param.fftsize       = 1024;
        param.band          = 4;
        param.cp1           = 256;
        param.cp            = 256;
        param.fs            = 15.36e6;
        param.Nrb           = 50;                                      
        param.adreses       = 0x000401D2;
        param .MMCM         = 0x00000010;
        param .MMCM_2       = 0x00002004;
        param.shift_mark                = param.fs/100-param.fs/1000-param.fftsize;
        param.path_first_part   [0]     = "./signal_storage/SSS_array_B4.txt";
        param.path_second_part  [0]     = "./signal_storage/SSS_array_B4_n2.txt";;
        param.windowing     = 5099;
        param.refsamples    = 18933;
        param.correct       =   1228;
    break;

    case 23:
        param.fftsize       = 1536;
        param.band          = 5;
        param.cp1           = 384;
        param.cp            = 384;
        param.fs            = 23.04e6;
        param.Nrb           = 75;                                      
        param.adreses       = 0x000501A4;
        param .MMCM         = 0x0002FE0A;
        param .MMCM_2       = 0x01702004;
        param.shift_mark                = param.fs/100-param.fs/1000-param.fftsize;
        param.path_first_part   [0]     = "./signal_storage/SSS_array_B5_n1_1.txt";
        param.path_first_part   [1]     = "./signal_storage/SSS_array_B5_n1_2.txt";
	    param.path_first_part   [2]     = "./signal_storage/SSS_array_B5_n1_3.txt";
        param.path_second_part  [0]     = "./signal_storage/SSS_array_B5_n2_1.txt";
        param.path_second_part  [1]     = "./signal_storage/SSS_array_B5_n2_2.txt";
	    param.path_second_part  [2]     = "./signal_storage/SSS_array_B5_n2_3.txt";
        param.windowing     = 7645;
        param.refsamples    = 28912;
        param.shift_band    =  256;
        param.correct       =   2372;
    break;

    case 30:
        param.fftsize       = 2048;
        param.band          = 6;
        param.cp1           = 512;
        param.cp            = 512;
        param.fs            = 30.72e6;
        param.Nrb           = 100;                                     
        param.adreses       = 0x00060800;
        param .MMCM         = 0x00000008;
        param .MMCM_2       = 0x00002004;
        param.shift_mark                = param.fs/100-param.fs/1000-param.fftsize;
        param.path_first_part   [0]     = "./signal_storage/SSS_array_B6_n1_1.txt";
        param.path_first_part   [1]     = "./signal_storage/SSS_array_B6_n1_2.txt";
        param.path_first_part   [2]     = "./signal_storage/SSS_array_B6_n1_3.txt";
        param.path_second_part  [0]     = "./signal_storage/SSS_array_B6_n2_1.txt";
        param.path_second_part  [1]     = "./signal_storage/SSS_array_B6_n2_2.txt";
        param.path_second_part  [2]     = "./signal_storage/SSS_array_B6_n2_3.txt";
        param.windowing     = 10200;
        param.refsamples    = 38900;
        param.shift_band    =  512;
        param.correct       =   3532;
        break;
    
    default:
        mark::TDDException("Error set parametrs to param_storage"); // если призойдет ошибка и не один из кейсов не будет выбран кидаем исключение и сворачиваем стэк
    break;
    }
    return param;
    }

    _parametrs parametrs::Norm_cp(int band)
    {
        _parametrs param;
        param.cyclic        = 1;
        
        switch (band)
        {
    case 1:
        param.fftsize       = 1024;
        param.band          = 4;
        param.cp1           = 80;
        param.cp            = 72;
        param.fs            = 15.36e6;
        param.Nrb           = 50;                                      
        param.adreses       = 0x000401D2;
        param .MMCM         = 0x00000010;
        param .MMCM_2       = 0x00002004;
        param.path_first_part   [0]     = "./signal_storage/SSS_array_B4.txt";
        param.path_second_part  [0]     = "./signal_storage/SSS_array_B4_n2.txt";
        param.shift_mark                = param.fs/100-param.fs/1000-param.fftsize;
        param.windowing     =  5265;
        param.refsamples    =  18500;
        param.correct       =   1398;

    break;
    
    case 3:
        param.fftsize       = 256;
        param.band          = 2;
        param.cp1           = 20;
        param.cp            = 18;
        param.fs            = 3.84e6;
        param.Nrb           = 15;                                     
        param.adreses      = 0x000200D2;
        param .MMCM         = 0x00000040;
        param .MMCM_2       = 0x00002004;
        param.path_first_part[0]   = "./signal_storage/SSS_array_B2.txt";
        param.path_second_part[0]   = "./signal_storage/SSS_array_B2_n2.txt";
        param.shift_mark    = param.fs/100-param.fs/1000- 4 *param.fftsize;
        param.windowing     =  1288;
        param.refsamples    =  4636;
        param.correct       = -500;


    break;
    
    case 7:
        param.fftsize       = 512;
        param.band          = 3;
        param.cp1           = 40;
        param.cp            = 36;
        param.fs            = 7.68e6;
        param.Nrb           = 25;                              
        param.adreses     = 0x00030136;
        param.MMCM         = 0x00000020;
	    param.MMCM_2       = 0x00002004;
        param.path_first_part[0]   = "./signal_storage/SSS_array_B3.txt";
        param.path_second_part[0]   = "./signal_storage/SSS_array_B3_n2.txt";
        param.shift_mark    = param.fs/100-param.fs/1000- 3 * param.fftsize;
        param.windowing     = 2619;
        param.refsamples    = 9790;
        param.correct       = 0;

    break;
    
    case 15:
        param.fftsize       = 1024;
        param.band          = 4;
        param.cp1           = 80;
        param.cp            = 72;
        param.fs            = 15.36e6;
        param.Nrb           = 50;                                     
        param.adreses     = 0x000401D2;
        param .MMCM         = 0x00000010;
        param .MMCM_2       = 0x00002004;
        param.shift_mark                = param.fs/100-param.fs/1000-param.fftsize;
        param.path_first_part   [0]     = "./signal_storage/SSS_array_B4.txt";
        param.path_second_part  [0]     = "./signal_storage/SSS_array_B4_n2.txt";
        param.windowing     =   5265;
        param.refsamples    =   18500;
        param.correct       =   1075;

    break;

    case 23:
        param.fftsize       =   1536;
        param.band          =   5;
        param.cp1           =   120;
        param.cp            =   108;
        param.fs            =   23.04e6;
        param.Nrb           =   100;                                    
        param.adreses       =   0x000501A4;
        param .MMCM         =   0x0002FE0A;
        param .MMCM_2       =   0x01702004;
        param.shift_mark              = param.fs/100-param.fs/1000-param.fftsize;
        param.path_first_part   [0]   = "./signal_storage/SSS_array_B5.txt";
        param.path_first_part   [0]   = "./signal_storage/SSS_array_B5_n1_1.txt";
        param.path_first_part   [1]   = "./signal_storage/SSS_array_B5_n1_2.txt";
	    param.path_first_part   [2]   = "./signal_storage/SSS_array_B5_n1_3.txt";
        param.path_second_part  [0]   = "./signal_storage/SSS_array_B5_n2_1.txt";
        param.path_second_part  [1]   = "./signal_storage/SSS_array_B5_n2_2.txt";
	    param.path_second_part  [2]   = "./signal_storage/SSS_array_B5_n2_3.txt";
        param.windowing     =   7938;
	    param.refsamples    =   28312;
        param.shift_band    =   256;
        param.correct       =   1958;
    break;

    case 30:
        param.fftsize       =   2048;
        param.band          =   6;
        param.cp1           =   160;
        param.cp            =   144;
        param.fs            =   30.72e6;
        param.Nrb           =   100;                                      
        param.adreses       =   0x000601AE;
        param .MMCM         =   0x00000008;
        param .MMCM_2       =   0x00002004;
        param.shift_mark                = param.fs/100-param.fs/1000-param.fftsize;
        param.path_first_part   [0]       = "./signal_storage/SSS_array_B6_n1_1.txt";
        param.path_first_part   [1]       = "./signal_storage/SSS_array_B6_n1_2.txt";
        param.path_first_part   [2]       = "./signal_storage/SSS_array_B6_n1_3.txt";
        param.path_second_part  [0]      = "./signal_storage/SSS_array_B6_n2_1.txt";
        param.path_second_part  [1]      = "./signal_storage/SSS_array_B6_n2_2.txt";
        param.path_second_part  [2]      = "./signal_storage/SSS_array_B6_n2_3.txt";
        param.windowing     =   10650;
        param.refsamples    =   38000;
        param.shift_band    =   512;
        param.correct       =   3072;

    break;
    
    default:
        mark::TDDException("Error set parametrs to param_storage");// если призойдет ошибка и не один из кейсов не будет выбран кидаем исключение и сворачиваем стэк
    break;
    }
    return param;
    }

         
    _parametrs  parametrs::set_param(tch::FullTusurCommonConfig _config)
    {
        int band = _config.bandwidth;
        if(_config.cp_mode == tch::CpMode::Normal){   
                return Norm_cp(band);
            }
        else
            {
                return Ext_cp(band);
            }
            
    }

    

}//namespace param




