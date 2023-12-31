#include "header.h"
// генератор RS сигналов  согласно TS 36.211 - 6.10.1
namespace nrs
{
    // Входные параметры функции 
    NRS_GEN::NRS_GEN(param_store::_parametrs param,int Cellid):
    rs_space_1_fix_normal{1,5,8,12,15,19,22,26,29,33,36,40,43,47,50,54,57,61,64,68,71,75,78,82,85,89,92,96,99,103,106,110,113,117,120,124,127,131,134,138},
    rs_space_1_fix_extended{1,4,7,10,13,16,19,22,25,28,31,34,37,40,43,46,49,52,55,58,61,64,67,70,73,76,79,82,85,88,91,94,97,100,103,106,109,112,115,118},
    NS_1_normal{1,5},NS_1_extended{1,4}
    {
        _CellId = Cellid;
        M   = 220;
        Ncp = param.cyclic == 1  ? 1 : 0;
        Lb  = param.cyclic == 1  ? 7 : 6;


    }

    NRS_GEN::~NRS_GEN()
    {
    }

    void NRS_GEN::NRC(param_store::_parametrs param,double** rs_signal_fixed_real, double** rs_signal_fixed_imag, int** rs_space_index)
    {
        int size = 31+M*2+Nc;
        int rs_space_1_fix[40];
        int NS_1[2];
        double rs_signal_real[M][Ns*2];
        double rs_signal_imag[M][Ns*2];
xvec hui[M];
const xd J(0, 1);
        int o = 0 ;
            // Цикл генерит и выдает парамметры пилотов
            if(param.cyclic == 1 ){
                std::copy(std::begin(rs_space_1_fix_normal),std::end(rs_space_1_fix_normal),std::begin(rs_space_1_fix));
                std::copy(std::begin(NS_1_normal),std::end(NS_1_normal),std::begin(NS_1));
            }
            if(param.cyclic == 2 ){
                std::copy(std::begin(rs_space_1_fix_extended),std::end(rs_space_1_fix_extended),std::begin(rs_space_1_fix));
                std::copy(std::begin(NS_1_extended),std::end(NS_1_extended),std::begin(NS_1));
            }
            //Инициализация C_init
            for (int i = 0; i < Ns; i++){
                 for (int j = 0;j < 2;j++){
                        Ns_fix = i;
                        fix_1  = NS_1[j] - 1; 
                        C_init = 1024*(7*(Ns_fix+1)+fix_1+1)*(2*_CellId+1)+2*_CellId+Ncp;
        //в двоичное 31 разрядное число
        std::bitset<31>ns_fix31(C_init);
            for (int i=0;i<31/2;++i){
                bool t = ns_fix31[i];
                ns_fix31[i] = ns_fix31[31-i-1];
                ns_fix31[31-i-1] =t;
            }

        //M-sequence 1, x1 (инициализация последовательности 1, согласно 7.2)
        int x1[size]; x1[0] = 1; 
            for(int k=0;k<M*2+Nc;k++){
                x1[k+31] = (x1[k+3]+x1[k])%2;
            }        
        //M-sequence 2, x2 (инициализация последовательности 2, согласно 7.2)
        int x2[size];
            for (int k=30,l=0;k>=0;k--){
                x2[l]=ns_fix31[k];
            l++;
            }

            for (int k=0; k<M*2+Nc;k++){    
                x2[k+31] = ((x2[k+3]+x2[k+2]+x2[k+1]+x2[k])%2);

            }
        //пилотоы
        int c[M*2];
            for(int i=0;i<M*2;i++){
                c[i] = (x1[i+Nc]+x2[i+Nc])%2;
            }
        //модуляция пилотов
            for (int i=0;i<M;i++){

                rs_signal_real[i][o] = (1/sqrt(2))*(1-2*c[2*i]);
                rs_signal_imag[i][o] = (1/sqrt(2))*(1-2*c[2*i+1]);

            }

            for (int h = 0;h<2*param.Nrb;h++){
                m_=h+110-param.Nrb;
                rs_signal_fixed_real[h][o] = rs_signal_real[m_][o];
                rs_signal_fixed_imag[h][o] = rs_signal_imag[m_][o];
            }
        o++;
        }

        
    }
// маппинг  пилотов

        double rs_space_1 [Ns*2];
            for (int i=0;i<Ns*2;i++){
                rs_space_1[i]=rs_space_1_fix[i];
            }

        double v_shift =_CellId-(floor(_CellId/6)*6);
        int v_[2]={3,0};
        int l;

            for(int i=0;i<=Ns*2;i++){
                int j = i-(floor(i/2)*2)+1;
                    for (int n_dl_rb = 1;n_dl_rb<=param.Nrb;n_dl_rb++){
                        for(int m=1;m<=2*n_dl_rb;m++){
                                l = 6*(m-1)+ ((v_[j-1]+v_shift)-(floor((v_[j-1]+v_shift)/6))*6);
                                    rs_space_index[m-1][i-1] = l+1;

                        }
                    }
   
            }
    }
}
