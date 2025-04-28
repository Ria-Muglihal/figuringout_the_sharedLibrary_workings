compiling steps:

g++ -o silcontroller silcontroller.cpp -ldl -g -lpthread
g++ -std=c++11 -fPIC -shared -o vecutasks.so vecutasks.cpp -g
g++ -fPIC -shared -o vecu.so vecu.cpp -ldl -g
g++ -fPIC -shared -o fmuwrapper.so fmuwrapper.cpp -ldl -g
