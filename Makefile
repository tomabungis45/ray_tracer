render: main.o sphere.o hittable_list.o color.h vec3.o hittable.h rtweekend.h camera.o
	g++ main.o sphere.o vec3.o hittable_list.o camera.o -o render

camera.o: camera.h camera.cpp
	g++ -c camera.cpp

hittable_list.o: hittable.h hittable_list.h hittable_list.cpp sphere.o vec3.o interval.h
	g++ -c hittable_list.cpp 

sphere.o: sphere.cpp vec3.o ray.h interval.h
	g++ -c sphere.cpp 

vec3.o: vec3.cpp vec3.h 
	g++ -c vec3.cpp

clean: 
	rm *.o render
	