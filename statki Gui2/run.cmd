g++ -c main.cpp -c display.cpp -c code.cpp -DSFML_STATIC -IC:\SFML\include 
g++ -o statkiRUN main.o -static -LC:/SFML/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype 
start statkiRUN.exe