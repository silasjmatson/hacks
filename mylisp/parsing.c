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

long eval_op(long x, char* op, long y) {
  if (strcmp(op, "+") == 0) { return x + y; }
  if (strcmp(op, "-") == 0) { return x - y; }
  if (strcmp(op, "*") == 0) { return x * y; }
  if (strcmp(op, "/") == 0) { return x / y; }

  return 0;
}

// Evaluation
long eval(mpc_ast_t* tree) {
  // If tag is a number, just convert to C type and return
  if (strstr(tree->tag, "number")) {
    return atoi(tree->contents);
  }

  // The first child is '(', so second is the operator
  char* op = tree->children[1]->contents;

  long x = eval(tree->children[2]);

  // Recursively eval the rest;
  int i = 3;
  while (strstr(tree->children[i]->tag, "expr")) {
    x = eval_op(x, op, eval(tree->children[i]));
    i++;
  }

  return x;
}


int main(int argc, char** argv) {
  mpc_parser_t* Number    = mpc_new("number");
  mpc_parser_t* Operator  = mpc_new("operator");
  mpc_parser_t* Expr      = mpc_new("expr");
  mpc_parser_t* Lispy     = mpc_new("lispy");

  mpca_lang(MPC_LANG_DEFAULT,
    "                                                                     \
      number    : /-?[0-9]+([.][0-9]*)?/ ;                                \
      operator  : '+' | '-' | '*' | '/' | '%' ;                           \
      expr      : <number> | '(' <operator> <expr>+ ')' ;                 \
      lispy     : /^/ <operator> <expr>+ /$/ ;                            \
    ",
    Number, Operator, Expr, Lispy
  );


  puts("Lispy Version 0.0.0.0.1");
  puts("This is my lisp!");
  puts("Press Ctrl-C to Exit\n");

  while (1) {
    char* input = readline("lispy> ");

    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      /* Successfully parsed the input as 'Lispy' */
      long result = eval(r.output);
      printf("%li\n", result);
      mpc_ast_delete(r.output);
    } else {
      /* Errored */
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }
  }

  mpc_cleanup(4, Number, Operator, Expr, Lispy);
  return 0;
}
