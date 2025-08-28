/*
 *      .-    .-..  .     -..-  ..    ...       --..  ..-   -.    ..    --.   .-
 *      A     L     E     X     I     S         Z     Ú     Ñ     I     G     A  
 *  -------------------------------------------------------------------------------
 *     { Full name } : Alexis Alberto Zúñiga Alonso       { Semester } : Fifth
 *            { Course } : Automatons I     { Partial } : First Partial
 *  -------------------------------------------------------------------------------
 *          { Instagram: @thisisalexza }        { GitHub: @codingcluster }
 *                                  © Copyright 2025
 *  -------------------------------------------------------------------------------
 *  >> Description:
 *  En una productora Aguacatera se establece que:
 *  1. Existen dos calidades de aguacate: premium y estándar
 *  2. El aguacate premium puede tener un peso alto y un peso bajo, los aguacates
 *     estándar con peso bajo se clasifican en la misma categoría que los premium
 *  3. Los aguacates estándar que no obtienen el peso bajo se descartan
 * 
 *  >> Instructions:
 *  Genere un mecanismo para contener la expresión en el lenguaje de programación
 *  seleccionado para que el usuario ingrese el estado y la transición:
 *  δ: (q, a) = q'
 */

// { Dependencies }
#include <iostream>
#include <windows.h>
#include <cstdint>
#include <string>
#include <limits>
#include <map>
#include <set>

#define NOMINMAX

// { Utility functions }
void logo();
void clearScreen();
int intParser(std::string);

// { Automaton }
class Automaton {
private:
    std::string initialState;
    std::map<std::pair<std::string, std::string>, std::string> deltaTransitions; // Delta function for transitions
    std::set<std::string> states, alphabet;
public:
    // { Automaton's Constructor }
    Automaton(const std::string& initialState,
              const std::map<std::pair<std::string, std::string>, std::string>& deltaTransitions,
              const std::set<std::string>& states,
              const std::set<std::string>& alphabet)
        : initialState(initialState),
          deltaTransitions(deltaTransitions),
          states(states),
          alphabet(alphabet) {}
    
    // { Transaction Processing Method }
    void processTransaction(const std::string& currentState, std::string input) {
        auto deltaTransition = deltaTransitions.find({currentState, input});
        
        // Validation for non-defined transitions
        if (deltaTransition == deltaTransitions.end()) {
            std::cerr << "No defined transitions for the state '" << currentState
                << "' with input '" << input << "'." << std::endl;
            return;
        }
        
        std::string nextState = deltaTransition -> second;
        std::cout << "δ(" << currentState << ", " << input << ") = " << nextState << std::endl;
        
        reportState(input, nextState);
    }
    
    void reportState(const std::string& input, const std::string& state) {
        std::string inputName;
        std::string stateName;
        
        // { Input descriptions }
        if (input == "x1")      inputName = "Premium";
        else if (input == "x2") inputName = "Estándar";
        else if (input == "a1") inputName = "Peso Alto";
        else if (input == "a2") inputName = "Peso Bajo";
        else if (input == "a3") inputName = "Descartes";
        else if (input == "a2" || state == "q3")    inputName = "Peso bajo";
        else if (input == "a1" || state == "q4")    inputName = "Peso alto";
        else if (input == "a3" || state == "q4")    inputName = "Descartes";
        else if (input == "a2" || state == "q5")    inputName = "Peso bajo";
        else                    inputName = "Desconocido";
        
        // { State Descriptions }
        if (state == "q1")      stateName = "Aguacate Premium";
        else if (state == "q2") stateName = "Aguacate Estándar";
        else if (state == "q3") stateName = "Aguacate Premium de Peso Alto";
        else if (state == "q4") stateName = "Aguacate Premium de Peso Bajo";
        else if (state == "q5") stateName = "Aguacate Descartado";
        
        std::cout << "Reporte del Estado: " << input << " = " << inputName << std::endl;
        std::cout << "δ(" << state << ") = " << stateName << std::endl;
    }
};

// { Main program }
int main() {
    SetConsoleOutputCP(CP_UTF8);
    
    // States, alphabet and transitions
    std::set<std::string> states = {"q0", "q1", "q2", "q3", "q4", "q5"};
    std::set<std::string> alphabet = {"a1", "a2", "a3", "x1", "x2"};
    std::map<std::pair<std::string, std::string>, std::string> deltaTransitions {
        {{"q0", "x1"}, "q1"},   // Entrada -> Premium
        {{"q0", "x2"}, "q2"},   // Entrada -> Estándar
        {{"q1", "a1"}, "q3"},   // Premium -> Peso alto
        {{"q1", "a2"}, "q4"},   // Premium -> Peso bajo
        {{"q2", "a2"}, "q4"},   // Estándar -> Peso bajo
        {{"q2", "a3"}, "q5"},   // Estándar -> Descartes
        {{"q3", "a2"}, "q4"},   // Peso alto -> Peso bajo
        {{"q4", "a1"}, "q3"},   // Peso bajo -> Peso alto
        {{"q4", "a3"}, "q5"},   // Peso bajo -> Descartes
        {{"q5", "a2"}, "q4"}    // Descartes -> Peso bajo
    };
      
    bool exit = 0;
    do {
        // Some variables
        std::string menuInput;
        uint8_t parsedMenuInput;
        
        clearScreen();
        logo();
        
        std::cin >> menuInput;
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        parsedMenuInput = intParser(menuInput);
                
        switch(parsedMenuInput) {
            case 1: {
                std::string state1;
                std::string state2;
                Automaton automaton("q0", deltaTransitions, states, alphabet);
                
                std::cout << "\nIngrese el estado de su preferencia." << std::endl;
                std::cout << " [q0] Entrada" << std::endl;
                std::cout << " [q1] Aguacate Premium" << std::endl;
                std::cout << " [q2] Aguacate Estándar" << std::endl;
                std::cout << " [q3] Peso alto" << std::endl;
                std::cout << " [q4] Peso bajo" << std::endl;
                std::cout << " [q5] Descartes" << std::endl;
                std::cout << "\nEntrada: ";
                std::getline(std::cin, state1);
                std::cin.clear();
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                
                std::cout << "Ingrese la transición de su preferencia." << std::endl;
                std::cout << " [x1] Premium" << std::endl;
                std::cout << " [x2] Estándar" << std::endl;
                std::cout << " [a1] Peso Alto" << std::endl;
                std::cout << " [a2] Peso Bajo" << std::endl;
                std::cout << " [a3] Descartes" << std::endl;
                std::cout << "\nEntrada: ";
                std::getline(std::cin, state2);
                std::cin.clear();
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                
                automaton.processTransaction(state1, state2);
                
                getchar();
                getchar();
                
                break;
            }
            case 2:
                
                exit = 1;
        }
    } while(exit != 1);
      
    return 0;
}

//  { Clear terminal }
void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// { My logo }
void logo() {
    std::cout << " .-    .-..  .     -..-  ..    ..." << std::endl;
    std::cout << " A     L     E     X     I     S"  << std::endl;
    std::cout << "\n --..  ..-   -.    ..    --.   .-" << std::endl;
    std::cout << " Z     Ú     Ñ     I     G     A" << std::endl;
    std::cout << "\n----------------------------------\n" << std::endl;
    std::cout << " [1] Autómata de Estados" << std::endl;
    std::cout << " [2] Salir" << std::endl;
    std::cout << " Please, input your choice: ";
}

int intParser(std::string userInput) {
    int parsedMenuInput;
    bool success = false;
    
    while(success != true) {
        try {
            parsedMenuInput = std::stoi(userInput);
            success = true;
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "The input must be either \"1\" or \"2\". Please, try again." << std::endl;
            std::cout << "Please, input your choice: ";
            std::cin >> userInput;
            std::cin.clear();
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Input out of range. Please, try again." << std::endl;
            std::cout << "Please, input your choice: ";
            std::cin >> userInput;
            std::cin.clear();
        }
    }
    
    return parsedMenuInput;
}