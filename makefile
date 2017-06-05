CXX = g++
CXXFLAGS = -std=c++11
FILES = mandelbrot.cpp main.cpp
LIBS = -lGL -lGLU -lglut -lglfw3 -lX11 -lXxf86vm -lXrandr -pthread -lXi -ldl -lXinerama -lXcursor
OBJECTS = $(FILES:%.cpp=%.o)

.PHONY : all
all : $(OBJECTS)
	@ $(CXX) $(CXXFLAGS) $^ -o mandelbrot $(LIBS)
	@ ./mandelbrot
	@ rm $(OBJECTS) mandelbrot

.SILENT : $(OBJECTS)
$(OBJECTS) :

clean :
	@ rm $(OBJECTS) mandelbrot
