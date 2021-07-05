#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <chrono>
#include <random>
#include <ctime>
#include <mutex>
using namespace std;

void createRandomVec(vector<int>& vec, int& size);
void displayVector(vector<int>& vec);
void nonThreadedsort(vector<int>& vec);
void threadedSort(vector<int>& vec);
void bubbleSort(vector<int>& vec);
void swap(int *xp, int *yp);
void displayTime(std::chrono::system_clock::time_point& start, std::chrono::system_clock::time_point& end);
mutex mu;

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
void selectionSort(vector<int>& vec)
{
    int i, j, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < vec.size()-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < vec.size(); j++)
        if (vec[j] < vec[min_idx])
            min_idx = j;
 
        // Swap the found minimum element with the first element
        swap(&vec[min_idx], &vec[i]);
    }
}

void threadSelectionSort(vector<int>& vec, int start, int end)
{
    int i, j, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = start; i < end-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < end; j++)
        if (vec[j] < vec[min_idx])
            min_idx = j;   
        swap(&vec[min_idx], &vec[i]); // Swap the found minimum element with the first element      
    }
}

int main()
{
    vector<int> vec;
    vector<int> vec2;
    int size = 1;
    cout << "enter in the size\n";
    cin >> size;
    int size2 = size;

//----Setup-------
    createRandomVec(vec,size);
    createRandomVec(vec2,size2);
//----------------

    nonThreadedsort(vec);
    threadedSort(vec2);

    //displayVector(vec);
    //displayVector(vec2);

    return 0;
}

void threadedSort(vector<int>& vec)
{
    const unsigned int threadCount = 2;
    vector<thread> t_vec;
    bool isOdd = false;

    if(vec.size()%2 != 0)
        isOdd = true;

    int partition = vec.size() / threadCount;
    int vecStart = 0;
    int vecEnd = partition;
    vector<int> out(vec.size(),0);


//------sort------
    auto start = std::chrono::system_clock::now();
        for(int i = 0; i < threadCount; ++i)
        {
            t_vec.emplace_back(threadSelectionSort, ref(vec), vecStart, vecEnd);
            vecStart += partition;
            vecEnd += partition;
            if(isOdd && i+2 == threadCount)
                vecEnd++;
        }
        for(auto &i : t_vec)
            i.join();

        merge(vec.begin(),vec.begin()+partition,vec.begin()+partition,vec.end(),out.begin());
        vec = move(out);
    auto end = std::chrono::system_clock::now();
//---------------

//---displaytime--
    displayTime(start,end);
//----------------
}

void nonThreadedsort(vector<int>& vec)
{
//------sort------
auto start = std::chrono::system_clock::now();
    selectionSort(vec);
auto end = std::chrono::system_clock::now();
//----------------


//---displaytime--
    displayTime(start,end);
//----------------

}

/*
creates a vector with a specified size with values from 1 to size and shuffles the contents;
used for sorting
*/
void createRandomVec(vector<int>& vec, int& size)
{
    for(int i = 1; i <= size; ++i)
        vec.push_back(i);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(vec.begin(), vec.end(), std::default_random_engine(seed));
}

void displayVector(vector<int>& vec)
{
    for(auto &i : vec)
        cout << i << endl;
}


/*
Displays the time between the start and end intervals passed; used for calculating processing time of code
*/
void displayTime(std::chrono::system_clock::time_point& start, std::chrono::system_clock::time_point& end)
{
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
}