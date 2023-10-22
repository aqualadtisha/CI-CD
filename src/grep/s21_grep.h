
#ifndef C3_SIMPLEBASHUTILS_0_SRC_GREP_S21_GREP_H_
#define C3_SIMPLEBASHUTILS_0_SRC_GREP_S21_GREP_H_

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct fl {
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int o;
  char def;
  int err;
  char str_o[1024];
  int eeee;
} Fl;

typedef struct counts {
  int end;
  int temps;
  int paths;
  int success;
  int ef;
  int no_str;
  int no_path;
  int no_num_str;
} Count;

void parser(Fl *flags, Count *num, char **term_str, char **paths,
            regex_t **templates, int term_arr_len);
void open_file(Fl *flag, Count *num, char *path, regex_t **templates);
void regex_comp(Fl *flags, Count *num, regex_t **templates, char *pattern);
void file_parser(Fl *flags, Count *num, char *pattern, regex_t **template);
int regex_ec(Fl *flag, Count *num, char *str, regex_t **templates);
void flags_print(Fl *flag, Count *num, int count_str_num, char *str,
                 int reg_res, char *path);
void e_f_search(Fl *flags, Count *num, char **term_str, int term_arr_len,
                regex_t **templates, char **path);
void switch_flag(Fl *flags, Count *num, char **term_str, int j);

#endif  // C3_SIMPLEBASHUTILS_0_SRC_GREP_S21_GREP_H_
