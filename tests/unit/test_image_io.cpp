#include <image_io.h>

#include <point2D.h>

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
    const std::vector<Point2D> emptyVector;
    CHECK(saveToFile(emptyVector)); // Writes an empty white image
}
