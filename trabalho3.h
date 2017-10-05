#include <EXTERN.h>
#include <stdio.h>
#include <perl.h>
#include <exception>
#include <string>
#include <iostream>
using namespace std;

static PerlInterpreter *my_perl;

class Filtro
{
public:
	Filtro();
	~Filtro();
	string getInTitle();
	string getOutTitle();
	void chooseInTitle();
	void chooseOutTitle();
	void censurar();
	void eufemizar();
	void showFile(string file);
private:
	string infilename;
	string outfilename;
	string censurapm;
	string eufemizapm;
	string printfilepl;
};

inline bool exists(const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

void erro10(string c);