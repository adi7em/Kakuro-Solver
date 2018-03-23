#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <ctime>
#include <string>
#include <sstream>
#include "Node.h"
#include "CSP.h"
#include "utility.h"
using namespace std;
int row,col;
string in,in1,in2;
string temp,temp2;
int main(int argc,char* argv[])
{   
    if(argc!=3){
        cout<<"Invalid number of arguments"<<endl;
        return -1;
    }
    ifstream file;
    ofstream ofile;
    file.open(argv[1]);
    ofile.open(argv[2]);
    if(!file.is_open()){
        perror("Error while opening input file");
    }
    if(!ofile.is_open()){
        perror("Error while opening output file");
    }
    //FILE* status= fopen("/proc/self/status/","r");
    file>>in2;
    //cout<<in2<<endl;
    stringstream geek(in2.substr(in2.find('=')+1,in2.length()));
    geek >> row;
    //cout<<row<<endl;
    file>>in1;
    //cout<<in1<<endl;
    stringstream geek2(in1.substr(in1.find('=')+1,in1.length()));
    geek2 >> col;
    //cout<<col<<endl;
    file>>temp2;
    int arrh[row][col];
    int arrv[row][col];
    for(int i=0;i<row;i++){
        file>>in;
        //cout<<in<<endl;
        istringstream inn (in);
        for(int j=0;j<col;j++){
            if(!getline(inn,temp,',')) break;
            if(temp=="#")
                arrh[i][j]=-1;
            else{
            stringstream geek3(temp);
            geek3 >> arrh[i][j];
            }
        }
    }
    file>>temp2;
    for(int i=0;i<row;i++){
        file>>in;
        istringstream inn (in);
        for(int j=0;j<col;j++){
            if(!getline(inn,temp,',')) break;
            if(temp=="#")
                arrv[i][j]=-1;
            else{
            stringstream geek3(temp);
            geek3 >> arrv[i][j];
            }
        }
    }
    vector<vector<Node> > initial_state;
    cout<<"row="<<row<<" col="<<col<<endl;
    CSP csp(row,col);
    //cout<<"initiallize"<<endl;
    //initialize the initial and current states
    for(int i=0;i<row;i++){
        vector<Node> temp;
        for(int j=0;j<col;j++){
            Node node=Node(i,j);
            if(arrh[i][j]==0 && arrv[i][j]==0){
                node.set_row_type(0);
                node.set_col_type(0);
                node.set_domain();
            }
            if(arrh[i][j]>0){
                node.set_row_type(1);
                node.set_row(arrh[i][j]);
            }
            if(arrv[i][j]>0){
                    node.set_col_type(1);
                    node.set_col(arrv[i][j]);
            }
            temp.push_back(node);
        }
        initial_state.push_back(temp);
    }
    //cout<<"done done"<<endl;
    csp.create_csp_elements(initial_state);

    //cout<<"element created"<<endl;
    if(Node_consistency(csp))
        cout<<"Consistency done"<<endl;
    //print_domain(csp.get_var());
    vector<vector<pair<int,int> > > graph= csp.get_graph();
    //cout<<"this is"<<endl;
    list<Node> assigned;
    int start1= clock();
    int result1= BS_MAC(csp,assigned);
    int stop1= clock();
    //auto duration= duration_cast<microseconds>(stop-start);
    cout<<"time taken by BS_MAC= "<<(stop1-start1)/double(CLOCKS_PER_SEC)*1000<<endl;
    if(result1){
        cout<<"BS complete complete"<<endl;
    }
    //cout<<"this is"<<endl;
    /*int start= clock();
    int result= BS_MAC(csp,assigned);
    int stop= clock();
    //auto duration= duration_cast<microseconds>(stop-start);
    cout<<"time taken by BS_MAC= "<<(stop-start)/double(CLOCKS_PER_SEC)*1000<<endl;
    if(result){
        cout<<"BS_MAC complete complete"<<endl;

    }*/
for(unsigned int i=0;i<assigned.size();i++){
            list<Node>::iterator it= assigned.begin();
            advance(it,i);
            arrh[it->get_row_index()][it->get_col_index()]=it->get_value();
            arrv[it->get_row_index()][it->get_col_index()]=it->get_value();
        }
    ofile<<in2<<endl<<in1<<endl<<"Horizontal"<<endl;
    for(int i=0;i<row;i++){
        for(int j=0;j<col-1;j++){
            if(arrh[i][j]==-1)
                ofile<<"#,";
            else
                ofile<<arrh[i][j]<<",";
        }
        if(arrh[i][col-1]==-1)
                ofile<<"#";
            else
                ofile<<arrh[i][col-1];
        ofile<<endl;
    }
    ofile<<"Vertical"<<endl;
    for(int i=0;i<row;i++){
        for(int j=0;j<col-1;j++){
            if(arrv[i][j]==-1)
                ofile<<"#,";
            else
                ofile<<arrv[i][j]<<",";
        }
        if(arrv[i][col-1]==-1)
                ofile<<"#";
            else
                ofile<<arrv[i][col-1];
        ofile<<endl;
    }
    return 0;
    }
