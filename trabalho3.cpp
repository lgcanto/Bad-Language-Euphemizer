#include <EXTERN.h>
#include <stdio.h>
#include <perl.h>
#include <exception>
#include <string>
#include <iostream>
#include "trabalho3.h"
using namespace std;

//------------------------Erros------------------------------//
string aexists="Nome já utilizado por outro arquivo.";
string dexists="Arquivo não encontrado.";
string not10 = "Por favor, apenas insira 0 ou 1:";

inline void erro10(string c){
	if(c!="1" && c!="0")
    throw not10;
}

Filtro::Filtro(){
	
	int argc;char **argv;char **env;
	PERL_SYS_INIT3(&argc, &argv, &env);
    my_perl = perl_alloc();
    perl_construct(my_perl);
    PL_exit_flags |= PERL_EXIT_DESTRUCT_END;	
	
	censurapm="censura.pm";
	eufemizapm="eufemismo.pm";
	printfilepl="printfile.pl";
	
	cout<<endl<<endl;
	cout<<"--------Bem-vindo ao Filtro de Má Linguagem--------"<<endl<<endl<<endl<<endl;
	cout<<"Atenção: para que o programa funcione corretamente coloque seus arquivos de texto a serem modificados na pasta raíz do programa."<<endl<<endl;
}

Filtro::~Filtro(){
	perl_destruct(my_perl);
    perl_free(my_perl);
    PERL_SYS_TERM();
	cout<<endl<<endl;
	cout<<"----------------Programa Finalizado----------------"<<endl<<endl<<endl<<endl;
}



string Filtro::getInTitle(){
	return infilename;
}

string Filtro::getOutTitle(){
	return outfilename;
}

void Filtro::chooseInTitle(){
	bool c=1;
	cout<<endl<<"Insira o nome do arquivo texto a ser modificado:"<<endl;
	while(c){
		getline(cin,infilename);
		try{
			if(!exists(getInTitle() ) )
			throw dexists;
			c=0;
		}
		catch(string erro1){
			cout<<erro1<<endl;
			cout<<endl<<"Por favor, insira o nome de um arquivo existente:"<<endl;
		}
	}
}

void Filtro::chooseOutTitle(){
	bool c=1;
	cout<<endl<<"Insira um nome para o novo arquivo:"<<endl;
	while(c){
		getline(cin,outfilename);
		try{
			if(exists(getOutTitle() ) )
			throw aexists;
			c=0;
		}
		catch(string erro2){
			cout<<erro2<<endl;
			cout<<endl<<"Por favor, insira um nome ainda não utilizado:"<<endl;
		}
	}
}

void Filtro::censurar(){
	string c;
	bool c2=1;
	
	char* censuraPack = const_cast<char*> ( censurapm.c_str() );
	char* ofile = const_cast<char*> ( outfilename.c_str() );
	char* ifile = const_cast<char*> ( infilename.c_str() );
	char *args[]={ifile,ofile,NULL};
	char *my_argv[] = {NULL,censuraPack}; //"censura.pm"
	perl_parse(my_perl, NULL,2, my_argv, (char **)NULL);
	perl_run(my_perl);
	call_argv("censurar", G_DISCARD,args);

	cout<<endl<<"Ver texto censurado?"<<endl<<"1-sim"<<endl<<"0-não"<<endl<<endl;
	while(c2){
		try{
			getline(cin,c);
			erro10(c);
			if(c=="1")
			showFile(outfilename);
			c="nothing";
			c2=0;
		}
		catch(string erro){
			cout<<erro<<endl;
		}
	}
	c2=1;
	cout<<endl<<"Ver arquivo original?"<<endl<<"1-sim"<<endl<<"0-não"<<endl<<endl;
	while(c2){
		try{
			getline(cin,c);
			erro10(c);
			if(c=="1")
			showFile(infilename);
			c="nothing";
			c2=0;
		}
		catch(string erro){
			cout<<erro<<endl;
		}
	}
}

void Filtro::eufemizar(){
	string c;
	bool c2=1;
	char* eufemizaPack = const_cast<char*> ( eufemizapm.c_str() );
	char* ofile = const_cast<char*> ( outfilename.c_str() );
	char* ifile = const_cast<char*> ( infilename.c_str() );
	char *args2[]={ifile,ofile,NULL};
	char *my_argv2[] = {NULL,eufemizaPack};
	perl_parse(my_perl, NULL,2, my_argv2, (char **)NULL);
    perl_run(my_perl);
    call_argv("eufemizar", G_DISCARD,args2);

    cout<<endl<<"Ver texto eufemizado?"<<endl<<"1-sim"<<endl<<"0-não"<<endl<<endl;
	while(c2){
		try{
			getline(cin,c);
			erro10(c);
			if(c=="1")
			showFile(outfilename);
			c="nothing";
			c2=0;
		}
		catch(string erro){
			cout<<erro<<endl;
		}
	}
	c2=1;
	cout<<endl<<"Ver arquivo original?"<<endl<<"1-sim"<<endl<<"0-não"<<endl<<endl;
	while(c2){
		try{
			getline(cin,c);
			erro10(c);
			if(c=="1")
			showFile(infilename);
			c="nothing";
			c2=0;
		}
		catch(string erro){
			cout<<erro<<endl;
		}
	}
	
}

void Filtro::showFile(string file){
	cout<<endl;
	cout<<"----------Arquivo "<<"'"<<file<<"'"<<" ------------";
	cout<<endl<<endl;
	char* printPack = const_cast<char*> ( printfilepl.c_str() );
	char* ofile = const_cast<char*> ( file.c_str() );
	char *args3[]={ofile,NULL};
	char *my_argv3[] = {NULL,printPack};
	perl_parse(my_perl, NULL,2, my_argv3, (char **)NULL);
    perl_run(my_perl);
    call_argv("printfile", G_DISCARD,args3);
    cout<<endl;
    cout<<"---------------------------------------------------";	
}