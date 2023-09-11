//-*- mode: c++; mode: linum -*-
/* Implementation of HCNode
 * Crystina Callahan
 * A13070475
 */

//Dependencies 
#include "BitInputStream.h"

//This function gets all the bits and inefficiently stores them as
//integers in a integers in a vector
std::vector<int> BitInputStream::getBits(){
  bits = std::vector<int>();
  
  //grab a bit
  while(1){
    buffer = in.get();
    if ( in.eof() ) break;

    //extract the bits and tack them on to the bits vector
    for (int i=0; i<8; i++){
      int grabber = ((1<<7)&buffer)>>7;
      bits.push_back(grabber);
      buffer = buffer << 1;
    }
  }
  in.close();
  return bits;
}

//grabs an int from the file array, relies on *getBits*
int BitInputStream::getInt(int loc){
  int fromBits=0;
  //intentionally left as 8*4 for ease of readability (4bytes)
  for (int i=0; i<(8*4); i++){
    fromBits=fromBits<<1;
    fromBits=fromBits|bits[loc];
    loc++;
  } 
  return fromBits;
}

