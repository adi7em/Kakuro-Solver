#include <iostream>
#include <utility>
#include <algorithm>
#include <list>
#include "Node.h"
#include "CSP.h"
#include "utility.h"
using namespace std;


CSP::CSP(const int row, const int column){
    this->row= row;
    this->column= column;
}

const int& CSP::get_row() const{
    return row;
}

const int& CSP::get_col() const{
    return column;
}

const vector<vector<pair<int,int> > >& CSP::get_hor_cons() const{
    return Hor_const;
}


const vector<vector<pair<int,int> > >& CSP::get_ver_cons() const{
    return Ver_const;
}


const vector<vector<pair<int,int> > >& CSP::get_graph() const{
    return const_graph;
}

//Function that initializes variables,const_graph,Hor_const,Ver_const
void CSP::create_csp_elements(const vector<vector<Node> >& state){
    for(int i=0;i<row;i++){
        for(int j=0;j<column;j++){
            if(state[i][j].get_row_type()==0 && state[i][j].get_col_type()==0){
                variables.push_back(state[i][j]);
            }
            if(state[i][j].get_row_type() == 1){
                vector<pair<int,int> > hor;
                hor.push_back(make_pair(state[i][j].get_row(),state[i][j].get_row()));
                int temp= j+1;
                while(state[i][temp].get_row_type()==0 && temp<column){
                    hor.push_back(make_pair(state[i][temp].get_row_index(),state[i][temp].get_col_index()));
                    temp++;
                }
                Hor_const.push_back(hor);
                add_to_graph(hor);
            }
            if(state[i][j].get_col_type() == 1){
                vector<pair<int,int> > ver;
                ver.push_back(make_pair(state[i][j].get_col(),state[i][j].get_col()));
                int temp= i+1;
                while(temp<row && state[temp][j].get_col_type()==0){
                    ver.push_back(make_pair(state[temp][j].get_row_index(),state[temp][j].get_col_index()));
                    temp++;
                }
                Ver_const.push_back(ver);
                add_to_graph(ver);
            }
        }
    }
}

//Function for adding a particular constraint to the constraint graph
void CSP::add_to_graph(const vector<pair<int,int> >& hor){
    for(unsigned int i=1;i<hor.size();i++){
        for(unsigned int j=1;j<hor.size();j++){
            int flag=0;
            for(unsigned int k=0;k<const_graph.size();k++){
                if(const_graph[k][0]==hor[i]){
                     flag=1;
                     if(i!=j){
                        const_graph[k].push_back(hor[j]);
                    }
                    break;
                }
            }
            if(!flag && i!=j){
                vector<pair<int,int> > temp;
                temp.push_back(hor[i]);
                temp.push_back(hor[j]);
                const_graph.push_back(temp);
            }
        }
    }
}


const list<Node>& CSP::get_var() const{
    return variables;
}
/*
void CSP::delete_node_hor(const int& row, const int& col){
    Hor_const[row].erase(Hor_const[row].begin()+col);
}

void CSP::delete_node_ver(const int& row, const int& col){
    Ver_const[row].erase(Ver_const[row].begin()+col);
}
*/
void CSP::change_sum(const int& value, const int& pos, int which){
    if(which){
        Hor_const[pos][0].first-=value;
        Hor_const[pos][0].second-=value;
    }
    else{
        Ver_const[pos][0].first-=value;
        Ver_const[pos][0].second-=value;
    }
}

/*
void CSP::delete_domain_var(const int& pos, const int& value){
    list<Node>::iterator it=next(variables.begin(),pos);
    it->del_domain(value);
}
*/
void CSP::alter_state(const Node& node, const int& value){
    if(del_ele(value,node,Hor_const)){
        //cout<<"hor success"<<endl;
    }
    if(del_ele(value,node,Ver_const)){
        //cout<<"ver success"<<endl;
    }
    _List_iterator<Node> it= find_if(variables.begin(),variables.end(),Node(node));
    it->assign_value(value);
}


int CSP::help_node(const int& type){
    if(type){
        for(unsigned int i=0;i<Hor_const.size();i++){
            if(!help_help_node(Hor_const[i]))
                return 0;
        }
    }
    else{
        for(unsigned int i=0;i<Ver_const.size();i++){
            if(!help_help_node(Ver_const[i]))
                return 0;
        }
    }
    return 1;
}

int CSP::help_help_node(vector<pair<int,int> >& cons){
    int size_in= cons.size()-1;
    //cout<<"size= "<<size_in<<endl;
    int S=cons[0].first;
    //cout<<"S= "<<S<<endl;
    list<Node>::iterator it= find_if(variables.begin(),variables.end(),Node(cons[1].first,cons[1].second));
    if(cons.size()==2 && it->get_value()>0 && S!=it->get_value()){
        return 0;
    }
    int maxVal= S-(size_in*(size_in-1)/2);
    int minVal= S-((size_in-1)*(20-size_in)/2);
    //cout<<"max= "<<maxVal<<" min= "<<minVal<<endl;
    for(unsigned int j=1;j<=size_in;j++){
            list<Node>::iterator it= find_if(variables.begin(),variables.end(),Node(cons[j].first,cons[j].second));
            if(it!=variables.end()){
                it->alter_domain(minVal,maxVal);
                if(it->get_domain().empty())
                    return 0;
        }
    }
    return 1;
}



int CSP::del_ele(const int& value,const Node& node, vector<vector<pair<int,int> > >& variables){
    for(unsigned int i=0;i<variables.size();i++){
        vector<pair<int,int> >::iterator it= find(variables[i].begin()+1,variables[i].end(),make_pair(node.get_row_index(),node.get_col_index()));
        if(it!=variables[i].end()){
            variables[i].erase(it);
            variables[i][0].first-=value;
            variables[i][0].second-=value;
            return 1;
        }
    }
    return 0;
}

int CSP::Remove_inconsistent(const pair<int,int>& source, const pair<int,int>& dest){
    int removed=0;
    list<Node>::iterator its= find(variables.begin(),variables.end(),Node(source.first,source.second));
    list<Node>::iterator itd= find(variables.begin(),variables.end(),Node(dest.first,dest.second));
    vector<int> domain1= its->get_domain();
    vector<int> domain2= itd->get_domain();
    for(unsigned int i=0;i<domain1.size();i++){
        int iscons=0;
        for(unsigned int j=0;j<domain2.size();j++){
            if(domain2[j]!=domain1[i]){
                iscons=1;
                break;
            }
        }
        if(iscons==0){
            //vector<int> dom=its->get_domain();
            //cout<<"before  ";
            /*for(int m=0;m<dom.size();m++){
                cout<<dom[m]<<" "<<endl;
            }*/
            its->del_domain_val(domain1[i]);
            //dom=its->get_domain();
            //cout<<"after  ";
            /*for(int m=0;m<dom.size();m++){
                cout<<dom[m]<<" "<<endl;
            }*/
            if(its->get_domain().empty()){
                return 2;
            }
            //i--;
            removed=1;
        }
    }
    return removed;
}


list<Node>::const_iterator CSP::get_next() const{
    list<Node>::const_iterator it= variables.begin();
    while(it!=variables.end()){
        if(it->get_value()==0)
           return it;
        else
            it++;
    }
    return variables.end();
}

bool CSP::complete() const{
    list<Node>::const_iterator it= variables.begin();
    while(it!=variables.end()){
        if(it->get_value()==0)
            return 0;
    }
    return 1;
}

CSP::~CSP(){
    //this is destructor
}
