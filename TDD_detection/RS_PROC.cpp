#include "header.h"

namespace RS
{
    RS_cut::RS_cut(param_store::_parametrs param) : framesig_RS(param.Nrb*2*4,0), ref_RS(param.Nrb*2*4,0)
    {
        _param = param;
        d = 0;
        k = 0;
        j = 0;
        s = 0;
        size = _param.Nrb*2*4;
    }
    
    RS_cut::~RS_cut(){};

    
    
    int RS_cut::set_RS(xvec sig_shift_1, xvec sig_shift_2, int first_1, int first_2)
    {   
        int sub = _param.fs/1e3;
        xvec Frame(sig_shift_1.begin()+first_1-(2*_param.fftsize)-_param.cp-_param.cp1-sub-1,sig_shift_1.begin()+first_1-(2*_param.fftsize)-_param.cp-_param.cp1-1+(4*sub));
        Frame.insert(Frame.end(),sig_shift_2.begin()+first_2-(2*_param.fftsize)-_param.cp-_param.cp1-sub-1,sig_shift_2.begin()+first_2-(2*_param.fftsize)-_param.cp-_param.cp1-1+(4*sub));
        gen_NRS();
        cut_slot(Frame);
        
	    return search_maximum();
        
    }

    void RS_cut::gen_NRS()
    {
        try{
            rs_signal_fixed_real = new double*[2*_param.Nrb];
                for(int i = 0; i <2*_param.Nrb;i++)
                    {
                        rs_signal_fixed_real[i] = new double [_param.Ns*2];
                    }
     
            rs_signal_fixed_imag = new double*[2*_param.Nrb];
                for(int i = 0; i <2*_param.Nrb;i++)
                    {
                        rs_signal_fixed_imag[i] = new double [_param.Ns*2];
                    }
            
            rs_space_index = new int*[2*_param.Nrb];
                for(int i = 0; i <2*_param.Nrb;i++)
                    {
                        rs_space_index[i] = new int [_param.Ns*2];
                    }
        }
      
      catch (std::bad_alloc ba){
            std::cout<<"no memory allocated"<<std::endl;
            std::cout<<ba.what()<<std::endl;
        }
        
      nrs::NRS_GEN RS(_param,_param.CellId);

      RS.NRC(_param,rs_signal_fixed_real,rs_signal_fixed_imag,rs_space_index);

    }

    void  RS_cut::cut_slot(xvec Frame)
    {
        int Slot_size = _param.fs/2000;

        for (int snum = 0; snum < 20;snum++)
        {
	        xvec SLot(Frame.begin()+snum*Slot_size,Frame.begin()+(snum+1)*Slot_size);
            xvec Slot_sig_1(SLot.begin()+_param.cp1,SLot.begin()+_param.cp1+_param.fftsize);
            fft_cut(Slot_sig_1);
            xvec Slot_sig_2(SLot.begin()+_param.cp1 + 4*(_param.fftsize + _param.cp),SLot.begin()+_param.cp1 + 5*(_param.fftsize + _param.cp) - _param.cp);
            fft_cut(Slot_sig_2);
        }
        
        std::ofstream outFile("framesig_RS.txt");
        for (const auto &e : framesig_RS) {outFile << e <<"\n";}
        outFile.close();

        search_maximum();
	}

   
    void RS_cut::fft_cut(xvec slotsig)
    {
      LTE::FFT_transform fft(_param.fftsize);
      xvec SLOT_sig_fft = fft.fft(slotsig);
      xvec slot_sig_cut(SLOT_sig_fft.begin()+_param.fftsize/2-(2*_param.Nrb)*3,SLOT_sig_fft.begin()+_param.fftsize/2);
      slot_sig_cut.insert(slot_sig_cut.end(),SLOT_sig_fft.begin()+_param.fftsize/2+1,SLOT_sig_fft.begin()+_param.fftsize/2+(2*_param.Nrb)*3+1);
      std::cout<<"SLOT_sig_fft.size() = "<< SLOT_sig_fft.size()<<std::endl;
      for(int i = 0; i <SLOT_sig_fft.size();i++)
      {
        
        std::cout<<SLOT_sig_fft[i]<<std::endl;
        }
      gen_array(slot_sig_cut);
    }

    void RS_cut::gen_array(xvec Slot)
    {
	    double maximume = 0;
        LTE::xcorr corr;
        
        
        for (int i = 0; i < _param.Nrb*2;i++){
            int a = rs_space_index[i][d]-1;
           // std::cout<<a<<std::endl;
                framesig_RS[k] = Slot[a];
                ref_RS[k] = xd(rs_signal_fixed_real[i][j],rs_signal_fixed_imag[i][j]);
                k++;
        }
        j++;
           
            if (d == 3) { 
                d = 0;
                k = 0; 
                cor_arr[s] = corr.fin_cor(framesig_RS,ref_RS,size);
                s++;
           } 
           else {d++;}
    }

int RS_cut::search_maximum()
    {
        double max = *std::max_element(cor_arr.begin(),cor_arr.end());
        for (int i = 0; i < 10; i++) {
          TDD_conf[i] = (cor_arr[i]<(max/10))  ? 0 : 1;
          std::cout<<cor_arr[i]<<std::endl;

        }
        return TDD_config();
    }

    
    int RS_cut::TDD_config()
    {
      const std::array<std::array<int, 10>, 7> TDD_patterns {{
        {1,1,0,0,0,1,1,0,0,0},
        {1,1,0,0,1,1,1,0,0,1},
        {1,1,0,1,1,1,1,0,1,1},
        {1,1,0,0,0,1,1,1,1,1},
        {1,1,0,0,1,1,1,1,1,1},
        {1,1,0,1,1,1,1,1,1,1},
        {1,1,0,0,0,1,1,0,0,1}
    }};
    
    int TDD_config = -1;
    
    for (int i = 0; i < TDD_patterns.size(); ++i){
        if (TDD_conf == TDD_patterns[i]){
            TDD_config = i;
            break;
        }
    }

    return TDD_config;
}

} //namespace RS