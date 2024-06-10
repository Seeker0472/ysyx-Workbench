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

#include "sdb.h"

#define NR_WP 32





static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;
//head用于组织使用中的监视点结构, free_用于组织空闲的监视点结构

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

WP* new_wp(){
  if(free_==NULL)
    assert(0);//没有空闲了
  WP* op=free_;
  free_=(*free_).next;
  op->next=NULL;
  //放进队列
  op->next=head;
  head=op;
  return op;
}
void free_wp(WP *wp){
  for(WP *cur=head;cur!=NULL;cur=cur->next){
    if(cur->next==wp){
      cur->next=wp->next;
      wp->next=free_;
      free_=wp;
      return;
    }
  }
  assert(0);//没找到
}

void print_watch_points(){
  printf("No\tLast_val\tExpression\n");
  for(WP* cur=head;cur!=NULL;cur=cur->next){
    printf("%d\t%lu\t%s",cur->NO,cur->last_result,cur->expr);
  }
}