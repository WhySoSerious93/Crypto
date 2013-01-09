// StartUp.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//


#include <iostream>
#include <string>
#include <stdio.h>
#include "Crypto.h"

using namespace std;


int main(void)
{
    string userinput = ""; // Der String, der verschlüsselt werden muss 
    string answer;
    string ec_input, dc_input; // der ver-und entschlüsselte String

    cout << "Welcome to the Crypto - Tool (Beta)" << endl;
    cout << "************************************" << endl;

    // const char* const alpha = "ABCDEFGH IJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    cout << "Please type in your string (Finish with '.') : " ; 
    getline(cin, userinput, '.');

    cin.clear(); // buffer von getline leeren
    cin.sync(); // das nächste getline mit dem input stream synchronisieren --> Beide Funktionen wirken i-wie nicht richtig

    cout << "Please type in a password: "; // Password, damit nicht jeder den String wieder entschlüsseln kann  
    inputPassword();						// --> Dient für mich als Password-Programmierübung
	std::cout << std::endl;

    ec_input = encoder(userinput); // encoder = Funktion zur Verschlüsselung

    cout << endl;
    cout << "Do you want to decode your string again ? (y/n): "; // Frage ob String wieder entschlüsselt werden soll 
    getline(cin, answer);

    cin.ignore(); // Funktion, damit das "newline"-Zeichen aus dem Buffer ignoriert wird --> Funktioniert aber leider nicht wirklich
 
    cout << "Answer : " << answer << endl;

    if (answer == "y" || answer == "Y") 
    {
        cout << "Please type the Password : ";
        if(!checkPassword()) // Prüfung ob Passwort übereinstimmt
        {
            cout << "\nERROR : Password doesnt match !" << endl;
        }
        else
        {
            dc_input = decoder(); // Funktion zum Entschlüsseln
            cout << "\nYour original string : " << dc_input << endl;
        }
    }
    else if (answer == "n" || answer == "N")
    {
        cout << "\nYour coded string : " << ec_input << endl; 
    }
    else
    {
        cout << "\nERROR : Couldnt understand your input !" << endl;
    }

    cout << endl;

    return 0;
}

