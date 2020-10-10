# variable definition
OPT = -O3
STD = -std=c++17
COMPILER = g++ $(OPT)
PROGRAM_NAME = program
OUTNAME = -o $(PROGRAM_NAME)

# directory definition

RANDOM = random/rand_generator.cpp
MAIN = $(PROGRAM_NAME).cpp


TARGET = $(RANDOM) 

# rule definition
program: $(TARGET) $(MAIN) $(TARGET:.cpp=.h)
	$(COMPILER) $(STD) $(TARGET) $(MAIN) $(OUTNAME)

clean:
		rm $(PROGRAM_NAME)
