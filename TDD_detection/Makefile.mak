CC = gcc 
CFLAGS = -std=c++17  -ltch -lstdc++ -lpython3.10 -pthread -lutil -ldl -lm -W -export-dynamic  -lm -ldevmem -ldmac -lfftw3 -lm
LIBS = -L/root/test/tusur/TDD_detection_v3/TDD_detection/lib 
all: TDD_detection
$(info ************  TDD_detection v 1.1.1 ************)
TDD_detection: main.o param_storage.o create_mark.o signal_create.o fpga_configure.o LTE_PROC.o fft.o SSS_process.o TDD_calculate.o RS_PROC.o NRS_gen.o pss.o
	$(CC) main.o param_storage.o create_mark.o signal_create.o fpga_configure.o LTE_PROC.o fft.o SSS_process.o TDD_calculate.o RS_PROC.o NRS_gen.o pss.o -o TDD_detection

main.o: main.cpp
	$(CC) $(LIBS) $(CFLAGS)  main.cpp

param_storage.o: param_storage.cpp
	$(CC) $(CFLAGS) param_storage.cpp

create_mark.o: create_mark.cpp
	$(CC) $(CFLAGS) create_mark.cpp

signal_create.o: signal_create.cpp
	$(CC) $(CFLAGS) signal_create.cpp

fpga_configure.o: fpga_configure.cpp
	$(CC) $(CFLAGS) fpga_configure.cpp

LTE_PROC.o: LTE_PROC.cpp
	$(CC) $(CFLAGS) LTE_PROC.cpp

fft.o: fft.cpp
	$(CC) $(CFLAGS) fft.cpp

SSS_process.o: SSS_process.cpp
	$(CC) $(CFLAGS) SSS_process.cpp

TDD_calculate.o: TDD_calculate.cpp
	$(CC) $(CFLAGS) TDD_calculate.cpp

RS_PROC.o: RS_PROC.cpp
	$(CC) $(CFLAGS) RS_PROC.cpp

NRS_gen.o: NRS_gen.cpp
	$(CC) $(CFLAGS) NRS_gen.cpp

pss.o: pss.cpp
	$(CC) $(CFLAGS) pss.cpp

clean:
	rm -rf *.o hello
