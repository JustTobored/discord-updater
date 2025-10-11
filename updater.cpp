#include <iostream>

void getDiscordDeb();
void runResponseChecks(char response);
void vencordInstall(std::string &response);

int main() {
  std::cout << "Discord Updater (online)" << '\n';
  std::cout << "If you don't have wget installed, please install it." << '\n';
  std::cout << "Debian: sudo apt-get install wget" << '\n';
  std::cout << "Arch: sudo pacman -S wget" << '\n';
 
  // I did not add vencord as yet, only adding the deb for now.
 
  char response;

  std::cout << "Do you want to install the lastest discord .deb? [y or n] ";
  std::cin >> response; 

  runResponseChecks(response);

  return 0;
}


void getDiscordDeb() {

  std::cout << '\n' << "If wget is not installed this will not work";
  std::system("cd ~/Downloads && mkdir DISAUTOUP");
  std::system("cd ~/Downloads/DISAUTOUP && rm -rf ./*");

  std::system("cd ~/Downloads/DISAUTOUP && wget --content-disposition 'https://discord.com/api/download?platform=linux&format=deb'");
  std::system("cd ~/Downloads/DISAUTOUP && sudo dpkg -i ./*.deb");
  std::system("cd ~/Downloads && rm -rf DISAUTOUP");

  std::cout << '\n';
  std::cout << "Finished Installing latest discord .deb!";
  
}

void runResponseChecks(char response) {

  if(response == 'y') {
    getDiscordDeb();
  } else {
    std::cout << '\n' << "No updates installed.";
  }
}
