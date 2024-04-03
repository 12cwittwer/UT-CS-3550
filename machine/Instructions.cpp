#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include "Instructions.h"


const unsigned char PUSH_EBX = 0x53;
const unsigned char PUSH_ESI = 0x56;
const unsigned char PUSH_EDI = 0x57;
const unsigned char POP_EDI = 0x5F;
const unsigned char POP_ESI = 0x5E;
const unsigned char POP_EBX = 0x5B; 


// Some assembly like definitions for our machine code:
const unsigned char PUSH_EBP = 0x55;
const unsigned char MOV_EBP_ESP1 = 0x8B;
const unsigned char MOV_EBP_ESP2 = 0xEC;

const unsigned char POP_EBP = 0x5D;
const unsigned char NEAR_RET = 0xC3;

// Put one instruction at a time into mCode:
void InstructionsClass::Encode(unsigned char c)
{
	if(mCurrent + sizeof(unsigned char) < MAX_INSTRUCTIONS)
	{
		mCode[mCurrent] = c;
		mCurrent += sizeof(unsigned char);
	}
	else
	{
		std::cerr << "Error.  Used up all " << MAX_INSTRUCTIONS 
			<< " instructions." << std::endl;
		exit(1);
	}
}

InstructionsClass::InstructionsClass()
{
	mprotect((void *)((uintptr_t)mCode& ~(sysconf(_SC_PAGE_SIZE)-1)), 
		MAX_INSTRUCTIONS, PROT_READ|PROT_WRITE|PROT_EXEC);

	mCurrent = 0;
	mStartOfMain = 0;

	// All functions start this way. So does our main function.
	Encode(PUSH_EBP);
	Encode(MOV_EBP_ESP1);
	Encode(MOV_EBP_ESP2);

	// Make sure we save and restore all 5 Callee-Save registers.
	// That is, EBP, ESP, EBX, ESI, and EDI
	Encode(PUSH_EBX);
	Encode(PUSH_ESI);
	Encode(PUSH_EDI);

}

void InstructionsClass::Finish()
{
	// Retore Callee-Saved registers:
	Encode(POP_EDI);
	Encode(POP_ESI);
	Encode(POP_EBX);

	// All functions end this way:
	Encode(POP_EBP);
	Encode(NEAR_RET);

	std::cout << "Finished creating " << mCurrent << 
		" bytes of machine code" << std::endl;
}

void InstructionsClass::Execute()
{
	// Jump into the main function of what we just coded, 
	//	found at mCode[mStartOfMain]
	std::cout << "About to Execute the machine code..." << std::endl;
	void * ptr = &(mCode[mStartOfMain]);
	void (*f)(void);
	f = (void (*)(void)) ptr ;
	f();
	// Did everything work?
	std::cout << "\nThere and back again!" << std::endl; 
}

void InstructionsClass::Encode(int x)
{
	*((int*)(&( mCode [mCurrent]))) = x;
	mCurrent += sizeof(int);
}

void InstructionsClass::Encode(long long int x) 
{
	*((long long int*)(&( mCode [mCurrent]))) = x;
	mCurrent += sizeof(long long int);
}

void InstructionsClass::Encode(void * p)
{
        int pointerSize = sizeof(p);

        if (pointerSize==4)
        {
                Encode((int)(long long)p);
        }
        else if(sizeof(p)==8)
        {
                Encode((long long)p);
        }
}


