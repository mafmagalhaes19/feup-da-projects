

#include "Menu.h"

using namespace std;

Menu::Menu(TravelAgency travelAgency): _travelAgency(travelAgency){}

int Menu::validadeInput(string input) {
    if(input.length() >= 1 && isdigit(input[0])){
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

    cout << "------------------------------------------------------------------------------------------------------------------------\n";
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
            cout << "------------------------------------------------------------------------------------------------------------------------\n";
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
    int source, destination;

    cout << endl;
    cout << endl;

    cout << "------------------------------------------------------------------------------------------------------------------------\n";
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
                //Scene 1.1
                helperSetGraph();

                source = 0;
                destination = 0;
                cout << "Origem: "; cin >> source;
                cout << "Destino: "; cin >> destination;

                _travelAgency.sceneOneOne(source, destination);
                break;
            case 2:
                //Scene 1.2
                helperSetGraph();

                source = 0;
                destination = 0;
                cout << "Origem: "; cin >> source;
                cout << "Destino: "; cin >> destination;

                _travelAgency.sceneOneTwo(source, destination);
                break;
            case 3:
                break;
            default:
                input = -1;
                cout << "Input invalido, por favor tente outra vez: " << endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.clear();
                break;
        }
        if(input != -1 && input != 3){
            cout << endl;
            cout << endl;

            cout << "------------------------------------------------------------------------------------------------------------------------\n";
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
    int source, destination;
    int groupDimension, groupAdded;

    cout << endl;
    cout << endl;

    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "CENARIO 2\n"
         << "1. Determinar um encaminhamento para um grupo\n"
         << "2. Corrigir um encaminhamento para que a dimensao do grupo seja um numero de unidades exato\n"
         << "3. Determinar a dimensao maxima de um grupo e o respetivo encaminhamento\n"
         << "4. Partindo de um grafo aciclico, determinar quando e que um grupo se reune novamente no destino, no minimo\n"
         << "5. Indicar o tempo maximo de espera e os locais em que haveria elementos que esperam esse tempo, utilizando as condicoes de 2.4\n"
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
                helperSetGraph();

                groupDimension = 0;

                source = 0;
                destination = 0;
                cout << "Origem: "; cin >> source;
                cout << "Destino: "; cin >> destination;
                cout << "Numero total de elementos do grupo: "; cin >> groupDimension;

                _travelAgency.sceneTwoOne(source, destination, groupDimension, false, 0);
                break;
            case 2:
                //Scene 2.1
                helperSetGraph();

                groupDimension = 0;

                source = 0;
                destination = 0;
                cout << "Origem: "; cin >> source;
                cout << "Destino: "; cin >> destination;
                cout << "Numero total de elementos do grupo: "; cin >> groupDimension;

                //Scene 2.2
                groupAdded = 0;

                cout << "Numero de pessoas adicional: "; cin >> groupAdded;

                _travelAgency.sceneTwoOne(source, destination, groupDimension, true, groupAdded);

                break;
            case 3:
                //Scene 2.3
                helperSetGraph();

                source = 0;
                destination = 0;
                cout << "Origem: "; cin >> source;
                cout << "Destino: "; cin >> destination;

                _travelAgency.sceneTwoThree(source, destination);
                break;
            case 4:
                //Scene 2.4
                helperSetGraph();
                groupDimension = 0;

                source = 0;
                destination = 0;
                cout << "Origem: "; cin >> source;
                cout << "Destino: "; cin >> destination;
                cout << "Numero total de elementos do grupo: "; cin >> groupDimension;

                _travelAgency.sceneTwoFour(source, destination, groupDimension);
                break;
            case 5:
                //Scene 2.5
                helperSetGraph();
                _travelAgency.sceneTwoFive();
                break;
            case 6:
                break;
            default:
                input = -1;
                cout << "Input invalido, por favor tente outra vez: " << endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.clear();
                break;
        }
        if(input != -1 && input != 6){
            cout << endl;
            cout << endl;

            cout << "------------------------------------------------------------------------------------------------------------------------\n";
            cout << "CENARIO 2\n"
                 << "1. Determinar um encaminhamento para um grupo\n"
                 << "2. Corrigir um encaminhamento para que a dimensao do grupo seja um numero de unidades exato\n"
                 << "3. Determinar a dimensao maxima de um grupo e o respetivo encaminhamento\n"
                 << "4. Partindo de um grafo aciclico, determinar quando e que um grupo se reune novamente no destino, no minimo\n"
                 << "5. Indicar o tempo maximo de espera e os locais em que haveria elementos que esperam esse tempo, utilizando as condicoes de 2.4\n"
                 << "6. Sair\n"
                 << endl
                 <<"Introduza a sua escolha: ";


        }


    } while (input != 6);
}

void Menu::helperSetGraph() {
    string choice;
    int input;


    while(true){
        cout << endl;
        cout << "Escolha o grafo a utilizar (entre 1 a 11 - preferencialmente o 11): ";

        cin >> choice;
        cout << endl;
        input = validadeInput(choice);
        if(input <= 11 && input > 0){
            _travelAgency.setGraph(input);
            break;
        }
        cout << "Input invalido, por favor tente outra vez." << endl;

        helperSetGraph();

    }

}


