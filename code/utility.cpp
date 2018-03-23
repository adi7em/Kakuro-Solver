#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include "Node.h"
#include "CSP.h"
#include "utility.h"
using namespace std;
//backtracking Search

int BS_MAC(CSP& problem, list<Node>& assigned){
    return recursiveBS_MAC(problem, assigned);
}


int recursiveBS_MAC(CSP problem, list<Node>& assigned){
    //cout<<"In BS mac"<<endl;
    list<Node>::const_iterator it=problem.get_next();
    if(it==problem.get_var().end())
        return 1;
    Node node=*it;
    //cout<<"node *it"<<endl;
    //cout<<"size= "<<problem.get_var().size()<<endl;
    vector<int> Domain=node.get_domain();
    //cout<<"got domain"<<endl;
    for(unsigned int i=0;i<Domain.size();i++){
        //cout<<"i= "<<i<<" "<<"value "<<Domain[i]<<endl;
        if(sum_consistency(problem.get_hor_cons(),problem.get_ver_cons(),node,Domain[i]) && isConsistent(Domain[i],node,problem.get_graph(),problem.get_var())){
            CSP csp=problem;
            node.set_value(Domain[i]);
            csp.alter_state(node,Domain[i]);
            assigned.push_back(node);
            //vector<vector<Node>> arcs=create_arcs(csp.get_graph(),node);
            if(!Node_consistency(csp)){
                //cout<<"FAIL NODE"<<endl;
                continue;
            }
            vector<vector<pair<int,int> > > arcs= create_arcs(csp.get_graph(),node);
            if(!Arc_consistency(arcs,csp)){
                //cout<<"FAIL NODE"<<endl;
                continue;
            }
            list<Node> ass;
            if(recursiveBS_MAC(csp,ass)){
                assigned.insert(assigned.end(),ass.begin(),ass.end());
                problem.alter_state(node,Domain[i]);
                return 1;
            }
            assigned.pop_back();

        }
    }
    return 0;
}

int BS(CSP& problem, list<Node>& assigned){
    return recursiveBS(problem, assigned);
}


int recursiveBS(CSP problem, list<Node>& assigned){
    list<Node>::const_iterator it=problem.get_next();
    if(it==problem.get_var().end())
        return 1;
    Node node=*it;
    //cout<<"size= "<<problem.get_var().size()<<endl;
    vector<int> Domain=node.get_domain();
    for(unsigned int i=0;i<Domain.size();i++){
        //cout<<"i= "<<i<<" "<<"value "<<Domain[i]<<endl;
        if(sum_consistency(problem.get_hor_cons(),problem.get_ver_cons(),node,Domain[i]) && isConsistent(Domain[i],node,problem.get_graph(),problem.get_var())){
            CSP csp=problem;
            node.set_value(Domain[i]);
            csp.alter_state(node,Domain[i]);
            assigned.push_back(node);
            list<Node> ass;
            if(recursiveBS(csp,ass)){
                assigned.insert(assigned.end(),ass.begin(),ass.end());
                problem.alter_state(node,Domain[i]);
                return 1;
            }
            assigned.pop_back();

        }
    }
    return 0;
}

////arch consistency of nodes
int Arc_consistency(vector<vector<pair<int,int> > > arcs, CSP& problem){
    while(!arcs.empty()){
        //cout<<"arch size= "<<arcs.size()<<endl;
        if(arcs[0].size()<2){
            arcs.erase(arcs.begin());
            continue;
        }
        //cout<<"list size= "<<arcs[0].size()<<endl;
        pair<int,int> source=arcs[0][1];
        pair<int,int> dest= arcs[0][0];
        arcs[0].erase(arcs[0].begin()+1);
        //cout<<"here"<<endl;
        int res= problem.Remove_inconsistent(source,dest);
        //cout<<"there"<<endl;
        if(res==1){
            //cout<<"sorce decrease"<<endl;
            neighours(arcs,source,problem);
        }
        else if(res==2){
            //cout<<"arc failure"<<endl;
            return 0;
        }
    }
    return 1;
}


void neighours(vector<vector<pair<int,int> > >& arcs, const pair<int,int>& node, const CSP& csp){
    int pos,flag=1;
    for(unsigned int i=0;i<arcs.size();i++){
        if(arcs[i][0].first==node.first && arcs[i][0].second==node.second){
            pos=i;
            flag=0;
            break;
        }
    }
    if(flag)
        pos=arcs.size();

    for(unsigned int i=0;i<csp.get_graph().size();i++){
        if(csp.get_graph()[i][0].first==node.first && csp.get_graph()[i][0].second==node.second){
            if(flag)
                arcs.push_back(csp.get_graph()[i]);
            else
                arcs[pos]=csp.get_graph()[i];
        }
    }
}




////Sum consistency of nodes
int sum_consistency(const vector<vector<pair<int,int> > >& hor,const vector<vector<pair<int,int> > >& ver, const Node& node, const int& val){
    for(unsigned int i=0;i<hor.size();i++){
        if(hor[i][1].first==node.get_row_index() && hor[i][1].second==node.get_col_index()){
            if(hor[i].size()==2 && hor[i][0].first!=val){
                return 0;
            }
            else
                break;
        }
    }
    for(unsigned int i=0;i<ver.size();i++){
        if(ver[i][1].first==node.get_row_index() && ver[i][1].second==node.get_col_index()){
            if(ver[i].size()==2 && ver[i][0].first!=val){
                return 0;
            }
            else
                break;
        }
    }
    return 1;
}


//Node consistency of nodes
int Node_consistency(CSP& problem){
    if(!problem.help_node(0))
        return 0;
    if(!problem.help_node(1))
        return 0;
    return 1;
}



int isConsistent(const int& value, const Node& node, const vector<vector<pair<int,int> > >& graph, const list<Node>& var){
    for(unsigned int k=0;k<graph.size();k++){
        if(node.get_row_index()==graph[k][0].first && node.get_col_index()==graph[k][0].second){
            for(int i=1;i<graph[k].size();i++){
                _List_const_iterator<Node> it= find_if(var.begin(),var.end(),Node(graph[k][i].first,graph[k][i].second));
                if(it->get_value()==value){
                    //cout<<"same value"<<endl;
                    return 0;
                }

                if(!domain_check(it->get_domain(),value)){
                    //cout<<"domain mismatch"<<endl;
                    return 0;
                }
            }
            //cout<<"is consistent"<<endl;
            return 1;
        }
    }
}

int domain_check(const vector<int>& Domain, const int& value){
    for(unsigned int i=0;i<Domain.size();i++){
        if(Domain[i]!=value){
            return 1;
        }
    }
    return 0;
}


void print(const vector<vector<pair<int,int> > >& co){
    for(unsigned int i=0;i<co.size();i++){
        cout<<co[i][0].first<<" "<<endl;
        for(unsigned int j=1;j<co[i].size();j++){
            cout<<"("<<co[i][j].first<<","<<co[i][j].second<<"),";
        }
        cout<<endl;
    }
}

void print_domain(const list<Node>& var){
    for(unsigned int i=0;i<var.size();i++){
        list<Node>::const_iterator it= var.begin();
        advance(it,i);
        vector<int> domain= it->get_domain();
        cout<<"index= ("<<it->get_row_index()<<","<<it->get_col_index()<<") ";
        for(unsigned int j=0;j<domain.size();j++){
            cout<<domain[j]<<" ";
        }
        cout<<endl;
    }
}


vector<vector<pair<int,int> > > create_arcs(const vector<vector<pair<int,int> > >& graph, const Node& node){
    for(int i=0;i<graph.size();i++){
        if(graph[i][0].first==node.get_row_index() && graph[i][0].second==node.get_col_index()){
            vector<vector<pair<int,int> > > arcs;
            arcs.push_back(graph[i]);
            return arcs;
        }
    }
}

bool compare(Node& object, const Node& node){
    return object==node;
}
