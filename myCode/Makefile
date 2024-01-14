CXX = g++
CXXFLAGS = -std=c++11

SRCS =C:\cygwin64\home\ozeem\myLibraryProject\myCode\myCodeFile.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = execute_myCodeFile

True: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
