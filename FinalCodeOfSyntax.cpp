#include<iostream>
#include<stack>
#include<algorithm>
#include <string>
#include <fstream>
using namespace std;
const int NUM_NONTERMINALS = 10; // number of nonterminals in the grammar
const int NUM_TERMINALS = 19; 
stack<string> stck;
stack<string> buffer;
string parse_table[NUM_NONTERMINALS][NUM_TERMINALS];
int Size=0;
enum NonTerminals {
    S,S1,D,I,G,K,C,E,Expr,T,Op
};
enum Terminals {
	Cout,lS,String,terminator,Cin,rS,variable,Type,Equal,number,ifCn,roundO,roundC,curlyO,curlyC,elseifCn,elseCn,arithmatic,conditional,$
    };
void parser(){
	// Initialize the parse table
for (int i = 0; i < NUM_NONTERMINALS; i++) {
    for (int j = 0; j < NUM_TERMINALS; j++) {
        parse_table[i][j] = "-1"; // set all entries to -1 as an error marker
    }
}
parse_table[S][Cout] = "Cout lS String terminator";
parse_table[S][Cin] = "Cin rS variable terminator";
}


bool matches (string a, string  b) {
	if (a == b) {
		return true;
	} else {
		return false;
	}
}
bool isTerminal(string s){
	//S,S1,D,I,G,K,C,E,Expr,T,Op
	if(s=="S"||s=="S1"||s=="D"||s=="I"||s=="G"||s=="K"||s=="C"
	||s=="E"||s=="Expr"||s=="T"||s=="Op") return false;
	return true;
}
string strRule(string terminal,string nonTerminal){
	if(terminal=="S"&&nonTerminal=="Cout")
		return "S1";
	else if(terminal=="S"&&nonTerminal=="Cin")
		return "S1";
	else if(terminal=="S"&&nonTerminal=="Type")
		return "D";
	else if(terminal=="S"&&nonTerminal=="ifCn")
		return "S1";
	else if(terminal=="S1"&&nonTerminal=="Cout")
		return "Cout lS string terminator";
	else if(terminal=="S1"&&nonTerminal=="Cin")
		return "Cin rS variable terminator";
	else if(terminal=="S1"&&nonTerminal=="ifCn")
		return "C";
	else if(terminal=="D"&&nonTerminal=="Type")
		return "Type I terminator";
	else if(terminal=="I"&&nonTerminal=="variable")
		return "variable G";
	else if(terminal=="G"&&nonTerminal=="terminator")
		return "0";
	else if(terminal=="G"&&nonTerminal=="Equal")
		return "Equal K";
	else if(terminal=="K"&&nonTerminal=="variable")
		return "variable";
	else if(terminal=="K"&&nonTerminal=="number")
		return "number";
	else if(terminal=="C"&&nonTerminal=="ifCn")
		return "ifCn roundO Expr roundC curlyO S curlyC E";
	else if(terminal=="E"&&nonTerminal=="Cout")
		return "S1";
	else if(terminal=="E"&&nonTerminal=="Cin")
		return "S1";
	else if(terminal=="E"&&nonTerminal=="ifCn")
		return "S1";
	else if(terminal=="E"&&nonTerminal=="curlyC")
		return "0";
	else if(terminal=="E"&&nonTerminal=="elseifCn")
		return "elseifCn roundO Expr roundC curlyO S curlyC E";
	else if(terminal=="E"&&nonTerminal=="elseCn")
		return "elseCn curlyO S curlyC";
	else if(terminal=="E"&&nonTerminal=="$")
		return "0";
	else if(terminal=="Expr"&&nonTerminal=="variable")
		return "T Op T";
	else if(terminal=="Expr"&&nonTerminal=="number")
		return "T Op T";
	else if(terminal=="T"&&nonTerminal=="variable")
		return "variable";
	else if(terminal=="T"&&nonTerminal=="number")
		return "number";
	else if(terminal=="Op"&&nonTerminal=="Equal")
		return "Equal";
	else if(terminal=="Op"&&nonTerminal=="arithmatic")
		return "arithmatic";
	else if(terminal=="Op"&&nonTerminal=="conditional")
		return "conditional";
	else return "-1";
	
}
//counts words in a string
int strA2(string a){
	int k=0;
	for(int i=0;i<a.length();i++){
		if(a[i]==' '){
			++k;
		}
	}
	Size=k;
	return k;
}

//returns string array that contains rules left for stack
string* strA(string a){
	a=a+" ";
	int k=0;
	string* arr= new string[strA2(a)];
	string Token="";
	for(int i=0;i<a.length();i++){

		Token=Token+a[i];
		if(a[i]==' '||a[i]=='\0'){
			//cout<<Token;
			arr[k]=Token;
			k++;
			Token="";
		}
	}
	return arr;
}
string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}
void storeStack(string *arr){
	stck.pop();
	for(int k=Size-1;k>=0;k--){
		
		stck.push(removeSpaces(arr[k]));
	}
}





///////////////////////////////////////////     lexical Analyzer
int i,chk=0;
int dfa = 0;
string currToken="";
string arr1[100][2]; 
int k=1,l=0; 
void state0(char c)
{
    if (c == '\"') {
    	currToken += c;
        dfa = 1;
    }
    else if(c=='\''){
    	currToken += c;
    	dfa=3;
	}
	else if (c == '/') {
    	currToken=currToken+c;
        dfa = 4;
    }
    else if (c=='+') {
    	currToken += c;
        dfa = 10;
    }
    else if (c=='-') {
    	currToken += c;
        dfa = 11;
    }
    else if (c=='*'||c=='%'||c=='='||c=='!'||c=='^') {
    	currToken += c;
        dfa = 12;
    }
    else if (c=='>') {
    	currToken += c;
        dfa = 14;
    }
    else if (c=='<') {
    	currToken += c;
        dfa = 13;
    }
    else if (c=='&') {
    	currToken += c;
        dfa = 9;
    }
    else if (c=='|') {
    	currToken += c;
        dfa = 15;
    }
    else if (c=='_'||(c>=65&&c<=90)||(c>=97&&c<=122)) {
    	currToken += c;
        dfa = 18;
    }
    else if (c=='('||c==';'||c== ':'||c == ','||c == '{'||
			c == '}'||c == '['||c == ']'||c == ')'||c=='#'
			||c=='?'||c=='!'||c=='~'||c=='^') {
    	currToken += c;
    	if(currToken==";"){
    	    arr1[k][l]="terminator";arr1[k][l+1]=currToken;
    	}
    	else if(currToken=="("){
    	    arr1[k][l]="roundO";arr1[k][l+1]=currToken;
    	}
    	else if(currToken==")"){
    	    arr1[k][l]="roundC";arr1[k][l+1]=currToken;
    	}
    	else if(currToken=="{"){
    	    arr1[k][l]="curlyO";arr1[k][l+1]=currToken;
    	}
    	else if(currToken=="}"){
    	    arr1[k][l]="curlyC";arr1[k][l+1]=currToken;
    	}
    	else{
    	arr1[k][l]="Special Symbol";arr1[k][l+1]=currToken;}
		k++;
        dfa = 20;
        currToken="";
    }
    else if (c >= '1' && c <= '9') {
    	currToken += c;
    	dfa=21;
    }
    else if(c=='0'){
    	currToken += c;
    	dfa=24;
	}
  
    else {
        dfa = 0;
        currToken="";
    }

}
void _1(char c)
{
	currToken=currToken+c;
    if (c == '\"') {
        dfa = 2;    
        arr1[k][l]="string";arr1[k][l+1]=currToken;
		k++;
    }
    else{
        dfa = 1;
    }
}
void _2(char c)
{
	dfa=0;
	currToken = "";
}
void _3(char c)
{
	
	currToken=currToken+c;
    if (c == '\'') {
        dfa = 2;
		arr1[k][l]="Character";arr1[k][l+1]=currToken[1];
		k++;   
    }
    else{
        dfa = 3;
    }
}
void _4(char c)
{

    if (c == '/') {
    	currToken=currToken+c;
        dfa = 5;
    }
    else if(c=='*'){
    	currToken=currToken+c;
        dfa = 7;
    }
    else{
    	arr1[k][l]="Operator";arr1[k][l+1]=currToken;
    	k++;
    	dfa=19;
    }
}
  void _5(char c)
{	
    if (c == '\n') {
    	//cout<<currToken<<endl;
    	//arr1[k][l]="Comment";arr1[k][l+1]=currToken;
		//k++;
        dfa = 6;
    }
    else {
    	currToken=currToken+c;
        dfa = 5;
    }
}

 void _6(char c)
{
	currToken="";
	dfa=0;
}
  void _7(char c)
{
	currToken=currToken+c;
    if (c == '*') {
        dfa = 8;
    }
    else {
        dfa = 7;
    }
}
 void _8(char c)
{
	currToken=currToken+c;
    if (c == '/') {
        dfa = 6;
        //arr1[k][l]="Comment";arr1[k][l+1]=currToken;
        //k++;
    }
    else {
        dfa = 7;
    }
}

void _10(char c)
{
	if (c=='+'||c=='=') {
    	currToken += c;
    	cout<<currToken<<endl;
    	arr1[k][l]="Operator ";arr1[k][l+1]=currToken;
		k++;
        dfa = 16;
    }
	else{
		cout<<currToken<<endl;
		arr1[k][l]="arithmetic";arr1[k][l+1]=currToken;
		k++;
		dfa=16;
	}
}
  void _11(char c)
{
	if (c=='-'||c=='=') {
    	currToken += c;
    	//cout<<currToken<<endl;
    	arr1[k][l]="Operator ";arr1[k][l+1]=currToken;
		k++;
        dfa = 16;
    }
	else{
		//cout<<currToken<<endl;
		arr1[k][l]="arithmetic";arr1[k][l+1]=currToken;
		k++;
		dfa=16;
	}
}
void _12(char c)
{
	if (c=='=') {
    	currToken += c;
    	//cout<<currToken<<endl;
    	arr1[k][l]="conditional";arr1[k][l+1]=currToken;
		k++;
        dfa = 16;
    }
	else{
		//cout<<currToken<<endl;
		if (currToken=="=")
		{
			arr1[k][l]="Equal";arr1[k][l+1]=currToken;
		}
		else
		arr1[k][l]="arithmetic";arr1[k][l+1]=currToken;
		k++;
		dfa=16;
	}
}
void _14(char c)
{
	if (c=='=') {
    	currToken += c;
    	//cout<<currToken<<endl;
    	arr1[k][l]="Operator ";arr1[k][l+1]=currToken;
		k++;
        dfa = 16;
    }
    else if(c=='>') {
    	currToken += c;
        dfa = 17;
    } 
	else {
		arr1[k][l]="conditional ";arr1[k][l+1]=currToken;
		k++;
		dfa=16;
	}
}
void _17(char c)
{
	if (c=='=') {
    	currToken += c;
    	//cout<<currToken<<endl;
    	arr1[k][l]="Operator ";arr1[k][l+1]=currToken;
		k++;
        dfa = 16;
    }
	else{
		//cout<<currToken<<endl;
		if(currToken=="<<"){
		    arr1[k][l]="lS ";arr1[k][l+1]=currToken;
		}
		else
		arr1[k][l]="rS ";arr1[k][l+1]=currToken;
		k++;
		dfa=16;
	}
}
void _13(char c)
{
	if (c=='=') {
    	currToken += c;
    	//cout<<currToken<<endl;
    	arr1[k][l]="Operator ";arr1[k][l+1]=currToken;
		k++;
        dfa = 16;
    }
    else if(c=='<') {
    	currToken += c;
    	arr1[k][l]="Operator ";arr1[k][l+1]=currToken;
        dfa = 17;
    } 
	else {
		//cout<<currToken<<endl;
		arr1[k][l]="conditional ";arr1[k][l+1]=currToken;
		k++;
		dfa=16;
	}
}
void _9(char c)
{
	if (c=='&') {
    	currToken += c;
    	//cout<<currToken<<endl;
    	arr1[k][l]="Operator ";arr1[k][l+1]=currToken;
		k++;
        dfa = 16;
    }
	else{
		//cout<<currToken<<endl;
		arr1[k][l]="Operator ";arr1[k][l+1]=currToken;
		k++;
		dfa=16;
	}
}
void _15(char c)
{
	if (c=='|') {
    	currToken += c;
    	//cout<<currToken<<endl;
    	arr1[k][l]="Operator ";arr1[k][l+1]=currToken;
		k++;
        dfa = 16;
    }
	else{
		//cout<<currToken<<endl;
		arr1[k][l]="Operator ";arr1[k][l+1]=currToken;
		k++;
		dfa=16;
	}
}



void _16(char c){
	dfa=0;
	currToken="";
}

void _18(char c){
	   if (c=='_'||(c>=65&&c<=90)||(c>=97&&c<=122)||c=='0'||c=='1'
		||c=='2'||c=='3'||c=='4'
		||c=='5'||c=='6'||c=='7'
		||c=='8'||c=='9') 
		{	
			currToken=currToken+c;
			dfa=18;
    	}
    	else{      
        	if(currToken== "while" || currToken== "do" ||
        		currToken== "break" || currToken== "continue"
				|| currToken== "int"|| currToken== "double" || currToken== "float"
				|| currToken== "return" || currToken== "char"|| currToken== "case" 
				|| currToken== "char"|| currToken== "sizeof" || currToken== "long"
				|| currToken== "short" || currToken== "typedef"
				|| currToken== "switch" || currToken== "unsigned"
				|| currToken== "void" || currToken== "static"
				|| currToken== "struct" || currToken== "goto"||currToken=="bool"
				|| currToken=="catch"||currToken=="class"||currToken=="struct"||currToken=="delete"
				||currToken=="for"||currToken=="private"||currToken=="protected"||currToken=="public"
				||currToken=="try"||currToken=="switch"||currToken=="case"||currToken=="true"||currToken=="using"
				||currToken=="define"||currToken=="auto"||currToken=="string")
				{
					arr1[k][l]="Type";arr1[k][l+1]=currToken;
					k++;
				}
			else if(currToken=="if"){
			        if(chk==1){
			          k--;
			            arr1[k][l]="elseifCn";arr1[k][l+1]="else if";
			            k++; 
			        }
			        else
					{arr1[k][l]="ifCn";arr1[k][l+1]=currToken;
					k++;}
					chk=1;
				}
			else if(currToken== "else"){
			    arr1[k][l]="elseCn";arr1[k][l+1]=currToken;
					k++;
			}
			else if(currToken=="cout"){
					arr1[k][l]="Cout";arr1[k][l+1]=currToken;
					k++;
				}
			else if(currToken=="cin"){
					arr1[k][l]="Cin";arr1[k][l+1]=currToken;
					k++;
				}
			else {
					arr1[k][l]="variable";arr1[k][l+1]=currToken;
					k++;
				}
			dfa=19;
    }
}

 void _19(char c)
{
	dfa=0;
	currToken = "";
}
void _20(char c)
{
    dfa=0;
	currToken = "";
}
/////////
void _21(char c) 
{
	if(c >= '0' && c <= '9')  {
    	currToken += c;
        dfa = 21;
    }
    else if(c=='.'){
    	currToken += c;
    	dfa=22;
	}
	else if(c=='\n'||c==';'||c==' '||c=='+'||c=='-'||
			c=='*'||c=='/'||c=='\0')
			{
			    cout<<c;
				arr1[k][l]="number";arr1[k][l+1]=currToken;
				k++;
				dfa=23;
			}
	else {
		dfa=0;
		currToken="";
	}
}
void _22(char c)
{
	if(c >= '0' && c <= '9')  {
    	currToken += c;
        dfa = 22;
    }
    else if(c=='\n'||c==';'||c==' '||c=='+'||c=='-'
			||c=='*'||c=='/'||c=='\0')
	{
		arr1[k][l]="number";arr1[k][l+1]=currToken;
		k++;
		dfa=23;
	}
    else{
        dfa = 0;
    }
}
void _23(char c)
{
	dfa=0;
	currToken="";
}
void _24(char c){
	if(c == 'x'){
    	currToken += c;
        dfa = 25;
    }
    else if(c=='.'){
    	currToken += c;
    	dfa=22;
	}
    else if(c>='1'&&c<='9'){
    	currToken = currToken+c;
        dfa = 21;
	}
	else if(c=='\n'||c==';'||c==' '||c=='+'||c=='-'
			||c=='*'||c=='/'||c=='\0')
	{
		arr1[k][l]="number";arr1[k][l+1]=currToken;
		k++;
		dfa=23;
	}
    else{
    	dfa=0;
    	currToken="";
	}
}
void _25(char c){
	if((c >= '0' && c <= '9')||c=='A'||c=='a'||c=='b'||c=='d'
	||c=='e'||c=='f'||c=='B'||c=='C'||c=='D'||c=='E'||c=='F')  {
    	currToken += c;
        dfa = 25;
    }
    else if(c=='\n'||c==';'||c==' '||c=='+'||c=='-'
			||c=='*'||c=='/'||c=='\0')
	{
		arr1[k][l]="number";arr1[k][l+1]=currToken;
		k++;
		dfa=23;
	}
	else {
		dfa=0;
		currToken="";
	}
}
//////////
int isAccepted(string str)
{
    int  len = str.length(); 
    for (i = 0; i < len; i++) {
        if (dfa == 0)
            {
			state0(str[i]);			}
        else if (dfa == 1)
            {
			_1(str[i]);
			}
        else if (dfa == 2)
        	{			
            _2(str[i]); 
			i--;         
        }
        else if (dfa == 3){
            _3(str[i]); 
        }
        else if (dfa == 4)
            {
			_4(str[i]);
			}
        else if (dfa == 5)
        	{			
            _5(str[i]);          
        }
        else if (dfa == 6){
            _6(str[i]); 
            i--;
        }
        else if (dfa == 7)
            {
			_7(str[i]);
			}
        else if (dfa == 8)
        	{			
            _8(str[i]);          
        }
          else if (dfa == 9)
            {
			_9(str[i]);
			}
        else if (dfa == 10)
        	{			
            _10(str[i]);          
        }
        else if (dfa == 11){
            _11(str[i]); 
        }
        else if (dfa == 12)
            {
			_12(str[i]);
			}
        else if (dfa == 13)
        	{			
            _13(str[i]);          
        }
        else if (dfa == 14){
            _14(str[i]); 
        }
        else if (dfa == 15)
            {
			_15(str[i]);
			}
        else if (dfa == 16)
        	{			
            _16(str[i]);          
			i--;  
			i--;      
        }
        else if (dfa == 17)
        	{			
            _17(str[i]); 
        }
        else if (dfa == 18)
        	{			
            _18(str[i]); 
        }
        else if (dfa == 19)
        	{		
            _19(str[i]); 
			i--;
			i--;	
        }
        else if (dfa == 20)
        	{		
            _20(str[i]);
            i--;
        }
        else if (dfa == 21)
        	{		
            _21(str[i]);
				
        }
        else if (dfa == 22)
        	{		
            _22(str[i]);
			
        }
        else if (dfa == 23)
        	{		
            _23(str[i]);
			i--; 
			i--;
        }else if (dfa == 24)
        	{		
            _24(str[i]);	
        }
        else if (dfa == 25)
        	{		
            _25(str[i]);	
        }
        else 
            i++;
    }  
}
///////////////////////////////////////////     lexical Analyzer



int main() {
	
    /// @code for lexical /////
    ///  
    string qu="";
	string myText;
	ifstream MyReadFile("sk.txt");
		while (getline (MyReadFile, myText)) {
  			qu=qu+"\n"+myText;
		}
    int a=0;
	cout<<qu;
	MyReadFile.close();
    isAccepted(qu);
    cout<<qu<<endl;
    cout<<"///////tt";
    for(int i=0;i<k;i++){
    	for(int j=0;j<=1;j++){
    		cout<<arr1[i][j]<<" \t\t";
		}
		cout<<endl;
	}	
	/// @brief /////
	/// @return ///
	buffer.push("$");
    // cout<<"///////tt";
	for(int i=k-1;i>=0;i--){

        buffer.push(arr1[i][0]);
        //cout<<buffer.top()<<" \t\t";
	}
	
	stck.push("$");
	stck.push("S");
	
	string TOP="",LookAhead="";
    buffer.pop();
    LookAhead=buffer.top();//cout<<LookAhead<<endl;
	//cout<<">>>>>>>>>>>>>"<<endl;
    //cout<<LookAhead;
    //cout<<">>>>>>>>>>>>>"<<endl;
	while(!stck.empty()&&!buffer.empty()){
		TOP=stck.top(); //cout<<TOP<<endl;
			LookAhead=buffer.top();//cout<<LookAhead<<endl;
			if(!isTerminal(TOP)){
				//cout<<"Check1 top="<<TOP<<" "<<TOP<<endl;
				LookAhead=removeSpaces(LookAhead);
				TOP=removeSpaces(TOP);
				
				if (strRule(( TOP),(LookAhead))=="-1") 
				{
					//cout<<"Check2"<<endl;
					cout<<removeSpaces(LookAhead)<<""<<TOP<<"k";
					cout<<"\tInvalid String..."<<endl;
					return 0;
				}
			
				else if (strRule(TOP,LookAhead)=="0") 
				{
					stck.pop();

				}
				else if(strRule(TOP,LookAhead)!="-1"){
					//cout<<"Check3"<<endl;
						storeStack(strA(strRule(TOP,LookAhead)));
				}
			//cout<<"Check4"<<endl;
			}
			else{
				//cout<<"Check5"<<" LookAhead ="<<LookAhead<<"Top="<<TOP<<";;"<<endl;
				if (LookAhead=="$"&&TOP=="$"){
				//	cout<<"Check6"<<endl;
					cout<<"Valid String.."<<endl;
					return 0;
				}
				else if (stck.top()=="$"){
				    stck.push("S");
				}
				else if(removeSpaces(LookAhead)==removeSpaces(TOP)){
			       // cout<<"bufferTop"<<LookAhead<<" "<<TOP;
				//	cout<<"Check7"<<endl;
					buffer.pop();
					stck.pop();
					
				}
				else{
				//	cout<<"Check8"<<endl;
                    cout<<LookAhead<<" "<<TOP;
					cout<<"\tInvalid String..."<<endl;
					return 0;
				}
			}

	}
	
return 0;
}
