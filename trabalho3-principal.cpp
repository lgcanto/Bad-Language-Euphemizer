#include <string>
#include <iostream>
#include <exception>
#include "trabalho3.h"
using namespace std;

int main()
{	
    Filtro a;
    string c;
    bool c2=1;
    bool c3=1;
    bool c4;
    while(c2){
        a.chooseInTitle();
        a.chooseOutTitle();
        cout<<endl<<"Você deseja censurar ou eufemizar o arquivo?"<<endl<<"1-censurar"<<endl<<"0-eufemizar"<<endl<<endl;
        while(c3){
            try{
                getline(cin,c);
                erro10(c);
                if(c=="1"){
                    a.censurar();
                }else{
                    a.eufemizar();
                }
                c="nothing";
                c3=0;
            }
            catch(string erro){
                cout<<erro<<endl;
            }
        }
        cout<<endl<<"Fazer outra operação?"<<endl<<"1-sim"<<endl<<"0-fechar programa"<<endl<<endl;
        c4=1;
        while(c4){
            try{
                getline(cin,c);
                erro10(c);
                if(c=="1"){
                    c3=1;
                }else{
                    c2=0;
                }
                c="nothing";
                c4=0;
            }
            catch(string erro){
                cout<<erro<<endl;
            }
        }
    }
    
    return 0;
}	