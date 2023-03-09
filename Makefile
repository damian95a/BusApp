OBJS	= query.o GUI.o main.o BusApp_Insertion.o BusApp_main_window.o BusApp_printout.o
SOURCE	= query.cpp GUI.cpp main.cpp BusApp_Insertion.cpp BusApp_main_window.cpp BusApp_printout.cpp
HEADER	= query.h BusApp_Insertion.h BusApp_main_window.h BusApp_printout.h GUI.h
OUT	= a.out
CC	 = g++
FLAGS	 = -g -c -Wall `wx-config --cxxflags`
LFLAGS	 = `wx-config --libs` -lpqxx -lpq

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

GUI.o: GUI.cpp GUI.h
	$(CC) $(FLAGS) GUI.cpp 

main.o: main.cpp BusApp_main_window.h
	$(CC) $(FLAGS) main.cpp 

BusApp_Insertion.o: BusApp_Insertion.cpp BusApp_Insertion.h query.h
	$(CC) $(FLAGS) BusApp_Insertion.cpp 

BusApp_main_window.o: BusApp_main_window.cpp BusApp_main_window.h query.h
	$(CC) $(FLAGS) BusApp_main_window.cpp 

BusApp_printout.o: BusApp_printout.cpp BusApp_printout.h
	$(CC) $(FLAGS) BusApp_printout.cpp 

query.o: query.h query.cpp
	$(CC) $(FLAGS) query.cpp 


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)
