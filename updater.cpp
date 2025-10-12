#include <iostream>
#include <getopt.h>
#include <string>

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

void std::string installDiscord() {

  // Old, bad code but it works so...
  std::system("cd ~/Downloads && mkdir DISAUTOUP");
  std::system("cd ~/Downloads/DISAUTOUP && rm -rf ./*");

  std::system("cd ~/Downloads/DISAUTOUP && wget -q --content-disposition 'https://discord.com/api/download?platform=linux&format=deb'");
  std::system("cd ~/Downloads/DISAUTOUP && sudo dpkg -i ./*.deb");
  std::system("cd ~/Downloads && rm -rf DISAUTOUP");
}

int main(int argc, char* argv[]) {

  bool install_vencord = false;
  bool silent = false;
  bool showVersion = false;
  std::string package_url;


  // Code below is just looking at the flags, and also setting options

  stataic struct option long_options[] = {
    {"help",    no_argument,         0, 'h'}
    {"cord",    no_argument,         0, 'c'}
    {"package", optional,            0, 'p'}
    {"silent",  no_argument,         0, 's'}
    {"version", no_argument,         0, 'v'}
    {0, 0, 0, 0}
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
        package_url = optarg;
        break;
      case 's':
        silent = true;
        break;
      case v:
        showVersion = true;
        break;
      default:
        print_help();
        return 1;
    }
  }

  installDiscord()
 
  if(showVerison) {
    std::cout << R"(

    

 ██████████   █████  █████████  █████  █████ ███████████ 
░░███░░░░███ ░░███  ███░░░░░███░░███  ░░███ ░░███░░░░░███
 ░███   ░░███ ░███ ░███    ░░░  ░███   ░███  ░███    ░███
 ░███    ░███ ░███ ░░█████████  ░███   ░███  ░██████████ 
 ░███    ░███ ░███  ░░░░░░░░███ ░███   ░███  ░███░░░░░░  
 ░███    ███  ░███  ███    ░███ ░███   ░███  ░███        
 ██████████   █████░░█████████  ░░████████   █████       
░░░░░░░░░░   ░░░░░  ░░░░░░░░░    ░░░░░░░░   ░░░░░        

By Justtobored, version (1.0)
    )" << '\n';
  }


  if(install_vencord) {
    std::cout << (silent ? "" : "Installing Vencord...\n");
    std::system("sh -c `$(curl -sS https://raw.githubusercontent.com/Vendicated/VencordInstaller/main/install.sh)`");
  }

  if(!package_url().empty()) {
    std::string themesLoc = ".config/Vencord/themes";
    std::cout << "Where is your vencord themes folder located? (default = " << themesLoc << "): ";
    std::string input;
    std::getline(std::cin, input);

    if(!input.empty()){
      themesLoc = input;
    }

    std::cout << (silent? "" : "Using: " << themesLoc << "\n");

    char target = '/';
    size_t lastSlash = package_url.rfind(target);

    if(lastSlash != std::string::npos) 
      std::string fileName = package_url.substr(lastSlash + 1);
      std::string command = "curl -L -s -o ~/" + themesLoc + fileName + " " + package_url;

      /**
       * Should come out like:
       * curl -L -s -o ~/.config/Vencord/themes/example.theme.css https://bad_example_link.com/example.theme.css
       * 
       * What this does:
       * Extracts the last part of the link; starting with the last '/' then moving onwards
       * No verification just yolo 😭
       * */

      std::system(command.c_str());
      std::cout << (silent? "": fileName << " has been added to the themes folder! \n");

    } else {
      std::cout << "Link extraction error has occured. Exiting Program \n";
      return 1;
    }

  } else {
    std::cout << (silent? "" : "No package provided. \n";
  }
}
