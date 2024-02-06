#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

int main()
{
    fs::path path = "/home/duki/sdl2_music_project";
    for (const auto & entry : fs::directory_iterator(path))
    {
        std::cout << entry.path().filename() << entry.is_directory() << std::endl;
    }
}
