#include <image_io.h>

#include <point2D.h>

#include <fstream>

#include <CppUTest/TestHarness.h>

TEST_GROUP(SavingPointsToFile) 
{
    void setup()
    {
        // Sadly it seems that Qt is leaking quite some memory...
        // ...or it uses static variables that CppUTest does not like.
        // TODO: Double check this. 
        MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
    }

    void teardown()
    {
        MemoryLeakWarningPlugin::turnOnNewDeleteOverloads();
    }
};

TEST(SavingPointsToFile, DoesNotFailWithEmptyVector)
{
    const std::vector<std::vector<Point2D>> emptyVector;
    const std::string filename("test.png");
    CHECK(saveToFile(filename, emptyVector)); // Writes an empty white image

    std::ifstream imageFile (filename.c_str());
    CHECK(imageFile.good());
}

