#
# Sample makefile updated to include the commands to run the Clang Static Analyzer
#
#    scan-build will "make" your program and run CSA at the same time.
#
#    scan-view will do a scan-build (if necessary) and then open a web browser
#      window to review the results.
#
CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = 537make
SCAN_BUILD_DIR = scan-build-out

all: main.o parsing1.o graphBuilder.o runTarget.o checkCycles.o cmdLine.o
	$(CC) -o $(EXE) main.o parsing1.o graphBuilder.o runTarget.o checkCycles.o cmdLine.o

main.o: main.c parsing1.h
	$(CC) $(WARNING_FLAGS) -c main.c
parsing1.o: parsing1.c parsing1.h graphBuilder.h
	$(CC) $(WARNING_FLAGS) -c parsing1.c
graphBuilder.o: graphBuilder.c graphBuilder.h
	$(CC) $(WARNING_FLAGS) -c graphBuilder.c
runTarget.o: runTarget.c runTarget.h
	$(CC) $(WARNING_FLAGS) -c runTarget.c
checkCycles.o: checkCycles.c checkCycles.h
	$(CC) $(WARNING_FLAGS) -c checkCycles.c
cmdLine.o: cmdLine.c cmdLine.h
	$(CC) $(WARNING_FLAGS) -c cmdLine.c
clean:
	rm -f $(EXE) *.o
	rm -rf $(SCAN_BUILD_DIR)

#
# Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
# View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html 

