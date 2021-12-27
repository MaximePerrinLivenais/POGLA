#include "option_parser.hh"

#include <iostream>
#include <boost/program_options.hpp>

namespace opt = boost::program_options;

namespace misc
{
    Options::Options(int argc, char* argv[])
    {
        opt::options_description desc("program options");
        desc.add_options()("help", "show usage");

        desc.add_options()(
            "obj_file,f",
            opt::value<std::string>(&obj_file_path)->default_value(""));

        desc.add_options()("shaders_dir,s",
                           opt::value<std::filesystem::path>(&shaders_dir_path)
                               ->default_value("../src/shaders/"));

        desc.add_options()("width,w",
                           opt::value<int>(&screen_width)->default_value(1000),
                           "Render width");

        desc.add_options()("height,h",
                           opt::value<int>(&screen_height)->default_value(1000),
                           "Render height");

        opt::variables_map vm;
        try
        {
            opt::store(opt::command_line_parser(argc, argv).options(desc).run(),
                       vm);
            opt::notify(vm);
        }
        catch (...)
        {
            /* unknown options */
            std::cerr << "error: unknown option " << desc << '\n';
            std::exit(1);
        }

        if (vm.count("help"))
        {
            /* found --help */
            std::cout << desc;
            std::exit(0);
        }

        if (vm.count("obj_file"))
        {
            if (!std::filesystem::exists(obj_file_path))
                obj_file_path = "";
        }
    }

} // namespace misc
