#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

void FileRead(string *str)
{

    ifstream fin;
    fin.open("test.txt", ios::in);
    stringstream buf;
    buf << fin.rdbuf();
    *str = buf.str();

    //cout << *str << endl;

    fin.close();
}


#endif // FILE_H_INCLUDED
