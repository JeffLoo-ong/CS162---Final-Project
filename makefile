CXX = g++

CXXFLAGS = -Wall
CXXFLAGS += -c
LFLAGS = -Wall -g

OBJS = main.o Barbarian.o BlueMen.o Goblin.o ReptilePeople.o Shadow.o Queue.o Stack.o

HEADERS = Creature.hpp Barbarian.hpp Goblin.hpp ReptilePeople.hpp BlueMen.hpp Shadow.hpp

.PHONY: all assign4 

all: assign4 

assign4: $(OBJS)
	$(CXX) $(OBJS) -o assign4

main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) main.cpp

Barbarian.o: Barbarian.cpp Barbarian.hpp
	$(CXX) $(CXXFLAGS) Barbarian.cpp

BlueMen.o: BlueMen.cpp BlueMen.hpp
	$(CXX) $(CXXFLAGS) BlueMen.cpp

Goblin.o: Goblin.cpp Goblin.hpp
	$(CXX) $(CXXFLAGS) Goblin.cpp

ReptilePeople.o: ReptilePeople.cpp ReptilePeople.hpp
	$(CXX) $(CXXFLAGS) ReptilePeople.cpp	

Shadow.o: Shadow.cpp Shadow.hpp
	$(CXX) $(CXXFLAGS) Shadow.cpp

Queue.o: Queue.cpp Queue.hpp
	$(CXX) $(CXXFLAGS) Queue.cpp

Stack.o: Stack.cpp Stack.hpp
	$(CXX) $(CXXFLAGS) Stack.cpp

clean:
	rm -f $(OBJS) assign4  