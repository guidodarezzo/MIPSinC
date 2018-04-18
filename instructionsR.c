/* 
 * File:   instructionsR.c
 * Author: Caroline
 *
 * Created on April 27, 2015, 10:05 PM
 */

#include <stdio.h>
#include <stdint.h>
#include "cpu.h"
#include "r_instructions.h"


//these are my four masks for R-instructions
uint32_t RS_MASK = 0x03E00000;
uint32_t RT_MASK = 0x001F0000;
uint32_t RD_MASK = 0x0000F800;
uint32_t SHAMT_MASK = 0x000007C0;

//these are the four macros for my R-instructions
#define RS_FIELD(instruction)((instruction & RS_MASK) >> 21);
#define RD_FIELD(instruction)((instruction & RD_MASK) >> 11);
#define RT_FIELD(instruction)((instruction & RT_MASK) >> 16);
#define SHAMT_FIELD(instruction)((instruction & SHAMT_MASK) >> 6);

//next functions implement the R-instructions
void add(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  int32_t castRS = (int32_t)registers[rs];
  int32_t castRT = (int32_t)registers[rt];
  
  registers[rd] = (uint32_t)(castRS + castRT);
  
}

void addu (uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  uint32_t castRS = (uint32_t)registers[rs];
  uint32_t castRT = (uint32_t)registers[rt];
  
  registers[rd] = (castRS + castRT);
  
}

void sub (uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  int32_t castRS = (int32_t)(registers[rs]);
  int32_t castRT = (int32_t)(registers[rt]);
  
  registers[rd] = (uint32_t)(castRS - castRT);
  
}

void subu (uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  uint32_t castRS = (uint32_t)(registers[rs]);
  uint32_t castRT = (uint32_t)(registers[rt]);
  
  registers[rd] = (castRS - castRT);
}

void mult (uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  int64_t castRS = (int64_t)((int32_t)(registers[rs]));
  int64_t castRT = (int64_t)((int32_t)(registers[rs]));
  
  int64_t mult = castRS * castRT;
  
  HI = (uint32_t)(mult >> 32);
  LO = (uint32_t)(mult & 0x00000000FFFFFFFF);

}

void multu (uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  uint64_t castRS = (uint64_t)(registers[rs]);
  uint64_t castRT = (uint64_t)(registers[rt]);
          
  uint64_t mult = castRS * castRT;
  
  HI = (uint32_t)((int64_t)mult >> 32);
  LO = (uint32_t)((int64_t)mult & 0x 00000000FFFFFFFF);

}

void div (uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  LO = (uint32_t)((int32_t)(registers[rs]) / (int32_t)(registers[rt]));
  HI = (uint32_t)((int32_t)(registers[rs]) % (int32_t)(registers[rt]));
}

void divu (uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  LO = (uint32_t)((registers[rs]) / (registers[rt]));
  HI = (uint32_t)((registers[rs]) % (registers[rt]));
}
void and (uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  registers[rd] = ((uint32_t)(registers[rt])) & ((uint32_t)(registers[rs]));
}

void nor (uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  registers[rd] = ~(((uint32_t)(registers[rt])) | ((uint32_t)(registers[rs])));
}

void or (uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  registers[rd] = ((uint32_t)(registers[rt])) | ((uint32_t)(registers[rs]));
}

void xor (uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  registers[rd] = ((uint32_t)(registers[rt])) ^ ((uint32_t)(registers[rs]));
}

void sll (uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  uint8_t shamt = SHAMT_FIELD(instruction);
 
  registers[rd] = (uint32_t)(registers[rs] << registers[shamt]);
}

void sllv (uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
 
  registers[rd] = (uint32_t)(registers[rs] << registers[rt]);
}
void srl (uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  uint8_t shamt = SHAMT_FIELD(instruction);
 
  registers[rd] = (uint32_t)(registers[rs] >> registers[shamt]); //casting?
}

void sra (uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  uint8_t shamt = SHAMT_FIELD(instruction);

  registers[rd] = (uint32_t)(((int32_t)(registers[rt])) >> ((int8_t)shamt));
}

void srlv (uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  uint8_t shamt = SHAMT_FIELD(instruction);
 
  registers[rd] = (registers[rs] >> registers[rt]); //casting issue?
}

void srav (uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  uint8_t shamt = SHAMT_FIELD(instruction);

  registers[rd] = (uint32_t)((int32_t)registers[rs] >> registers[rt]);
}

void slt (uint32_t instruction)
{
  int8_t rs = RS_FIELD(instruction);
  int8_t rt = RT_FIELD(instruction);
  int8_t rd = RD_FIELD(instruction);
 
  if ((registers[rs]) < (registers[rt])){
    registers[rd] = 1; }
  else {
    registers[rd] = 0; }
}

void sltu (uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
 
  if (registers[(uint32_t)(rs)] < registers[(uint32_t)(rt)]){
    registers[rd] = 1; }
  else {
    registers[rd] = 0; }
}

void jr (uint32_t instruction) 
{
  uint8_t rs = RS_FIELD(instruction);
  npc  = registers[(uint32_t)rs];
}

void jalr (uint32_t instruction) 
{
  uint8_t rs = RS_FIELD(instruction);
  registers[31] = pc + 4;
  npc = registers[(uint32_t)rs];
}

void mfhi (uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  registers[rd] = HI;
}

void mflo (uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  uint8_t rd = RD_FIELD(instruction);
  registers[rd] = LO;
}

void syscall(uint32_t instruction); //see syscall.c for this