CC = gcc
LIBS = -lstdc++ -ltch -lpython3.10 -pthread -lutil -ldl -lm -W -export-dynamic -lm -ldevmem -ldmac -lfftw3 -lm
CFLAGS = -std=c++17 -L$(LIB_PATH)
LIB_PATH = ./lib
ENV = LD_LIBRARY_PATH="$$LD_LIBRARY_PATH:$(LIB_PATH)"


CPP_FILES = $(wildcard *.cpp)

all: TDD_detection
$(info ************  TDD_detection v 1.1.1 ************)
TDD_detection:
	$(ENV) $(CC) $(CFLAGS) -o test $(CPP_FILES) $(LIBS)
