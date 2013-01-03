#include <string>
#include <algorithm>
#include <conio.h> // Angeblich veraltete, Non-Standard Bibliothek (Erkennt man vllt schon an dem .h)
#include <windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <ctype.h>
#include "Crypto.h"

const char* const a_bet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Nat�rliches Alphabet zum Ver-und Entschl�sseln

std::string c_bet[] = {":)",":(",";(","xD","^^","*_*","._.","#o#",":))","x)","'_'",
						"*o*","._*",":>",";<",":/",";/","x(",":p",";p","~.~","~x~",
											"~o~","<_<",">_>","!_!"}; // Code-Alphabet bestehend aus Emoticons
std::string dc_param = ""; // Der endg�ltige, verschl�sselte String

std::vector<int> positions; // Positionen der Leerzeichen
std::vector<int> charac;  // Positionen der Kleinbuchstaben

std::string result[1000];
int c = 0;

std::string StringToUpper(std::string strToConvert) // Funktion zum Hochstellen der Buchstaben 
{
	std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);

	return strToConvert;
}

std::string encoder (std::string input)
{
	for (unsigned int l = 0; l < input.length(); l++)
	{
		c = input[l];
		if (isspace(input[l])) // Leerzeichen gefunden
		{
			positions.push_back(l);
		}
		else if(!isupper(c)) // Kleinbuchstabe gefunden
		{
			charac.push_back(l);
		}
	}

	input = StringToUpper(input);

	input.erase(std::remove_if(input.begin(), input.end(), &::isspace), input.end()); // Leerzeichen werden entfernt

	for(unsigned int i = 0;i < input.length(); i++) // Jedem Character des Ausgangsstrings wird der entsprechende Code-String zugeordnet
	{
		for(int j = 0; j < 26; j++)
		{
			if (input[i] == a_bet[j])
			{
				result[c] = c_bet[j]; // Entsprechender Code-Strings wird dem Array hinzugef�gt
				c++;
			}
		}
	}


	for (unsigned int k = 0; k < input.length(); k++)
	{
		dc_param += result[k] + "|"; // die '|' dienen dazu, damit der decoder sp�ter die Code-Strings besser voneinander unterscheiden kann
	}

	std::ofstream codefile; // Der codierte String wird in eine extra Textdatei hineingespeichert

	codefile.open("code.txt", std::ios::trunc);

	if (codefile.is_open())
	{
		std::cout << "Code File Opening successful" << std::endl;
	}
	else
	{
		std::cout << "Couldnt open the Code File" << std::endl;
	}
	codefile << dc_param; // Code-String wird in die Datei hineingeschrieben
	codefile.close();
	
	return dc_param; // Der codierte String wird zur�ckgegeben
}

std::string decoder()
{
	int start = 0; 
	int end;

	std::vector<std::string> container; // Dient als Speicher f�r die einzelnen Code-Strings
	std::string final = ""; // der endg�ltige, entschl�sselte String 
	std::string codeinput; // Dorthin wird der Inhalt der Textdatei extrahiert

	std::ifstream decodefile;

	decodefile.open("code.txt", std::ios::in); // Textdatei mit Code wird ge�ffnet
	decodefile.seekg(0, std::ios::end); // Bewegt Zeiger bis zum Ende der Zeile

	int length = decodefile.tellg(); // Position des Zeigers fungiert hier als "L�nge" des Textdateiinhaltes

	decodefile.seekg(0, std::ios::beg); // Zeiger wird wieder zum Anfang gezogen

	if (decodefile.is_open())
	{
		std::cout << "Code File Opening successful" << std::endl;
	}
	else
	{
		std::cout << "Couldnt open the Code File" << std::endl;
	}

	if(length == 0) // Kein Inhalt
	{
		std::cout << "HACK! : Somebody tried to break into the file !" << std::endl;
		// IDEE : Fals jemand beim Passwort 3 mal verkackt, wird dass als Hackversuch gewertet und der Inhalt der Textdatei gel�scht
	}
	else
	{
		decodefile >> codeinput;

		decodefile.close();

		for (unsigned int i = 0; i < codeinput.length(); i++)
		{
			if(codeinput[i] == '|') // Die Code-Strings werden entsprechend der Markierung extrahiert
			{
				end = i;
				container.push_back(codeinput.substr(start, (end) - start));
				start = i+1;
			}
		}

		std::cout << "**********************" << std::endl;

		for (unsigned int j = 0; j < container.size(); j++)
		{
			for (int k = 0; k < 26 ; k++)  
			{
				if(container.at(j) == c_bet[k]) // R�ckumwandlung Code-Strings --> Normale Buchstaben
				{
					final += a_bet[k]; // Entsprechender Code-String wird wieder in normalen Buchstaben umgewandelt
				}
			}
		}

		for (unsigned int p = 0; p < positions.size(); p++)
		{
			final.insert(positions.at(p), 1, ' '); // Lehrzeichen werden wieder eingef�gt
		}

		for(unsigned int k = 0; k < charac.size(); k++)
		{
			final[charac.at(k)] = tolower(final[charac.at(k)]); // Kleinbuchstaben werden wieder eingef�gt
		}
	}

	return final; // Ursprungsstring wird wieder zur�ckgegeben
}

void inputPassword() // Funktion zur Passworteingabe
{
	char temp1;
	std::string userpassword; // Das sp�tere Nutzerpassword

	while(true)
	{
		temp1 = getch();

        // Das "Zeichen" carriage return - also ENTER - hat den ASCII-Code 13.
        // D.h. sobald das eingelesene Zeichen gleich 13 ist, ist die Eingabe zu beenden.
        if (temp1 == 13) 
        {
            break;
        }

		userpassword += temp1; // Die einzelnen Char werden dem Password hinzugef�gt
		std::cout << "*"; // Die ber�hmten Sternchen
	}

	std::ofstream codewriter; // Password wird ebenfalls in einer Textdatei gespeichert
	codewriter.open("password.txt", std::ios::trunc);

	codewriter << userpassword;
	codewriter.close();

}

bool checkPassword()
{
	char temp2;
	std::string userinput; // das vom Benutzer eingetippte Password
	std::string password; // Das Ursprungspasswort

	while(true)
	{
		temp2 = getch(); 
		if (temp2 == 13) // Siehe inputPassword
        {
            break;
        }

		userinput += temp2;
		std::cout << "*"; 
	}

	std::ifstream codereader; // Das Ursprungspassword wird wieder aus der Datei extrahiert
	codereader.open("password.txt", std::ios::in);

	codereader >> password;
	codereader.close();

	if(userinput.length() != password.length()) // Die L�nge muss auf jeden Fall �bereinstimmen
	{
		std::cout << "ERROR : Password doesnt match !" << std::endl;
		return false;
	}
	else
	{
		for (unsigned int i = 0; i < userinput.length(); i++)
		{
			if(userinput[i] != password[i]) // Jeder Char wird einzeln �berpr�ft
			{
				std::cout << "ERROR : Password doesnt match !" << std::endl;
				return false; // Passw�rter stimmen nicht �berein
			}
		}
	}
	// NOTIZ: Man k�nnte sich doch die ganze Prozedur sparen, wenn man userinput == password benutzt, oder ? Sry wenns ne dumme Idee ist 

	return true; // Passw�rter stimmen �berein
}