/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include "local-include/reg.h"
#include <cpu/cpu.h>
#include <cpu/ifetch.h>
#include <cpu/decode.h>
#pragma GCC diagnostic ignored "-Wnarrowing"

//my_func
void write_iringbuf(paddr_t pc, word_t inst);
void ftrace_func_call(paddr_t pc_now,paddr_t target);
void ftrace_func_ret(paddr_t pc_now,paddr_t address);

#define R(i) gpr(i)
#define Mr vaddr_read
#define Mw vaddr_write
#define Ext32(x) ((x)&0x80000000)?((x)|0xFFFFFFFF00000000):((x)&0x00000000FFFFFFFF)
#define Ext16(x) ((x)&0x8000)?((x)|0xFFFFFFFFFFFF0000):((x)&0x000000000000FFFF)
#define Ext8(x) ((x)&0x80)?((x)|0xFFFFFFFFFFFFFF00):((x)&0x0000000000000FF)
#define Ext4(x) ((x)&0x8)?((x)|0xFFFFFFFFFFFFFFF0):((x)&0x000000000000000F)

enum {
  TYPE_I, TYPE_U, TYPE_S,
  TYPE_N, // none
  TYPE_J,
  TYPE_R,
  TYPE_B
};

#define src1R() do { *src1 = R(rs1); } while (0)
#define src2R() do { *src2 = R(rs2); } while (0)
#define immI() do { *imm = SEXT(BITS(i, 31, 20), 12); } while(0)
#define immU() do { *imm = SEXT(BITS(i, 31, 12), 20) << 12; } while(0)
#define immS() do { *imm = (SEXT(BITS(i, 31, 25), 7) << 5) | BITS(i, 11, 7); } while(0)
#define immJ() do { *imm = (SEXT(BITS(i, 31, 31), 1) << 20) | (BITS(i, 19, 12) << 12) | (BITS(i, 20, 20) << 11) | (BITS(i, 30, 21) << 1 ); } while(0)
#define immB() do { *imm = (SEXT(BITS(i, 31, 31), 1) << 12) | (BITS(i, 7, 7) << 11) | (BITS(i, 30, 25) << 5) | (BITS(i, 11, 8 ) << 1); } while(0)
//^^^用于从指令中抽取出立即数W

static void decode_operand(Decode *s, int *rd, word_t *src1, word_t *src2, word_t *imm, int type) {
  uint32_t i = s->isa.inst.val;
  int rs1 = BITS(i, 19, 15);
  int rs2 = BITS(i, 24, 20);
  *rd     = BITS(i, 11, 7);
  switch (type) {
    case TYPE_I: src1R();          immI(); break;
    case TYPE_U:                   immU(); break;
    case TYPE_S: src1R(); src2R(); immS(); break;
    case TYPE_J:                   immJ(); break;
    case TYPE_R: src1R(); src2R();         break;
    case TYPE_B: src1R(); src2R(); immB(); break;
  }
}

int32_t mulh(int32_t src1, int32_t src2) {
    // int64_t result = 
    return (int32_t)(((int64_t)src1 * (int64_t)src2)>> 32);
}

// decode_operand译码工作， 这个函数将会根据传入的指令类型type来进行操作数的译码, 译码结果将记录到函数参数rd, src1, src2和imm中
static int decode_exec(Decode *s) {
  int rd = 0;
  word_t src1 = 0, src2 = 0, imm = 0;
  s->dnpc = s->snpc;

#define INSTPAT_INST(s) ((s)->isa.inst.val)
#define INSTPAT_MATCH(s, name, type, ... /* execute body */ ) { \
  decode_operand(s, &rd, &src1, &src2, &imm, concat(TYPE_, type)); \
  __VA_ARGS__ ; \
}
//模式匹配
//INSTPAT(模式字符串, 指令名称, 指令类型, 指令执行操作);
//模式字符串?=>0/1
//指令名称在代码中仅当注释使用, 不参与宏展开;
//指令类型用于后续译码过程
//
  INSTPAT_START();
  INSTPAT("??????? ????? ????? ??? ????? 00101 11", auipc  , U, R(rd) = (s->pc + (imm)));
  INSTPAT("??????? ????? ????? 100 ????? 00000 11", lbu    , I, R(rd) = Mr(src1 + imm, 1));
  INSTPAT("??????? ????? ????? 000 ????? 01000 11", sb     , S, Mw(src1 + imm, 1, src2));
  INSTPAT("??????? ????? ????? 000 ????? 00100 11", addi   , I, R(rd)=(src1+(imm)););
  INSTPAT("??????? ????? ????? ??? 00001 11011 11", jal1   , J, R(rd)=s->snpc;s->dnpc=s->pc+imm;IFDEF(CONFIG_FTRACE,ftrace_func_call(s->pc,s->dnpc)));//jump and link x1 --- Func Call!!printf("%x\n",imm);
  INSTPAT("??????? ????? ????? ??? ????? 11011 11", jal    , J, R(rd)=s->snpc;s->dnpc=s->pc+imm);
  INSTPAT("??????? ????? ????? 000 00001 11001 11", jalr1  , I, R(rd)=s->snpc;s->dnpc=src1+imm;IFDEF(CONFIG_FTRACE,ftrace_func_call(s->pc,s->dnpc)));//jump and link reg x1 --- Func Call!!
  INSTPAT("0000000 00000 00001 000 00000 11001 11", ret    , I, R(rd)=s->snpc;s->dnpc=src1+imm;IFDEF(CONFIG_FTRACE,ftrace_func_ret(s->pc,s->dnpc)));//presudo --- Ret!!
  INSTPAT("??????? ????? ????? 000 ????? 11001 11", jalr   , I, R(rd)=s->snpc;s->dnpc=src1+imm);
  INSTPAT("??????? ????? ????? 011 ????? 01000 11", sd     , S, Mw(src1 + imm, 8, src2));

  INSTPAT("??????? ????? ????? 010 ????? 00000 11", lw     , I, R(rd)=Ext32(Mr(src1+imm,4)));
  INSTPAT("0000000 ????? ????? 000 ????? 01110 11", addw   , R, R(rd)=Ext32(src1+src2));//符号拓展？？可能有问题
  INSTPAT("??????? ????? ????? 000 ????? 00110 11", addiw  , I, R(rd)=Ext32(src1+imm));//这两个先用64位相加，取32位？
  INSTPAT("??????? ????? ????? 011 ????? 00000 11", ld     , I, R(rd)=Mr(src1+imm,8));

  INSTPAT("0100000 ????? ????? 000 ????? 01100 11", sub    , R, R(rd)=src1-src2);
  INSTPAT("??????? ????? ????? 011 ????? 00100 11", sltiu  , I, R(rd)=src1<imm);
  INSTPAT("??????? ????? ????? 000 ????? 11000 11", beq    , B, if(src1==src2) s->dnpc=s->pc+imm);
  INSTPAT("??????? ????? ????? 001 ????? 11000 11", bne    , B, if(src1!=src2) s->dnpc=s->pc+imm);

  INSTPAT("??????? ????? ????? 001 ????? 01000 11", sh     , S, Mw(src1 + imm, 2, src2));
  INSTPAT("0100000 ????? ????? 101 ????? 00100 11", srai   , I, MUXDEF(RV64,R(rd)=((int64_t)src1)>>(imm),R(rd)=((int32_t)src1)>>(imm)));//??(&0xf?)
  INSTPAT("0000000 ????? ????? 000 ????? 01100 11", add    , R, R(rd)=(src1+src2));
  INSTPAT("??????? ????? ????? 111 ????? 00100 11", andi   , I, R(rd)=src1&imm);//??
  INSTPAT("0000000 ????? ????? 001 ????? 01110 11", sllw   , R, R(rd)=(src1<<src2)&0xffffffff);
  INSTPAT("0000000 ????? ????? 111 ????? 01100 11", and    , R, R(rd)=src1&src2);
  INSTPAT("0000000 ????? ????? 011 ????? 01100 11", sltu   , R, R(rd)=src1<src2);
  INSTPAT("??????? ????? ????? 100 ????? 00100 11", xori   , I, R(rd)=src1^imm);
  INSTPAT("0000000 ????? ????? 110 ????? 01100 11", or     , R, R(rd)=src1|src2);

  INSTPAT("000000? ????? ????? 001 ????? 00100 11", slli   , I, R(rd)=src1<<(imm););//?printf("%x,%lx\n",(int)imm,(imm&0xf));
  INSTPAT("000000? ????? ????? 101 ????? 00100 11", srli   , I, R(rd)=src1>>(imm));
  INSTPAT("??????? ????? ????? 101 ????? 11000 11", bge    , B, if((int32_t)src1>=(int32_t)src2) s->dnpc=s->pc+imm);
  INSTPAT("??????? ????? ????? 010 ????? 01000 11", sw     , S, Mw(src1 + imm, 4, src2));


  INSTPAT("??????? ????? ????? ??? ????? 01101 11", lui    , U, R(rd) = Ext32(imm););
  INSTPAT("0000000 ????? ????? 101 ????? 00110 11", srliw  , I, R(rd)=(((src1)&0xffffffff)>>(imm)););
  INSTPAT("0000000 ????? ????? 100 ????? 01100 11", xor    , R, R(rd)=src1^src2);
  INSTPAT("??????? ????? ????? 111 ????? 11000 11", bgeu   , B, if((uint32_t)src1>=(uint32_t)src2) s->dnpc=s->pc+imm);

  INSTPAT("0000001 ????? ????? 000 ????? 01110 11", mulw   , R, R(rd)=Ext32(src1*src2););
  INSTPAT("0000001 ????? ????? 100 ????? 01110 11", divw   , R, R(rd)=Ext32(((long)src1)/((long)src2)););

  INSTPAT("0000001 ????? ????? 110 ????? 01110 11", remw   , R, R(rd)=(((long)src1)%((long)src2)));

  INSTPAT("??????? ????? ????? 100 ????? 11000 11", blt    , B, if((int32_t)src1<(int32_t)src2) s->dnpc=s->pc+imm);
  INSTPAT("0000000 ????? ????? 010 ????? 01100 11", slt    , R, R(rd)=(int32_t)src1<(int32_t)src2);
  INSTPAT("??????? ????? ????? 001 ????? 00000 11", lh     , I, R(rd)=Ext16(Mr(src1+imm,2)));
  INSTPAT("??????? ????? ????? 101 ????? 00000 11", lhu    , I, R(rd)=(Mr(src1+imm,2))&0xffff);

  INSTPAT("000000? ????? ????? 001 ????? 00110 11", slliw  , I, R(rd)=Ext32(src1<<(imm)););
  INSTPAT("0000001 ????? ????? 000 ????? 01100 11", mul    , R, R(rd)=src1*src2);
  INSTPAT("0000001 ????? ????? 110 ????? 01100 11", rem    , R, R(rd)=src1%src2);
  INSTPAT("0000001 ????? ????? 111 ????? 01100 11", remu   , R, R(rd)=src1%src2);//what-defferent?
  INSTPAT("0100000 ????? ????? 000 ????? 01110 11", subw   , R, R(rd)=Ext32(src1-src2););
  INSTPAT("0100000 ????? ????? 101 ????? 00110 11", sraiw  , I, R(rd)=Ext32(src1>>(imm&0x1f)););//??(&0xf?)

  INSTPAT("0100000 ????? ????? 101 ????? 01110 11", sraw  , R, R(rd)=Ext32((long long)src1>>(src2&0x1f)););//??(&0xf?)
  INSTPAT("0000000 ????? ????? 101 ????? 01110 11", srlw  , R, R(rd)=Ext32((src1&0xffffffff)>>(src2&0x1f)););//??(&0xf?)

  INSTPAT("??????? ????? ????? 110 ????? 11000 11", bltu    , B, if((uint32_t)src1<(uint32_t)src2) s->dnpc=s->pc+imm);


  INSTPAT("0000001 ????? ????? 001 ????? 01100 11", mulh    , R, R(rd)=mulh(src1, src2););//TODO:Why?printf("%x---%x\n",src1,src2);
  INSTPAT("0000001 ????? ????? 101 ????? 01100 11", divu   , R, R(rd)=Ext32((src1)/(src2)););//TODO:
  INSTPAT("0000000 ????? ????? 001 ????? 01100 11", sll   , R, R(rd)=src1<<src2);
  INSTPAT("0100000 ????? ????? 101 ????? 01100 11", sra   , R, MUXDEF(RV64,R(rd)=((int64_t)src1)>>(src2),R(rd)=((int32_t)src1)>>(src2)));//??(&0xf?)
  INSTPAT("0000000 ????? ????? 101 ????? 01100 11", srl   , R, R(rd)=(src1)>>(src2));
  INSTPAT("0000001 ????? ????? 100 ????? 01100 11", div   , R, printf("%x---%x\n",src1,src2);MUXDEF(RV64,R(rd)= ((int64_t)src1)/((int64_t)(src2)),R(rd)=  src2==0?0:src1==INT32_MIN&&src2==-1?0: ((int32_t)src1)/((int32_t)(src2))));

  INSTPAT("??????? ????? ????? 000 ????? 00000 11", lb  , I, R(rd)= Ext8(Mr(src1 + imm, 1)););
  INSTPAT("??????? ????? ????? 110 ????? 00100 11", ori   , I, R(rd)=src1|imm);
  INSTPAT("??????? ????? ????? 010 ????? 00100 11", sltiu  , I, MUXDEF(RV64,R(rd)=((int64_t)src1)<((int64_t)(imm)),R(rd)=((int32_t)src1)<((int32_t)(imm))));


  INSTPAT("0000000 00001 00000 000 00000 11100 11", ebreak , N, NEMUTRAP(s->pc, R(10))); // R(10) is $a0
  INSTPAT("??????? ????? ????? ??? ????? ????? ??", inv    , N, INV(s->pc));//Invalid--非法指令！！
  INSTPAT_END();

  R(0) = 0; // reset $zero to 0

  return 0;
}

int isa_exec_once(Decode *s) {
  //取指 物理机大端小端问题？
  //TODO:内存非对齐访问！
  s->isa.inst.val = inst_fetch(&s->snpc, 4);
  //使用指令环形缓冲区记录
  IFDEF(CONFIG_ITRACE, write_iringbuf(s->pc, s->isa.inst.val));
  return decode_exec(s);
}
