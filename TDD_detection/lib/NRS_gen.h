// генератор RS сигналов  согласно TS 36.211 - 6.10.1
#ifndef defined NRS_gen
#define NRS_gen

#include "../../TDD_detection/header.h"
#include <bitset>


namespace nrs
{
class NRS_GEN
{
    protected:
        int M;//количество пилотов
        int Ncp,Ns_fix,fix_1,C_init,C_init_fix,r,m_,Lb;
        int Ns  = 20; // колтчество сабфреймов в кадре
        int Nc  =   1600; // сдвиг
        int _CellId; // идентификатор соты
        int rs_space_1_fix_normal[40];  //задающая последовательность для нормального префикса
        int rs_space_1_fix_extended[40]; //задающая последовательность для расширенного префикса
        int NS_1_normal[2]; //корни для нормального
        int NS_1_extended[2]; //корни для расширенного 

    public:
        NRS_GEN(param_store::_parametrs param,int);
        ~NRS_GEN();
        void NRC(param_store::_parametrs param,double** rs_signal_fixed_real, double** rs_signal_fixed_imag, int** rs_space_index );
};


} //namespace RS


#endif //NRS_gen