#include <iostream>
#include "Queues.h"

int main() {
    AQueue a;  //AQueue has been written to only support strings, ints, and doubles, but supporting other atomic data types should also be written in
    void *ptr;
    string b = "and", c = "the";
    int x = 1, y = 2;
    double z = 3.4, w = 4.6;

    a.enqueue(&x,"int");
    a.enqueue(&y,"int");
    a.enqueue(&z,"double");
    a.enqueue(&w,"double");
    a.enqueue(&b,"string");
    a.enqueue(&c,"string");

    std::cout << "Size: " << a.length() << std::endl;

    for (int i = 0; i < 6; i++){
        a.dequeue();
    }

    std::cout << "Size: " << a.length() << std::endl;

    return 0;
}
