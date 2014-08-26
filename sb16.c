#include <sb16.h>

#define DSP_DATA_AVL 0xE + 0x220
#define DSP_READO 0xA + 0x220
int32 DSPBase = 0x220;
int32 DSPWrite = 0x220 + 0xC;
int32 DSPReset = 0x6 + 0x220;
int32 DSPStatus = 0x220 + 0x000E;
int32 DSPVersionNum = 0;
unsigned char value;
int32 BasePort = 0x220;

#define DSP_RESET 0x06
#define DSP_DATAAVAIL 0x0E
#define DSP_READ 0x0A
int ResetDSP( unsigned int BasePort )
{
outb(BasePort + DSP_RESET, 0x01); // write 0x01 to DSP_RESET
delay_ms(10); // reinitialization
outb(BasePort + DSP_RESET, 0x00); // write 0x00 to DSP_RESET
delay_ms(10); // waiting for results
if ((inb(BasePort + DSP_DATAAVAIL) & 0x80)==0x80 && (inb(BasePort + DSP_READ) == 0xAA))
{
// DSP was found
return(1);
};
return(0); // No DSP found
}

void DSPWait(void)
{
    int i = 0;
    /*while((inb(DSP_READO) & 0x80)!=0)
    {
        i++;
        //vga_printf(inb(DSP_READ) & 0x80, 1);
    }*/
        delay_ms(100);
}

void DSPDataAvail()
{  while((inb(DSPStatus) & 0x80)==0);
}

void ReadDSP(unsigned char *value)
{ DSPDataAvail(); 
    *value=inb(DSP_READO);
}

void GetDSPVersion(void)
{ unsigned char VersionMaj,VersionMin;
  DSPWait();
  outb(DSPWrite,0xE1); //send instruction
  DSPDataAvail(); //wait for dsp to flag u for instruction

  ReadDSP(&VersionMaj);
  ReadDSP(&VersionMin);
  DSPVersionNum=(float)VersionMaj;
  DSPVersionNum+=((float).01*(float)VersionMin);
}

void DSP_Reset()
{ 
  outb(DSPReset,0x01); //write 1 to the port
  delay_ms(1000); 
  outb(DSPReset,0x00); //write 0 to the port
  DSPDataAvail();
  int32 p;
  for(p=0;p<1000;p++)
    { if((inb(DSP_READ))==0xAA)
        {//GetDSPVersion();
         return; //return to caller (SUCCESS)
        }   
    } 
  //cout<<"Unable to Reset the DSP!\n"; //this will happen should 1000 tries fail.
     
}

void WriteDSP(unsigned char value)
{ DSPWait();    
  //  delay_ms(1000);
  outb(DSPWrite,(unsigned char)value);
}

#define SBCMD_SPKR_ON           0xD1
#define SBCMD_SET_RATE          0x40

void SetupDirectPlay()
{
    outb(0x220 + 0x0C, SBCMD_SPKR_ON);            // Turn on DAC Speaker
    
    //DmaInit( 1, SbInfo.bufphys, 0x8000, autoinit, true);

    outb(0x220 + 0x0C, SBCMD_SET_RATE);
    outb(0x220 + 0x0C, 0xD2);     /* E9 = 44100 Hz , D2 = 22050 Hz*/
    
    outb(0x220 + 0x0C, 0x48);
    outb(0x220 + 0x0C, 0xFF);
    outb(0x220 + 0x0C, 0x3F);

    ResetDSP(0x220);
    int Div = 1193180 / 1000;
    outb(0x43, 0x3c);
    outb(0x40, Div & 0x00ff);
    outb(0x40, (Div>>8)&0x00ff);
}

void DirectPlay(unsigned char byte)
{WriteDSP(0x10);
 WriteDSP(byte);
}