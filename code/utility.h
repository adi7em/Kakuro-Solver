#ifndef UTILITY_H
#define UTILITY_H
#include <vector>
#include <list>
#include "Node.h"
#include "CSP.h"
using namespace std;

int BS(CSP&, list<Node>&);
int recursiveBS(CSP,list<Node>&);
int BS_MAC(CSP&, list<Node>&);
int recursiveBS_MAC(CSP,list<Node>&);
void delete_node(CSP&, vector<vector<pair<int,int> > >&);
int sum_consistency(const vector<vector<pair<int,int> > >&, const vector<vector<pair<int,int> > >&, const Node&, const int&);
int isConsistent(const int& , const Node&, const vector<vector<pair<int,int> > >&, const list<Node>&);
int domain_check(const vector<int>&, const int&);
void print(const vector<vector<pair<int,int> > >&);
void print_domain(const list<Node>&);
int Node_consistency(CSP&);
int Arc_consistency(vector<vector<pair<int,int> > > , CSP&);
void neighours(vector<vector<pair<int,int> > >& , const pair<int,int>&, const CSP&);
int sum_pos(int&, int&, const Node&, const vector<pair<int,vector<Node> > >&);
int var_pos(int&, const Node&, const list<Node>&);
bool compare(Node&, const Node& );
vector<vector<pair<int,int> > > create_arcs(const vector<vector<pair<int,int> > >& , const Node&);
#endif // UTILITY_INCLUDE

