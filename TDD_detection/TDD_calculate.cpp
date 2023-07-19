#include "header.h"


namespace mark
{
    TDD_create::TDD_create(param_store::_parametrs param)
    {
        _param = param;
    }

    TDD_create::~TDD_create(){};

    int TDD_create::Calculate_TDD()
    {
            std::cout<<"start TDD calculate :"<<std::endl;
            xvec sig_part_2 = set_mark(_param.path_second_part,"fr2.txt"); // ставим метку на вторую половину кадра, и считываем 400000 отсчетов
            xvec sig_part_1 = set_mark(_param.path_first_part,"fr1.txt");//   ставим метку на первую половину кадра, и считываем 400000 отсчетов
            int first_1 = second_corr(sig_part_1);// уточнаяющая корреляция для второго считывания первой половины
            int first_2 = second_corr(sig_part_2);// уточнаяющая корреляция для второго считывания второй половины
            double angle_1 = calculate_angle(sig_part_1,first_1);// рачитываем частотный сдвиг для первой половины
            double angle_2 = calculate_angle(sig_part_2,first_2);// рачитываем частотный сдвиг для второй  половины
            xvec sig_shift_1 = freq_shift_remove(sig_part_1,angle_1);// устраняем сдвиг
            xvec sig_shift_2 = freq_shift_remove(sig_part_2,angle_2);// устраняем сдвиг
            RS::RS_cut RS_proc(_param);// протоип класса
            return RS_proc.set_RS(sig_shift_1,sig_shift_2,first_1,first_2);// считаем TDD config
        

    }

    xvec TDD_create::set_mark(std::string path[3],std::string name)
    {
        int ERROR_count; // счетчик ошибок
        bool validate_bit = 0; // бит валидации
        int half = 0; // части SSS сигнала
        fpga_configure::config_fpga check(_param); 

        /* пока с fpga части не придел бит валидации (подверждение того что синхронизация с SSS произошла ) перебираем  частии  сигнала SSS  
         так как размер коррелятора 1024 , генерировать SSS пришлось частями. */
        while (!validate_bit)
        {
            fpga_configure::SSS_upload::load_SSS(_param.CellId,path[half++],_param.adreses); // грузим SSS сигнал в fpga
            fpga_configure::SSS_upload::shift_mark(_param.shift_mark); // устанавливаем сдвиг
	        usleep(10000000);// ждем пока устаканится корреляция
            validate_bit = check.read_validate_bit(ERROR_count);// проверяем бит валидации если есть выходим из цикла, если нет инкрементируем ошибку
            if(_param.band > 4 && half == 3 ){half = 0;} // для бесконечного перебора
	        else if(_param.band < 5 && half == 1) {half = 0;}

            if(ERROR_count == 10 )// если 10 ошибок, сворачиваес стек и выдаем ошибку
            {
                tch::write_common("SSS not found");
                throw mark::TDDException("SSS signal not found, try again");
                break;//
            }
        }
        if(debug)
        {
            std::cout<<"number SSS half = "<<half<<std::endl;
        }
        signal::signal_create download_sig; 
        xvec signal = download_sig.download_convert_signal(name);// считываем сигнал
        return signal;
    }

    int TDD_create::second_corr(xvec signal) // расчет коэффициента корреляции медом матричного перемножения
    {
        LTE::xcorr corr;
        xvec PSS = PSS_generate::pss::get_pss(_param.PSS_number,_param.fftsize,_param.cp); // генерим PSS(только одну так как знаем из ее номер )
        return corr.corr_coef(signal,PSS,_param.refsamples,_param.fftsize,_param.cp,_param.shift_second_cor_start,_param.shift_second_cor_stop);
    }

    
    double TDD_create::calculate_angle(xvec signal, int first)
    {
        LTE::freq_shift_estimate freq; // считаем частотный сдвиг
        return freq.get_angle(signal,_param.cp,_param.fftsize,first);
    }

    
    xvec TDD_create::freq_shift_remove(xvec signal,double angle)
    {
        xvec sig(signal.size());
        for(double i = 0; i <signal.size();i++) // устраняем сдвиг
        {
            sig[i] = signal[i] * exp(J*(i)*(angle/_param.fftsize));
        }
        return sig;
    }

}