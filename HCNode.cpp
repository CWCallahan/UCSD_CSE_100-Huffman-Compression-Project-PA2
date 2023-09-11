//-*- mode: c++; mode: linum -*-
/* Implementation of HCNode
 * Crystina Callahan
 * A13070475
 */

//Dependencies 
#include "HCNode.h"
//End Dependencies

//'<' operator overload
//used to flip the heap and break ties
bool HCNode::operator<(const HCNode& other){
  if(count != other.count)
    return count > other.count;
  else // we need a tie breaker
    return symbol < other.symbol;
}
