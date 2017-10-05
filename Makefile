CPP=g++
CPPFLAGS=`perl -MExtUtils::Embed -e ccopts -e ldopts`

trabalho3:
	$(CPP) trabalho3.cpp trabalho3-principal.cpp -o Trabalho3 $(CPPFLAGS)

clean:
	rm -vf Trabalho3 *.o