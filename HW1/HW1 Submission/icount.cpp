#include "pin.H"
#include "util.h"
CUtilImage pinutil;

VOID EveryInst(ADDRINT ip, ADDRINT * regRAX, ADDRINT * regRBX, ADDRINT * regRCX, ADDRINT * regRDX) ;

VOID Instruction(INS ins, VOID *v)
{
    ADDRINT addr = INS_Address(ins);
    string strDis = INS_Disassemble(ins);
    if( pinutil.IsMainRoutine(addr) ) {
        Log("[%s:%lx] %s\n", pinutil.GetImageName(addr), addr, strDis.c_str());  
       switch( addr ) {
            case 0x55555555594c:
                {
                    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)EveryInst, IARG_INST_PTR, 
                    IARG_REG_REFERENCE, REG_RAX, 
                    IARG_REG_REFERENCE, REG_RBX, 
                    IARG_REG_REFERENCE, REG_RCX, 
                    IARG_REG_REFERENCE, REG_RDX, 
                    IARG_END); 

                }
                break;
                case 0x555555555892:
                {
                    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)EveryInst, IARG_INST_PTR, 
                    IARG_REG_REFERENCE, REG_RAX, 
                    IARG_REG_REFERENCE, REG_RBX, 
                    IARG_REG_REFERENCE, REG_RCX, 
                    IARG_REG_REFERENCE, REG_RDX, 
                    IARG_END); 

                }
                break;
                
            case 0x555555555903: 
                {
                    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)EveryInst, IARG_INST_PTR, 
                    IARG_REG_REFERENCE, REG_RAX, 
                    IARG_REG_REFERENCE, REG_RBX, 
                    IARG_REG_REFERENCE, REG_RCX, 
                    IARG_REG_REFERENCE, REG_RDX, 
                    IARG_END); 

                }
                break;
                  
        }
    }
}


VOID EveryInst(ADDRINT ip, ADDRINT * regRAX, ADDRINT * regRBX, ADDRINT * regRCX, ADDRINT * regRDX) 
{
  
    if( ip == 0x55555555594c) {
       *regRCX = 0;
       *regRAX = 0;
    }
    else if( ip == 0x555555555892 ) {
        *regRCX = 0;
    } 
    else if ( ip == 0x555555555903 ) {
        *regRAX = 0;
        *regRCX = 0;
        *regRDX = 0;
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

