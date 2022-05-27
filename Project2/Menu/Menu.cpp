

#include "Menu.h"

using namespace std;

Menu::Menu(TravelAgency travelAgency): _travelAgency(travelAgency){}

int Menu::validadeInput(string input) {
    if(input.length() == 1 && isdigit(input[0])){
        stringstream ss(input);
        int number;
        ss >> number;
        return number;
    }else{return -1;}
}

unsigned Menu::mainMenu() {
    string choice;
    int input;
    cout << endl;

    cout << "Bem vindo a Agencia de Viagens!!!" ;

    cout << endl;
    cout << endl;



    cout << "MENU PRINCIPAL\n"
         << "1. Cenario 1\n"
         << "2. Cenario 2\n"
         << "3. Cenario 3\n"
         << "4. Sair\n"
         << endl
         <<"Introduza a sua escolha: ";

    do
    {
        input = -1;
        cin >> choice;
        if (!cin.fail() && cin.peek() == '\n'){
            input = validadeInput(choice);
        }

        switch (input)
        {
            case 1:
                //Scene 1
                _travelAgency.sceneOne();
                break;
            case 2:
                //Scene 2
                _travelAgency.sceneTwo();
                break;
            case 3:
                //Scene 3
                _travelAgency.sceneThree();
                break;
            case 4:
                break;
            default:
                input = -1;
                cout << "Input invalido, por favor tente outra vez:" << endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.clear();
                break;
        }
        if(input != -1 && input != 4){
            cout << endl;
            cout << endl;

            cout << "MENU PRINCIPAL\n"
                 << "1. Cenario 1\n"
                 << "2. Cenario 2\n"
                 << "3. Cenario 3\n"
                 << "4. Sair\n"
                 << endl
                 <<"Introduza a sua escolha: ";


        }


    } while (input != 4);
    return 0;
}

