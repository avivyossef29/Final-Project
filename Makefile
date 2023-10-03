symnmf: h_optimize.c symnmf.c matric_op.c
	gcc  -ansi -Wall -Wextra -Werror -pedantic-errors h_optimize.c symnmf.c matric_op.c -o symnmf -lm 
