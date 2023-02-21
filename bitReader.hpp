#ifndef _TARR_BITREADER_
#define _TARR_BITREADER_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "../../funciones/strings.hpp"

using namespace std;

struct BitReader
{
   int t[8];
   int c;
   FILE* archivo;
};

BitReader bitReader(FILE* f)
{
   BitReader br;
   br.c=0;
   br.archivo=f;
   for(int i=0;i<8;i++)
   {
      br.t[i]=2;
   }
   return br;
}

int bitReaderRead(BitReader& br)
{
   if(br.c==0)
   {
      char ch = read<char>(br.archivo);

      int chi=ch;
      //convertimos el char a un byte en un array?
      if(chi>=128){br.t[0]=1; chi = chi-128;}
      else{br.t[0]=0;}
      if(chi>=64){br.t[1]=1; chi = chi-64;}
      else{br.t[1]=0;}
      if(chi>=32){br.t[2]=1; chi = chi-32;}
      else{br.t[2]=0;}
      if(chi>=16){br.t[3]=1; chi = chi-16;}
      else{br.t[3]=0;}
      if(chi>=8){br.t[4]=1; chi = chi-8;}
      else{br.t[4]=0;}
      if(chi>=4){br.t[5]=1; chi = chi-4;}
      else{br.t[5]=0;}
      if(chi>=2){br.t[6]=1; chi = chi-2;}
      else{br.t[6]=0;}
      if(chi==1){br.t[7]=1; chi = chi-1;}
      else{br.t[7]=0;}

   }
   br.c++;
   if(br.c==8){br.c=0;}

   return br.c==0?br.t[7]:br.t[(br.c)-1];
}

#endif
