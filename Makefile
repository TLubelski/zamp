__start__: obj interp __plugin__ __lines_for_space__
	./run.sh

obj:
	mkdir obj


__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo


__plugin__:
	cd plugin; make

CPPFLAGS=-Wall -pedantic -std=c++17 -Iinc
LDFLAGS=-Wall




interp: obj/main.o obj/LibInterface.o obj/FileParser.o obj/xmlinterp.o
	g++ ${LDFLAGS} -o interp  obj/main.o obj/LibInterface.o obj/FileParser.o obj/xmlinterp.o -ldl -lxerces-c

obj/main.o: src/main.cpp inc/Interp4Command.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/LibInterface.o: inc/LibInterface.hh inc/Interp4Command.hh src/LibInterface.cpp
	g++ -c ${CPPFLAGS} -o obj/LibInterface.o src/LibInterface.cpp

obj/FileParser.o: src/FileParser.cpp inc/FileParser.hh
	g++ -c ${CPPFLAGS} -o obj/FileParser.o src/FileParser.cpp

obj/Scene.o: src/Scene.cpp inc/Scene.hh
	g++ -c ${CPPFLAGS} -o obj/Scene.o src/Scene.cpp

obj/xmlinterp.o: src/xmlinterp.cpp inc/xmlinterp.hh
	g++ -c ${CPPFLAGS} -o obj/xmlinterp.o src/xmlinterp.cpp


clean:
	rm -f obj/* interp core*

clean_plugin:
	cd plugin; make clean

cleanall: clean
	cd plugin; make cleanall
	cd dox; make cleanall
	rm -f libs/*
	find . -name \*~ -print -exec rm {} \;

help:
	@echo
	@echo "  Lista podcelow dla polecenia make"
	@echo 
	@echo "        - (wywolanie bez specyfikacji celu) wymusza"
	@echo "          kompilacje i uruchomienie programu."
	@echo "  clean    - usuwa produkty kompilacji oraz program"
	@echo "  clean_plugin - usuwa plugin"
	@echo "  cleanall - wykonuje wszystkie operacje dla podcelu clean oraz clean_plugin"
	@echo "             oprocz tego usuwa wszystkie kopie (pliki, ktorych nazwa "
	@echo "             konczy sie znakiem ~)."
	@echo "  help  - wyswietla niniejszy komunikat"
	@echo
	@echo " Przykladowe wywolania dla poszczegolnych wariantow. "
	@echo "  make           # kompilacja i uruchomienie programu."
	@echo "  make clean     # usuwa produkty kompilacji."
	@echo
 
