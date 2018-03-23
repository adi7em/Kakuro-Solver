#ifndef NODE_H
#define NODE_H
#include <vector>
using namespace std;

class Node{
    private:
        int node_type_row;
        int node_type_col;
        vector<int> domain;
        int node_value;
        int col_const;
        int row_const;
        int row_index;
        int col_index;
    public:
        Node(int,int);
        void operator=(const Node &node);
        void alter_domain(const int min, const int max);
        void set_value(const int value);
        void set_col(const int value);
        void set_row(const int value);
        const vector<int>& get_domain() const;
        void del_domain_val(const int&);
        const int get_value() const;
        const int& get_row_type() const;
        void assign_value(const int&);
        const int& get_col_type() const;
        bool operator()(const Node&) const;
        bool operator()(const int&, const int&) const;
        const int get_row_index() const;
        const int get_col_index() const;
        void set_row_type(const int);
        bool operator==(const Node&) const;
        void set_col_type(const int);
        const int get_col() const;
        const int get_row() const;
        void set_domain();
        ~Node();
    friend class CSP;
};



#endif

