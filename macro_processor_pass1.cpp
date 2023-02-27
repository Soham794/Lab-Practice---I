#include<bits/stdc++.h>
#include<fstream>

using namespace std;


class Macro_Pass1 // macro pass 1 -> macro data structures creation, macro code 
{

private: 
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
    void Initiate_PassI(); // reads given input file and generates pass1 output in output file
    void PrintMNT();// console print mnt
    void PrintMDT();// console print mdt
    void GetMDTOutput(); // creates mdt file and stores the MDT
    void GetMNTOutput(); // creates mnt file and stores the MNT
};

void Macro_Pass1::Initiate_PassI()
{
    fstream input; // to read the input file
    fstream output; // to write the output in file

    input.open("macro_pass1_in.txt" , fstream::in);// opening the files
    output.open("macro_pass1_out.txt" , fstream::out);
    
    string curr_word;

    bool is_macro = false;
    while(!input.eof()) // read while not end of file(eof)
    {
        input>>curr_word; // to read from input file object
        // cin>> curr_word; // to read from console;
        if(!is_macro) // ismacro == false then current if is true
        {
            if(curr_word == "macro")
            {
                is_macro = true;
                input>>curr_word;
                // every time finds a name 
                mnt[mnt_cnt].mntc = mnt_cnt; // set mntc to mnt_cnt
                mnt[mnt_cnt].macro_name = curr_word;// set name of macro to curr_word
                mnt[mnt_cnt].mdtc = mdt_cnt; // 
                
                mnt_cnt++;
                
            }
            else if(curr_word == "start")
            {	
            // cout << word // console printing
                output<<curr_word<<" ";
                input>>curr_word;
                output<<curr_word<<"\n";

            }
            else if(curr_word == "end")
            {
                output<<curr_word<<"\n";
                break;
            }
            else
            {
                bool is_macro_name = false;
                for(int i=0;i<mnt_cnt;i++)
                {
                    if(curr_word==mnt[i].macro_name)
                    {
                        output<<curr_word<<endl;
                        is_macro_name = true;
                    }
                }

                if(!is_macro_name)
                {
                    output<<curr_word<<" ";
                    input>>curr_word;
                    output<<curr_word<<" ";
                    input>>curr_word;
                    output<<curr_word<<"\n";
                }
                
            }
        }
		else{
            // else part inserts the definition in mdt
            if(curr_word=="mend")
            {
                is_macro = false;
                mdt[mdt_cnt].mdtc = mdt_cnt;
                mdt[mdt_cnt].statement = curr_word;
                mdt_cnt++;
            }
            else    
            {
                string curr_statement  = curr_word; // store the current word in the variable
                curr_statement +=" "; // space after that instruction
                input>>curr_word; // take next word input
                curr_statement +=curr_word; // append the curr word again as it is the next instruction
                curr_statement +=" "; // space after that word
                input>>curr_word; // next input as word
                curr_statement +=curr_word; // append that word in line
                
                mdt[mdt_cnt].mdtc = mdt_cnt;
                mdt[mdt_cnt].statement = curr_statement ;
                
                mdt_cnt++;	
            }
            
        }
    }
    
    input.close();
    output.close();
}

void Macro_Pass1 :: GetMDTOutput(){
	fstream output;
	output.open("macro_pass1_mdt.txt", ios::out);// opeing for writing purpose
	output << "MDTC \t Macro Definition\n";

	for(int i=0;i<mdt_cnt;i++){
		string line = "";
		line += to_string(mdt[i].mdtc);// converting to string from int
		line += "\t";// spacing
		line += mdt[i].statement;// appending the statement stored in mdt
		line += "\n";	
		output << line;
	}
}

void Macro_Pass1 :: GetMNTOutput(){

	fstream output;// to output in the mdt file
	output.open("macro_pass1_mnt.txt", ios::out); // open for writing
	output << "MNTC \t Macro Name \t MDTC\n";

	for(int i=0;i<mnt_cnt;i++){
		string line = "";
		line += to_string(mnt[i].mntc);// converting to string as it is integer
		line += "\t  ";// spacing
		line += mnt[i].macro_name;// append the macro name
		line += "\t\t";// spacing
		line += to_string(mnt[i].mdtc);// converting to string as it is an integer
		line += "\n";// appending the new line
		output << line;
	}
}

void Macro_Pass1::PrintMNT()
{
    cout<<"\n\tMacro Name Table : \n";
    cout<<"-------------------------------------------"<<endl;
    cout<<"MNTC \tName of Macro \tMDTC \n";
    for(int i=0;i<mnt_cnt;i++)
    {
        cout<<mnt[i].mntc<<"\t\t"<<mnt[i].macro_name<<"\t\t\t\t"<<mnt[i].mdtc<<"\n";
    }
}

void Macro_Pass1::PrintMDT()
{
    cout<<"\n\tMacro Definition Table : \n";
    cout<<"-------------------------------------------"<<endl;
    cout<<"MDTC \tMacro Definition  \n";
    for(int i=0;i<mdt_cnt;i++)
    {
        cout<<mdt[i].mdtc<<"\t\t"<<mdt[i].statement<<"\n";
    }
}


int main()
{
    Macro_Pass1 code;
    code.Initiate_PassI();
    code.PrintMNT();
    code.PrintMDT();
    code.GetMDTOutput();
    code.GetMNTOutput();
}