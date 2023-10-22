#include "s21_cat.h"

int main(int n, char **option) {
  char *paths[n];
  Fl flags = {0};
  int sum_flags = 0;
  int sum_paths = parser(&flags, option, paths, n, &sum_flags);
  if (sum_paths > 0) {
    file_w(paths, sum_paths, sum_flags, &flags);
  } else {
    fprintf(stderr, "ERROR! INCORRECT PATH");
  }
  return 0;
}

void file_w(char **paths, int sum_paths, int sum_flags, Fl *flag) {
  for (int i = 0; i < sum_paths; i++) {
    if (sum_flags > 0) {
      flags_menu(paths[i], flag);
    } else {
      cat_print(paths[i]);
    }
  }
}

void flags_menu(char *path, Fl *flag) {
  FILE *text;
  int count = 1, count_all = 1;
  int count_numb_enter = 0;
  if ((text = fopen(path, "r")) != NULL) {
    char c;
    int count_enter = 1;
    while ((c = (char)fgetc(text)) != EOF) {
      if (flag->def != 0) {
        fprintf(stderr, "cat: illegal option -- %c", flag->def);
      } else {
        int status = enter_flags(c, &count, &count_numb_enter, &count_all,
                                 count_enter, flag);
        if (status == -1) {
          continue;
        }
        status = tabs_flags(c, flag);
        if (c != '\n') {
          count_enter = 0;
        } else {
          count_enter = 1;  // enter now
        }
        if (status == -1) {
          continue;
        }
        c_print(c, flag);
      }
    }
    fclose(text);
  } else {
    fprintf(stderr, "cat: %s: No such file or directory", path);
  }
}

void c_print(char c, Fl *flag) {
  if (flag->t + flag->e + flag->v > 0) {
    if (c < 32 && c != '\n' && c != '\t') {
      printf("^%c", c + 64);
    } else if (c == '\t' && flag->t == 1) {
      printf("^%c", c + 64);
    } else if (c > 126) {
      printf("^%c", c - 64);
    } else {
      printf("%c", c);
    }
  } else {
    printf("%c", c);
  }
}

int tabs_flags(char c, Fl *flag) {
  int status = 0;
  if (flag->t == 1 || flag->T == 1) {
    if (c == '\t') {
      printf("^I");
      status = -1;
    }
  }
  if (flag->e == 1 || flag->E == 1) {
    if (c == '\n') {
      printf("$");
    }
  }
  return status;
}

int enter_flags(char c, int *count, int *count_numb_enter, int *count_all,
                int count_enter, Fl *flag) {
  int status = 0;
  if (flag->s == 1) {  // delete enters
    if (c == '\n') {
      if (*count_numb_enter < 2) {
        *count_numb_enter = *count_numb_enter + 1;
      } else {
        status = -1;
      }
    } else {
      *count_numb_enter = 0;
    }
  }

  if (flag->b == 1) {  // numbering nonvoid
    if (c != '\n' && count_enter == 1) {
      printf("%6.d\t", *count);
      *count = *count + 1;
    }
    flag->n = 0;
  }

  if (flag->n == 1) {  // numbering all
    if (count_enter == 1 && status != -1) {
      printf("%6.d\t", *count_all);
      *count_all = *count_all + 1;
    }
  }
  return status;
}

void long_flags(Fl *flags, char *term_str, int *sum_flags) {
  int status = 0;
  int res = strcmp(term_str, "--number-nonblank");
  if (res == 0) {
    flags->b = 1;
    *sum_flags += 1;
    status++;
  }
  res = strcmp(term_str, "--number");
  if (res == 0) {
    flags->n = 1;
    *sum_flags += 1;
    status++;
  }
  res = strcmp(term_str, "--squeeze-blank");
  if (res == 0) {
    flags->s = 1;
    *sum_flags += 1;
    status++;
  }
  if (status == 0) {
    flags->def = ' ';
  }
}

int parser(Fl *flags, char **term_str, char **paths, int term_str_len,
           int *sum_flags) {
  int paths_count = 0;
  if (term_str_len > 1) {
    for (int j = 1; j < term_str_len; j++) {
      size_t str_len_term = strlen(term_str[j]);
      if (term_str[j][0] == '-' && paths_count == 0) {  // check on flags
        for (size_t i = 1; i < str_len_term; i++) {
          if (term_str[j][i] == '-') {
            long_flags(flags, term_str[j], sum_flags);
          } else {
            switch_flags(flags, term_str[j][i], sum_flags);
          }
        }
      } else {
        paths[paths_count] = term_str[j];
        paths_count++;
      }
    }
  }
  return paths_count;
}
void switch_flags(Fl *flags, char c, int *sum_flags) {
  switch (c) {
    case 'b':
      flags->b = 1;
      *sum_flags += 1;
      break;
    case 'E':
      flags->E = 1;
      *sum_flags += 1;
      break;
    case 'T':
      flags->T = 1;
      *sum_flags += 1;
      break;
    case 'e':
      flags->e = 1;
      *sum_flags += 1;
      break;
    case 'v':
      flags->v = 1;
      *sum_flags += 1;
      break;
    case 'n':
      flags->n = 1;
      *sum_flags += 1;
      break;
    case 's':
      flags->s = 1;
      *sum_flags += 1;
      break;
    case 't':
      flags->t = 1;
      *sum_flags += 1;
      break;
    default:
      flags->def = c;
      break;
  }
}

void cat_print(char *path) {
  char c;
  FILE *text;
  if ((text = fopen(path, "r")) != NULL) {
    while (fscanf(text, "%c", &c) != EOF) {
      printf("%c", c);
    }
    fclose(text);
  } else {
    fprintf(stderr, "cat: %s: No such file or directory", path);
  }
}
