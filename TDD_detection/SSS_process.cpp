#include "header.h"
#include "../TDD_detection/signal_storage/SSS.h"
namespace SSS
{
    SSS::SSS_PROC::SSS_PROC(){}
    SSS::SSS_PROC::~SSS_PROC(){}

    int SSS::SSS_PROC::CellId_calculate(xvec signal, param_store::_parametrs& param,int first)
    {
        xvec SSS_cut(param.fftsize); // вектор для вырезанного SSS сигнала
        cut_sss_signal(signal,SSS_cut,param,first); // вырезаем сигнал
        xvec SSS_fft(param.fftsize);// вектор для сигнала после БПФ
        fft_sss_signal(param.fftsize,SSS_cut,SSS_fft); // делаем БПФ
        xvec SSS_62(62); //  вектор для вырезанных 62 элементов
        cut_62_elemets_sss(param.fftsize,SSS_62,SSS_fft);// вырезаем 62 элемента
        double maxSSS1 = 0,maxSSS2 = 0;// максимму корреляции для первой и второй половины
        int Cellid1 = sss_corelatate(SSS_first_part,maxSSS1,SSS_62);// корреляция первой половины
        int Cellid2 = sss_corelatate(SSS_second_part,maxSSS2,SSS_62);// корреляция второй половины
        int CellId = maxSSS1>maxSSS2?Cellid1:Cellid2;// смотрим в какой половине было наибольшее значение корреляции, и выбираем CelliD.
        return CellId;//

    }

    void SSS::SSS_PROC::cut_sss_signal(xvec signal,xvec& SSS_cut,param_store::_parametrs param,int first) //вырезаем отсчет содержащий SSS
    {
        int start = first - (param.fftsize + param.cp)- (param.fftsize + param.cp1) - param.fftsize-1; // начало SSS символа
        int stop  = first - 2 * param.fftsize -  param.cp-  param.cp1 -1; // конец SSS символа
        std::copy(signal.begin()+start,signal.begin()+stop,SSS_cut.begin()); // вырезаем SSS символ
    }

    void SSS::SSS_PROC::fft_sss_signal(int fft_size,xvec SSS_cut,xvec& SSS_fft) // производим БПФ
    {
        LTE::FFT_transform fft(fft_size);
        SSS_fft = fft.fft(SSS_cut);
    }

    void SSS::SSS_PROC::cut_62_elemets_sss(int fft_size,xvec& SSS_62,xvec SSS_fft) // вырезаеи 62 элемента из SSS сигнала в частотной области
    {
        int begin_1 = fft_size/2 - 31;  // вырезаем первую половину состоящую из  31 элемента
        int end_1   = fft_size/2;       
        int begin_2 = fft_size/2 + 1;   // вырезаем вторую половину состоящую из  31 элемента
        int end_2   = fft_size/2 + 32; 

        /* это необходимо потуму что посередине между первой и второй половиной расположет "0" под несущий сигнал
        111111111111111111111111111101111111111111111111111111111
        |          первая половина | |вторая половина            |*/

            std::copy(SSS_fft.begin()+begin_1,SSS_fft.begin()+end_1,SSS_62.begin());
            std::copy(SSS_fft.begin()+begin_2,SSS_fft.begin()+end_2,SSS_62.begin()+31);

    }
    /* коррелируем с двумя заранее сгенерированными массивами SSS сигналов хранящихся в .../lib/SSS.h.
     Два массива необходимо потому что один кадр содержит два SSS сигнала расоложеные в первой и второй полоивенине кадра.
     Для каждой половины кадра SSS сигналы отличаются что бы мы могли понимать в какую половину попали при синхронизации.
     Номер SSS из массива с котрым была наилучшая корреляция и будет номером ячейки CelliD*/

    int SSS::SSS_PROC::sss_corelatate(double (&SSS_signal)[504][62],double& maxSSS,xvec SSS_62) 
    {                                                                                           
   
    double Corlvln = 0;
    int Cellid = 0;       
    xd CorRe;
        for ( int i = 0; i < 504;i++) // 504 SSS в массиве
            {
                for (int j = 0; j < 62; j++) // длина SSS последовательности
                    {
                        CorRe  +=  SSS_62[j]*SSS_signal[i][j]; // в аккамулятор записываются значения перемножения  
                    }

           Corlvln =  sqrt(pow(CorRe.real(),2)+pow(CorRe.imag(),2)); // получаем значение по модулю
                    if(Corlvln > maxSSS)
                        {
                            maxSSS = Corlvln; //  записываем сюда наибольшее значение ксли выполнилось условие
                            Cellid = i;
                        }
            CorRe  = 0;
            }
    return Cellid;
    }

}