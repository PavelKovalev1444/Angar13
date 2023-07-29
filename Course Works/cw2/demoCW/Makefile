all: imgEditor

imgEditor: main.o readFile.o writeFile.o rectangle.o frame.o rotation.o
	gcc main.o readFile.o writeFile.o rectangle.o frame.o rotation.o -lpng -o imgEditor

main.o: main.c
	gcc -c main.c -lpng

readFile.o: readFile.c readFile.h
	gcc -c readFile.c -lpng

writeFile.o: writeFile.c writeFile.h
	gcc -c writeFile.c -lpng

rectangle.o: rectangle.c rectangle.h
	gcc -c rectangle.c -lpng

frame.o: frame.c frame.h
	gcc -c frame.c -lpng

rotation.o: rotation.c rotation.h
	gcc -c rotation.c -lpng

clean:
	rm -rf *.o
