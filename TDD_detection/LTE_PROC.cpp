#include "header.h"



namespace LTE
{
    xcorr::xcorr(){}
    xcorr::~xcorr(){}
// честная корреляция для синхронизации по PSS
   cor_data xcorr::correlate(xvec signal,xvec ref_signal,int start,int stop,int shift)
    {
        LTE::cor_data data = {};

            for (int i = start - shift; i <stop + shift; i++)
                {
                    for (int j = 0; j<ref_signal.size(); j++)
                        {    
                            data.cor_lvl += signal[i+j]*conj(ref_signal[j]);
                        }                      
                            data.level = abs(data.cor_lvl);
                                if (data.level > data.maximum)
                                    {
                                        data.maximum = data.level;
                                        data.first = i;
                                        
                                    }
                            data.cor_lvl = 0;                        
                  
                }
    
    return data;
    }

// расчет коэффициента корреляции путем матричного перемножения для второго и третьего считываний
    int xcorr::corr_coef(xvec signal,xvec ref_signal,int ref_samples,int fftsize,int cp, int shift_second_cor_start,int shift_second_cor_stop)
    {
        LTE::cor_data data{};
            for(int j = shift_second_cor_start; j < shift_second_cor_stop; j++)
            {
                for(int i = ref_samples+j,k = 0; i < ref_samples+j+fftsize+cp;i++)
                {
                    data.cor_lvl += signal[i]*conj(ref_signal[k]);
                    k++;  
                }
                    data.level = abs(data.cor_lvl);
                        if (data.level > data.maximum)
                            {
                                data.maximum = data.level;
                                data.first = j;   
                            }
                    data.cor_lvl = 0;       
            }
        return ref_samples + data.first;
    }

    // корреляция для пилотных сигналов
    double xcorr::fin_cor(xvec framesig_RS, xvec ref_RS,int size)
    {
        xd CoR = 0;
        double Corlvln = 0 ;   
            for (int i = 0; i<size ; i++){
		CoR += framesig_RS[i]*conj(ref_RS[i]);
        }               
        Corlvln = abs(CoR);  
       
      return Corlvln; 

    }

    freq_shift_estimate::freq_shift_estimate(){}
    freq_shift_estimate::~freq_shift_estimate(){};

    // рассчет частотного сдвига методом циклически-префиксной корреляции
    double freq_shift_estimate::get_angle(xvec signal,int cp,int fftsize,int first)
    {
        /*вырезаем сp двух рядомстоящих OFDM символов*/
        int start_cp1   = first-1; 
        int stop_cp1    = first+cp-1;
        int start_cp2   = first+fftsize-1;
        int stop_cp2    = first+fftsize+cp-1;

        xvec s1(signal.begin()+start_cp1,signal.begin()+stop_cp1); 
        xvec s2(signal.begin()+start_cp2,signal.begin()+stop_cp2);
        return calculate_angle(s1,s2,cp);
    }

    double freq_shift_estimate::calculate_angle(xvec cp1,xvec cp2,int cp)
    {
        /*коррелируем два выресаных cp друг с другом */
        std::complex<double> CoR;
        LTE::cor_data data{};
           
            for (int j = 0; j<cp+1 ; j++)
                {
                    CoR += cp1[j]*conj(cp2[j]);   
                }

            double angle = atan2(CoR.imag(),CoR.real());  // считаем арктангенс между реально и мнимой части 

        return angle;
    }
}//namespace LTE