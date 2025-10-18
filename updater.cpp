#include <iostream>
#include <getopt.h>
#include <string>
#include <cstdlib>

bool install_vencord = false;
bool silent = false;
bool showVersion = false;
std::string package_url;
std::string themesLoc = ".config/Vencord/themes/";

void print_help() {
  std::cout << "Usage: disupdate [options]\n"
            << "\nOptions:\n"
            << "  -h, --help                        Show this help message\n"
            << "  -c, --cord                        Installs vencord\n"
            << "  -p, --package <url> (optional)    Installs a specific css package\n"
            << "                                    ex. https://github.com/refact0r/system24/blob/master/theme/system24.theme.css \n"
            << "  -s, --silent                      No log install\n"
            << "  -v, --version                     Tells you the package version...duh\n";

}

void installDiscord() {

  // Old, bad code but it works so...
  std::system("cd ~/Downloads && mkdir DISAUTOUP");
  std::system("cd ~/Downloads/DISAUTOUP && rm -rf ./*");

  std::system("cd ~/Downloads/DISAUTOUP && wget -q --content-disposition 'https://discord.com/api/download?platform=linux&format=deb'");
  std::system("cd ~/Downloads/DISAUTOUP && sudo dpkg -i ./*.deb");
  std::system("cd ~/Downloads && rm -rf DISAUTOUP");
}

int main(int argc, char* argv[]) {

  // Code below is just looking at the flags, and also setting options

  static struct option long_options[] = {
    {"help",    no_argument,         nullptr, 'h'},
    {"cord",    no_argument,         nullptr, 'c'},
    {"package", optional_argument,   nullptr, 'p'},
    {"silent",  no_argument,         nullptr, 's'},
    {"version", no_argument,         nullptr, 'v'},
    {nullptr, 0, nullptr, 0}
  };

  int opt;

  while((opt = getopt_long(argc, argv, "hcp:sv", long_options, nullptr)) != -1) {
    switch (opt) {
      case 'h':
        print_help();
        return 0;
      case 'c':
        install_vencord = true;
        break;
      case 'p':
        if (optarg) package_url = optarg;
        break;
      case 's':
        silent = true;
        break;
      case 'v':
        showVersion = true;
        break;
      default:
        print_help();
        return 1;
    };
  };

  installDiscord();
 
  if(showVersion) {
    std::cout << R"(

    

 ██████████   █████  █████████  █████  █████ ███████████ 
░░███░░░░███ ░░███  ███░░░░░███░░███  ░░███ ░░███░░░░░███
 ░███   ░░███ ░███ ░███    ░░░  ░███   ░███  ░███    ░███
 ░███    ░███ ░███ ░░█████████  ░███   ░███  ░██████████ 
 ░███    ░███ ░███  ░░░░░░░░███ ░███   ░███  ░███░░░░░░  
 ░███    ███  ░███  ███    ░███ ░███   ░███  ░███        
 ██████████   █████░░█████████  ░░████████   █████       
░░░░░░░░░░   ░░░░░  ░░░░░░░░░    ░░░░░░░░   ░░░░░        

By Justtobored, version (2.0)
    )" << '\n';
  }


  if(install_vencord) {
    if (!silent) std::cout << "Installing Vencord...\n";
    std::system("sh -c \"$(curl -sS https://raw.githubusercontent.com/Vendicated/VencordInstaller/main/install.sh)\"");
  }

  if(!package_url.empty()) {
    std::cout << "Where is your vencord themes folder located? (default = ~/" << themesLoc << "): ";
    std::string input;
    std::getline(std::cin >> std::ws, input); // eat leftover whitespace/newline(recommended by gpt)

    if(!input.empty()){
      themesLoc = input;
      if (themesLoc.back() != '/') themesLoc += "\n";
    }

    if (!silent) std::cout << "Using: ~/" << themesLoc << "\n";

    char target = '/';
    size_t lastSlash = package_url.rfind(target);

    if(lastSlash != std::string::npos){ 
      std::string fileName = package_url.substr(lastSlash + 1);
      std::string command = std::string("curl -L -s -o ~/") + themesLoc + fileName + " " + package_url;

      /**
       * Should come out like:
       * curl -L -s -o ~/.config/Vencord/themes/example.theme.css https://bad_example_link.com/example.theme.css
       * 
       * What this does:
       * Extracts the last part of the link; starting with the last '/' then moving onwards
       * No verification just yolo 😭
       * */

      std::system(command.c_str());
      if(!silent) std::cout << fileName << " has been added to the themes folder! \n";

    } else {
      std::cout << "Link extraction error has occured. Exiting Program \n";
      return 1;
    }

  } else {
    if (!silent) std::cout << "No package provided. \n";
  }

  return 0;
}
