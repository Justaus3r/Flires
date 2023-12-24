#ifndef  TICKET_CREATION_INTERNAL_H
#define TICKET_CREATION_INTERNAL_H 

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>

using namespace std;

void replacePlaceholder(string& str, const string& placeholder, const string& replacement);

void replaceNameInTicketHTML(const string& inputHtmlTicket, const string& outputHtmlTicket, const string& newName, const string& age, const string& gender, const string& weight,
                       const string& eticketno, const string& flightname, const string& departdate, const string& baggage_weight,
                       const string& fare, const string& terminal) {
    ifstream inputFile(inputHtmlTicket.c_str());

    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << inputHtmlTicket << endl<<"Press Any Key to Continue...";
        _getch();
        exit(0);
    }

    string htmlContent((istreambuf_iterator<char>(inputFile)),
                       istreambuf_iterator<char>());

    replacePlaceholder(htmlContent, "<name>", newName);
    replacePlaceholder(htmlContent, "<age>", age);
    replacePlaceholder(htmlContent, "<gender>", gender);
    replacePlaceholder(htmlContent, "<weight>", weight);
    replacePlaceholder(htmlContent, "<eticketno>", eticketno);
    replacePlaceholder(htmlContent, "<flightname>", flightname);
    replacePlaceholder(htmlContent, "<departdate>", departdate);
    replacePlaceholder(htmlContent, "<baggage_weight>", baggage_weight);
    replacePlaceholder(htmlContent, "<fare>", fare);
    replacePlaceholder(htmlContent, "<terminal>", terminal);

    inputFile.close();

    ofstream outputFile(outputHtmlTicket.c_str());
    outputFile << htmlContent;
    outputFile.close();

}

void replacePlaceholder(string& str, const string& placeholder, const string& replacement) {
    size_t found = str.find(placeholder);
    while (found != string::npos) {
        str.replace(found, placeholder.length(), replacement);
        found = str.find(placeholder, found + replacement.length());
    }
}
#endif // ! TICKET_CREATION_INTERNAL_H

