// zCPUSpecs.cpp
// Carsten Edenfeld - origin: Intel

#include <windows.h> 
#include <limits.h>
#include <stdlib.h>

#include "zcore.h"
#include "zCPUSpecs.h"

// Global Variable /////////////////////////////////////////////
int clone_flag;				// Flag to show whether processor
							//   is an Intel clone

#define ROUND_THRESHOLD		6

// Tabs set at 4

static FREQ_INFO GetCmosCpuSpeed();
static FREQ_INFO GetRDTSCCpuSpeed();
static FREQ_INFO GetBSFCpuSpeed(ulong cycles);

static unsigned long diffTime64(unsigned long t1Hi, unsigned long t1Low, 
						 unsigned long t2Hi, unsigned long t2Low, 
 					 	 unsigned long *tHi, unsigned long *tLow );

// Number of cycles needed to execute a single BSF instruction.
//    Note that processors below i386(tm) are not supported.
static ulong processor_cycles[] = {
	00,  00,  00, 115, 47, 43, 
	38,  38,  38, 38,  38, 38, 
};


// Public Functions ////////////////////////////////////////

/***************************************************************
* wincpuidsupport()
*
* Inputs: none
*
* Returns:
*  1 = CPUID opcode is supported
*  0 = CPUID opcode is not supported
***************************************************************/

WORD wincpuidsupport() {
	int cpuid_support = 1;

	_asm {
        pushfd					// Get original EFLAGS
		pop		eax
		mov 	ecx, eax
        xor     eax, 0x200000	// Flip ID bit in EFLAGS
        push    eax				// Save new EFLAGS value on
        						//   stack
        popfd					// Replace current EFLAGS value
        pushfd					// Get new EFLAGS
        pop     eax				// Store new EFLAGS in EAX
        xor     eax, ecx		// Can not toggle ID bit,
        jnz     support			// Processor=80486
		
		mov cpuid_support,0		// Clear support flag
support:
      }
	
	return cpuid_support;

} // wincpuidsupport()



/***************************************************************
* wincpuid()
*
* Inputs: none
*
* Returns:
*  0 = 8086/88
*  2 = 80286
*  3 = 80386
*  4 = 80486
*  5 = Pentium(R) Processor
*  6 = PentiumPro(R) Processor
*  7 or higher = Processor beyond the PentiumPro6(R) Processor
*
*  Note: This function also sets the global variable clone_flag
***************************************************************/

WORD wincpuid() {

	WORD cpuid;
	
	if ( wincpuidsupport() ) 	// Determine whether CPUID 
								//   opcode is supported
		cpuid=check_IDProc();

	else {
		
		clone_flag=check_clone();
	
		cpuid=check_8086();			// Will return FFFFh or 0
		if (cpuid == 0) goto end;
	
    	cpuid=check_80286();       	// Will return FFFFh or 2
		if (cpuid == 2) goto end;

    	cpuid=check_80386();       	// Will return FFFFh or 3
		if (cpuid == 3) goto end;    // temporarily commented out.
        
        cpuid=4;		// If the processor does not support CPUID,
        				//  is not an 8086, 80286, or 80386, assign
        				//  processor to be an 80486
	}

end:
	if (clone_flag)
		cpuid = cpuid | CLONE_MASK;	// Signify that a clone has been
									//   detected by setting MSB high 

   	return cpuid;

} // wincpuid ()



/***************************************************************
* wincpuidext()
*
* Inputs: none
*
* Returns:
* AX(15:14) = Reserved (mask these off in the calling code 
*				before using)
* AX(13:12) = Processor type (00=Standard OEM CPU, 01=OverDrive,
*				10=Dual CPU, 11=Reserved)
* AX(11:8)  = CPU Family (the same 4-bit quantity as wincpuid())
* AX(7:4)   = CPU Model, if the processor supports the CPUID 
*				opcode; zero otherwise
* AX(3:0)   = Stepping #, if the processor supports the CPUID 
*				opcode; zero otherwise
*
*  Note: This function also sets the global variable clone_flag
***************************************************************/

WORD wincpuidext() {

		int i=0;
		WORD cpu_type=0x0000;
		WORD cpuidext=0x0000;
		BYTE vendor_id[13]="------------";
		BYTE intel_id[13]="GenuineIntel";

	if ( wincpuidsupport() ) {

_asm {      

		xor     eax, eax		// Set up for CPUID instruction
        
		CPU_ID                  // Get and save vendor ID

		mov     dword ptr vendor_id, ebx
		mov     dword ptr vendor_id[+4], edx
		mov     dword ptr vendor_id[+8], ecx
}

for (i=0;i<12;i++)
{
	if (!(vendor_id[i]==intel_id[i]))
		clone_flag = 1;    
}

_asm {
        
		cmp     eax, 1			// Make sure 1 is valid input 
        						//   for CPUID
        
        jl      end_cpuidext	// If not, jump to end
        xor     eax, eax
        inc		eax
        CPU_ID					// Get family/model/stepping/
        						//   features

		mov		cpuidext, ax

end_cpuidext:
		mov		ax, cpuidext
    	}
	}
	else {

	cpu_type = wincpuid();		// If CPUID opcode is not
	cpuidext = cpu_type << 8;	//   supported, put family
								//   value in extensions and
	}							//   return
	
	return cpuidext;

} // wincpuidext()



/***************************************************************
* wincpufeatures()
*
* Inputs: none
*
* Returns:
*   0 = Processor which does not execute the CPUID instruction.
*          This includes 8086, 8088, 80286, 80386, and some 
*		   older 80486 processors.                       
*
* Else
*   Feature Flags (refer to App Note AP-485 for description).
*      This DWORD was put into EDX by the CPUID instruction.
*
*	Current flag assignment is as follows:
*
*		bit31..10   reserved (=0)
*		bit9=1      CPU contains a local APIC (iPentium-3V)
*		bit8=1      CMPXCHG8B instruction supported
*		bit7=1      machine check exception supported
*		bit6=0      reserved (36bit-addressing & 2MB-paging)
*		bit5=1      iPentium-style MSRs supported
*		bit4=1      time stamp counter TSC supported
*		bit3=1      page size extensions supported
*		bit2=1      I/O breakpoints supported
*		bit1=1      enhanced virtual 8086 mode supported
*		bit0=1      CPU contains a floating-point unit (FPU)
*
*	Note: New bits will be assigned on future processors... see
*         processor data books for updated information
*
*	Note: This function also sets the global variable clone_flag
***************************************************************/

DWORD wincpufeatures() {

	int i=0;
	DWORD cpuff=0x00000000;
	BYTE vendor_id[13]="------------";
	BYTE intel_id[13]="GenuineIntel";

	if ( wincpuidsupport() ) {

_asm {      

		xor     eax, eax		// Set up for CPUID instruction
        
		CPU_ID                  // Get and save vendor ID

        mov     dword ptr vendor_id, ebx
        mov     dword ptr vendor_id[+4], edx
        mov     dword ptr vendor_id[+8], ecx
}

for (i=0;i<12;i++)
{
	if (!(vendor_id[i]==intel_id[i]))
		clone_flag = 1;    
}

_asm {
         
		cmp     eax, 1			// Make sure 1 is valid input 
        						//   for CPUID
        
        jl      end_cpuff		// If not, jump to end
        xor     eax, eax
        inc		eax
        CPU_ID					// Get family/model/stepping/
        						//   features

		mov		cpuff, edx

end_cpuff:
		mov		eax, cpuff
      }
	}

	return cpuff;

} // wincpufeatures()



/***************************************************************
* winrdtsc()
*
* Inputs: none
*
* Returns:
*   0 = CPU does not support the time stamp register
*
* Else
*   Returns a variable of type TIME_STAMP which is composed of 
*      two DWORD variables. The 'High' DWORD contains the upper
*      32-bits of the Time Stamp Register. The 'Low' DWORD 
*      contains the lower 32-bits of the Time Stamp Register.
*
*  Note: This function also sets the global variable clone_flag
***************************************************************/

TIME_STAMP winrdtsc() {

	struct TIME_STAMP timestamp;    // Return variable for time
									//   stamp read
	DWORD features = wincpufeatures();	// Processor Features
	
	timestamp.Low  = 0;
	timestamp.High = 0;
		
	if ( features & 0x00000010 ) {

		RDTSC						// Read Time Stamp

		_asm
			{
			MOV timestamp.Low, EAX
			MOV timestamp.High, EDX

			}
	}
	
	return timestamp;

} // winrdtsc


/***************************************************************
* check_clone()
*
* Inputs: none
*
* Returns:
*   1      if processor is clone (limited detection ability)
*   0      otherwise
***************************************************************/

WORD check_clone()
{
	short cpu_type=0;

	_asm 
		{
  					MOV AX,5555h	// Check to make sure this
					XOR DX,DX		//   is a 32-bit processor
					MOV CX,2h
					DIV CX			// Perform Division
					CLC
					JNZ no_clone
					JMP clone
		no_clone:	STC
		clone:		PUSHF
					POP AX          // Get the flags
					AND AL,1
					XOR AL,1        // AL=0 is probably Intel,
									//   AL=1 is a Clone
					
					MOV cpu_type, ax
		}
	
    cpu_type = cpu_type & 0x0001;
    
	return cpu_type;
		
} // check_clone()



/***************************************************************
* check_8086()
*
* Inputs: none
*
* Returns: 
*   0      if processor 8086
*   0xffff otherwise
***************************************************************/

WORD check_8086()
{

		WORD cpu_type=0xffff;

_asm {
        pushf                   // Push original FLAGS
        pop     ax              // Get original FLAGS
        mov     cx, ax          // Save original FLAGS
        and     ax, 0fffh       // Clear bits 12-15 in FLAGS
        push    ax              // Save new FLAGS value on stack
        popf                    // Replace current FLAGS value
        pushf                   // Get new FLAGS
        pop     ax              // Store new FLAGS in AX
        and     ax, 0f000h      // If bits 12-15 are set, then
        cmp     ax, 0f000h      //   processor is an 8086/8088
        mov     cpu_type, 0    	// Turn on 8086/8088 flag
        je      end_8086    	// Jump if processor is 8086/
        						//   8088
        mov		cpu_type, 0ffffh
end_8086:
		push 	cx
		popf
		mov		ax, cpu_type

      }
	
	return cpu_type;

} // check_8086()



/***************************************************************
* check_80286()
*
* Inputs: none
*
* Returns:
*   2      if processor 80286
*   0xffff otherwise
***************************************************************/

WORD check_80286()
{

		WORD cpu_type=0xffff;

_asm {
		pushf
		pop		cx
		mov		bx, cx
        or      cx, 0f000h      // Try to set bits 12-15
        push    cx              // Save new FLAGS value on stack
        popf                    // Replace current FLAGS value
        pushf                   // Get new FLAGS
        pop     ax              // Store new FLAGS in AX
        and     ax, 0f000h      // If bits 12-15 are clear
        
        mov     cpu_type, 2     // Processor=80286, turn on 
        						//   80286 flag
        
        jz      end_80286       // If no bits set, processor is 
        						//   80286
		
		mov		cpu_type, 0ffffh
end_80286:
		push	bx
		popf
		mov		ax, cpu_type

      }
	
	return cpu_type;

} // check_80286()



/***************************************************************
* check_80386()
*
* Inputs: none
*
* Returns:
*   3      if processor 80386
*   0xffff otherwise
***************************************************************/

WORD check_80386()
{

		WORD cpu_type=0xffff;

_asm {   
		mov 	bx, sp
		and		sp, not 3
        pushfd					// Push original EFLAGS 
        pop     eax				// Get original EFLAGS
        mov     ecx, eax		// Save original EFLAGS
        xor     eax, 40000h		// Flip AC bit in EFLAGS
        
        push    eax             // Save new EFLAGS value on
        						//   stack
        
        popfd                   // Replace current EFLAGS value
        pushfd					// Get new EFLAGS
        pop     eax             // Store new EFLAGS in EAX
        
        xor     eax, ecx        // Can't toggle AC bit, 
        						//   processor=80386
        
        mov     cpu_type, 3		// Turn on 80386 processor flag
        jz      end_80386		// Jump if 80386 processor
		mov		cpu_type, 0ffffh
end_80386:
		push	ecx
		popfd
		mov		sp, bx
		mov		ax, cpu_type
		and		eax, 0000ffffh
      }

	return cpu_type;

} // check_80386()



/***************************************************************
* check_IDProc()
*
* Inputs: none
*
* Returns:
*  CPU Family (i.e. 4 if Intel 486, 5 if Pentium(R) Processor)
*
*  Note: This function also sets the global variable clone_flag
***************************************************************/

WORD check_IDProc() {

		int i=0;
		WORD cpu_type=0xffff;
		BYTE stepping=0;
		BYTE model=0;
		BYTE vendor_id[13]="------------";
		BYTE intel_id[13]="GenuineIntel";

_asm {      

        xor     eax, eax		// Set up for CPUID instruction
        
        CPU_ID                  // Get and save vendor ID

        mov     dword ptr vendor_id, ebx
        mov     dword ptr vendor_id[+4], edx
        mov     dword ptr vendor_id[+8], ecx
}

for (i=0;i<12;i++)
{
	if (!(vendor_id[i]==intel_id[i]))
		clone_flag = 1;    
}

_asm {

        cmp     eax, 1			// Make sure 1 is valid input 
        						//   for CPUID
        
        jl      end_IDProc		// If not, jump to end
        xor     eax, eax
        inc		eax
        CPU_ID					// Get family/model/stepping/
        						//   features

		mov 	stepping, al
		and		stepping, 0x0f //0fh
		
		and 	al, 0f0h
		shr		al, 4
		mov 	model, al
		
		and		eax, 0f00h
        shr     eax, 8			// Isolate family
		and		eax, 0fh
        mov     cpu_type, ax	// Set _cpu_type with family

end_IDProc:
		mov		ax, cpu_type
      }
	
	return cpu_type;

} // Check_IDProc()



/***************************************************************
* CpunormSpeed() -- Return the raw clock rate of the host CPU.
*
* Inputs:
*	clocks:		0: Use default value for number of cycles
*				   per BSF instruction.
*               -1: Use CMos timer to get cpu speed.
*   			Positive Integer: Use clocks value for number
*				   of cycles per BSF instruction.
*
* Returns:
*		If error then return all zeroes in FREQ_INFO structure
*		Else return FREQ_INFO structure containing calculated 
*       clock frequency, normalized clock frequency, number of 
*       clock cycles during test sampling, and the number of 
*       microseconds elapsed during the sampling.
***************************************************************/

unsigned long cpunormspeed(int clocks)
{
	struct FREQ_INFO cpu_speed;
	HKEY hKey;
	LPBYTE ProcSpeed;
	DWORD buflen, ret;

    if (!RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey)) 
	{
        ProcSpeed = 0;
        buflen = sizeof( ProcSpeed );
        ret = RegQueryValueEx(hKey, "~MHz", NULL, NULL, (LPBYTE) &ProcSpeed, &buflen);
		// If we don't succeed, try some other spellings.
		if (ret != ERROR_SUCCESS) 
	        ret = RegQueryValueEx(hKey, "~Mhz", NULL, NULL, (LPBYTE) &ProcSpeed, &buflen);
		if (ret != ERROR_SUCCESS) 
			ret = RegQueryValueEx(hKey, "~mhz", NULL, NULL, (LPBYTE) &ProcSpeed, &buflen);
        RegCloseKey(hKey);
		if (ret == ERROR_SUCCESS) 
            return (unsigned long)ProcSpeed;
    }
	cpu_speed = cpuspeed(clocks);
	return cpu_speed.norm_freq;
}

/***************************************************************
* ProcessorCount() -- Return the number of CPU's on this machine.
*
* Inputs:
*
* Returns:
*		count of the number of processors on this machine.
***************************************************************/

unsigned long ProcessorCount()
{
	DWORD ProcessAffinityMask, SystemAffinityMask, count;

	GetProcessAffinityMask(GetCurrentProcess(),	&ProcessAffinityMask, &SystemAffinityMask);	

    // count bits in the mask
    for (count = 0; SystemAffinityMask != 0; count++)
		SystemAffinityMask &= (SystemAffinityMask-1);

	return count;
}

/***************************************************************
* CpurawSpeed() -- Return the raw clock rate of the host CPU.
*
* Inputs:
*	clocks:		0: Use default value for number of cycles
*				   per BSF instruction.
*               -1: Use CMos timer to get cpu speed (DOES NOT WORK FOR WINNT).
*   			Positive Integer: Use clocks value for number
*				   of cycles per BSF instruction.
*
* Returns:
*		If error then return all zeroes in FREQ_INFO structure
*		Else return FREQ_INFO structure containing calculated 
*       clock frequency, normalized clock frequency, number of 
*       clock cycles during test sampling, and the number of 
*       microseconds elapsed during the sampling.
***************************************************************/

unsigned long cpurawspeed(int clocks)
{
	struct FREQ_INFO cpu_speed;

	cpu_speed = cpuspeed(clocks);
	return cpu_speed.raw_freq;
}


/***************************************************************
* CpuSpeed() -- Return the raw clock rate of the host CPU.
*
* Inputs:
*	clocks:		0: Use default value for number of cycles
*				   per BSF instruction.
*               -1: Use CMos timer to get cpu speed.
*   			Positive Integer: Use clocks value for number
*				   of cycles per BSF instruction.
*
* Returns:
*		If error then return all zeroes in FREQ_INFO structure
*		Else return FREQ_INFO structure containing calculated 
*       clock frequency, normalized clock frequency, number of 
*       clock cycles during test sampling, and the number of 
*       microseconds elapsed during the sampling.
***************************************************************/

FREQ_INFO cpuspeed(int clocks) 
{
	ulong  cycles;					// Clock cycles elapsed 
									//   during test
	
	ushort processor = wincpuid();	// Family of processor

	DWORD features = wincpufeatures();	// Features of Processor

	int manual=0;			// Specifies whether the user 
							//   manually entered the number of
							//   cycles for the BSF instruction.

	struct FREQ_INFO cpu_speed;		// Return structure for
									//   cpuspeed

	memset(&cpu_speed, 0x00, sizeof(cpu_speed));
	
	if ( processor & CLONE_MASK )
		return cpu_speed;

	// Check for manual BSF instruction clock count
	if (clocks <= 0) {
		cycles = ITERATIONS * processor_cycles[processor];
	}
	else if (0 < clocks && clocks <= MAXCLOCKS)  {
		cycles = ITERATIONS * clocks;
		manual = 1;			// Toggle manual control flag.
							//   Note that this mode will not
							// 	 work properly with processors
							//   which can process multiple
							//   BSF instructions at a time.
							//   For example, manual mode
							//   will not work on a 
							//   PentiumPro(R)
	}

	if ( ( features&0x00000010 ) && !(manual) ) {						
						// On processors supporting the Read 
						//   Time Stamp opcode, compare elapsed
						//   time on the High-Resolution Counter
						//   with elapsed cycles on the Time 
						//   Stamp Register.
		if ( clocks == 0 )
			return GetRDTSCCpuSpeed();
		else
			return GetCmosCpuSpeed();
    }
	else if ( processor >= 3 ) {
		return GetBSFCpuSpeed(cycles);
	}

	return cpu_speed;

} // cpuspeed()


FREQ_INFO GetBSFCpuSpeed(ulong cycles)
{
	// If processor does not support time 
	//   stamp reading, but is at least a 
	//   386 or above, utilize method of 
	//   timing a loop of BSF instructions 
	//   which take a known number of cycles
	//   to run on i386(tm), i486(tm), and
	//   Pentium(R) processors.
	LARGE_INTEGER t0,t1;			// Variables for High-
									//   Resolution Performance
									//   Counter reads

	ulong freq  =0;			// Most current frequ. calculation

	ulong  ticks;					// Microseconds elapsed 
									//   during test
	
	LARGE_INTEGER count_freq;		// High Resolution 
									//   Performance Counter 
									//   frequency

	int i;						// Temporary Variable

	ulong current = 0;          // Variable to store time
									//   elapsed during loop of
									//   of BSF instructions

	ulong lowest  = ULONG_MAX;	// Since algorithm finds 
									//   the lowest value out of
									//   a set of samplings, 
									//   this variable is set 
									//   intially to the max 
									//   unsigned long value). 
									//   This guarantees that 
									//   the initialized value 
									//   is not later used as 
									//   the least time through 
									//   the loop.

	struct FREQ_INFO cpu_speed;

	memset(&cpu_speed, 0x00, sizeof(cpu_speed));

	if ( !QueryPerformanceFrequency ( &count_freq ) )
		return cpu_speed;

	for ( i = 0; i < SAMPLINGS; i++ ) { // Sample Ten times. Can
									 //   be increased or 
									 //   decreased depending
									 //   on accuracy vs. time
									 //   requirements

		QueryPerformanceCounter(&t0);	// Get start time

			_asm 
			{
				
					mov eax, 80000000h	
					mov bx, ITERATIONS		
								// Number of consecutive BSF 
								//   instructions to execute. 
								//   Set identical to 
								//   nIterations constant in
								//   speed.h
	           
				loop1:	bsf ecx,eax
       
	       				dec	bx
						jnz	loop1
			}
							 
		QueryPerformanceCounter(&t1);	// Get end time
		current = (ulong) t1.LowPart - (ulong) t0.LowPart;	
								// Number of external ticks is
								//   difference between two
								//   hi-res counter reads.

		if ( current < lowest )		// Take lowest elapsed
			lowest = current;		//   time to account
	}								//   for some samplings
										//   being interrupted
										//   by other operations 
		 
	ticks = lowest;

	// Note that some seemingly arbitrary mulitplies and
	//   divides are done below. This is to maintain a 
	//   high level of precision without truncating the 
	//   most significant data. According to what value 
	//   ITERATIIONS is set to, these multiplies and
	//   divides might need to be shifted for optimal
	//   precision.

	ticks = ticks * 100000;	
						// Convert ticks to hundred
						//   thousandths of a tick
			
	ticks = ticks / ( count_freq.LowPart/10 );		
						// Hundred Thousandths of a 
						//   Ticks / ( 10 ticks/second )
						//   = microseconds (us)
		
	if ( ticks%count_freq.LowPart > count_freq.LowPart/2 )	
		ticks++;				// Round up if necessary
			
	freq = cycles/ticks;		// Cycles / us  = MHz

	cpu_speed.raw_freq  = freq;
    if ( cycles%ticks > ticks/2 )
   		freq++;					// Round up if necessary	

	cpu_speed.in_cycles = cycles;	// Return variable structure
	cpu_speed.ex_ticks  = ticks;	//   determined by one of 
	cpu_speed.norm_freq = freq;

	return cpu_speed;
}	

FREQ_INFO GetRDTSCCpuSpeed()
{
	struct FREQ_INFO cpu_speed;
	LARGE_INTEGER t0,t1;			// Variables for High-
									//   Resolution Performance
									//   Counter reads

	ulong freq  =0;			// Most current frequ. calculation
	ulong freq2 =0;			// 2nd most current frequ. calc.
	ulong freq3 =0;			// 3rd most current frequ. calc.
	
	ulong total;			// Sum of previous three frequency
							//   calculations

	int tries=0;			// Number of times a calculation has
							//   been made on this call to 
							//   cpuspeed

	ulong  total_cycles=0, cycles;	// Clock cycles elapsed 
									//   during test
	
	ulong  stamp0, stamp1;			// Time Stamp Variable 
									//   for beginning and end 
									//   of test

	ulong  total_ticks=0, ticks;	// Microseconds elapsed 
									//   during test
	
	LARGE_INTEGER count_freq;		// High Resolution 
									//   Performance Counter 
									//   frequency

#ifdef WIN32
	int iPriority;
	HANDLE hThread = GetCurrentThread();
#endif // WIN32;

	memset(&cpu_speed, 0x00, sizeof(cpu_speed));

	if ( !QueryPerformanceFrequency ( &count_freq ) )
		return cpu_speed;

	// On processors supporting the Read 
	//   Time Stamp opcode, compare elapsed
	//   time on the High-Resolution Counter
	//   with elapsed cycles on the Time 
	//   Stamp Register.
	
	do {			// This do loop runs up to 20 times or
	   				//   until the average of the previous 
	   				//   three calculated frequencies is 
	   				//   within 1 MHz of each of the 
	   				//   individual calculated frequencies. 
					//   This resampling increases the 
					//   accuracy of the results since
					//   outside factors could affect this
					//   calculation
			
		tries++;		// Increment number of times sampled
						//   on this call to cpuspeed
			
		freq3 = freq2;	// Shift frequencies back to make
		freq2 = freq;	//   room for new frequency 
						//   measurement

    	QueryPerformanceCounter(&t0);	
    					// Get high-resolution performance 
    					//   counter time
			
		t1.LowPart = t0.LowPart;		// Set Initial time
		t1.HighPart = t0.HighPart;

#ifdef WIN32
		iPriority = GetThreadPriority(hThread);
		if ( iPriority != THREAD_PRIORITY_ERROR_RETURN )
		{
			SetThreadPriority(hThread, THREAD_PRIORITY_TIME_CRITICAL);
		}
#endif // WIN32

   		while ( (ulong)t1.LowPart - (ulong)t0.LowPart<50) {	  
   						// Loop until 50 ticks have 
   						//   passed	since last read of hi-
						//	 res counter. This accounts for
						//   overhead later.

			QueryPerformanceCounter(&t1);

			RDTSC;						// Read Time Stamp
			_asm {
				MOV stamp0, EAX
			}
		}
			
			
		t0.LowPart = t1.LowPart;		// Reset Initial 
		t0.HighPart = t1.HighPart;		//   Time

   		while ((ulong)t1.LowPart-(ulong)t0.LowPart<1000 ) {
   						// Loop until 1000 ticks have 
   						//   passed	since last read of hi-
   						//   res counter. This allows for
						//   elapsed time for sampling.
   			
				
   			QueryPerformanceCounter(&t1);
   			

			RDTSC;						// Read Time Stamp
			__asm {
				MOV stamp1, EAX
			}
		}

			

#ifdef WIN32
		// Reset priority
		if ( iPriority != THREAD_PRIORITY_ERROR_RETURN )
		{
			SetThreadPriority(hThread, iPriority);
		}
#endif // WIN32

       	cycles = stamp1 - stamp0;	// Number of internal 
        							//   clock cycles is 
        							//   difference between 
        							//   two time stamp 
        							//   readings.

    	ticks = (ulong) t1.LowPart - (ulong) t0.LowPart;	
								// Number of external ticks is
								//   difference between two
								//   hi-res counter reads.
	

		// Note that some seemingly arbitrary mulitplies and
		//   divides are done below. This is to maintain a 
		//   high level of precision without truncating the 
		//   most significant data. According to what value 
		//   ITERATIIONS is set to, these multiplies and
		//   divides might need to be shifted for optimal
		//   precision.

		ticks = ticks * 100000;	
							// Convert ticks to hundred
							//   thousandths of a tick
			
		ticks = ticks / ( count_freq.LowPart/10 );		
							// Hundred Thousandths of a 
							//   Ticks / ( 10 ticks/second )
							//   = microseconds (us)

		total_ticks += ticks;
		total_cycles += cycles;

		if ( ticks%count_freq.LowPart > count_freq.LowPart/2 )
			ticks++;			// Round up if necessary
			
		freq = cycles/ticks;	// Cycles / us  = MHz
        										
     	if ( cycles%ticks > ticks/2 )
       		freq++;				// Round up if necessary
          	
		total = ( freq + freq2 + freq3 );
							// Total last three frequency 
							//   calculations

	} while ( (tries < 3 ) || 		
	          (tries < 20)&&
	          ((abs(3 * freq -total) > 3*TOLERANCE )||
	           (abs(3 * freq2-total) > 3*TOLERANCE )||
	           (abs(3 * freq3-total) > 3*TOLERANCE )));	
					// Compare last three calculations to 
	          		//   average of last three calculations.		

	// Try one more significant digit.
	freq3 = ( total_cycles * 10 ) / total_ticks;
	freq2 = ( total_cycles * 100 ) / total_ticks;


	if ( freq2 - (freq3 * 10) >= ROUND_THRESHOLD )
		freq3++;

	cpu_speed.raw_freq = total_cycles / total_ticks;
	cpu_speed.norm_freq = cpu_speed.raw_freq;

	freq = cpu_speed.raw_freq * 10;
	if( (freq3 - freq) >= ROUND_THRESHOLD )
		cpu_speed.norm_freq++;

	cpu_speed.ex_ticks = total_ticks;
	cpu_speed.in_cycles = total_cycles;

	return cpu_speed;
}

int GetCmosTick(void)
{
	int tick = 0;

	// __asm	mov ah, 02h
	// __asm	int 1Ah
	// __asm	mov al, dh
	// __asm	and ax, 000Fh  

	__asm  xor ax, ax
	__asm  out 070h, al

	__asm  xor ax, ax
	__asm  in  al, 071h

    // _outp( 0x70, offset );
    // base = _inp( 0x71 ); 

// value returned in ax by function

	__asm 	mov word ptr tick, ax

	return tick;
}

//***************************************************************
//
// Function: cpuTimeStamp
//
//		Returns the pentium cpu time stamp in 2 32 bit unsigned longs
//
//	Notes: maintains a flag to make sure the cpu supports the RDTSC instruction.  There is
//		the overhead of checking the cpu the first time afterwhich the time consumed in 
//		checking the flag is very minimal.  You could adjust the count but then you would
//		have to do 64bit math.  ugh.
//
//***************************************************************
unsigned long cpuTimeStamp(unsigned long *hi, unsigned long *low)
{
	unsigned long ulHi = 0L;
	unsigned long ulLow = 0L;
	__asm {
		;RDTSC
		_emit 0Fh
		_emit 31h
		mov ulLow, eax
		mov ulHi, edx
	}		

	*hi = ulHi;
	*low = ulLow;

	return ulLow;		
}	

//***************************************************************
//
// Function: diffTime64
//
//		Calculates the difference of a 64 bit time as represented by
//		two 32 bit unsigned longs
//
//***************************************************************

unsigned long diffTime64(unsigned long t1Hi, unsigned long t1Low, 
						 unsigned long t2Hi, unsigned long t2Low, 
 					 	 unsigned long *tHi, unsigned long *tLow )
{
	unsigned long xl, xh;

	__asm {
		mov eax, t2Low
		mov ebx, t1Low
		sub eax, ebx
		mov xl, eax
		mov eax, t2Hi
		mov ebx, t1Hi
		sbb eax, ebx
		mov xh, eax
	}

	*tLow = xl;
	*tHi  = xh;

	return *tLow;
}

//#define ABS_TICK(a,b)  (b<a)?b+60-a:b-a
// since I am only interested in single ticks
#define ABS_TICK(a,b)  (b<a)?b+10-a:b-a

struct FREQ_INFO GetCmosCpuSpeed()
{
	unsigned long 	t1Low, t1High, t2Low, t2High, tResLow, tResHigh;
	int	timeStart, timeStop, lapseTime;
	unsigned long   temp;
	unsigned long   temp1;
	struct FREQ_INFO cpu_speed;
	unsigned long   cpuSpeed = 0l;
#ifdef WIN32
	HANDLE	hThread = GetCurrentThread();
	int		iPriority;
#endif // WIN32
	

	memset(&cpu_speed, 0x00, sizeof(cpu_speed));

	// This loop waits for the next tick
	// so that we begin speed test on a tick edge
#ifdef WIN32
		iPriority = GetThreadPriority(hThread);
		if ( iPriority != THREAD_PRIORITY_ERROR_RETURN )
		{
			SetThreadPriority(hThread, iPriority+1);
		}
#endif // WIN32

	timeStart = GetCmosTick();
	for(;;)
	{
		timeStop = GetCmosTick();
		if (  ABS_TICK(timeStart,timeStop) > 0 )
		{
			cpuTimeStamp(&t1High, &t1Low);
			break;	
		}	
	}

	timeStart = timeStop;

	for(;;)
	{
		timeStop = GetCmosTick();
		if (  ABS_TICK(timeStart,timeStop) > 0 )
		{
			cpuTimeStamp(&t2High, &t2Low);
			break;	
		}	
	}

#ifdef WIN32
		// Set thread priority back.
		if ( iPriority != THREAD_PRIORITY_ERROR_RETURN )
		{
			SetThreadPriority(hThread, iPriority);
		}
#endif // WIN32

	diffTime64(t1High, t1Low, t2High, t2Low, &tResHigh, &tResLow );
	lapseTime = ABS_TICK(timeStart,timeStop);

	cpuSpeed = tResLow; ///lapseTime; 
	cpu_speed.in_cycles = tResLow;		// Cycles count since we in this routine

	//round to nearest digit
	temp =  cpuSpeed/1000000; 	
	temp1 = cpuSpeed/100000;  
	temp = temp * 10;  // realign with last digit = zero

	cpuSpeed = cpuSpeed/1000000; // cpuSpeed/1000000;
	cpu_speed.raw_freq = cpuSpeed;	

	if( (temp1 - temp) >= ROUND_THRESHOLD )
		cpuSpeed++;
	
	cpu_speed.norm_freq = cpuSpeed;	
	cpu_speed.ex_ticks = (timeStop - timeStart) * 1000000;

	return cpu_speed;			
}

