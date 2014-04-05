#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32

static char buffer[2048];

char *readline(char* prompt) {
  fputs("lispy> ", stdout);
  fgets(buffer, 2048, stdin);

  char* cpy = malloc(strlen(buffer) + 1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy) - 1] = '\0';
  return cpy;
}

void add_history(char* unused) {}

#else

#include <readline/readline.h>
#include <readline/history.h>

#endif

// Lexer Defining & Parsing
#include "mpc.h"


int main(int argc, char** argv) {
  mpc_parser_t* Number    = mpc_new("number");
  mpc_parser_t* Decimal   = mpc_new("decimal");
  mpc_parser_t* Operator  = mpc_new("operator");
  mpc_parser_t* Expr      = mpc_new("expr");
  mpc_parser_t* Lispy     = mpc_new("lispy");

  mpca_lang(MPC_LANG_DEFAULT,
    "                                                                     \
      number    : /-?[0-9]+/ ;                                            \
      decimal   : // <number>+ /[.]+[0-9]+/ ;                             \
      operator  : '+' | '-' | '*' | '/' | '%' ;                           \
      expr      : <number> | <decimal> | '(' <operator> <expr>+ ')' ;     \
      lispy     : /^/ <operator> <expr>+ /$/ ;                            \
    ",
    Number, Decimal, Operator, Expr, Lispy
  );


  puts("Lispy Version 0.0.0.0.1");
  puts("This is my lisp!");
  puts("Press Ctrl-C to Exit\n");

  while (1) {
    char* input = readline("lispy> ");

    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      /* Successfully parsed the input as 'Lispy' */
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      /* Errored */
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }
  }

  mpc_cleanup(5, Number, Decimal, Operator, Expr, Lispy);
  return 0;
}
