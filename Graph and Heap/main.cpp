#include "BinaryHeap.h"
#include "MeshGraph.h"
#include "ObjLoader.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <cstdio>
#include <fstream>
#include <sstream>

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

    void ReadExpectedColors(std::vector<Color>& outColors,
                            const std::string& fName)
    {
        std::ifstream colorFile(fName.c_str());
        if(!colorFile)
        {
            std::cout << "Unable to Open " << fName << std::endl;
            return;
        }

        std::string line;
        while(std::getline(colorFile, line))
        {
            // Each line has a single color
            unsigned int rgb[3] = {};
            std::stringstream ss(line);
            std::string v;
            int j = 0;
            while(std::getline(ss, v, ','))
            {
                std::stringstream c(v);
                c >> rgb[j];
                j++;
            }

            Color c;
            c.r = static_cast<unsigned char>(rgb[0]);
            c.g = static_cast<unsigned char>(rgb[1]);
            c.b = static_cast<unsigned char>(rgb[2]);
            outColors.push_back(c);
        }
    }

    bool CheckColorArray(const std::vector<Color>& expected,
                         const std::vector<Color>& colors)
    {
        if(expected.size() != colors.size())
        {
            std::printf("Size mismatch, Expected %lu, Found %lu\n",
                        expected.size(), colors.size());
            return false;
        }

        for(size_t i = 0; i < colors.size(); i++)
        {
            if(expected[i].r != colors[i].r ||
               expected[i].g != colors[i].g ||
               expected[i].b != colors[i].b)
            {
                std::printf("index[%lu] Mismatch: Expected[%d, %d, %d] Found [%d, %d, %d]\n",
                            i,
                            static_cast<int>(expected[i].r),
                            static_cast<int>(expected[i].g),
                            static_cast<int>(expected[i].b),
                            static_cast<int>(colors[i].r),
                            static_cast<int>(colors[i].g),
                            static_cast<int>(colors[i].b));
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
        return 50;
    }

    void TestCase1();
    void TestCase2();
    void TestCase3();
    void TestCase4();
    void TestCase5();
    void TestCase6();
    void TestCase7();
    void TestCase8();
    void TestCase9();
    void TestCase10();
};

template <>
void HW3Tester::CHECK_RESULT(double result, double expected, int point, const std::string& s)
{
    static const double EPSILON = 0.0001;
    if(std::abs(result - expected) < EPSILON)
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

// Constructor & Avg Distance between vertices (6)
void HW3Tester::TestCase1()
{
    pts.push_back(0);
    ObjLoader loader;
    {
        const std::string FILE_NAME = "plane-low.obj";
        printf("Checking AverageEdgePerVertex of %s\n",
                FILE_NAME.c_str());
        loader.LoadObjFile(FILE_NAME);
        MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
        double d = g.AverageDistanceBetweenVertices();
        CHECK_RESULT(d, 3.0, 1, "TestCase 1 AverageDistanceBetweenVertices()");
    }
    {
        const std::string FILE_NAME = "plane.obj";
        printf("Checking AverageEdgePerVertex of %s\n",
                FILE_NAME.c_str());
        loader.LoadObjFile(FILE_NAME);
        MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
        double d = g.AverageDistanceBetweenVertices();
        CHECK_RESULT(d, 0.75, 1, "TestCase 1 AverageDistanceBetweenVertices()");
    }
    {
        const std::string FILE_NAME = "man-low.obj";
        printf("Checking AverageEdgePerVertex of %s\n",
                FILE_NAME.c_str());
        loader.LoadObjFile(FILE_NAME);
        MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
        double d = g.AverageDistanceBetweenVertices();
        CHECK_RESULT(d, 1.83508, 2, "TestCase 1 AverageDistanceBetweenVertices()");
    }
    {
        const std::string FILE_NAME = "facem-low2.obj";
        printf("Checking AverageEdgePerVertex of %s\n",
                FILE_NAME.c_str());
        loader.LoadObjFile(FILE_NAME);
        MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
        double d = g.AverageDistanceBetweenVertices();
        CHECK_RESULT(d, 1.75865, 2, "TestCase 1 AverageDistanceBetweenVertices()");
    }
}

// AverageEdgePerVertex (3)
void HW3Tester::TestCase2()
{
    pts.push_back(0);
    ObjLoader loader;
    {
        const std::string FILE_NAME = "plane-low.obj";
        printf("Checking AverageEdgePerVertex of %s\n",
                FILE_NAME.c_str());
        loader.LoadObjFile(FILE_NAME);
        MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
        double d = g.AverageEdgePerVertex();
        CHECK_RESULT(d, 1.66667, 1, "TestCase 2 AverageEdgePerVertex()");
    }
    {
        const std::string FILE_NAME = "plane.obj";
        printf("Checking AverageEdgePerVertex of %s\n",
                FILE_NAME.c_str());
        loader.LoadObjFile(FILE_NAME);
        MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
        double d = g.AverageEdgePerVertex();
        CHECK_RESULT(d, 1.90476, 1, "TestCase 2 AverageEdgePerVertex()");
    }
    {

        const std::string FILE_NAME = "man-low.obj";
        printf("Checking AverageEdgePerVertex of %s\n",
                FILE_NAME.c_str());
        loader.LoadObjFile(FILE_NAME);
        MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
        double d = g.AverageEdgePerVertex();
        CHECK_RESULT(d, 2.97222, 1, "TestCase 2 AverageEdgePerVertex()");
    }
}

// Total Vertex and Total Edge Count(2)
void HW3Tester::TestCase3()
{
    pts.push_back(0);
    ObjLoader loader;
    {
        const std::string FILE_NAME = "plane-low.obj";
        printf("Checking TotalVertexCount and TotalEdgeCount of %s\n",
                FILE_NAME.c_str());
        loader.LoadObjFile(FILE_NAME);
        MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
        int vc = g.TotalVertexCount();
        CHECK_RESULT(vc, 36, 1, "TestCase 3 TotalVertexCount()");
        int ec = g.TotalEdgeCount();
        CHECK_RESULT(ec, 60, 1, "TestCase 3 TotalEdgeCount()");
    }
    //{
    //    const std::string FILE_NAME = "man-low.obj";
    //    printf("Checking TotalVertexCount and TotalEdgeCount of %s\n",
    //           FILE_NAME.c_str());
    //    loader.LoadObjFile(FILE_NAME);
    //    MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
    //    int vc = g.TotalVertexCount();
    //    CHECK_RESULT(vc, 252, 1, "TestCase 3 TotalVertexCount()");
    //    int ec = g.TotalEdgeCount();
    //    CHECK_RESULT(ec, 749, 1, "TestCase 3 TotalEdgeCount()");
    //}
}

// Vertex Edge Count (4)
void HW3Tester::TestCase4()
{
    pts.push_back(0);
    ObjLoader loader;
    {
        const int VERTEX_ID = 2;
        const std::string FILE_NAME = "plane-low.obj";
        printf("Checking VertexEdgeCount of %s, with vertexId %d\n",
                FILE_NAME.c_str(), VERTEX_ID);
        loader.LoadObjFile(FILE_NAME);
        MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
        int ec = g.VertexEdgeCount(VERTEX_ID);
        CHECK_RESULT(ec, 3, 1, "TestCase 4 VertexEdgeCount()");
        printf("Checking edge case...\n");
        ec = g.VertexEdgeCount(-2);
        CHECK_RESULT(ec, -1, 1, "TestCase 4 VertexEdgeCount()");
    }
    {
        const int VERTEX_ID = 220;
        const std::string FILE_NAME = "man-low.obj";
        printf("Checking VertexEdgeCount of %s, with vertexId %d\n",
                FILE_NAME.c_str(), VERTEX_ID);
        loader.LoadObjFile(FILE_NAME);
        MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
        int ec = g.VertexEdgeCount(VERTEX_ID);
        CHECK_RESULT(ec, 6, 1, "TestCase 4 VertexEdgeCount()");
        printf("Checking edge case...\n");
        ec = g.VertexEdgeCount(50000);
        CHECK_RESULT(ec, -1, 1, "TestCase 4 VertexEdgeCount()");
    }
}

// ImmediateNeighbours (5)
void HW3Tester::TestCase5()
{
    pts.push_back(0);
    ObjLoader loader;
    {
        const int VERTEX_ID = 8;
        const std::string FILE_NAME = "plane-low.obj";
        printf("Checking ImmNeighbours of %s, with vertexId %d\n",
                FILE_NAME.c_str(), VERTEX_ID);
        loader.LoadObjFile(FILE_NAME);
        MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
        std::vector<int> outIds;
        g.ImmediateNeighbours(outIds, VERTEX_ID);
        std::sort(outIds.begin(), outIds.end());
        int expected[4] = {2, 7, 9, 14};
        CHECK_RESULT<size_t>(outIds.size(), 4, 1, "TestCase 5 ImmediateNeighbours()");
        for(int i = 0; i < 4; i++)
        {
            CHECK_RESULT(outIds[i], expected[i], 1,
                            "TestCase 5 ImmediateNeighbours()");
        }
    }
    //{
    //    const int VERTEX_ID = 129;
    //    const std::string FILE_NAME = "man-low.obj";
    //    printf("Checking ImmNeighbours of %s, with vertexId %d\n",
    //           FILE_NAME.c_str(), VERTEX_ID);
    //    loader.LoadObjFile(FILE_NAME);
    //    MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
    //    std::vector<int> outIds;
    //    g.ImmediateNeighbours(outIds, VERTEX_ID);
    //    std::sort(outIds.begin(), outIds.end());
    //    int expected[5] = {122, 125, 127, 128, 134};
    //    CHECK_RESULT(outIds.size(), 5ull, 1, "TestCase 5 ImmediateNeighbours()");
    //    for(int i = 0; i < 5; i++)
    //    {
    //        CHECK_RESULT(outIds[i], expected[i], 1,
    //                     "TestCase 5 ImmediateNeighbours()");
    //    }
    //}
}

// PaintInBetweenVertex (10)
void HW3Tester::TestCase6()
{
    pts.push_back(0);
    ObjLoader loader;
    {
        const int VERTEX_ID_FROM = 138;
        const int VERTEX_ID_TO = 24;
        const Color c = {255, 0, 0};
        const std::string FILE_NAME = "facem-low2.obj";
        printf("Checking PaintInBetweenVertex of %s, "
                "with from %d and to %d, c:[%d, %d, %d]\n",
                FILE_NAME.c_str(),
                VERTEX_ID_FROM,
                VERTEX_ID_TO, c.r, c.g, c.b);
        loader.LoadObjFile(FILE_NAME);
        MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
        std::vector<Color> outColors;
        g.PaintInBetweenVertex(outColors, VERTEX_ID_FROM,
                                VERTEX_ID_TO, c);

        static const std::string EXPECTED_FILE_NAME = "facem-low2-138-24-RED.txt";
        //MeshGraph::WriteColorToFile(outColors, EXPECTED_FILE_NAME);
        std::vector<Color> expectedColors;
        ReadExpectedColors(expectedColors, EXPECTED_FILE_NAME);

        bool allOK = CheckColorArray(expectedColors, outColors);
        if (allOK)
        {
            printf("OK\n");
            pts.back() = 10;
        }
    }
}

// PaintInRangeGeodesic (10)
void HW3Tester::TestCase7()
{
    pts.push_back(0);
    ObjLoader loader;
    {
        const double ALPHA = 15.0;
        const int MAX_DEPTH = 4;
        const int VERTEX_ID_FROM = 220;
        const Color c = {255, 0, 0};
        const std::string FILE_NAME = "man-low.obj";
        printf("Checking PaintInRangeGeodesic of %s, "
                "with vertex %d, c:[%d, %d, %d], "
                "Gaussian, alpha %f, depth %d\n",
                FILE_NAME.c_str(),
                VERTEX_ID_FROM,
                c.r, c.g, c.b, ALPHA, MAX_DEPTH);
        loader.LoadObjFile(FILE_NAME);
        MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
        std::vector<Color> outColors;
        g.PaintInRangeGeodesic(outColors, VERTEX_ID_FROM, c, MAX_DEPTH, FILTER_GAUSSIAN,
                                ALPHA);

        static const std::string EXPECTED_FILE_NAME = "man-low-220-RED-gauss-alpha15-depth4-Geo.txt";
        //MeshGraph::WriteColorToFile(outColors, EXPECTED_FILE_NAME);
        std::vector<Color> expectedColors;
        ReadExpectedColors(expectedColors, EXPECTED_FILE_NAME);

        bool allOK = CheckColorArray(expectedColors, outColors);
        if (allOK)
        {
            printf("OK\n");
            pts.back() = 10;
        }
    }

    {
        const double ALPHA = 3.0;
        const int MAX_DEPTH = 3;
        const int VERTEX_ID_FROM = 221;
        const Color c = {255, 0, 0};
        const std::string FILE_NAME = "plane.obj";
        printf("Checking PaintInRangeGeodesic of %s, "
                "with vertex %d, c:[%d, %d, %d], "
                "Gaussian, alpha %f, depth %d\n",
                FILE_NAME.c_str(),
                VERTEX_ID_FROM,
                c.r, c.g, c.b, ALPHA, MAX_DEPTH);
        loader.LoadObjFile(FILE_NAME);
        MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
        std::vector<Color> outColors;
        g.PaintInRangeGeodesic(outColors, VERTEX_ID_FROM, c, MAX_DEPTH, FILTER_GAUSSIAN,
                                ALPHA);

        static const std::string EXPECTED_FILE_NAME = "plane-221-RED-gauss-alpha3-depth3-Geo.txt";
        //MeshGraph::WriteColorToFile(outColors, EXPECTED_FILE_NAME);
        std::vector<Color> expectedColors;
        ReadExpectedColors(expectedColors, EXPECTED_FILE_NAME);

        bool allOK = CheckColorArray(expectedColors, outColors);
        if (allOK)
        {
            printf("OK\n");
            pts.back() = 10;
        }
    }
}

// PaintInRangeEuclidian (10)
void HW3Tester::TestCase8()
{
    pts.push_back(0);
    ObjLoader loader;
    {
        const double ALPHA = 7.0;
        const int MAX_DEPTH = 4;
        const int VERTEX_ID_FROM = 220;
        const Color c = {255, 0, 0};
        const std::string FILE_NAME = "man-low.obj";
        printf("Checking PaintInRangeEuclidian of %s, "
                "with vertex %d, c:[%d, %d, %d],"
                "Box, alpha %f, depth %d\n",
                FILE_NAME.c_str(),
                VERTEX_ID_FROM,
                c.r, c.g, c.b, ALPHA, MAX_DEPTH);
        loader.LoadObjFile(FILE_NAME);
        MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
        std::vector<Color> outColors;
        g.PaintInRangeEuclidian(outColors, VERTEX_ID_FROM, c, MAX_DEPTH, FILTER_BOX,
                                ALPHA);

        static const std::string EXPECTED_FILE_NAME = "man-low-220-RED-box-alpha7-depth4-Euc.txt";
        //MeshGraph::WriteColorToFile(outColors, EXPECTED_FILE_NAME);
        std::vector<Color> expectedColors;
        ReadExpectedColors(expectedColors, EXPECTED_FILE_NAME);

        bool allOK = CheckColorArray(expectedColors, outColors);
        if (allOK)
        {
            printf("OK\n");
            pts.back() = 10;
        }
    }
    {
        const double ALPHA = 1.0;
        const int MAX_DEPTH = 3;
        const int VERTEX_ID_FROM = 230;
        const Color c = {255, 0, 0};
        const std::string FILE_NAME = "plane.obj";
        printf("Checking PaintInRangeEuclidian of %s, "
                "with vertex %d, c:[%d, %d, %d], "
                "Gaussian, alpha %f, depth %d\n",
                FILE_NAME.c_str(),
                VERTEX_ID_FROM,
                c.r, c.g, c.b, ALPHA, MAX_DEPTH);
        loader.LoadObjFile(FILE_NAME);
        MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
        std::vector<Color> outColors;
        g.PaintInRangeEuclidian(outColors, VERTEX_ID_FROM, c, MAX_DEPTH, FILTER_GAUSSIAN,
                                ALPHA);

        static const std::string EXPECTED_FILE_NAME = "plane-230-RED-gauss-alpha1-depth3-Euc.txt";
        //MeshGraph::WriteColorToFile(outColors, EXPECTED_FILE_NAME);
        std::vector<Color> expectedColors;
        ReadExpectedColors(expectedColors, EXPECTED_FILE_NAME);

        bool allOK = CheckColorArray(expectedColors, outColors);
        if (allOK)
        {
            printf("OK\n");
            pts.back() = 10;
        }
    }
}

// EXTRA PaintInRangeEuclidian (7)
void HW3Tester::TestCase9()
{
    pts.push_back(0);
    ObjLoader loader;
    {
        const double ALPHA = 2.0;
        const int MAX_DEPTH = 5;
        const int VERTEX_ID_FROM = 35;
        const Color c = {0, 255, 0};
        const std::string FILE_NAME = "man-low.obj";
        printf("Checking PaintInRangeEuclidian of %s, "
                "with vertex %d, c:[%d, %d, %d],"
                "Box, alpha %f, depth %d\n",
                FILE_NAME.c_str(),
                VERTEX_ID_FROM,
                c.r, c.g, c.b, ALPHA, MAX_DEPTH);
        loader.LoadObjFile(FILE_NAME);
        MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
        std::vector<Color> outColors;
        g.PaintInRangeEuclidian(outColors, VERTEX_ID_FROM, c, MAX_DEPTH, FILTER_BOX,
                                ALPHA);

        static const std::string EXPECTED_FILE_NAME = "man-low-35-GREEN-box-alpha2-depth5-Euc.txt";
        //MeshGraph::WriteColorToFile(outColors, EXPECTED_FILE_NAME);
        std::vector<Color> expectedColors;
        ReadExpectedColors(expectedColors, EXPECTED_FILE_NAME);

        bool allOK = CheckColorArray(expectedColors, outColors);
        if (allOK)
        {
            printf("OK\n");
            pts.back() += 3;
        }
    }
    {
        const double ALPHA = 2.5;
        const int MAX_DEPTH = 100;
        const int VERTEX_ID_FROM = 11;
        const Color c = {0, 0, 255};
        const std::string FILE_NAME = "facem-low2.obj";
        printf("Checking PaintInRangeEuclidian of %s, "
                "with vertex %d, c:[%d, %d, %d], "
                "Gaussian, alpha %f, depth %d\n",
                FILE_NAME.c_str(),
                VERTEX_ID_FROM,
                c.r, c.g, c.b, ALPHA, MAX_DEPTH);
        loader.LoadObjFile(FILE_NAME);
        MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
        std::vector<Color> outColors;
        g.PaintInRangeEuclidian(outColors, VERTEX_ID_FROM, c, MAX_DEPTH, FILTER_GAUSSIAN,
                                ALPHA);

        static const std::string EXPECTED_FILE_NAME = "facem-low2-11-BLUE-gauss-alpha2.5-depth100-Euc.txt";
        //MeshGraph::WriteColorToFile(outColors, EXPECTED_FILE_NAME);
        std::vector<Color> expectedColors;
        ReadExpectedColors(expectedColors, EXPECTED_FILE_NAME);

        bool allOK = CheckColorArray(expectedColors, outColors);
        if (allOK)
        {
            printf("OK\n");
            pts.back() += 4;
        }
    }
}

// EXTRA PaintInRangeGeodesic (8)
void HW3Tester::TestCase10()
{
    pts.push_back(0);
    ObjLoader loader;
    {
        const double ALPHA = 2.0;
        const int MAX_DEPTH = 7;
        const int VERTEX_ID_FROM = 1;
        const Color c = {255, 255, 0};
        const std::string FILE_NAME = "man-low.obj";
        printf("Checking PaintInRangeGeodesic of %s, "
                "with vertex %d, c:[%d, %d, %d], "
                "Gaussian, alpha %f, depth %d\n",
                FILE_NAME.c_str(),
                VERTEX_ID_FROM,
                c.r, c.g, c.b, ALPHA, MAX_DEPTH);
        loader.LoadObjFile(FILE_NAME);
        MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
        std::vector<Color> outColors;
        g.PaintInRangeGeodesic(outColors, VERTEX_ID_FROM, c, MAX_DEPTH, FILTER_BOX,
                                ALPHA);

        static const std::string EXPECTED_FILE_NAME = "man-low-1-YELLOW-gauss-alpha2-depth7-Geo.txt";
        //MeshGraph::WriteColorToFile(outColors, EXPECTED_FILE_NAME);
        std::vector<Color> expectedColors;
        ReadExpectedColors(expectedColors, EXPECTED_FILE_NAME);

        bool allOK = CheckColorArray(expectedColors, outColors);
        if (allOK)
        {
            printf("OK\n");
            pts.back() += 4;
        }
    }

    {
        const double ALPHA = 0.5;
        const int MAX_DEPTH = 2;
        const int VERTEX_ID_FROM = 66;
        const Color c = {255, 0, 255};
        const std::string FILE_NAME = "facem-low2.obj";
        printf("Checking PaintInRangeGeodesic of %s, "
                "with vertex %d, c:[%d, %d, %d], "
                "Gaussian, alpha %f, depth %d\n",
                FILE_NAME.c_str(),
                VERTEX_ID_FROM,
                c.r, c.g, c.b, ALPHA, MAX_DEPTH);
        loader.LoadObjFile(FILE_NAME);
        MeshGraph g(loader.GetVertexPos(), loader.GetEdges());
        std::vector<Color> outColors;
        g.PaintInRangeGeodesic(outColors, VERTEX_ID_FROM, c, MAX_DEPTH, FILTER_GAUSSIAN,
                                ALPHA);

        static const std::string EXPECTED_FILE_NAME = "facem-low2-66-MAGENTA-gauss-alpha0.5-depth2-Geo.txt";
        //MeshGraph::WriteColorToFile(outColors, EXPECTED_FILE_NAME);
        std::vector<Color> expectedColors;
        ReadExpectedColors(expectedColors, EXPECTED_FILE_NAME);

        bool allOK = CheckColorArray(expectedColors, outColors);
        if (allOK)
        {
            printf("OK\n");
            pts.back() += 4;
        }
    }
}

int main(int argv, const char* argc[])
{
    typedef void (HW3Tester::*TestFuncs)();
    HW3Tester t;
    TestFuncs tests[] =
    {
        &HW3Tester::TestCase1,
        &HW3Tester::TestCase2,
        &HW3Tester::TestCase3,
        &HW3Tester::TestCase4,
        &HW3Tester::TestCase5,
        &HW3Tester::TestCase6,
        &HW3Tester::TestCase7,
        &HW3Tester::TestCase8,
        &HW3Tester::TestCase9,
        &HW3Tester::TestCase10
    };

    int i = std::atoi(argc[1]);
    // i -= 7;

    std::cout << "TC" << (i) << std::endl;
    (t.*tests[i-1])();
    printf("%d\n", t.TotalPts());

    // HW3Tester t;
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
    // std::cout << "TC7" << std::endl;
    // t.TestCase7();
    // std::cout << "TC8" << std::endl;
    // t.TestCase8();

    // printf("Total %d / %d\t", t.TotalPts(), t.MaxPts());
}
