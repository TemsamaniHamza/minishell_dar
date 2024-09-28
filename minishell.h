#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef enum t_token
{
	PIPE,       // |
	HEREDOC,    // <<
	LPR,        // (
	RPR,        // )
	AND,        // &&    
	OR,         // ||
	APPEND,     // >>
	OUT,        // >
	IN,         // <
	STR,        // string
	END         // end dyal cmd
}   s_token;

typedef struct t_redir
{
	s_token			tok;
	char			*file;
	int			flg;
	int				fd;
	struct s_redir	*prev;
	struct s_redir	*next;
}s_redir;

typedef struct t_input
{
	char			*pre_cmd;
	char			**cmd;
	s_token			tok;
	int				precedence;
	s_redir			*redirections;
	int				fd[2];
	struct s_node	*prev;
	struct s_node	*next;
}   s_input;

// s_input collect_input(char *rl);
// s_input	*ft_lstnew_m(char *data);

#endif
