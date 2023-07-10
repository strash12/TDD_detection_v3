#ifndef defined SIGNAL_CREATE
#define SIGNAL_CREATE

#include<complex>
#include<vector>

typedef std::complex<double> xd;
typedef std::vector<xd> xvec;

namespace signal
{
    class signal_create
    {
        private:
            void save_signal_to_file(std::vector<int32_t> samples,std::string name);
        public:
            signal_create();
            ~signal_create();
            xvec download_convert_signal(std::string name);
            
    };
} //namespace signal


#endif //SIGNAL_CREATE