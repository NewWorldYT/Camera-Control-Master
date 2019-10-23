//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Debug.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


//---------------------------------------------------------------------------

static int dumpIndex = 0;
static unsigned int dump[0x500000];
static int lastIndex = 0;
static int validCount = 0;
static int cycles = 0;
static unsigned int results[1000];
static int resultIndex;
static char buf[0x100000];
static char buf2[0x100000];


//---------------------------------------------------------------------------
void resetMeasurement()
{
//   memset(done, 1, sizeof(done));
   memcpy(buf2,buf, sizeof(buf));
   validCount = sizeof(buf);
   lastIndex = 0;
   dumpIndex = 0;
   cycles = 0;
}

//---------------------------------------------------------------------------
void doMeasurement()
{
    DWORD count;
    bool result = ReadProcessMemory(
        a_hGplProcess,	// handle of the process whose memory is read
        (void *)(0x540000),	// address to start reading
        &buf,	// address of buffer to place read data
        sizeof(buf),	// number of bytes to read
        &count 	// address of number of bytes read
    );

    if (!result)
        return;

 //   if (validCount < 10)
  //      return;

            if (resultIndex < 1000)
            {
  //              for (int x = 0; x < 8; x++)
       //         {
                    results[resultIndex++] = *((unsigned long *)&(buf[0x397c8]));
  //                  results[resultIndex++] = *((unsigned long *)&(buf[0x397e8]));
   //             }
            }
    if (cycles == 4)
        return;



    // check
    unsigned short *pMemVal1;
    unsigned short *pMemVal2;
    validCount = 0;
    for (int i = 0; i < sizeof(buf)-100; i+=2)
    {
 //       if (done[i] != 1)
 //          continue;
        pMemVal1 = (unsigned short *)&(buf[i]);
        pMemVal2 = (unsigned short *)&(buf2[i]);

 /*       if (*pMemVal1 == a_startAddress)
        {
            if (dumpIndex < 100)
            {
                dump[dumpIndex++] = i;
            }
        }
 */
//        if (*pMemVal1 == (*pMemVal2)+1 && *pMemVal1 < 10)
//        {
            dumpIndex = i*5+cycles;
            if (dumpIndex < 0x500000)
            {
                dump[dumpIndex] = *pMemVal1;
            }

 //           validCount++;
//            lastIndex = i;
//        }
        buf2[i] = buf[i];
//        else
//        {
//            done[i] = 0;
//        }
    }
//    dump[dumpIndex++] = 0;
    cycles++;
    if (cycles == 4)
    {
        int x=0;
        for (int i = 0; i < 0x500000; i+=5)
        {
            unsigned int dif1 = dump[i+1] - dump[i];
            unsigned int dif2 = dump[i+2] - dump[i+1];
            unsigned int dif3 = dump[i+3] - dump[i+2];
  //          if (dif1 == dif2 && dif1 == dif3 && dif1 != 0)
            if (dif1==36 || dif2==36 || dif3==36)
            {
                dump[x]=dump[i];
                dump[x+1]=dump[i+1];
                dump[x+2]=dump[i+2];
                dump[x+3]=dump[i+3];
                dump[x+4]=i/5;
                x+=5;
            }
        }
        dumpIndex=x;
    }

}

