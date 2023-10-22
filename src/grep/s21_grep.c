#include "s21_grep.h"

int main(int n, char **options) {
  char *paths[n];
  regex_t *templates[100] = {0};
  Fl flags = {0};
  Count num = {0};
  parser(&flags, &num, options, paths, templates, n);
  if (flags.def != 0) {
    fprintf(stderr, "s21_grep: Invalid argument");
  } else {
    if (num.paths > 0) {
      for (int i = 0; i < num.paths && flags.err == 0; i++) {
        open_file(&flags, &num, paths[i], templates);
      }
    } else {
      if (flags.s != 1) {
        fprintf(stderr, "s21_grep: No such file or directory");
      }
    }
  }
  for (int i = 0; i < 100; i++) {
    if (templates[i] != NULL) {
      regfree(templates[i]);
      free(templates[i]);
    }
  }
  return 0;
}

void regex_comp(Fl *flags, Count *num, regex_t **templates, char *pattern) {
  regex_t *regex = NULL;
  if (num->temps > 99) {
    fprintf(stderr, "Pattern buffer is over!\n");
    flags->err = 1;
  } else {
    if (pattern != NULL && (int)strlen(pattern) > 0) {
      regex = malloc(sizeof(regex_t));
      if (regex != NULL) {
        int reg_res;
        if (flags->i == 1) {
          int cflags = REG_NEWLINE | REG_ICASE;
          reg_res = regcomp(regex, pattern, cflags);
        } else {
          reg_res = regcomp(regex, pattern, REG_NEWLINE);
        }
        if (reg_res == 0) {
          templates[num->temps] = regex;
          num->temps++;
        } else {
          free(regex);
          fprintf(stderr, "Couldn't compile regex\n");
        }
      } else {
        fprintf(stderr, "No allowed memory\n");
      }
    }
  }
}

int regex_ec(Fl *flag, Count *num, char *str, regex_t **templates) {
  regmatch_t pos = {0};
  int start_point = 0, matches = 0, status = 0;
  int len_str = (int)strlen(str);
  char str_o[1024] = "";
  memset(flag->str_o, 0, 1024);
  for (int i = 0; i < num->temps; i++) {
    int reg_res = 0;
    while (reg_res == 0) {
      reg_res = regexec(templates[i], str + start_point, 1, &pos, REG_NEWLINE);
      if (reg_res == 0) {
        int len = (int)(pos.rm_eo - pos.rm_so);
        if (flag->o == 1 && flag->l + flag->c == 0) {
          sprintf(str_o, "%.*s\n", len, (str + start_point + pos.rm_so));
          strcat(flag->str_o, str_o);
        }
        start_point += (int)pos.rm_eo;
        matches++;
        if (start_point > len_str) {
          reg_res = -1;
        }
      }
    }
  }
  if (matches == 0 && flag->v != 1) {
    status = -1;
  }
  if (matches != 0 && flag->v == 1) {
    status = -1;
  }
  return status;
}

void flags_print(Fl *flag, Count *num, int count_str_num, char *str,
                 int reg_res, char *path) {
  if (reg_res == 0 || num->end == 1) {
    if (flag->l == 1 && num->success > 0) {
      num->end = 1;
    }
    if (num->end == 1 && reg_res != 0) {
      if (flag->c == 1) {
        if (flag->h == 0 && num->paths > 1) {
          printf("%s:", path);
        }
        printf("%d\n", num->success);
      }
    } else {  // res = 0
      if (str[0] != '\0') {
        if (num->no_path == 0) {
          printf("%s:", path);
        }
        if (num->no_num_str == 0 && flag->n == 1) {
          printf("%d:", count_str_num);
        }
        if (num->no_str == 0) {
          printf("%s", str);
        }
      }
      if (flag->c == 1 && num->end == 1) {
        if (flag->h == 0 && num->paths > 1) {
          printf("%s:", path);
        }
        printf("%d\n", num->success);
      }
      if (flag->o == 1 && flag->v != 1) {
        printf("%s", flag->str_o);
      }
      if (flag->l == 1 && num->success > 0) {
        printf("%s\n", path);
      }
    }
  }
  memset(str, 0, 1024);
}

void open_file(Fl *flag, Count *num, char *path, regex_t **templates) {
  FILE *text;
  if ((text = fopen(path, "r")) != NULL) {
    char c = ' ';
    char str[1024] = "";
    int numb = 0, count_str_num = 0;
    while (c != EOF && num->end != 1) {
      c = (char)fgetc(text);
      if (c == EOF) {
        num->end = 1;
        if (numb > 0 && str[numb - 1] != '\n') {
          str[numb] = '\n';
          numb++;
        }
      } else {
        str[numb] = c;
      }
      if (c == '\n' || num->end == 1) {
        count_str_num++;
        int reg_res = regex_ec(flag, num, str, templates);
        if (reg_res == 0 && str[0] != '\0') {
          num->success++;
        }
        flags_print(flag, num, count_str_num, str, reg_res, path);
        numb = 0;
        str[0] = '\0';
      } else {
        numb++;
        continue;
      }
    }
    num->success = 0;
    num->end = 0;
    fclose(text);
  } else {
    if (flag->s != 1) {
      fprintf(stderr, "s21_grep: %s: No such file or directory", path);
    }
  }
}

void file_parser(Fl *flags, Count *num, char *pattern,
                 regex_t **template) {  // temp_count
  FILE *pattern_f;
  if ((pattern_f = fopen(pattern, "r")) != NULL) {
    int i = 0;
    char str[1024] = {0};
    char c = ' ';
    while (c != EOF) {
      c = (char)getc(pattern_f);
      if (c == '\n' || c == EOF) {
        if (c == '\n' && i == 0) {
          str[i] = '\n';
        }
        if (flags->err == 0) {
          regex_comp(flags, num, template, str);
          memset(str, 0, 1024);
          i = 0;
        }
      } else {
        str[i] = c;
        i++;
      }
    }
    fclose(pattern_f);
  } else {
    fprintf(stderr, "s21_grep: %s: No such file or directory", pattern);
  }
}

void switch_flag(Fl *flags, Count *num, char **term_str, int j) {
  int len = (int)strlen(term_str[j]);
  for (int i = 1; i < len; i++) {
    switch (term_str[j][i]) {
      case 'e':
        num->ef++;
        break;  // template
      case 'i':
        flags->i = 1;
        break;  // ignoring register
      case 'v':
        flags->v = 1;
        break;  // invert meaning of search
      case 'c':
        flags->c = 1;
        num->no_str++;
        num->no_num_str++;
        num->no_path++;
        break;  // enter the number of the same str
      case 'l':
        flags->l = 1;
        num->no_str++;
        num->no_num_str++;
        num->no_path++;
        break;  // enter the number of the same files
      case 'n':
        flags->n = 1;
        break;  // enter str with number of this str in file
      case 'h':
        flags->h = 1;
        break;  // enter same str without filenames
      case 's':
        flags->s = 1;
        break;  // del errors messages about non-existent file
      case 'f':
        num->ef++;
        break;  // get regular messages from file
      case 'o':
        flags->o = 1;
        break;  // enter only the same parts of str
      default:
        flags->def = term_str[j][i];
        break;
    }
  }
}

void e_f_search(Fl *flags, Count *num, char **term_str, int term_arr_len,
                regex_t **templates, char **path) {
  for (int j = 1; j < term_arr_len; j++) {
    if (term_str[j][0] == '-') {
      switch_flag(flags, num, term_str, j);
    }
  }
  if (num->ef > 0) {
    for (int j = 1; j < term_arr_len; j++) {
      int flag = 0;
      int len = (int)strlen(term_str[j]);
      if (term_str[j][0] == '-' &&
          (term_str[j][len - 1] == 'e' || term_str[j][len - 1] == 'f')) {
        if (term_str[j][len - 1] == 'e') {
          regex_comp(flags, num, templates, term_str[j + 1]);
          j += 2;
          flag = 1;
        } else if (term_str[j][len - 1] == 'f') {
          file_parser(flags, num, term_str[j + 1], templates);
          j += 2;
          flag = 1;
        }
      }
      while (j < term_arr_len && term_str[j][0] != '-') {
        path[num->paths] = term_str[j];
        num->paths++;
        flag = 1;
        j++;
      }
      if (flag == 1) {
        j--;
      }
    }
  }
}

void parser(Fl *flags, Count *num, char **term_str, char **paths,
            regex_t **templates, int term_arr_len) {
  if (term_arr_len > 1) {
    e_f_search(flags, num, term_str, term_arr_len, templates, paths);
    if (num->ef == 0) {
      int flag = 0;
      for (int i = 1; i < term_arr_len; i++) {
        if (term_str[i][0] != '-') {
          if (flag == 0) {
            flag = 1;
            regex_comp(flags, num, templates, term_str[i]);
          } else {
            paths[num->paths] = term_str[i];
            num->paths++;
          }
        }
      }
    }
  } else {
    flags->def = -1;
  }
  if ((flags->h == 1 && num->paths > 1) || num->paths < 2) {
    num->no_path++;
  }
  if (flags->v == 0 && flags->o == 1) {
    num->no_str++;
  }
}
