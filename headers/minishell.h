#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft_torename/libft.h"

typedef enum t_token
{
	IN,         // <		
	OUT,        // >		
	HEREDOC,    // <<		
	APPEND,     // >>		
	AND,        // &&		
	PIPE,       // |		
	OR,         // ||		
	LPR,        // (		
	RPR,        // )		
	STR,        // string	
	END         // end dyal cmd
}   s_token;

typedef struct t_redir
{
	s_token			tok;
	char			*file;
	int				flg;
	int				fd;
	struct t_redir	*left;
	struct t_redir	*right;
}s_redir;

typedef struct t_input
{
	s_token			tok;
	char			*command;
	char			**cmd;
	int				token_flag;
	struct t_input	*left;
	struct t_input	*right;
	s_redir			*redirections;
}   s_input;

typedef struct t_global
{
	char			**env;
	struct t_input	input;
}	s_global;

s_token 		check_token(char c1, char c2);
int 			check_beggining_of_str(char *str);
void 			shunting_yard(s_input **head, s_input **tok_stack, s_input **new_stack);
void 			push_2(s_input **top, s_input *to_add);
void 			push(s_input **a_head, s_input **b_head, int flg);
s_input 		*re_order_command(s_input **head);
s_input 		*list_to_tree(s_input *root);
s_input 		*parsing(char *rl);
int 			check_true(s_token tok);
s_input 		*my_Tokenizer(char *str);
int 			check_rpr(char *s, int i);
int 			check_token_syntax(char *s, int *i, int tok, int *par);
int 			check_syntax(s_token tok, char *s);
int 			check_spaces(char c);
int 			check_pre(s_token tok);
s_input 		*node_creation_cmd(char *s, s_redir *redir, s_token tok, int token_flag);
s_redir 		*node_creat_redir(char **s, s_token tok);
int 			build_redir_list(s_redir **head, s_redir *add);
void 			incre(char *s, int *i);
s_input 		*token_2(char *s, s_token tok, int *i);
int 			choose_str(char c, int flg);
int 			str_len(char *s, int i, int flg);
int 			check_next_quote(char *s, char c);
void 			check_flg(int flg, char *s, int *k);
char 			*cmd_help(char *s, int l, int *k, int flg);
char 			**fill_command(char *s, int l, int *k, int flg);
char 			**prep_cmd(char *s, int *i, s_token tok, int flg);
int 			token_1(s_input **head, char *s, int *i, int *par);
int 			check_left(s_input **head);
void			remove_top(s_input **tok_s);
int				build_command_list(s_input **head, s_input *add);
int				check_syntax_help(s_token tok, s_token next);
int 			ft_check_env(s_input *input, char **env);
void 			ft_expansion(s_input *input, s_global *global);
int 			ft_isspace(char c);
void 			expand_printf(char *output);



#endif
