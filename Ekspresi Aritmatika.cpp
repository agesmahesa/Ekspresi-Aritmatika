/*	Anggota Kelompok	: Muhammad Donda Fauzaan (2017051036)
				: Nesa Dwi Cahyani (2017051009)
				: Ages Mahesa (2017051027)*/

//Parsing String Infix
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

void Parsing_String_Infix(string input);

int main(){
    string input;
    getline(cin, input);
    Parsing_String_Infix(input);
    return 0;
}

void Parsing_String_Infix(string input){
    vector <char> parse;
    string data;

    char Number[] = "0123456789";
    char Symbol[] = "+-/%*";
    char Delimiter[] = "()";
    char c[1];

    for(auto i : input){
        c[0] = i;
        if(strspn(c, Symbol) || strspn(c, Number) || strspn(c, Delimiter)){
            parse.push_back(i);
        }
    }
    for (long unsigned int i = 0; i != parse.size(); i++){    
        c[0] = parse[i];

        if((strspn(c, Symbol) || parse[i] == ')') && parse[i] != '(' && i > 0){
            data += " ";
        }
        if(strspn(c, Number)){
            data += parse[i];
        }else{
            data += parse[i];
            if(i > 0){
                c[0] = parse[i - 1];

                if(parse[i] != '(' && strspn(c, Symbol)){
                    data += "1 * ";
                }else if(parse[i] != ')'){
                    c[0] = parse[i + 1];

                    if(!strspn(c, Symbol)){
                        data += " ";
                    }
                }
            }else if(parse[i + 1] == '('){
                data += "1 * ";                
            }
        }
    }
    cout << "Print : "<< data << endl;
}