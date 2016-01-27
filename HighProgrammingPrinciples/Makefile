OBJECTS = MeasuredValue.o Segment.o Interpolation.o Functions.o Fitness.o Parameters.o IntervalLoader.o RandomVectorGenerator.o Difuse2Param.o Database.o Simplex.o Manager.o Main.o OutputTable.o

CFLAGS = -std=c++11 -Wall -I /usr/local/intel/include -I /usr/include/qt4 -L /usr/local/intel/lib/intel64/gcc4.4 -O4 -Xlinker -rpath -Xlinker /usr/local/intel/lib/intel64/gcc4.4

LIBS = -lQtCore -lsqlite3 -ltbb
CC = g++-4.7

all: Vozabal_PPR_Sem 

Vozabal_PPR_Sem: MeasuredValue.o Segment.o Interpolation.o Functions.o Fitness.o Parameters.o IntervalLoader.o RandomVectorGenerator.o Difuse2Param.o Database.o Simplex.o Manager.o Main.o OutputTable.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ 
	rm -f *.o
	
MeasuredValue.o: MeasuredValue.cpp MeasuredValue.h 
	$(CC) $(CFLAGS) -c MeasuredValue.cpp

Segment.o: Segment.cpp Segment.h
	$(CC) $(CFLAGS) -c Segment.cpp

Interpolation.o: Interpolation.cpp Interpolation.h 
	$(CC) $(CFLAGS) -c Interpolation.cpp

Functions.o: Functions.cpp Functions.h 
	$(CC) $(CFLAGS) -c Functions.cpp

Fitness.o: Fitness.cpp Fitness.h
	$(CC) $(CFLAGS) -c Fitness.cpp

Parameters.o: Parameters.cpp Parameters.h
	$(CC) $(CFLAGS) -c Parameters.cpp

IntervalLoader.o: IntervalLoader.cpp IntervalLoader.h
	$(CC) $(CFLAGS) -c IntervalLoader.cpp

RandomVectorGenerator.o: RandomVectorGenerator.cpp RandomVectorGenerator.h
	$(CC) $(CFLAGS) -c RandomVectorGenerator.cpp

Difuse2Param.o: Difuse2Param.cpp Difuse2Param.h
	$(CC) $(CFLAGS) -c Difuse2Param.cpp

Database.o: Database.cpp Database.h
	$(CC) $(CFLAGS) -c -Wno-write-strings Database.cpp
	
Simplex.o: Simplex.cpp Simplex.h
	$(CC) $(CFLAGS) -c Simplex.cpp

Manager.o: Manager.cpp Manager.h
	$(CC) $(CFLAGS) -c Manager.cpp
	
Main.o: Main.cpp Main.h
	$(CC) $(CFLAGS) -c Main.cpp
	
OutputTable.o: OutputTable.cpp OutputTable.h
	$(CC) $(CFLAGS) -c OutputTable.cpp

%.o: %.c
	$(CC) -c $<  

clean: 
	rm -f *.o
