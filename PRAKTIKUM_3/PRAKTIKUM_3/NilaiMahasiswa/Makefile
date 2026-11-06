CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude
TARGET = NilaiMahasiswa
SRCS = src/main.cpp src/Mahasiswa.cpp src/MataKuliah.cpp src/NilaiMK.cpp src/KHS.cpp src/Pembayaran.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe

.PHONY: all run clean
