#ifndef ACCUMULTE_HPP
#define ACCUMULTE_HPP

#include <algorithm>
#include <numeric>
#include <thread>
#include <vector>

template<typename Iterator, typename T>
struct accumulate_block
{
    void operator()(Iterator first, Iterator last, T& result) {
        result = std::accumulate(first, last, result);
    }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
    const unsigned long length = std::distance(first, last);
    if (!length) {
        return init;
    }

    const unsigned long minPerThread = 25;
    const unsigned long maxThreads = (length + minPerThread - 1) / minPerThread;

    const unsigned long hardwareThreads = std::thread::hardware_concurrency();
    const unsigned long numThreads =
            std::min(hardwareThreads != 0 ? hardwareThreads : 2, maxThreads);

    const unsigned long blockSize = length / numThreads;

    std::vector<T> results(numThreads);
    std::vector<std::thread> threads(numThreads - 1);

    Iterator blockStart = first;
    for(unsigned long i = 0; i < (numThreads - 1); ++i) {
        Iterator blockEnd = blockStart;
        std::advance(blockEnd, blockSize);
        threads[i] = std::thread(
                    accumulate_block<Iterator, T>(),
                    blockStart, blockEnd, std::ref(results[i]));
        blockStart = blockEnd;
    }
    accumulate_block<Iterator, T>()(blockStart, last, results[numThreads - 1]);

    std::for_each(threads.begin(), threads.end(),
                  std::mem_fn(&std::thread::join));

    return std::accumulate(results.begin(), results.end(), init);
}

#endif // ACCUMULTE_HPP
