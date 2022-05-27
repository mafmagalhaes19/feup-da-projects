

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
         << "1. Cenario 1 - Grupos que nao se separam\n"
         << "2. Cenario 2 - Grupos que podem separar-se\n"
         << "3. Sair\n"
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
                SceneOneMenu();
                break;
            case 2:
                //Scene 2
                SceneTwoMenu();
                break;
            case 3:
                break;
            default:
                input = -1;
                cout << "Input invalido, por favor tente outra vez:" << endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.clear();
                break;
        }
        if(input != -1 && input != 3){
            cout << endl;
            cout << endl;

            cout << "MENU PRINCIPAL\n"
                 << "1. Cenario 1 - Grupos que nao se separam\n"
                 << "2. Cenario 2 - Grupos que podem separar-se\n"
                 << "3. Sair\n"
                 << endl
                 <<"Introduza a sua escolha: ";


        }


    } while (input != 3);
    return 0;
}

void Menu::SceneOneMenu() {
    string choice;
    int input;

    cout << endl;
    cout << endl;



    cout << "CENARIO 1\n"
         << "1. Maximizar a dimensao do grupo\n"
         << "2. Maximizar a dimensao do grupo e minimizar o numero de transbordos\n"
         << "3. Sair\n"
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
                _travelAgency.sceneOneOne();
                break;
            case 2:
                //Scene 2
                _travelAgency.sceneOneTwo();
                break;
            case 3:
                break;
            default:
                input = -1;
                cout << "Input invalido, por favor tente outra vez:" << endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.clear();
                break;
        }
        if(input != -1 && input != 3){
            cout << endl;
            cout << endl;

            cout << "CENARIO 1\n"
                 << "1. Maximizar a dimensao do grupo\n"
                 << "2. Maximizar a dimensao do grupo e minimizar o numero de transbordos\n"
                 << "3. Sair\n"
                 << endl
                 <<"Introduza a sua escolha: ";


        }


    } while (input != 3);
}

void Menu::SceneTwoMenu() {
    string choice;
    int input;

    cout << endl;
    cout << endl;



    cout << "CENARIO 2\n"
         << "1. Determinar um encaminhamento para um grupo\n"
         << "2. Corrigir um encaminhamento\n"
         << "3. Determinar a dimensao maxima de um grupo e um encaminhamento\n"
         << "4. Determinar quando um grupo se reune novamente no destino, no minimo\n"
         << "5. Indicar o tempo maximo de espera e os locais em que haveria elementos que esperam esse tempo\n"
         << "6. Sair\n"
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
                //Scene 2.1
                _travelAgency.sceneTwoOne();
                break;
            case 2:
                //Scene 2.2
                _travelAgency.sceneTwoTwo();
                break;
            case 3:
                _travelAgency.sceneTwoThree();
                break;
            case 4:
                _travelAgency.sceneTwoFour();
                break;
            case 5:
                _travelAgency.sceneTwoFive();
                break;
            case 6:
                break;
            default:
                input = -1;
                cout << "Input invalido, por favor tente outra vez:" << endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.clear();
                break;
        }
        if(input != -1 && input != 6){
            cout << endl;
            cout << endl;

            cout << "CENARIO 2\n"
                 << "1. Determinar um encaminhamento para um grupo\n"
                 << "2. Corrigir um encaminhamento\n"
                 << "3. Determinar a dimensao maxima de um grupo e um encaminhamento\n"
                 << "4. Determinar quando um grupo se reune novamente no destino, no minimo\n"
                 << "5. Indicar o tempo maximo de espera e os locais em que haveria elementos que esperam esse tempo\n"
                 << "6. Sair\n"
                 << endl
                 <<"Introduza a sua escolha: ";


        }


    } while (input != 6);
}


