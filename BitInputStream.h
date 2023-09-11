//-*- mode: c++; mode: linum -*-
/* A header for a bit by bit input stream
 * Crystina Callahan
 * A13070475
 */

//Definitions
#ifndef BITINPUTSTREAM_H
#define BITINPUTSTREAM_H
//Dependencies 
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

class BitInputStream {
  
public:
  //Functions:
  //  Grabs all of the bits from the file at once
  std::vector<int> getBits();
  //  grabs an individual int from the bits
  int getInt(int loc);

  //Variables:
  std::ifstream & in;
  //  this is where we put the bits from getBits()
  std::vector<int> bits;
  //  this helps us track where we are in bits
  int location;

  //Constructor
  BitInputStream(std::ifstream & in,
		 int nBits = 0,
		 unsigned char buffer = 0)
    : in(in), nBits(nBits), buffer(buffer) {
  }

private:
  //number of bits in the buffer
  int nBits;
  //A buffer to store bits and write when full or read
  unsigned char buffer;
};
#endif
