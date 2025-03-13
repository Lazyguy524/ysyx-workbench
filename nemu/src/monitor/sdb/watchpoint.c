/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
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

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */
  char expr[256];        // 存储监视的表达式
  word_t old_val;        // 存储表达式上次求值的结果
} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
    // 初始化新增成员
    wp_pool[i].expr[0] = '\0';
    wp_pool[i].old_val = 0;
  }
  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

// 从空闲链表中获取一个监视点
WP* new_wp() {
  if (free_ == NULL) {
    printf("错误：没有可用的空闲监视点！\n");
    assert(0);  // 没有空闲监视点时终止程序
  }
  
  // 从空闲链表取出第一个节点
  WP *wp = free_;
  free_ = free_->next;
  
  // 清空监视点内容
  wp->expr[0] = '\0';
  wp->old_val = 0;
  wp->next = NULL;
  
  // 将新节点添加到使用中链表的头部
  if (head == NULL) {
    head = wp;
  } else {
    wp->next = head;
    head = wp;
  }
  
  return wp;
}

// 将监视点归还到空闲链表
void free_wp(WP *wp) {
  if (wp == NULL) return;
  
  // 从使用链表中删除
  if (wp == head) {
    head = head->next;
  } else {
    WP *prev = head;
    while (prev != NULL && prev->next != wp) {
      prev = prev->next;
    }
    
    if (prev == NULL) {
      printf("错误：在使用中的监视点列表中未找到该监视点！\n");
      return;
    }
    
    prev->next = wp->next;
  }
  
  // 清空监视点信息
  wp->expr[0] = '\0';
  wp->old_val = 0;
  
  // 添加到空闲链表的头部
  wp->next = free_;
  free_ = wp;
}

// 查找指定编号的监视点
WP* find_wp(int NO) {
  WP *p = head;
  while (p != NULL) {
    if (p->NO == NO) {
      return p;
    }
    p = p->next;
  }
  return NULL;
}

// 创建一个新的监视点
WP* set_watchpoint(char *expr_str) {
  if (expr_str == NULL || expr_str[0] == '\0') {
    printf("错误：表达式不能为空\n");
    return NULL;
  }
  
  bool success = true;
  
  // 计算表达式的初始值
  word_t val = expr(expr_str, &success);
  if (!success) {
    printf("错误：无效的表达式\n");
    return NULL;
  }
  
  // 分配一个新的监视点
  WP *wp = new_wp();
  
  // 设置监视点信息
  strncpy(wp->expr, expr_str, sizeof(wp->expr) - 1);
  wp->expr[sizeof(wp->expr) - 1] = '\0';  // 确保字符串以 null 结尾
  wp->old_val = val;
  
  printf("监视点 %d: %s = %u (0x%x)\n", wp->NO, wp->expr, val, val);
  return wp;
}

// 删除指定编号的监视点
bool delete_watchpoint(int NO) {
  WP *wp = find_wp(NO);
  if (wp == NULL) {
    return false;
  }
  
  free_wp(wp);
  return true;
}

// 打印所有使用中的监视点
void list_watchpoints() {
  if (head == NULL) {
    printf("没有监视点\n");
    return;
  }
  
  printf("编号\t表达式\t\t值\n");
  printf("----\t--------------\t--------------\n");
  
  WP *p = head;
  while (p != NULL) {
    printf("%d\t%-14s\t%u (0x%x)\n", p->NO, p->expr, p->old_val, p->old_val);
    p = p->next;
  }
}

// 检查监视点值是否发生变化
bool check_watchpoints() {
  if (head == NULL) {
    return false;  // 没有监视点
  }
  
  bool triggered = false;
  WP *p = head;
  
  while (p != NULL) {
    bool success = true;
    word_t new_val = expr(p->expr, &success);
    
    if (success && new_val != p->old_val) {
      // 监视点触发
      printf("\n监视点 %d: %s\n", p->NO, p->expr);
      printf("旧值 = %u (0x%x)\n", p->old_val, p->old_val);
      printf("新值 = %u (0x%x)\n", new_val, new_val);
      
      p->old_val = new_val;  // 更新值
      triggered = true;
    }
    
    p = p->next;
  }
  
  return triggered;
}

int set_watchpoint_cmd(char *expr_str, bool *success) {
  if (expr_str == NULL || expr_str[0] == '\0') {
    printf("错误：表达式不能为空\n");
    *success = false;
    return -1;
  }
  
  bool eval_success = true;
  
  // 计算表达式的初始值
  word_t val = expr(expr_str, &eval_success);
  if (!eval_success) {
    printf("错误：无效的表达式\n");
    *success = false;
    return -1;
  }
  
  // 分配一个新的监视点
  WP *wp = new_wp();
  
  // 设置监视点信息
  strncpy(wp->expr, expr_str, sizeof(wp->expr) - 1);
  wp->expr[sizeof(wp->expr) - 1] = '\0';  // 确保字符串以 null 结尾
  wp->old_val = val;
  
  printf("设置监视点: %s = %u (0x%x)\n", wp->expr, val, val);
  
  *success = true;
  return wp->NO;  // 返回监视点编号而不是指针
}