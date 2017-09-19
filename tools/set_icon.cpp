#include <string>
#include <cstdlib>

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        exit(0);
    }

    std::string icon = std::string(argv[1], strlen(argv[1]));
    std::string dir = std::string(argv[2], strlen(argv[2])) + "/Icon\r";
    std::string touch = std::string("touch ") + dir;
    std::string sips = std::string("sips -i ") + icon;
    std::string derez = std::string("DeRez -only icns ") + icon + " > temp.rsrc";
    std::string rez = std::string("Rez -append temp.rsrc -o ") + dir;
    std::string set_file = std::string("SetFile -a V ") + dir;
    std::string set_f = std::string("SetFile -a C ") + std::string(argv[2], strlen(argv[2]));
    std::string rm = std::string("rm -f temp.rsrc");
    system(touch.c_str());
    system(sips.c_str());
    system(derez.c_str());
    system(set_f.c_str());
    system(rez.c_str());
    system(set_file.c_str());
    system(rm.c_str());


    return 0;
}