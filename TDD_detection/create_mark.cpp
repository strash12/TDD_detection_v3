/*в данной функции происходит установка параметров в fpga, 
загрузка сигнала, кореляция с первичным синхронизирующим сигналом(PSS), 
а так же расчет идентификатора соты (CelliD)*/


#include "header.h"

namespace mark
{
        

        create_mark::create_mark(tch::FullTusurCommonConfig config)
        {
            _config = config; // прототип структуры содержащей парамеры для расчетов находятся в файле param_storage.cpp
        };
        create_mark::~create_mark(){};

        void create_mark::calculate_mark()
        {
            std::cout<<"start create mark:"<<std::endl;
            set_params(); // передача  параметров о полосе, регистрах, нобере бэнда в fpga 
            signal::signal_create download_sig;
            xvec signal = download_sig.download_convert_signal("real1.txt"); // загрузка сигнала, параметр который передаем, имя файла в который сохраниться сигнал
            corelate_signal(signal); // корреляция сигнала с PSS
            cell_id_calculate(signal);  // рассчет CellID

        }

        void create_mark::set_params()
        {
            param_store::parametrs params; // прототип структуры с параметрами
            _param = params.set_param(_config); // передаем параметры в коррелятор
            fpga_configure::config_fpga fpga(_param);
            fpga.set_PSS_fpga(); //поиск предположительного отсчета начала кадра

        } //set_params

        void create_mark::corelate_signal(xvec signal)
        {
            
            LTE::xcorr corr; // прототип структуры с параметрами корреляции
            double lvl = 0; // уровень корреляции
            xvec PSS(_param.fftsize+_param.cp); // вектор для хранения PSS сигнала
                for(int i = 0; i < 3; i++) // dctuj 3 PSS последовательности
                {   
                    PSS = PSS_generate::pss::get_pss(i,_param.fftsize,_param.cp); // генерируем pss
                    PSS_data = corr.correlate(signal,PSS,_param.windowing,_param.windowing,_param.shift); // передаем сгенерированную PSS ,принятый сигнал, окно корреляции и предположительное место расположения
                    if(PSS_data.maximum > lvl) // находим максимальный уровень из 3х PSS сигналов
                    {
                        lvl = PSS_data.maximum; // мощность корреляции
                        _param.first = PSS_data.first; // номер символа начала pss
                        _param.PSS_number = i; // номер pss сигнала с которым наибольшая корреляция
                    }
                }

                if(debug)
                {
                    std::cout<<"first symbol  = "<<_param.first<<std::endl;
                }

        } //corelate_signal

        
        void create_mark::cell_id_calculate(xvec signal)
        {
                SSS::SSS_PROC SSS; 
                _param.CellId = SSS.CellId_calculate(signal,_param,_param.first); // рассчет CelliD
                if(debug)
                {
                    std::cout<<"CellId = "<<_param.CellId<<std::endl;
                }
        } // cell_id_calculate


} // namespace mark