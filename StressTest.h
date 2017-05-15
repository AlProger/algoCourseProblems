// In progress

#include <iostream>
#include <vector>
#include <functional>
#include <cstdlib>

class StressTest {
private:
   int size = 0;
   size_t defaultSize = 100;
   int MaxNumber = 1000;
   std::vector<int> array;
   int times = _NULL;
   int third_param = _NULL;
public:
   StressTest() {
       size = rand() % defaultSize + 2;
       array.reserve(size);
       for (size_t i = 0; i != size; ++i) {
           array.push_back(rand() % MaxNumber);
       }
   }

   StressTest(int _third_param) : third_param(_third_param) {
       size = rand() % defaultSize + 2;
       array.reserve(size);
       for (size_t i = 0; i != size; ++i) {
           array.push_back(rand() % MaxNumber);
       }
   }

   StressTest(int _third_param, int _size) : third_param(_third_param), size(_size) {
       array.reserve(size);
       for (size_t i = 0; i != size; ++i) {
           array.push_back(rand() % MaxNumber);
       }
   }

   StressTest(int _third_param, int _size, int _times) : third_param(_third_param), size(_size), times(_times) {
       array.reserve(size);
       for (size_t i = 0; i != size; ++i) {
           array.push_back(rand() % MaxNumber);
       }

   }

   StressTest operator()() {}

   template<typename Func>
   void test(const Func &func1, const Func &func2) {
       while (true && third_param != _NULL) {
           for (int i = 0; i < size; ++i) {
               std::cout << array[i] << ' ';
           }
           std::cout << "\n";
           auto res1 = func1(array.begin(), array.end() - 1, (array.size() - 1) / 2 + 1);
           auto res2 = func2(array.begin(), array.end() - 1, (array.size() - 1) / 2 + 1);
           if (res1 != res2) {
               std::wcout << "Wrong result: " << res1 << " " << res2 << "\n";
               break;
           } else {
               std::cout << "OK\n";
           }
       }
   }

};
