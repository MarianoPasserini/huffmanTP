#ifndef _TARR_BITWRITER_
#define _TARR_BITWRITER_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "../../funciones/strings.hpp"

using namespace std;

struct BitWriter
{
   int c;
   int t[8];
   FILE* archivo;
};

BitWriter bitWriter(FILE* f)
{
   BitWriter bw;
   bw.c=0;
   bw.archivo = f;
   for(int i=0;i<8;i++)
   {
      bw.t[i]=2;
   }
   return bw;
}

void bitWriterWrite(BitWriter& bw,int bit)
{
   int numero=0;
   bw.t[bw.c]=bit;
   bw.c++;
   if(bw.c==8)
   {
      numero = 0;
      bw.c=0;
      //char ch = interpretarByte(br.bits);
      if(bw.t[0]==1){numero = numero+128;}
      if(bw.t[1]==1){numero = numero+64;}
      if(bw.t[2]==1){numero = numero+32;}
      if(bw.t[3]==1){numero = numero+16;}
      if(bw.t[4]==1){numero = numero+8;}
      if(bw.t[5]==1){numero = numero+4;}
      if(bw.t[6]==1){numero = numero+2;}
      if(bw.t[7]==1){numero = numero+1;}

      char c = numero;
      write<char>(bw.archivo,c);
   }
}

void bitWriterFlush(BitWriter& bw)
{
   while(bw.c!=0)
   {
      bitWriterWrite(bw,0);
   }
}

#endif
