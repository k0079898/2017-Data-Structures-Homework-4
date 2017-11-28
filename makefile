CC = g++ -std=c++11


RO_SRCS = ./*.cpp

main: RO 
	$(CC) -o $@ *.o



RO: $(RO_SRCS)
	$(CC) -c $(RO_SRCS)

.PHONY: clean
clean:
ifeq ($(OS),Windows_NT)
	del main.exe *.o
else
	rm main *.o
endif
