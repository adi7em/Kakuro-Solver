#ifndef CSP_H
#define CSP_H
#include <vector>
#include <list>
#include <memory>
#include "Node.h"
using namespace std;

class CSP{
    private:
        int row;
        int column;
        list<Node> variables;
        vector<vector<pair<int,int> > > Ver_const;
        vector<vector<pair<int,int> > > Hor_const;
        vector<vector<pair<int,int> > > const_graph;
    public:
        CSP(const int,const int);
        void alter_state(const int rpos, const int cpos, const int value);
        list<Node>::const_iterator get_next() const;
        const int& get_row() const;
        const int& get_col() const;
        const vector<vector<pair<int,int> > >& get_hor_cons() const;
        const vector<vector<pair<int,int> > >& get_ver_cons() const;
        bool complete() const;
        void create_csp_elements(const vector<vector<Node> >&);
        const vector<vector<pair<int,int> > >& get_graph() const;
        void set_var(const Node node);
        const list<Node>& get_var() const;
        void create_arcs();
        void delete_node_hor(const int& ,const int&);
        void delete_node_ver(const int& ,const int&);
        void change_sum(const int&, const int&, int);
        void add_to_graph(const vector<pair<int,int> >&);
        void delete_domain_var(const int&, const int&);
        int del_ele(const int&,const Node&, vector<vector<pair<int,int> > >&);
        //void delete_domain_ver(const int&, const int&, const int&);
        int Remove_inconsistent(const pair<int,int>&, const pair<int,int>&);
        int help_node(const int&);
        int help_help_node(vector<pair<int,int> >&);
        void alter_state(const Node&, const int&);
        ~CSP();
};


#endif // CSP_INCLUDE
