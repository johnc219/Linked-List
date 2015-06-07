
TestLL : TestLL.cpp LinkedList.h
	g++ -o TestLL TestLL.cpp

.PHONY : clean
clean :
	rm TestLL

.PHONY : run
run : TestLL
	./TestLL
