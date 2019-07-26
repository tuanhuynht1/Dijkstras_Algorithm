#include "Menu.hpp"
using namespace std;



int main(){
    Menu menu;
    char command;
    while(true){
        command = menu.options();
        if (command == 'q'){
            system("CLS");
            cout << "Bye!" << endl;
            break;
        }

        menu.parseCommand(command);
    }
}
