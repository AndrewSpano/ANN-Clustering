CC=g++

LSH: LSHMain LSHInterface.o interface_utils.o interface.o
	$(CC) -o bin/LSH object/LSHMain.o object/LSH_interface.o object/interface_utils.o object/interface.o

LSHMain:
	$(CC) -c -o object/LSHMain.o exc1/LSHMain.cpp

LSHInterface.o:
	$(CC) -c -o object/LSH_interface.o src/interfaces/LSH_interface.cpp

HCUBE_interface.o:
	$(CC) -c -o object/HCUBE_interface.o src/interfaces/HCUBE_interface.cpp

interface.o:
	$(CC) -c -o object/interface.o src/interfaces/interface.cpp

interface_utils.o:
	$(CC) -c -o object/interface_utils.o src/interfaces/interface_utils.cpp

clean:
	rm bin/* object/*.o
