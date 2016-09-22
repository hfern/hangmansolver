CXX ?= g++
STD ?= c++11
SOURCES = $(wildcard *.cpp)
OUTPUT ?= hmsolv

build:
	$(CXX) -std=$(STD) -o $(OUTPUT) $(SOURCES) 

