//
// Created by Mafalda Magalhães on 05/04/2022.
//

#include "Menu.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

Menu::Menu(DeliveryManager deliveryManager): _deliveryManager(deliveryManager){}



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

    cout << "Bem vindo a Delivery Manager!!!" << endl;

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
                showSceneOneMenu();
                break;
            case 2:
                //Scene 2
                _deliveryManager.sceneTwo();
                break;
            case 3:
                //Scene 3
                _deliveryManager.sceneThree();
                break;
            case 4:
                break;
            default:
                input = -1;
                cout << "Input invalido, por favor tente outra vez:" << endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.clear();
                break;
        }
        if(input != -1 && input != 4){
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

void Menu::showSceneOneMenu() {
    string choice;
    int input;
    cout << "CENARIO 1 \n"
         << "1. Best Fit Approach (Peso) \n"
         << "2. Best Fit Approach (Volume) \n"
         << "3. Voltar ao menu principal \n"
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
                _deliveryManager.sceneOneWeight();
                break;
            case 2:
                _deliveryManager.sceneOneVolume();
                break;
            case 3:
                break;
            default:
                input = -1;
                cout << "Input invalido, por favor tente outra vez:" << endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.clear();
                break;
        }
        if(input != -1 && input != 3){
            cout << endl;
            cout << "CENARIO 1 \n"
                 << "1. Best Fit Approach (Peso) \n"
                 << "2. Best Fit Approach (Volume) \n"
                 << "3. Voltar ao menu principal \n"
                 << endl
                 <<"Introduza a sua escolha: ";

        }


    } while (input != 3);

}
