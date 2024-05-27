#include "pin.H"

#include "util.h"
CUtilImage pinutil;

VOID OnMemWriteAfter(VOID * ip, VOID * addr, UINT32 size);
VOID OnMemRead(VOID * ip, VOID * addr, UINT32 size);
VOID Instruction(INS ins, VOID *v)
{
    ADDRINT addr = INS_Address(ins);
    string strDis = INS_Disassemble(ins);
    if( pinutil.IsMainRoutine(addr) ) {
        Log("[%s:%lx] %s\n", pinutil.GetImageName(addr), addr, strDis.c_str());

        if( addr == 0x555555555270 ) {
            INS_InsertDirectJump( ins, IPOINT_BEFORE, 0x555555555275 );
        }
    }
}

int* g_pnLuckyNum;
int* g_pnYourNum;

VOID OnMemWriteAfter(VOID * ip, VOID * addr, UINT32 size)
{
    Log("[MEMWRITE(AFTER)] %p, memaddr: %p, size: %d\n", ip, addr, size);
    LogData(addr, size);
    if( (VOID*)0x55555555526a == ip ) {
        g_pnYourNum = (int*) addr;
    }
}

VOID OnMemRead(VOID * ip, VOID * addr, UINT32 size)
{
    Log("[MEMREAD] %p, memaddr: %p, size: %d\n", ip, addr, size);
    LogData(addr, size);
    if( (VOID*)0x55555555526d == ip ) {
        g_pnLuckyNum = (int*) addr;

        if( g_pnYourNum && g_pnLuckyNum ) {
            *g_pnYourNum = *g_pnLuckyNum;
        }
    }
}

int main(int argc, char* argv[])
{
    PIN_InitSymbols();
    if (PIN_Init(argc, argv)) {
        return 0;
    }
    
    //=========== util.h ==================
    LogInit("log.txt");    
    pinutil.InstrumentImageLoad(0);
    //=========================================
    
    //==============================================
    INS_AddInstrumentFunction(Instruction, 0);    
    //==============================================

    //=======================================================    
    // Start the program, never returns
    PIN_StartProgram();

    return 0;
}

/* ===================================================================== */
/* eof */
/* ===================================================================== */
