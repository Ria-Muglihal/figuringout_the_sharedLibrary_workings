The sample app and libraries are created to verify the behaviour of a shared library when opened with dlmopen (into a new namespace) and how
its working affect at runtime.

compiling steps:

g++ -o silcontroller silcontroller.cpp -ldl -g -lpthread
g++ -std=c++11 -fPIC -shared -o vecutasks.so vecutasks.cpp -g
g++ -fPIC -shared -o vecu.so vecu.cpp -ldl -g
g++ -fPIC -shared -o fmuwrapper.so fmuwrapper.cpp -ldl -g

mkdir -p build;
g++ -o build/launchApp launchApp.cpp -ldl -g -pthread -m32;
g++ -o build/silcontroller silcontroller.cpp -ldl -g -pthread -m32;
g++ -fPIC -shared -o build/vecu.so vecu.cpp -ldl -g -m32 -pthread;
g++ -fPIC -shared -o build/fmuwrapper.so fmuwrapper.cpp -ldl -g -m32;
g++ -std=c++11 -fPIC -shared -o build/vecutasks.so vecutasks.cpp -g -m32;
