CC = g++
CCFLAGS = -Wall -Wextra -std=c++17 -lm

# List of source files
SRCS = servere.cpp colorare.cpp compresie.cpp criptat.cpp oferta.cpp

# List of executable targets
EXECUTABLES = $(SRCS:.cpp=)

.PHONY: build clean

build: $(EXECUTABLES)

# Run targets
run-p1:
	./servere
run-p2:
	./colorare
run-p3:
	./compresie
run-p4:
	./criptat
run-p5:
	./oferta

# Rule to build executables
%: %.cpp
	$(CC) -o $@ $^ $(CCFLAGS)

# Clean rule
clean:
	rm -f $(EXECUTABLES)