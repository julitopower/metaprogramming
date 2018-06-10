#include <iostream>
#include <string>
#include <cassert>

#include "type_list.hpp"

void my_assert(bool assertion) {
    assert(assertion);
}

int main(int argc, char** argv) {
    std::cout << "01 Type list example" << std::endl;

    using MyType = TypeList<int, char, double, std::string>;
    my_assert(is_same_type<std::string, type_at<3, MyType>::type>::value);
    my_assert(is_same_type<int, int>::value);
    my_assert(!is_same_type<int, bool>::value);
    my_assert(contains<int, MyType>::value);
    my_assert(!contains<unsigned int, MyType>::value);
    std::string s {"Bla"};
    my_assert(contains<decltype(s), MyType>::value);

}
