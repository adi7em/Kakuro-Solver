#include <iostream>
#include <list>
#include <algorithm>
#include "Node.h"
//#include "utility.h"

Node::Node(int row, int col){
    node_type_row=-1;
    node_type_col=-1;
    node_value=0;
    col_const=0;
    row_const=0;
    row_index=row;
    col_index=col;
}

void Node::operator=(const Node &node){
    node_type_row=node.node_type_row;
    node_type_col=node.node_type_col;
    node_value=node.node_value;
    col_const=node.col_const;
    row_const=node.col_const;
    row_index=node.row_index;
    col_index=node.col_index;
}

bool Node::operator==(const Node &node) const{
    return this->row_index==node.row_index && this->col_index==node.col_index;
}

bool Node::operator()(const Node &node) const{
    return this->row_index==node.row_index && this->col_index==node.col_index;
}

bool Node::operator()(const int& row, const int& col) const{
    return this->row_index==row && this->col_index==col;
}

void Node::alter_domain(const int min, const int max){
    vector<int>::iterator it=domain.begin();
    while(it!=domain.end()){
        if(*it>max || *it<min)
            it=domain.erase(it);
        else
            it++;
    }
}

void Node::set_value(const int value){
    node_value= value;
}

void Node::set_col(const int value){
    col_const= value;
}

void Node::set_row(const int value){
    row_const= value;
}

const vector<int>& Node::get_domain() const{
    return domain;
}

const int Node::get_value() const{
    return node_value;
}

const int& Node::get_row_type() const{
    return node_type_row;
}

const int& Node::get_col_type() const{
    return node_type_col;
}

void Node::set_row_type(const int type){
    node_type_row=type;
}

void Node::set_col_type(const int type){
    node_type_col=type;
}

const int Node::get_row() const{
    return row_const;
}

const int Node::get_col() const{
    return col_const;
}

const int Node::get_row_index() const{
    return row_index;
}

const int Node::get_col_index() const{
    return col_index;
}

void Node::set_domain(){
    int arr[]={1,2,3,4,5,6,7,8,9};
    domain.assign(arr,arr+9);
}


void Node::del_domain_val(const int& val){
    domain.erase(std::remove(domain.begin(),domain.end(),val),domain.end());
}

void Node::assign_value(const int& value){
    node_value=value;
}

Node::~Node(){

}

