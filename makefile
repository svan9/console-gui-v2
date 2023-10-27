CXX        := g++
CXX_FLAGS  := # -static-libgcc -static-libstdc++

SRC        := ./src
INCLUDE    := ./include

EXECUTABLE := ./bin/app.exe

SOURCES    := $(wildcard $(SRC)/**/*.cpp $(SRC)/*.cpp) $(wildcard $(INCLUDE)/*.h, $(INCLUDE)/**/*.h)
OBJECTS    := $(patsubst $(SRC)/%.cpp, ./bin/obj/%.o, $(SOURCES))

ifeq ($(wildcard bin),) 
$(shell mkdir "bin/obj")
endif 
ifeq ($(wildcard ./bin/obj),) 
$(shell mkdir "bin/obj")
endif 


all: ./$(EXECUTABLE)

run: all
	./$(EXECUTABLE)

./$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ 

./bin/obj/%.o: $(SRC)/%.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -I$(SRC) -c $< -o $@

clean:
	rmdir "./bin" /s /q

-include $(OBJECTS:.o=.d)