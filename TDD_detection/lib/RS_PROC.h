#ifndef defined RS_PROC
#define RS_PROC

#include "../../TDD_detection/header.h"
#include <string>


namespace RS
{
    class RS_cut
    {
        public:
            RS_cut(param_store::_parametrs param);
            ~RS_cut();
            param_store::_parametrs _param;
            int set_RS(xvec sig_shift_1, xvec sig_shift_2, int first_1, int first_2);
        private:
	        int d,k,j,size,s;
	        xvec framesig_RS;
            xvec ref_RS;		
            double** rs_signal_fixed_real;
            double** rs_signal_fixed_imag;
	        int** rs_space_index;
            std::array<int,10> TDD_conf;
	        std::array<double, 10>cor_arr;	
            void cut_slot(xvec Frame);
	        void gen_array(xvec Slot);	
            void gen_NRS();
            void fin_cor(xvec signal);
	        void fft_cut(xvec slotsig);	
            int search_maximum();
            int TDD_config();

    };

} //namespace RS


#endif //RS_PROC