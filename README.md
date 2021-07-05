# Threaded-Selection-Sort
Implementation of threads for comparing threaded selectionSort and regular selectionSort 
## Approach
I wanted to compare the speed increase of a poor sorting algorithm with one that had the implementation of using threads. I chose the simple selectionSort algorithm because its O(n^2) average complexity makes it easy to compare, plus it is a very simple algorithm to understand. With some notable helper functions like createRandomVec() the rest was up to the threaded implementation of selectionSort.
 
### Implementation
For sorting algorithms, the best way to parallelize the task is to partition out the array and give each thread a partition to process. This method ensures that there is no need for mutual exclusion, as no threads overlap each other's memory partition. For this implementation, there are just two threads, each thread taking care of the first and second half of the array respectively. This speeds up the sorting immensely, especially as selectionSort is O(n^2), splitting the work and array amongst two threads can exponentially lower the processing time.
 
### Other Thoughts / What I would expand on
Right now, while the way I implemented works correctly and shows a large decrease in processing time, my implementation is somewhat restricted. As of now, this implementation only utilizes two threads. Modularizing the implementation for the thread count of the user system would be ideal (for much larger sorting calculations). Which leads to the use of std::merge() function used for merging the two sorted partitions that were processed by the threads. The merge() function requires an output vector to write the two vector partitions. This doubles the required space complexity of the program.