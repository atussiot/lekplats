#include <chaos_game.h>
#include <image_io.h>

#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[])
{
    ChaosGame game { 500000, 4, Restriction::NextClockwise };
    if (!saveToFile("chaos.png", game.generate_points())) {
        std::cerr << "Could not save chaos game image" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

