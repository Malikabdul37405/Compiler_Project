#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;
void _0(char c);
void _1(char c);
void _2(char c);
void _3(char c);
void _4(char c);
void _5(char c);
void _6(char c);
void _7(char c);
void _8(char c);
void _9(char c);
void _10(char c);
void _11(char c);
void _12(char c);
void _13(char c);
void _14(char c);
void _15(char c);
void _16(char c);
void _17(char c);
void _18(char c);
void _19(char c);
void _20(char c);
void _21(char c);
void _22(char c);
void _23(char c);
void _24(char c);
void _25(char c);
void _26(char c);
void _27(char c);
void _28(char c);
void _29(char c);
void _30(char c);
void _31(char c);
void _32(char c);

bool isKeyword(const string &str)
{
    // List of C++ keywords
    unordered_set<string> keywords = {
        "alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit",
        "atomic_noexcept", "auto", "bitand", "bitor", "bool", "break", "case", "catch",
        "char", "char8_t", "char16_t", "char32_t", "class", "compl", "concept", "const",
        "consteval", "constexpr", "const_cast", "continue", "co_await", "co_return",
        "co_yield", "decltype", "default", "delete", "do", "double", "dynamic_cast",
        "else", "enum", "explicit", "export", "extern", "false", "float", "for", "friend",
        "goto", "if", "import", "inline", "int", "long", "module", "mutable", "namespace",
        "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private",
        "protected", "public", "reflexpr", "register", "reinterpret_cast", "requires",
        "return", "short", "signed", "sizeof", "static", "static_assert", "static_cast",
        "struct", "switch", "synchronized", "template", "this", "thread_local", "throw",
        "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using",
        "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq", "string"};

    // Check if the string is a C++ keyword
    return keywords.count(str) > 0;
}
bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool id(char c)
{
	if(c=='_' || (c>='a' && c<= 'z') || (c>= 'A' && c<= 'Z' ))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool constant(char c)
{
	  return (isDigit(c) || c == '.');
}
bool ws(char c)
{
	if(c==' ' || c=='\n' || c=='\r' || c=='\t' )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool op(char c)
{
	if(c==' ' || c=='+' || c=='-' || c=='*' || c=='\'' )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool spch(char c)
{
	if(c=='('||c==';'||c== ':'||c == ','||c == '{'||
	c == '}'||c == '['||c == ']'||c == ')'||c=='#'
    ||c=='?'||c=='!')
	{
		return true;
	}
	else
	{
		return false;
	}
}

//start 
	
int dfa = 0;

string currToken="";
string arr[100][2]; 
int k=1,l=0;
string symbolTab[100][3];
int z = 0;

void _0(char c)    
{
    
    
    
	// String 
	
	if (c == '\"') {
    	currToken += c;
        dfa = 16;
    }
	else if (c == '\'') {
    	currToken += c;
        dfa = 17;
    }
    
    //Constant
    
    else if (c >= '1' && c <= '9') 
	{
    	currToken += c;
    	dfa=19;
    }
	else if (c== '0') 
	{
    	currToken += c;
    	dfa=21;
    }
    
    //Identifier 
    
    else if (c=='-'||(c>='a'&&c<='z')||(c>='A'&&c<='Z')) 
	{
    	currToken += c;
        dfa = 24;
    }
    
    // Special
    
    else if (c=='('||c==';'||c== ':'||c == ','||c == '{'||
			c == '}'||c == '['||c == ']'||c == ')'||c=='#'
			||c=='?'||c=='!')
    {
    	currToken += c;
    	dfa=26;
    }
    
    // Comment 
    
    else if (c == '/')
	 {
    	currToken=currToken+c;
        dfa = 27;
    }
    

    
    else if (c=='&')
    {
    	currToken=currToken+c;
    	dfa = 1;
	}
	
	else if (c=='+')
    {
    	currToken=currToken+c;
    	dfa = 3;
	}
	
	else if (c=='-')
    {
    	currToken=currToken+c;
    	dfa = 5;
	}
	
	else if (c=='*'||c=='%'||c=='='||c=='!')
    {
    	currToken=currToken+c;
    	dfa = 7;
	}
	
	else if (c=='<')
    {
    	currToken=currToken+c;
    	dfa = 9;
	}
	
	else if (c=='>')
    {
    	currToken=currToken+c;
    	dfa = 11;
	}
    
    else if (c=='|')
    {
    	currToken=currToken+c;
    	dfa = 13;
	}
    
    else if(ws(c))
    {
        dfa=0;
        	currToken="";
    }
    
}

 // Operator 
    void _1(char c)
    {
    	if (c=='&')
    	{
    		currToken += c;
			dfa = 2; 
		}
		else if(ws(c) || id(c) || constant(c))
	 {
		
	_15(c);
     }
	}
	

    void _2(char c)
    {
    	if(ws(c) || id(c) || constant(c))
	 {
	
	_15(c);
     }
	}
	

    void _3(char c)
    {
    	if (c=='+' || '=')
    	{
    		currToken += c;
			dfa = 4; 
		}
	    else if(ws(c) || id(c) || constant(c))
	 {
		
		_15(c);
     }
		
	}
	

    void _4(char c)
    {
    	if(ws(c) || id(c) || constant(c))
	 {
	
		_15(c);
     }
	}
	
	
    void _5(char c)
    {
    	if (c=='-' || '=')
    	{
    		currToken += c;
			dfa = 6; 
		}
		
		else if(ws(c) || id(c) || constant(c))
	 {
	
		_15(c);
     }
	}
	
	
    void _6(char c)
    {
    	if(ws(c) || id(c) || constant(c))
	 {

		_15(c);
     }
	}
	
	
    void _7(char c)
    {
 if(ws(c) || id(c) || constant(c)||spch(c))
	 {
		
		_15(c);
     }
       else if (c=='=')
    	{
    		currToken += c;
			dfa = 8; 
		}
		
	
	}
	
	
    void _8(char c)
    {
    	if(ws(c) || id(c) || constant(c)||spch(c))
	 {
		
		_15(c);
     }
	}
	
	
    void _9(char c)
    {
    	if (c== '='|| c== '<')
    	{
    		currToken += c;
			dfa = 10; 
		}
		
		else if(ws(c) || id(c) || constant(c)||spch(c))
	 {
		_15(c);
     }
	}
	
	
    void _10(char c)
    {
    	if(ws(c) || id(c) || constant(c)||spch(c))
	 {
		
		_15(c);
     }
	}
	
	
    void _11(char c)
    {
    	if (c=='='|| c== '>')
    	{
    		currToken += c;
			dfa = 12; 
		}
		
		else if(ws(c) || id(c) || constant(c)||spch(c))
	 {
	
	_15(c);
     }
	}
	
	
    void _12(char c)
    {
    	if(ws(c) || id(c) || constant(c)||spch(c))
	 {
		
		_15(c);
     }
	}
	
	
    void _13(char c)
    {
    	if (c=='|')
    	{
    		currToken += c;
			dfa = 14; 
		}
		
		else if(ws(c) || id(c) || constant(c)||spch(c))
	 {
		
		_15(c);
     }
	}
	

    void _14(char c)
    {
    	if(ws(c) || id(c) || constant(c)||spch(c))
	 {
	
		_15(c);
     }
	}
	
	

    void _15(char c)
   {
	arr[k][l]="Operator";
		arr[k][l+1]=currToken;
		k++;
        currToken="";
		_0(c);
   }
	 void _16(char c)
    {
	currToken=currToken+c;
    if (c == '"')
     {
       currToken += c;
       _18(c);
     }
    else
	  {
        dfa = 16;
      }
    }
    
    
    // String
    
    void _17(char c)
    {
	currToken=currToken+c;
    if (c == '\'')
     {
      currToken += c;
       _18(c);
     }
    else
	  {
        dfa = 17;
      }
    }
    
    // String
    
    void _18(char c)
    {
	     
        arr[k][l]="String ";arr[k][l+1]=currToken;
        currToken="";
		k++;
        _0(c);
    }
    
    
    
    void _19(char c)
    {
	if(isDigit(c)) 
	{
    	currToken += c;
        dfa = 19;
    }
    else if(c=='.')
	{
    	currToken += c;
    	dfa=20;
	}
	else if(ws(c)||spch(c)||op(c))
	{
		_23(c);
	}
	else 
	{
		dfa=-1;
		currToken="";
	}
    
	}
	

    
    void _21(char c)
    {
	if(c == 'x' ) 
	{
    	currToken += c;
        dfa = 22;
    }
    else if(c=='.')
	{
    	currToken += c;
    	dfa=20;
	}
	else if(isDigit(c)) 
	{
    	currToken += c;
        dfa = 19;
    }
	else if(ws(c)||spch(c)||op(c))
	{
	_23(c);
	}
	else 
	{
		dfa=-1;
		currToken="";
	}
    }
    
    
    
    void _20(char c)
    {
	if(isDigit(c)) 
	{
    	currToken += c;
        dfa = 20;
    }
	else if(ws(c)||spch(c)||op(c))
	{
	
		_23(c);
	}
	else 
	{
		dfa=-1;
		currToken="";
	}
    }
    

    
    void _22(char c)
    {
	if(isDigit(c)||c=='A'||c=='B'||c=='C'||c=='D'
	||c=='E'||c=='F'||c=='a'||c=='b'||c=='c'||c=='d'||c=='e'||c=='f') 
	{
    	currToken += c;
        dfa = 22;
    }
	else if(ws(c)||spch(c)||op(c))
	{
		
		_23(c);
	}
	else 
	{
		dfa=-1;
		currToken="";
	}
    }
    
    
    
    void _23(char c)
    {
	 
		arr[k][l]="Constant";arr[k][l+1]=currToken;
		k++;
	 currToken = "";
             _0(c);
    }

    // Ientifier
    
    void _24(char c){
	   if (c=='-'||(c>='a'&&c<='z')||(c>='A'&&c<='Z')||c=='0'||c=='1'
		||c=='2'||c=='3'||c=='4'
		||c=='5'||c=='6'||c=='7'
		||c=='8'||c=='9') 
		{	
			currToken=currToken+c;
			dfa=24;
    	}
    	else {
            _25(c);
        }
}

    

    void _25(char c)
   {
	 if (isKeyword(currToken))
    {
       arr[k][l]="Keyword";arr[k][l+1]=currToken;
		k++;
        currToken="";
        _0(c);
    }
    else
    {
      arr[k][l]="identifier";arr[k][l+1]=currToken;
		k++;
        currToken="";
        _0(c);
    }
   }
   
   // Special 
   
   

    void _26(char c)
   {
	arr[k][l]="Special Symbol";
		arr[k][l+1]=currToken;
		 k++;
        currToken="";
        _0(c);
   }
   
   // Comment
   
   void _27(char c)
   {
   	if(c == '/') 
	{
    	currToken += c;
        dfa = 28;
    }
   	
   	else if(c == '*') 
	{
    	currToken += c;
        dfa = 30;
    }
    
    else if(c == '=') 
	{
    	currToken += c;
        dfa = 29;
    }
   	
   	else if(ws(c) || id(c) || constant(c)){
		
		_15(c);
   	
   }
}


   
   void _28(char c)
   {
   	if (c == '\n')
	{
        dfa = 32;
    }
    else
	{
    	currToken=currToken+c;
        dfa = 28;
    }
   }


   
   void _29(char c)
   {
   	if(ws(c) || id(c) || constant(c))
	 {
		
	_15(c);
     }
    }
    
    
   
   void _30(char c)
   {
   	if (c == '*')
	{
        dfa = 31;
    }
    else 
	{
    	currToken=currToken+c;
        dfa = 30;
    }
   }
   
   
   void _31(char c)
   {
	currToken=currToken+c;
    if (c == '/')
	{
        dfa = 32;
              
    }
    else if(c=='*')
	{
    	currToken=currToken+c;
        dfa = 31;
    }
    else 
	{
        dfa = 30;
    
    }
    }
    
    

    void _32(char c)
   {
	dfa=0;
	currToken = "";
   }
   
void isAccepted(string str)
{
    int i, len = str.length(); 
    for (i = 0; i < len; i++)
	 {
        if (dfa == 0)
            {
			_0(str[i]);			
			}
        else if (dfa == 1)
            {
			_1(str[i]);
			}
        else if (dfa == 2)
        	{			
            _2(str[i]); 
            
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
	
        }
        else if (dfa == 20)
        	{		
            _20(str[i]);
            
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
           
        }
		else if (dfa == 24)
        	{		
            _24(str[i]);	
        }
        else if (dfa == 25)
        	{		
            _25(str[i]);
				
        }
        else if (dfa == 26)
        	{			
            _26(str[i]); 
          
        }
		else if (dfa == 27)
        	{			
            _27(str[i]);
        }
		else if (dfa == 28)
        	{			
            _28(str[i]); 
        }
		else if (dfa == 29)
        	{			
            _29(str[i]); 
        }
		else if (dfa == 30)
        	{			
            _30(str[i]); 
        }
		else if (dfa == 31)
        	{			
            _31(str[i]); 
        }
		else if (dfa == 32)
        	{			
            _32(str[i]);
			
        }
        
    }  
}

int main()
{
	string q=" char b=5; \n";
    isAccepted(q);
    for(int i=0;i<k;i++)
	{
    	for(int j=0;j<=1;j++)
		{
    		cout<<arr[i][j]<<" \t\t";
		}
		cout<<endl;
	}	
	
	cout<<"***"<<endl;
	cout<<"SYMBOL TABLE:" << endl;
    for (int i = 0; i < z; i++)
    {
        cout << symbolTab[i][0] << endl;
    }
		
    return 0;
}