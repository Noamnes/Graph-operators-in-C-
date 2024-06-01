# id:212631071, mail:noamsayada1@gmail.com
CXX = g++
CXXFLAGS = -std=c++11 -g
OBJECTS= Graph.o Algorithms.o

run: tests
	./tests

tests: Test_ass1.o Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

demo : Demo.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

valgrind_tests: tests
	valgrind --leak-check=full ./$<

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm *.o tests demo