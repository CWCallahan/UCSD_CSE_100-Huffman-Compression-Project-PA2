//-*- mode: c++; mode: linum -*-
/* "Compresses" files using Huffman coding  
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
 * compress the initial file 
 */
int main(int argc, char** argv)
{
  //Declarations
  std::vector<int> freqs;
  freqs =          vector<int>(256,0);
  std::ifstream    in;
  std::ofstream    out;
  HCTree           key;

  //Assign  args
  string infile    =  argv[1];
  string outfile   =  argv[2];

  //Open the streams 
  in.open ( infile,  ios::binary );
  out.open( outfile, ios::binary );
  BitOutputStream bitOut(out);

  //Parse for frequency
  unsigned char grabber;
  int codeLength = 0;
  while(1){
    if ( in.eof() ) break;
    grabber = in.get();
    freqs[grabber]++;
    codeLength++;
  }
  codeLength--;
  in.close();
  
  //Construct a tree
  key.build(freqs);
  
  //Print Header
  bitOut.writeInt(codeLength); //track code length for last bit read
  for(int i=0; i<256; i++) {
    bitOut.writeInt(freqs[i]);
  }
  
  //*Encode file
  int numEncoded = 0;
  in.open( infile, ios::binary );
  while(1){
    grabber = in.get();
    if ( in.eof() ) break;
    key.encode(grabber, bitOut);
    numEncoded++;
  }
  bitOut.flush();
  in.close();

  //Close the out stream
  out.close();			     


}
