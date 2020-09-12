#include <chaos_game.h>
#include <image_io.h>

#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: ./chaos <polygon-sides> <rule>" << std::endl;
        return EXIT_FAILURE;
    }

    const auto vertices = static_cast<size_t>(std::strtol(argv[1], nullptr, 10));
    const auto rule = static_cast<Restriction>(std::strtol(argv[2], nullptr, 10));
    ChaosGame game { 500000, vertices, rule };

    if (!saveToFile("chaos.png", game.generate_points())) {
        std::cerr << "Could not save chaos game image" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

