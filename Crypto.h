
#pragma once
#ifndef _CRYPTO_H_
#define _CRYPTO_H_

#include <string>
#include <iostream>

// Header mit den Funktionen
std::string encoder (std::string input);
std::string decoder();
void inputPassword();
bool checkPassword ();

static const char* passwordFileName = "password.txt";
static const char* codeFileName = "code.txt";

#endif // _CRYPTO_H_
