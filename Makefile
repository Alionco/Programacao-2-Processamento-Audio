#// GRR20196992 Lucas Alionco

CFLAGS = -Wall

all: wavinfo wavvol wavnorm wavrev wavecho wavwide wavcat wavmix

# regras de ligacao

wavinfo: wavinfo.o wav_filter.o wav_access.o wav_terminal.o
	gcc wavinfo.o wav_filter.o wav_access.o wav_terminal.o -o wavinfo

wavvol: wavvol.o wav_filter.o wav_access.o wav_terminal.o
	gcc wavvol.o wav_filter.o wav_access.o wav_terminal.o -o wavvol

wavnorm: wavnorm.o wav_filter.o wav_access.o wav_terminal.o
	gcc wavnorm.o wav_filter.o wav_access.o wav_terminal.o -o wavnorm

wavrev: wavrev.o wav_filter.o wav_access.o wav_terminal.o
	gcc wavrev.o wav_filter.o wav_access.o wav_terminal.o -o wavrev

wavecho: wavecho.o wav_filter.o wav_access.o wav_terminal.o
	gcc wavecho.o wav_filter.o wav_access.o wav_terminal.o -o wavecho

wavwide: wavwide.o wav_filter.o wav_access.o wav_terminal.o
	gcc wavwide.o wav_filter.o wav_access.o wav_terminal.o -o wavwide

wavcat: wavcat.o wav_filter.o wav_access.o wav_terminal.o
	gcc wavcat.o wav_filter.o wav_access.o wav_terminal.o -o wavcat

wavmix: wavmix.o wav_filter.o wav_access.o wav_terminal.o
	gcc wavmix.o wav_filter.o wav_access.o wav_terminal.o -o wavmix

#regras de compilacao

wavinfo.o: wavinfo.c wav_filter.h wav_access.h wav_terminal.h wav_struct.h
	gcc -c wavinfo.c $(CFLAGS)

wavvol.o: wavvol.c wav_filter.h wav_access.h wav_terminal.h wav_struct.h
	gcc -c wavvol.c $(CFLAGS)

wavnorm.o: wavnorm.c wav_filter.h wav_access.h wav_terminal.h wav_struct.h
	gcc -c wavnorm.c $(CFLAGS)

wavrev.o: wavrev.c wav_filter.h wav_access.h wav_terminal.h wav_struct.h
	gcc -c wavrev.c $(CFLAGS)

wavecho.o: wavecho.c wav_filter.h wav_access.h wav_terminal.h wav_struct.h
	gcc -c wavecho.c $(CFLAGS)

wavwide.o: wavwide.c wav_filter.h wav_access.h wav_terminal.h wav_struct.h
	gcc -c wavwide.c $(CFLAGS)

wavcat.o: wavcat.c wav_filter.h wav_access.h wav_terminal.h wav_struct.h
	gcc -c wavcat.c $(CFLAGS)

wavmix.o: wavmix.c wav_filter.h wav_access.h wav_terminal.h wav_struct.h
	gcc -c wavmix.c $(CFLAGS)

wav_filter.o: wav_filter.c wav_filter.h wav_access.h wav_terminal.h wav_struct.h
	gcc -c wav_filter.c $(CFLAGS)

wav_access.o: wav_access.c wav_filter.h wav_access.h wav_terminal.h wav_struct.h
	gcc -c wav_access.c $(CFLAGS)

wav_terminal.o: wav_terminal.c wav_filter.h wav_access.h wav_terminal.h wav_struct.h
	gcc -c wav_terminal.c $(CFLAGS)

clean: 
	-rm -f *~ *.o

purge: clean
	-rm -f wavinfo wavvol wavnorm wavrev wavecho wavwide wavcat wavmix

	