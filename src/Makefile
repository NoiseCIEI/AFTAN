#
INST_DIR = ../bin
BIN  = aftan_c_test
BIN1 = aftan_f_test

fflags = -O -Wall -ffixed-line-length-none
cflags = -O -Wall 

LDLIBS =   -lfftw3

FFLAGS = $(DBG) $(fflags)

CFLAGS = $(DBG) $(cflags)

FC = gfortran

CC = gcc

DBG = -g

FOBJS = driver_c.o swapn.o aftanpg.o aftanipg.o ftfilt.o fmax.o taper.o \
	trigger.o tapers.o tgauss.o mspline.o pred_cur.o misc.o phtovel.o

FOBJS1 = driver.o swapn.o aftanpg.o aftanipg.o ftfilt.o fmax.o taper.o \
	trigger.o tapers.o tgauss.o mspline.o pred_cur.o misc.o phtovel.o

all : $(BIN) $(BIN1)
$(BIN) : $(FOBJS)
	$(FC) $(FFLAGS) $(CFLAGS) $(FOBJS) -o $(BIN) $(LDLIBS) 

$(BIN1) : $(FOBJS1)
	$(FC) $(FFLAGS) $(CFLAGS) $(FOBJS1) -o $(BIN1) $(LDLIBS) 

install :: $(BIN)
	install -s $(BIN) $(INST_DIR);
	install -s $(BIN1) $(INST_DIR)

clean ::
	rm -f $(BIN) $(BIN1) core $(FOBJS) $(FOBJS1)
