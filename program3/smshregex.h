#ifndef SMSHREGEX_H
#define SMSHREGEX_H
#include "cmdstruct.h"

#define CASE_EXIT         1
#define CASE_CD           2
#define CASE_STATUS       3

void check_pid(Cmd *cs, int argidx);
void check_builtin(struct cmd *cs);
void check_comment(struct cmd *cs, char *token, int len);
void check_bg(struct cmd *cs, char *cmdline);

#endif 
