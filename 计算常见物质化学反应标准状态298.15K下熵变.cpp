#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#include<cctype>
using namespace std;
int total_substance=0;
struct substance{
  string name;
  double MolarEntropy; //J/(mol*k)
  double MolarEnthalpy;//kJ/mol
};
substance my_substance[300];  
double entropy(string name){
   for(int i=0;i<total_substance;i++)
       if(name==my_substance[i].name)
          return my_substance[i].MolarEntropy;
}  
int main(){
  ifstream fin("standard entropy data.txt");
  while(!fin.eof()){
    fin>>my_substance[total_substance].name;
    fin>>my_substance[total_substance++].MolarEntropy;
  }
 /* for(int i=0;i<total_substance;i++)
    cout<<my_substance[i].name<<':'<<my_substance[i].MolarEntropy<<endl;  
  */
  while(1){
   // cout<<"Input the number of reactants\n";
    int tmp1;
    cin>>tmp1; 
   // cout<<"Input the name of reactants, their corresponding coefficients in the equation, and use the space to seperate them\n";
    string* my_string1=new string[tmp1];
    double* my_coefficient1=new double[tmp1];
    for(int i=0;i<tmp1;i++){
        cin>>my_string1[i];
        cin>>my_coefficient1[i];
    }  
   // cout<<"Input the number of products\n";
    int tmp2;
    cin>>tmp2; 
   // cout<<"Input the name of products, their corresponding coefficients in the equation, and use the space to seperate them\n";
    string* my_string2=new string[tmp2];
    double* my_coefficient2=new double[tmp2];
    for(int i=0;i<tmp2;i++){
        cin>>my_string2[i];
        cin>>my_coefficient2[i];
    }  
   // cout<<"the reaction relation is:\n";
    for(int i=0;i<tmp1;i++){
       if(my_coefficient1[i]!=1)
          cout<<my_coefficient1[i];

        if(i!=tmp1-1)
        cout<<my_string1[i]<<'+';
        else
        cout<<my_string1[i]<<"==";
    }
    for(int i=0;i<tmp2;i++){
       if(my_coefficient2[i]!=1)
          cout<<my_coefficient2[i];

        if(i!=tmp2-1)
        cout<<my_string2[i]<<'+';
        else
        cout<<my_string2[i]<<endl;
     }
    cout<<"The entropy change of the process is: ";
    double tmp3=0;
    for(int i=0;i<tmp1;i++)
        tmp3-=my_coefficient1[i]*entropy(my_string1[i]);
    for(int i=0;i<tmp2;i++)
        tmp3+=my_coefficient2[i]*entropy(my_string2[i]);
    cout<<tmp3<<endl;
     delete [] my_string1 ;
     delete [] my_string2 ;
     delete [] my_coefficient1;
     delete [] my_coefficient2;

   }      
  cout<<entropy("O2")<<"J/(mol*K)"<<'\t'<<entropy("H2O");
  fin.close();
  system("pause");
  return 0;
}   
