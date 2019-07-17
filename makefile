all: main.cpp 
	gcc main.cpp -o all -lstdc++
	./all
clean:
	rm -f all

