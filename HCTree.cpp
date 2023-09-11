//-*- mode: c++; mode: linum -*-
/* Implementation of HCTree
 * Crystina Callahan
 * A13070475
 */

//Dependencies 
#include "HCTree.h"

//Builds the tree from a vector
void HCTree::build(const vector<int>& freqs){
  //We'll need the heap with Node pointers (to prevent wasted memory from
  //  unnecessary  duplication)
  std::priority_queue<HCNode*,std::vector<HCNode*>,HCNodePtrComp> forest;
  int i = 0;

  //Throw everything into the heap, mark leaves
  for(vector<int>::const_iterator it=freqs.begin(); it!=freqs.end(); ++it, i++) {
    if (*it){
      HCNode* n = new HCNode(*it,i);
      forest.push(n);
      leaves[i] = n;
    }
  }
  
  //while the heap has multiple trees
  while(forest.size() > 1){
  //start combining trees and throwing them back on
    HCNode* n = new HCNode(0,0);
    //the next two node have already been compared so first can be n's c0
    n->c0 = forest.top();
    n->c0->p=n;
    forest.pop();
    //and second can be n's c1
    n->c1 = forest.top();
    n->c1->p=n;
    forest.pop();
    //and now we set n's values (freq and symbol)
    //the we will use the symbol of the 0 child
    n->symbol = n->c0->symbol;
    n->count  = n->c0->count + n->c1->count;

    forest.push(n);
  }

  root = forest.top();
}//end build


//used to encode an optomized header
//WIP
void HCTree::encodeHeader (BitOutputStream& out){
  HCNode* cn = root;
  //Starting at the root
  while (1){
    while (cn->c0){
      cn=cn->c0;
      out.add(0);
    }
    out.add(1);
    //record cn->symbol
    //for
    cn=cn->p->c1; //be sure about this one
    
    if (!cn->c0)//if this is a leaf
      //record 1
      //record cn->symbol
      while(cn->p->c1==cn){
	if (cn==root) return; // be careful about this one!
	cn=cn->p;
      }
  }//while1   
}

//Used to decode an optimized header
//WIP
void HCTree::decodeHeader (BitInputStream&  in){
  //Starting at the root
  root = new HCNode(0,0);
  HCNode* cn = root;
  int bit; // = the first symbol after residual bit
  byte sym;
  
  while(1){ 
    if (sym==0){ //add a left branch
      if (!cn->c0){      //if no left child
	cn->c0 = new HCNode(0,0);
	cn->c0->p = cn;
	cn= cn->c0;
	//read the next bit
	
      }else if(!cn->c1){ //if no right child
	cn->c1 = new HCNode(0,0);
	cn->c1->p = cn;
	cn= cn->c1;
	//DO NOT read the next bit yet

      }else {
	while (cn->c1){
	  cn=cn->p;
	  if( (cn==root)&&(root->c1) ) return;
	  //DO NOT read the bit symbol yet
	}
      }
      
    }else if(sym==1){ //add a leaf
      //need to read the following 8bytes (sym) 
      if ( (!cn->c0)&&(!cn->c1) ){
	//cn->symbol = sym;
	cn = cn->p;
	//read the next bit
	
      }else if(!cn->c1){
	//cn->c1 = new HCNode(0,sym);//double check on this one
	//read the next bit
	
      }else{
	while (cn->c1){
	  cn=cn->p;
	  if( (cn==root)&&(root->c1) ) return;
	}
      }
    }
  }//while 1    
}


//Encode to bits 
void HCTree::encode(byte symbol, BitOutputStream& out) const{
  HCNode* n   = leaves[symbol];
  std::stack<int> s;
  //We need to follow up the tree
  //  for each time that we move up add a bit to the buffer
  //  lets make stack of int then just add until the stack is empty
  while( n->p ){ 
        if (n->p->c0 == n)
	  s.push(0);
	else
	  s.push(1);	
	n=n->p;
  }
  while(s.size()){
    out.add(s.top());
    s.pop();
  }
 }


//Encode to char
void HCTree::encode(byte symbol, ofstream& out) const{
  HCNode* n   = leaves[symbol];
  string line = "";
  //get the string 
  while( n->p ){
  //record the branch
    if (n->p->c0 == n)
      line = "0"+line;
    else
      line = "1"+line;
    n=n->p;
  }
}



//Decode from Bits
int HCTree::decode(BitInputStream& in) const{
  HCNode* n  = root;
  int read;
  //start decoding the array from the front until we hit a leaf
  //each time we remove the past symbol from the array 
  while (n->c0){
    //only need to check one child, all nodes have both or none
    read = in.bits[in.location];
    in.location++;
    
    if (read == 0)
      n=n->c0;
    else if (read == 1)
      n=n->c1;
  }
  return n->symbol;
}


///*
//Decode from checkpoint
int HCTree::decode(ifstream& in) const{
  HCNode* n  = root;
  int read;
  in >> read;
  
  //follow tree down to a leaf and get a symbol 
  while (n->c0){
    //only need to check one child all nodes have both or none
    if (read == 0)
      n=n->c0;
    else if (read == 1)
      n=n->c1;

    in >> read; 
  }
  
  //return the symbol at that leaf
  return n->symbol;
}

//used along with print help for printing the tree
void HCTree::print(){
  if (!root)
    return;

  std::cout << "Left: \t";
  printHelp(root->c0);
  
  std::cout << "Right: \t";
  printHelp(root->c1);

  std::cout << "Root at: \t" << *root << std::endl;
}

void HCTree::printHelp(HCNode* n){
  if (!n)
    return;

  printHelp(n->c0);

  printHelp(n->c1);

  std::cout << *n << "\t" << *n->p << std::endl;
}

//recursive deletion for the destructor
void HCTree::deleteIt(HCNode* n){
  if (!n)
    return;
  deleteIt(n->c0);
  deleteIt(n->c1);
  delete n;  
}

HCTree::~HCTree(){
  deleteIt(root);
}

