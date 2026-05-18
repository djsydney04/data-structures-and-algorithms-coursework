/*
Full name: Dylan Mitic
Student ID: 2441836
Chapman email: mitic@chapman.edu
Course number and section: CPSC 350-01
Assignment or exercise number: A6
*/

#ifndef PROCESSFILES_H
#define PROCESSFILES_H

#include "WGraph.h"
#include <istream>
#include <string>

void processInput(std::istream& input, WGraph<std::string>& graph);
void processOutput(WGraph<std::string>& graph);

#endif
