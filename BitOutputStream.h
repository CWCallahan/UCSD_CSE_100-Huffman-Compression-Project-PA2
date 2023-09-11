//-*- mode: c++; mode: linum -*-
/* A header for a bit by bit outputstream
 * Crystina Callahan
 * A13070475
 */

//Definitions
#ifndef BITOUTPUTSTREAM_H
#define BITOUTPUTSTREAM_H
//Dependencies
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

class BitOutputStream {
  
public:
  //Functions
  //  Writes out a full buffer
  void write();
  //  Will add a bit to the buffer
  //  please only feed it 1 and 0
  void add(int bit);
  //  Will flush the remaining buffer
  void flush();
  //  Chops up an int and writes it out 
  void writeInt(int toWrite);
  
  //Variables
  std::ofstream & out;

  //Constructor
  BitOutputStream(std::ofstream & out,
		  int nBits = 0,
		  unsigned char buffer = 0)
    : out(out), nBits(nBits), buffer(buffer) {
    //out << "in constructor" << std::endl;
  }

private:
  //Tracks the number of bits in the buffer
  int  nBits;
  //A buffer to write and read bits 
  unsigned char buffer;
  
};
#endif

