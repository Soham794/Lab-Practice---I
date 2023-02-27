#include<bits/stdc++.h>
#include<fstream>

using namespace std;

class Macro_Pass2
{   
 
    struct MNT
    {
        int mntc;
        int mdtc;
        string macro_name;
    };
    
    struct MDT
    {
        int mdtc;
        string statement;
    };
    
    MNT mnt[100];
    MDT mdt[2000];

    int mnt_cnt = 0, mdt_cnt = 0;
    
  public:
  	void GetMDT();
  	void GetMNT();
    void Initiate_PassII();
    void PrintMNT();
    void PrintMDT();
};


void Macro_Pass2 :: GetMNT(){
	fstream input;
	input.open("macro_pass1_mnt.txt", ios::in);
	string word;
	for(int i=0;i<4;i++) input>>word;
	while(!input.eof()){
		
		input>>word;
		mnt[mnt_cnt].mntc = stoi(word);// string to int 
		input>>word;
		mnt[mnt_cnt].macro_name = word;
		input>>word;
		mnt[mnt_cnt].mdtc = stoi(word);
		mnt_cnt++;
	}
}

void Macro_Pass2 :: GetMDT(){
	fstream input;
	input.open("macro_pass1_mdt.txt", ios::in);
	string word;
	for(int i=0;i<3;i++) input>>word;

	while(!input.eof()){

		input>>word;

		mdt[mdt_cnt].mdtc = stoi(word);
		input>>word;

		if(word == "mend"){
			mdt[mdt_cnt].statement = word;
		}
		else{
			string line = "";
			line += word;
			line += " ";
			input>>word;
			line += word;
			line += " ";
			input>>word;
			line+=word;
			line += " ";
			mdt[mdt_cnt].statement = line;
		}
		mdt_cnt++;
	}
}


void Macro_Pass2 ::Initiate_PassII()
{
    fstream input , output;
    string buffer;
    
    input.open("macro_pass1_out.txt" , fstream::in);
    output.open("macro_pass2_out.txt", fstream::out);

    while(!input.eof())
    {
        bool is_macro = false;

        input>>buffer;// current word

        for(int i=0;i<mnt_cnt;i++)
        {
            if(buffer == mnt[i].macro_name)
            {
                int mdtc_index = mnt[i].mdtc ;
                is_macro = true;
                do
                {
                    output<<mdt[mdtc_index].statement<<endl;
                    mdtc_index++;
                }while(mdt[mdtc_index].statement!= "mend");
                break;
            }
        }
        
        if(!is_macro)
        {
            if(buffer == "start")
            {
                output<<buffer<<" ";
                input>>buffer;
                output<<buffer<<"\n";
            }
            else if(buffer == "end")
            {
                output<<buffer<<endl;
                break;
            }
            else
            {
                output<<buffer<<" ";
                input>>buffer;
                output<<buffer<<" ";
                input>>buffer;
                output<<buffer<<"\n";
            }
        }
        
    }
    
    input.close();
    output.close();
    
}

void Macro_Pass2 ::PrintMNT()
{
    cout<<"\nMacro Name Table : \n";
    cout<<"-------------------------------------------"<<endl;
    cout<<"MNTC \tMacro Name \t\tMDTC \n";
    for(int i=0;i<mnt_cnt;i++)
    {
        cout<<mnt[i].mntc<<"\t\t"<<mnt[i].macro_name<<"\t\t\t\t"<<mnt[i].mdtc<<"\n";
    }
}

void Macro_Pass2 ::PrintMDT()
{

    cout<<"\nMacro Definition Table:- \n";
    cout<<"-------------------------------------------"<<endl;
    cout<<"MDTC \tMacro Definition  \n";
    for(int i=0;i<mdt_cnt;i++)
    {
        cout<<mdt[i].mdtc<<"\t\t"<<mdt[i].statement<<endl;
    }
}


int main(){

	Macro_Pass2 code;
	code.GetMNT();
	code.PrintMNT();
	code.GetMDT();
	code.PrintMDT();
	code.Initiate_PassII();

return 0;
}