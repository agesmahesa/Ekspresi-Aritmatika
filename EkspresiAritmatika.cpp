/*	Anggota Kelompok	: Muhammad Donda Fauzaan (2017051036)
				: Nesa Dwi Cahyani (2017051009)
				: Ages Mahesa (2017051027)
*/

// PARSING STRING INFIX

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
    cout << data << endl;
}

// KONVERSI INFIX TO POSTFIX

#include <bits/stdc++.h>

using namespace std;

long unsigned int i;
bool Symbol(char a){
    if(a=='*' || a=='/' || a=='+' ||a=='-' || a=='%'){
        return true; 
    } else {    
        return false; 
    }
}

int parse(char a){ 
    if(a=='+' || a=='-'){ 
        return 1; 
    }
    if(a=='*' || a=='/' || a=='%'){ 
        return 2; 
    } 
    return 0;
}

string ubah(string b){
    stack <char> data;
    string postfix = "";
    
    for(i=0; i<b.length(); i++){
        if(isdigit(b[i])){
            while(i<b.length() && isdigit(b[i])){
                postfix += b[i];
                i++;
            }
            i--;
            postfix += " ";
        }else if(b[i] == '('){
            data.push(b[i]);
        }else if(b[i] == ')'){
            while(!data.empty() && data.top() != '('){
                postfix += data.top();
                data.pop();
                postfix += " ";
            }
            data.pop();
        }else{
            if(b[i] == '-'){
                if(i==0){
                    if(isdigit(b[i+1])){
                        postfix += b[i];
                        i++;
                        while(i<b.length() && isdigit(b[i])){
                            postfix += b[i];
                            i++;
                        }
                        i--;
                        postfix += " ";
                    }else{
                        postfix += "-1 ";
                        data.push('*');
                    }
                }else{
                    while(!data.empty() && parse(data.top()) >= parse(b[i]) && !Symbol(b[i-1])){
                        postfix += data.top();
                        postfix += " ";
                        data.pop();
                    }
                    if((isdigit(b[i+1]) || b[i+1]=='(') && (isdigit(b[i-1]) || b[i-1]==')')){
                        data.push(b[i]);
                    }else{
                        postfix += "-1 ";
                        data.push('*');
                    }
                }
            }else{
                while(!data.empty() && parse(data.top()) >= parse(b[i])){
                    postfix += data.top();
                    postfix += " ";
                    data.pop();
                }
                data.push(b[i]);
            }
        }
    }
    while(!data.empty()){
        postfix += data.top();
        postfix += " ";
        data.pop();
    }
    return postfix;
}
int main(){
    string c;
    getline(cin, c);
    string baru_c="";
    
    for(i=0; i<c.length(); i++){
        if(c[i]==' '){
            continue;
        }else{
            baru_c+= c[i];    
        }        
    }
    cout << ubah(baru_c);
    return 0;
}

// EVALUASI ARITMATIKA
#include <bits/stdc++.h>

using namespace std;

long unsigned int i;

bool Symbol(char a){
    if(a=='*' || a=='/' || a=='+' ||a=='-' || a=='%'){
        return true; 
    } else {    
        return false; 
    }
}

int parse(char a){ 
    if(a=='+' || a=='-'){ 
        return 1; 
    }
    if(a=='*' || a=='/' || a=='%'){ 
        return 2; 
    } 
    return 0;
}


double applyOpr(double satu, double dua, char opr){
    switch(opr){
        case '*': return satu * dua;    
        case '/': return satu / dua; 
        case '+': return satu + dua; 
        case '-': return satu - dua;
        }
    return 0;
}



void hasil(string in){
    stack<double> data;
    stack<char>operasi;

    for(i=0; i<in.length(); i++){
        if(isdigit(in[i])){
            int nilai=0;
            while(i<in.length() && isdigit(in[i])){
                nilai = (nilai*10) + (in[i] - '0');
                i++;
            }
            i--;
            data.push(nilai);
        }
            else if(in[i] == '(')
                operasi.push(in[i]);
            else if(in[i] == ')'){
                while(!operasi.empty() && operasi.top() != '('){
                    if(operasi.top() == '%'){
                        int kedua = data.top(); data.pop();
                        int pertama  = data.top(); data.pop();
                        operasi.pop();
                        data.push(pertama %kedua);
                        
                    } 
                    else
                         {
                        double kedua = data.top(); data.pop();
                        double pertama  = data.top(); data.pop();
                        char opr = operasi.top(); operasi.pop();
                        data.push(applyOpr(pertama , kedua, opr));
                    }
                }
                
                if(!operasi.empty())
                    operasi.pop();
                    
            } 
            else 
                {
                if(in[i] == '-'){
                    if(i==0){
                        if(isdigit(in[i+1])){
                            i++;
                            int nilai=0;
                            while(i<in.length() && isdigit(in[i])){
                                nilai = (nilai*10) + (in[i] - '0');
                                i++;
                            }
                            i--;
                            data.push(nilai*-1);
                        } else {
                            data.push(-1);
                            operasi.push('*');
                        }
                        
                    } 
                    else 
                        {
                        while(!operasi.empty() && parse(operasi.top()) >= parse(in[i]) && !Symbol(in[i-1])){
                            if(operasi.top() == '%'){
                                int kedua = data.top(); data.pop();
                                int pertama  = data.top(); data.pop();
                                operasi.pop();
                                data.push(pertama %kedua);
                            
                            } 
                            else 
                                {
                                double kedua = data.top(); data.pop();
                                double pertama  = data.top(); data.pop();
                                char opr = operasi.top(); operasi.pop();
                                data.push(applyOpr(pertama , kedua, opr));
                            }
                        }
                        if((isdigit(in[i+1]) || in[i+1]=='(') && (isdigit(in[i-1]) || in[i-1]==')'))
                            operasi.push(in[i]);
                        
                        else
                            {
                            data.push(-1);
                            operasi.push('*');
                        }
                    } 
                    
                } 
                else 
                    {
                    while(!operasi.empty() && parse(operasi.top()) >= parse(in[i])){
                        if(operasi.top() == '%'){
                            int kedua = data.top(); data.pop();
                            int pertama  = data.top(); data.pop();
                            operasi.pop();
                            data.push(pertama %kedua);
                        } 
                        else 
                            {
                            double kedua = data.top(); data.pop();
                            double pertama  = data.top(); data.pop();
                            char opr = operasi.top(); operasi.pop();
                            data.push(applyOpr(pertama , kedua, opr));
                        }
                    }
                    operasi.push(in[i]);
                }
            }
        }
        
        while(!operasi.empty()){
            if(operasi.top() == '%'){
                int kedua = data.top(); data.pop();
                int pertama  = data.top(); data.pop();
                operasi.pop();
                data.push(pertama %kedua);
         
            } 
            else 
                {
                double kedua = data.top(); data.pop();
                double pertama  = data.top(); data.pop();
                char opr = operasi.top(); operasi.pop();
                data.push(applyOpr(pertama , kedua, opr));
            }
        }
        cout << data.top() << endl;
    }

int main(){
    string ekspresi; getline(cin,ekspresi);
    string baru_ekspresi="";
    for(i=0;i<ekspresi.length();i++){
        if(ekspresi[i]==' ')
            continue;
        else
            baru_ekspresi+=ekspresi[i];
    }
    hasil(baru_ekspresi);

    return 0;
}
