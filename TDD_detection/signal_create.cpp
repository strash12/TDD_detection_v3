#include "header.h"
#include <fstream>
#include <exception>
namespace signal
{
    signal::signal_create::signal_create(){}
    signal::signal_create::~signal_create(){}
        
    xvec signal::signal_create::download_convert_signal(std::string name)
    {
	    int buffer_size = 163800;	// размер буффера 
        xvec signal(buffer_size);
        auto samples = dmac::read<int32_t>(327600,0);
            if (samples.size() == 0)
                {
                    throw mark::TDDException("Error load signal to signal_create.cpp"); // если буфер пустой ошибка
                }
                if(debug == 1){save_signal_to_file(samples,name);} // сохраняем в файл если включен режим дебага
            
            for(int  i = 0; i < buffer_size;i++)
                {   
                    signal[i] = xd((int16_t)(samples[i] & 0xffff),(int16_t)(samples[i] >>16)); // записываем считаные сигнал в комплексный вектор
                }
        return signal;
    }
    
    /* сохраням в файл*/
    void signal::signal_create::save_signal_to_file(std::vector<int32_t> samples,std::string name)
    {
        std::ofstream outFile(name);
        for (const auto &e : samples) outFile << (int16_t)(e& 0xffff)<<"  " << (int16_t)(e >>16)<<"\n";
        outFile.close();
    } //save_signal_to_file   
        

} // namespace signal