SRC = server.cpp
CXX = g++
LIB = -lpthread

server : server.cpp
	@$(CXX) $< -o output/$@ $(LIB)

.PHONY : clean

clean :
	@rm -rf output/server