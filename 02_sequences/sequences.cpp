#include <iostream>

#include "sequences.hpp"


int main(int argc, char** argv) {
    std::cout << "02 Template integer sequence generation" << std::endl;
    printSequence(sequence_gen<100>::type{});
    std::cout << std::endl;
    printSequence(sequence_gen<10>::type{});
    std::cout << std::endl;
}
