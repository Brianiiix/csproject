CXX	=	g++ -std=c++17 -O2
EXE = input2sat

all: $(EXE)

$(EXE): routingBoard.cpp IO_interface.hpp Structure.hpp output_gds.hpp
	$(CXX) $< -o $@

clean:
	rm -f $(EXE)
