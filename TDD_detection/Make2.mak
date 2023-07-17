CC = gcc
LIBS = -lstdc++ -ltch -lpython3.10 -pthread -lutil -ldl -lm -W -export-dynamic -lm -ldevmem -ldmac -lfftw3 -lm
CFLAGS = -std=c++17 -L$(LIB_PATH)
LIB_PATH = ./lib
ENV = LD_LIBRARY_PATH="$$LD_LIBRARY_PATH:$(LIB_PATH)"

all: TDD_detection

TDD_detection: 
	$(ENV) $(CC) $(CFLAGS) main.o param_storage.o create_mark.o signal_create.o fpga_configure.o LTE_PROC.o fft.o SSS_process.o TDD_calculate.o RS_PROC.o NRS_gen.o pss.o -o TDD_detection $(LIBS)

main.o: main.cpp
	$(ENV) $(CC) $(CFLAGS) main.cpp $(LIBS)

param_storage.o: param_storage.cpp
	$(ENV) $(CC) $(CFLAGS) param_storage.cpp $(LIBS)

create_mark.o: create_mark.cpp
	$(ENV) $(CC) $(CFLAGS) create_mark.cpp $(LIBS)

signal_create.o: signal_create.cpp
	$(ENV) $(CC) $(CFLAGS) signal_create.cpp $(LIBS)

fpga_configure.o: fpga_configure.cpp
	$(ENV) $(CC) $(CFLAGS) fpga_configure.cpp $(LIBS)

LTE_PROC.o: LTE_PROC.cpp
	$(ENV) $(CC) $(CFLAGS) LTE_PROC.cpp $(LIBS)

fft.o: fft.cpp
	$(ENV) $(CC) $(CFLAGS) fft.cpp $(LIBS)

SSS_process.o: SSS_process.cpp
	$(ENV) $(CC) $(CFLAGS) SSS_process.cpp $(LIBS)

TDD_calculate.o: TDD_calculate.cpp
	$(ENV) $(CC) $(CFLAGS) TDD_calculate.cpp $(LIBS)

RS_PROC.o: RS_PROC.cpp
	$(ENV) $(CC) $(CFLAGS) RS_PROC.cpp $(LIBS)

NRS_gen.o: NRS_gen.cpp
	$(ENV) $(CC) $(CFLAGS) NRS_gen.cpp $(LIBS)

pss.o: pss.cpp
	$(ENV) $(CC) $(CFLAGS) pss.cpp $(LIBS)

clean:
	rm -rf *.o TDD_detection