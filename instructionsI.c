/* 
 * File:   instructionsI.c
 * Author: Caroline
 *
 * Created on April 27, 2015, 8:32 PM
 */

//Caroline Lee's I Instructions

#include <stdio.h>
#include <stdint.h>
#include "cpu.h"
#include "i_instructions.h"



uint32_t RS_MASK_I = 0x03E00000;
uint32_t RT_MASK_I = 0x001F0000;
uint32_t IMM_MASK = 0x0000FFFF;

#define RS_FIELD(instruction)((instruction & RS_MASK_I) >> 21);
#define RT_FIELD(instruction)((instruction & RT_MASK_I) >> 16);
#define IMM_FIELD(instruction)(instruction & IMM_MASK);


void addi(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  int16_t imm = IMM_FIELD(instruction);
  int32_t castRS = (int32_t)registers[rs];
  int32_t castIMM = (int32_t)imm;

  registers[rt] = (uint32_t)(castRS + castImm); //cast to uint32 


}
void addiu(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  int16_t imm = IMM_FIELD(instruction);
  uint32_t castRS = (uint32_t)registers[rs];
  uint32_t castIMM = (uint32_t)imm;
  
  registers[rt] = castRS + castIMM;

}

void andi(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  int16_t imm = IMM_FIELD(instruction);
  uint32_t castRS = registers[(uint32_t)rs];
  uint32_t castIMM = (uint32_t)imm;
 
  registers[rt] = castRS & castIMM;

}
void ori(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  int16_t imm = IMM_FIELD(instruction);
  uint32_t castRS = registers[(uint32_t)rs];
  uint32_t castIMM = (uint32_t)imm;

  registers[(uint32_t)rt] = castRS | caastIMM;

}
void xori(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  int16_t imm = IMM_FIELD(instruction);
  uint32_t castRS = registers[(uint32_t)rs];
  uint32_t castIMM = (uint32_t)imm;
  
  registers[rt] = castRS ^ castIMM;

}
void slti(uint32_t instruction)
{ 
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  int16_t imm = IMM_FIELD(instruction);
  int32_t castRS = (int32_t)(registers[(uint32_t)rs]);
  int32_t castIMM = (int32_t)imm;

  if(castRS) < castIMM{
    registers[(uint32_t)rt] = 1;
  }

  else {
    registers[(uint32_t)rt] = 0;
  }

}
void sltiu(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  int16_t imm = IMM_FIELD(instruction);
  uint32_t castRS = registers[(uint32_t)rs];
  uint32_t castIMM = (uint32_t)imm;
  if(castRS < castIMM){
    registers[(uint32_t)rt] = 1;
  }
  else {
    registers[(uint32_t)rt] = 0;
  }
}
void beq(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  int16_t imm = IMM_FIELD(instruction);
  int32_t immShift = (int32_t)(imm << 2);

  if(registers[(uint32_t)rs] == registers[(uint32_t)rt]){
    npc = (uint32_t)(pc + 4 + immShift);
  }
  else{
    npc = (uint32_t)(pc + 4);
  }
}
void bne(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  int16_t imm = IMM_FIELD(instruction);
  int32_t immShift = (int32_t)(imm << 2);

  if(registers[(uint32_t)rs]!= registers[(uint32_t)rt]){
    npc = (uint32_t)(pc + 4 + immShift);
    }
  else {
    npc = (uint32_t)(pc + 4);
  }
}
void lb(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  int16_t imm = IMM_FIELD(instruction);
  int16_t *ptr = (int16_t*)((uint32_t*) &(memory[registers[rs] + imm]));
 
  registers[(uint32_t)rt] = *ptr;

}
void lbu(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  int16_t imm = IMM_FIELD(instruction);
  uint8_t *ptr = (uint8_t*)((uint32_t*) &(memory[registers[rs] + imm]));
  
  registers[(uint32_t)rt] = *ptr; //leave pointer unsigned

}
void lh(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  int16_t imm = IMM_FIELD(instruction);
  int16_t *ptr = (int16_t*)((uint32_t*) &(memory[registers[rs] + imm]));

  registers[(uint32_t)rt] = *ptr; //pass signed pointer

}
void lhu(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  int16_t imm = IMM_FIELD(instruction);
  uint16_t *ptr = (uint16_t*)((uint32_t*) &(memory[registers[rs] + imm]));

  registers[(uint32_t)rt] = *ptr; //pass the unsigned pointer

}
void lw(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  int16_t imm = IMM_FIELD(instruction);
  uint32_t *ptr = (uint32_t*) &memory[(int32_t)registers[(uint32_t)rs] + imm];

  registers[(uint32_t)rt] = *ptr;
  
}
void lui(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  int16_t imm = IMM_FIELD(instruction);
  uint32_t immShift = ((uint32_t)imm) << 16;
  
  registers[(uint32_t)rt] = immShift;
  
}
void sb(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  int16_t imm = IMM_FIELD(instruction);
  uint8_t newByte = (uint8_t)(registers[(uint32_t)rt] & 0x000000FF);

  *(uint8_t*) &memory[registers[(uint32_t)rs] + (uint32_t)imm] = newByte;

}
void sh(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  int16_t imm = IMM_FIELD(instruction);
  uint16_t newHalf = (uint16_t)(registers[(uint32_t)rt] & 0x0000FFFF);

   *(uint16_t*) &memory[registers[(uint32_t)rs] + (uint32_t)imm] = newHalf;

}
void sw(uint32_t instruction)
{
  uint8_t rs = RS_FIELD(instruction);
  uint8_t rt = RT_FIELD(instruction);
  int16_t imm = IMM_FIELD(instruction);
  uint32_t newWord = (uint32_t)(registers[(uint32_t)rt]);

  *(uint32_t*) &memory[registers[(uint32_t)rs] + imm] = newWord;
}
