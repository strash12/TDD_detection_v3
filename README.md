# TDD_detection_v3

gcc -std=c++17 -L/root/test/tusur/TDD_detection/lib -o test main.cpp param_storage.cpp create_mark.cpp signal_create.cpp fpga_configure.cpp LTE_PROC.cpp fft.cpp SSS_process.cpp TDD_calculate.cpp RS_PROC.cpp NRS_gen.cpp pss.cpp -ltch -lstdc++ -lpython3.10 -pthread -lutil -ldl -lm -W -export-dynamic -lm -ldevmem -ldmac -lfftw3 -lm
