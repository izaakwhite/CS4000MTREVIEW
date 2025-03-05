# Makefile for compiling semaphore and deadlock examples

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Werror

# Targets
TARGETS = semaphore.out dl_p.out dl_cpp.out dl_omp.out barrier.out

# Default target
all: $(TARGETS)

# Semaphore target
semaphore.out: semaphore.cc
	$(CXX) $(CXXFLAGS) -pthread $^ -o $@

# Deadlock pthread target
dl_p.out: deadlock_pthread.cc
	$(CXX) $(CXXFLAGS) -pthread $^ -o $@

# Deadlock C++ threads target
dl_cpp.out: deadlock_cppthreads.cc
	$(CXX) $(CXXFLAGS) -pthread $^ -o $@

# Deadlock OpenMP target
dl_omp.out: deadlock_omp.cc
	$(CXX) $(CXXFLAGS) -fopenmp $^ -o $@

barrier.out: barrier.cc
	$(CXX) $(CXXFLAGS) -fopenmp $^ -o $@
# Clean target to remove generated files
clean:
	rm -f $(TARGETS)
