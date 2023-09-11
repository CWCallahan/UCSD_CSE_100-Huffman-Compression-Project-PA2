//-*- mode: c++; mode: linum -*-
/* Implementation of the bit by bit out stream
 * Crystina Callahan
 * A13070475
 */

//Dependencies 
#include "BitOutputStream.h"

//actually writes to file and clears buffer
void BitOutputStream::write(){
  out.put(buffer);
  buffer = 0;
  nBits  = 0;
}

//adds in the new bit and calls write when full
void BitOutputStream::add(int bit){
  if (nBits == 8) write();
  buffer = buffer<<1;
  buffer = buffer&~1;
  buffer = buffer|bit;
  
  nBits++;
}

//slides the remaining bits to the left and calls write
void BitOutputStream::flush(){
  while (nBits<8){
    buffer = buffer<<1;
    nBits++;
  }
  write();
}

//Chops the int into 4 bytes and output in the RIGHT order
void BitOutputStream::writeInt(int toWrite){
  unsigned char p4=0;
  unsigned char p3=0;
  unsigned char p2=0;
  unsigned char p1=0;

  p4=p4|toWrite;
  p3=p3|(toWrite>>8);
  p2=p2|(toWrite>>(8*2));
  p1=p1|(toWrite>>(8*3));

  out.put(p1);
  out.put(p2);
  out.put(p3);
  out.put(p4);
}
