#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define numbers_of_files 2049

typedef struct flag {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} s21_flags_t;

int read_file(char **argv, s21_flags_t *flag);
int parsing_stdin(int argc, char **argv, s21_flags_t *flag);

int main(int argc, char **argv) {
  int error;

  s21_flags_t flag = {
      .b = 0,
      .e = 0,
      .n = 0,
      .s = 0,
      .t = 0,
      .v = 0,
  };

  error = parsing_stdin(argc, argv, &flag);

  if (error != 1) {
    if (flag.b) flag.n = 0;

    while (optind < argc) {
      if ((error = read_file(argv, &flag)) == 2)
        fprintf(stderr, "%s: %s: %s\n", argv[0], argv[optind], strerror(error));
      optind++;
    }
  }
  return error;
}

свсвюю

int parsing_stdin(int argc, char **argv, s21_flags_t *flag) {
  const char *short_options = "bvEnsTet";
  int opt;
  int error = 0;
  int option_index = 0;

  const struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};

  while ((opt = getopt_long(argc, argv, short_options, long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'E':
        flag->e = 1;
        break;
      case 'T':
        flag->t = 1;
        break;
      case 'b':
        flag->b = 1;
        break;
      case 'e':
        flag->e = 1;
        flag->v = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 't':
        flag->v = 1;
        flag->t = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      default: /* '?' */
        error = 1;
        break;
    }
  }
  return error;
}