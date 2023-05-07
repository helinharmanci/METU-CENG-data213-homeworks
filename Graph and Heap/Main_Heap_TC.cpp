#include "BinaryHeap.h"
#include "MeshGraph.h"
#include "ObjLoader.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <cfloat>
#include <cstdio>
#include <cstdlib>

void PrintElements(const std::vector<HeapElement>& v)
{
    std::cout << "[";
    for(int i = 0; i < static_cast<int>(v.size()); i++)
    {
        std::cout << "{" << v[i].uniqueId << ", "
                  << std::setprecision(5) << v[i].weight << "}";

        if(i != static_cast<int>(v.size() - 1))
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

class HW3Tester
{
    private:
    // Use heap to prevent access
    std::vector<int> pts;

    template <class T>
    void CHECK_RESULT(T result, T expected, int point, const std::string& s)
    {
        //std::cout << "Val: " << outId < ;
        //std::cout << "W : " << outWeight;
        if(result == expected)
        {
            std::cout << "OK" << std::endl;
            pts.back() += point;
        }
        else
        {
            std::cout << "Expected " << expected
                      << " but result is " << result
                      << " in " << s << std::endl;
        }
    }

    template <class T>
    bool CheckTArray(const std::vector<T>& expected,
                     const std::vector<T>& found)
    {
        if(expected.size() != found.size())
        {
            std::printf("Size mismatch, Expected %lu, Found %lu\n",
                        expected.size(), found.size());
            return false;
        }

        for(size_t i = 0; i < expected.size(); i++)
        {
            if(expected[i] != found[i])
            {
                std::printf("index[%lu] Mismatch: Expected[%f] Found [%f]\n",
                            i, expected[i], found[i]);
                return false;
            }
        }
        return true;
    }

    public:

    int TotalPts() const
    {
        return std::accumulate(pts.begin(), pts.end(), 0);
    }
    int MaxPts() const
    {
        return 25;
    }

    // Add - Remove (Single) (3)
    void TestCase1()
    {
        pts.push_back(0);

        BinaryHeap h;
        //std::cout << "Adding {1, 3.4}" << std::endl;

        // Add & Pop
        h.Add(1, 3.4);
        int outId = -1;
        double outWeight = FLT_MAX;
        bool success = h.PopHeap(outId, outWeight);

        CHECK_RESULT(outId, 1, 1, "TestCase1 Add - Remove (Single)");
        CHECK_RESULT(outWeight, 3.4, 1, "TestCase1 Add - Remove (Single)");
        CHECK_RESULT(success, true, 1, "TestCase1 Add - Remove (Single)");
    }

    // Add - HeapSize  (3)
    void TestCase2()
    {
        pts.push_back(0);
        BinaryHeap h;

        CHECK_RESULT(h.HeapSize(), 0, 1, "TestCase2 Add - HeapSize");
        //std::cout << "Adding {1, 3.4}" << std::endl;
        h.Add(2, 3.4);
        CHECK_RESULT(h.HeapSize(), 1, 1, "TestCase2 Add - HeapSize");

        //std::cout << "Adding {10, 9.9}" << std::endl;
        h.Add(10, 9.9);
        CHECK_RESULT(h.HeapSize(), 2, 1, "TestCase2 Add - HeapSize");

    }

    // Add non-unique() (5)
    void TestCase3()
    {
        pts.push_back(0);
        BinaryHeap h;

        CHECK_RESULT(h.HeapSize(), 0, 1, "TestCase3 Add Non-Unique");
        //std::cout << "Adding {77, 2.4}" << std::endl;
        bool addResult = h.Add(77, 3.4);
        CHECK_RESULT(h.HeapSize(), 1, 1, "TestCase3 Add Non-Unique");
        CHECK_RESULT(addResult, true, 1, "TestCase3 Add Non-Unique");

        //std::cout << "Adding {77, 9.9}" << std::endl;
        addResult = h.Add(77, 9.9);
        CHECK_RESULT(h.HeapSize(), 1, 1, "TestCase3 Add Non-Unique");
        CHECK_RESULT(addResult, false, 1, "TestCase3 Add Non-Unique");
    }

    // Add - Remove (But try to remove more) (6)
    void TestCase4()
    {
        pts.push_back(0);
        BinaryHeap h;

        int ids[10]        = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        double weights[10] = { 1, 2, 3, 5, 6, 4, 3, 2, 1, 0};

        for(int i = 0; i < 10; i++)
        {
            h.Add(ids[i], weights[i]);
        }
        for(int i = 0; i < 8; i++)
        {
            int outId;
            double outWeight;
            h.PopHeap(outId, outWeight);
        }

        int outId;
        double outWeight;
        bool result = h.PopHeap(outId, outWeight);
        CHECK_RESULT(outId, 7, 1, "TestCase4 Add - Remove (But try to remove more)");
        CHECK_RESULT(outWeight, 5.0, 1, "TestCase4 Add - Remove (But try to remove more)");
        //CHECK_RESULT(result, true, 1, "TestCase4 Add - Remove (But try to remove more)");

        result = h.PopHeap(outId, outWeight);
        CHECK_RESULT(outId, 6, 1, "TestCase4 Add - Remove (But try to remove more)");
        CHECK_RESULT(outWeight, 6.0, 1, "TestCase4 Add - Remove (But try to remove more)");
        CHECK_RESULT(result, true, 1, "TestCase4 Add - Remove (But try to remove more)");

        result = h.PopHeap(outId, outWeight);
        CHECK_RESULT(result, false, 1, "TestCase4 Add - Remove (But try to remove more)");
    }

    // Change Priority (6)
    void TestCase5()
    {
        pts.push_back(0);
        BinaryHeap h;

        int ids[10]         = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        double weights[10]  = { 1, 2, 3, 5, 6, 4, 3, 2, 1, 0};

        for(int i = 0; i < 10; i++)
        {
            h.Add(ids[i], weights[i]);
        }

        int outId;
        double outWeight;
        bool result = h.ChangePriority(6, -1.0);
        CHECK_RESULT(result, true, 1, "TestCase5 Change Priority");
        h.PopHeap(outId, outWeight);
        CHECK_RESULT(outId, 6, 1, "TestCase5 Change Priority");
        CHECK_RESULT(outWeight, -1.0, 1, "TestCase5 Change Priority");


        // Check bubble down now
        result = h.ChangePriority(1, 10.0);
        CHECK_RESULT(result, true, 1, "TestCase5 Change Priority");
        while(h.PopHeap(outId, outWeight));

        CHECK_RESULT(outId, 1, 1, "TestCase5 Change Priority");
        CHECK_RESULT(outWeight, 10.0, 1, "TestCase5 Change Priority");
    }

    // Change Priority Non-unique (2)
    void TestCase6()
    {
        pts.push_back(0);

        int ids[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        double weights[10] = {1, 2, 3, 5, 6, 4, 3, 2, 1, 0};

        BinaryHeap h;
        for(int i = 0; i < 10; i++)
        {
            h.Add(ids[i], weights[i]);
        }

        bool result = h.ChangePriority(999, 2.0f);
        CHECK_RESULT(result, false, 1, "TestCase6 Change Priority Not Found");

        h.Add(999, 2.0f);
        result = h.ChangePriority(999, 20000.0f);
        CHECK_RESULT(result, true, 1, "TestCase6 Change Priority Not Found");
    }

    // EXTRA TC 1 Stress Test (10)
    void TestCase7()
    {
        pts.push_back(0);
        // Check
        static const size_t HEAP_ELEMENT_COUNT = 5000;
        // Seed the RNG
        std::srand(0);

        std::vector<double> expected;

        BinaryHeap h;
        for(size_t i = 0; i < HEAP_ELEMENT_COUNT; i++)
        {
            double weight = static_cast<double>(std::rand()) / RAND_MAX;
            h.Add(static_cast<int>(i), weight);
            expected.push_back(weight);
        }
        std::sort(expected.begin(), expected.end());

        std::vector<double> found;
        double w;
        int id;
        while(h.PopHeap(id, w) > 0)
        {
            found.push_back(w);
        }

        bool allOK = CheckTArray(expected, found);
        if (allOK)
        {
            printf("OK\n");
            pts.back() = 10;
        }
    }
};

int main(int argv, const char* argc[])
{
    typedef void (HW3Tester::*TestFuncs)() ;

    HW3Tester t;
    TestFuncs tests[] =
    {
        &HW3Tester::TestCase1,
        &HW3Tester::TestCase2,
        &HW3Tester::TestCase3,
        &HW3Tester::TestCase4,
        &HW3Tester::TestCase5,
        &HW3Tester::TestCase6,
        &HW3Tester::TestCase7
    };

	// COMMENT THIS and uncomment lower part for full test
    int i = std::atoi(argc[1]);

    std::cout << "TC" << (i) << std::endl;
    (t.*tests[i-1])();
    std::printf("%d\n", t.TotalPts());

    // std::cout << "TC1" << std::endl;
    // t.TestCase1();
    // std::cout << "TC2" << std::endl;
    // t.TestCase2();
    // std::cout << "TC3" << std::endl;
    // t.TestCase3();
    // std::cout << "TC4" << std::endl;
    // t.TestCase4();
    // std::cout << "TC5" << std::endl;
    // t.TestCase5();
    // std::cout << "TC6" << std::endl;
    // t.TestCase6();
}
