#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h.in"

#include <vector>
#include <random>
#include <algorithm>


auto main(int argc, char **argv) -> int
{
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};

    int counter = 20;

    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.add_option("-c,--count", counter, "Wert für Var1. Default: 20");
        app.parse(argc, argv);


    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("\nHello, {}!\n", app.get_name());

    std::cout<<"\nHier ist der aktuelle Wert von Counter: "<<counter<<"\nUm den aktuellen Wert zu ändern gib ./exercise-001 -c (Neuer Wert) ein\n\n";
    std::vector<int> vec;

    for(int i=0;i<counter;i++)
    {
        int random = rand()%100;
        vec.push_back(random);
    }
    
    std::cout<<"Hier sind die unsortierten Werte von Vector:\n";
    for (int i=0;i<counter; i++)
    {
        fmt::print("{}, ", vec[i]);
    }

    auto start = std::chrono::system_clock::now();
    std::sort(vec.begin(), vec.end());
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout<<std::endl;

    std::cout<<"\nHier sind die sortierten Werte von Vector:\n";
    for (int i=0;i<counter; i++)
    {
        fmt::print("{}, ", vec[i]);
    }

    fmt::print("\n\nDie Sortierung hat {} Nanosekunden gedauert.\n", elapsed.count());

    return 0; /* exit gracefully*/
}
