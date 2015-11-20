all: clean main

main:
	g++ lib/util.cc lib/request.cc lib/router.cc lib/http.cc main.cc -o bin/main
	./run

clean:
	rm -f *.a *.o main bin/*.*
