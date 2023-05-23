#include <iostream>
#include <chrono>

using namespace std;

void iteration(int n)
{
    for (int i = 0; i < 10; i++)
    {
        i += 1;   
    }

    cout << endl;
}

int main(int argc, char const *argv[])
{
    auto begin = std::chrono::high_resolution_clock::now();

    iteration(1);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    cout << "Execution time: " << elapsed.count() << " Miliseconds";

    return 0;
}
