#include <iostream>
#include <vector>

#include "accumulte.hpp"

int main() {
    size_t n = 1000;
    std::vector<int> array(n);
    for(size_t i = 0; i < n; ++i) {
        array[i] = i + 1;
    }
    std::cout << "sum = " << parallel_accumulate(array.begin(), array.end(), 0) << std::endl;
    return 0;
}
