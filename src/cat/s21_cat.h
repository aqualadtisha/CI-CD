//
// Created by Aqualad Tisha on 10/27/22.
//

#ifndef C3_SIMPLEBASHUTILS_0_S21_CAT_H
#define C3_SIMPLEBASHUTILS_0_S21_CAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct fl {
  int b;
  int n;
  int s;
  int t;
  int e;
  int v;
  char def;
  int E;
  int T;
} Fl;

void cat_print(char *path);
void c_print(char c, Fl *flag);
int enter_flags(char c, int *count, int *count_numb_enter, int *count_all,
                int count_enter, Fl *flag);
int tabs_flags(char c, Fl *flag);
int parser(Fl *flags, char **term_str, char **paths, int term_str_len,
           int *sum_flags);
void flags_menu(char *path, Fl *flag);
void file_w(char **paths, int sum_paths, int sum_flags, Fl *flag);
void long_flags(Fl *flags, char *term_str, int *sum_flags);
void switch_flags(Fl *flags, char c, int *sum_flags);

#endif  // C3_SIMPLEBASHUTILS_0_S21_CAT_H
