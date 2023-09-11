//-*- mode: c++; mode: linum -*-
/* Retrieves a previously encoded file 
 * Crystina Callahan
 * A13070475
 */

//Dependencies 
#include "HCTree.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"
#include <fstream>
#include <string>
#include <cstdlib>

/*Function used to:
 * Read in chars from file to a freq array
 * use the array to build the tree
 * uncompress the encoded file 
 */
int main(int argc, char** argv)
{ 
  //Declarations
  std::vector<int> freqs;
  freqs =          vector<int>(256,0);
  std::ifstream    in;
  std::ofstream    out;
  BitInputStream   bitIn(in); 
  HCTree           key;
  int codeLength = 0;

  //Assign  args
  string infile    =  argv[1];
  string outfile   =  argv[2];
  
  //Open the streams
  in.open ( infile, ios::binary );
  out.open( outfile, ios::binary );

  //Copy file into an array for easier manipulation
  bitIn.getBits();
  //I know this isn't the best idea but its a minimum viable product
  //  if you're interested in my much better algorithm (unimplemented)
  //  see the WIP encodeHeader and decodeHeader functions

  //Get the codeLength
  codeLength = bitIn.getInt(0);

  //Read Header
  for (int i=(1); i<257; i++){ 
    freqs[i-1]=bitIn.getInt(i*32);
  }
  //The use of i*32 may seem odd but this is the exact length of an integer in bits
  //so we read a set of 32 entries and then jump to the next set of 32
  
  //Construct a tree
  key.build(freqs);
  
  //Decode file
  bitIn.location = 257*32;
  while (bitIn.location<bitIn.bits.size()&&codeLength){
    out.put( (char)key.decode(bitIn) );
    codeLength--;
  }

}
