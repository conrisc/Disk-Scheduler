## Konrad Cielecki, nr indeksu: 273278
## Pracownia z Systemów operacyjnych nr 2

main: main.cpp
	g++ -std=c++11 -Wall -Werror -pthread -c main.cpp
	g++ -std=c++11 -Wall -Werror -pthread -o main main.o

run: main
	./main 3 disk.in0 disk.in1 disk.in2 disk.in3 disk.in4

clean:
	rm -rf main.o

distclean:
	rm -rf main main.o
