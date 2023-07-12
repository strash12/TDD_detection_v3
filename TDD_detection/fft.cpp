/* класс для БПФ*/

#include "header.h"
#include <cstring>
#include <fftw3.h>

namespace LTE
{
    LTE::FFT_transform::FFT_transform(int fft_size)
    {
        _FFT_SIZE = fft_size;
    }

    LTE::FFT_transform::~FFT_transform(){}

    xvec LTE::FFT_transform::fft(xvec signal)
    {



        xd* mass = &signal[0]; // массив с нулями
        xd* sig_in = (xd*) fftw_malloc(sizeof(xd)*_FFT_SIZE); // входной сигнал
        xd* sig_out = (xd*) fftw_malloc(sizeof(xd)*_FFT_SIZE); // выходной сигнал 

        //заполняем массив
        memset(sig_in,0,sizeof(xd)*_FFT_SIZE);
        memcpy(sig_in,mass, sizeof(xd)*_FFT_SIZE);
        
        // создаем план для выполнения БПФ
        fftw_plan p = fftw_plan_dft_1d(_FFT_SIZE,reinterpret_cast<fftw_complex*>(sig_in),reinterpret_cast<fftw_complex*>(sig_out),FFTW_FORWARD,FFTW_ESTIMATE);
    
        fftw_execute(p); //выполняем план

        fftw_destroy_plan(p);// удаляем план

	    xvec out(_FFT_SIZE); // выходной вектор
        xvec in(_FFT_SIZE);

        int Half = _FFT_SIZE/2; // переменная для разварота спектра


        for(int i =0; i <_FFT_SIZE;i++)
        {
           in[i] = xd(sig_out[i].real(),sig_out[i].imag()); // разварот спектра
        }
	
               
        // копируем в выходной вектор
	    copy(in.begin()+Half,in.end(),out.begin());
        copy(in.begin(),in.begin()+Half,out.begin()+Half); 
        

    fftw_free(sig_in);// очищаем память
    fftw_free(sig_out);

	return(out);
    

    }

}