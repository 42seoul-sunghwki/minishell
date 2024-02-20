/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:45:18 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/20 19:25:07 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEW_PARSER_H
# define NEW_PARSER_H

# define NOTDEFINED		-1

# define OR				"||"
# define AND			"&&"
# define BRACKET		"()"
# define DOUBLEQUOT		"\""
# define SINGLEQUOT		"\'"
# define PIPE			"|"
# define REDIRINPUT		">"
# define REDIROUTPUT	"<"
//# define SPACE			" "

# define BRACKET_FLAG 1
# define LT_SIGN 0
# define DB_LT_SIGN 1
# define GT_SIGN 2
# define DB_GT_SIGN 4

# define NONODE			0
# define LEFTNODE		1
# define RIGHTNODE		2
# define CMDNODE		4

# include "../main.h"

# define BRACKET_FLAG 1

typedef struct s_cmd_node		t_cmd_node;
typedef struct s_ast_node		t_ast_node;
typedef struct s_minishell		t_minishell;
typedef struct s_redirection	t_redirection;

typedef struct s_redirection {
	int							flag;	// 0: <, 1: <<, 2: >, 4: >>
	char						*str;	// file name or here doc delim
	t_redirection				*next;
}	t_redirection;

typedef struct s_redirection {
	int		flag;	// 0: <, 1: <<, 2: >, 4: >>
	char	*str;	// file name or here doc delim
}	t_redirection;

typedef struct s_cmd_node
{
	char			*cmd_name;	//command name
	char			**str;		//command arguments
}	t_cmd_node;

typedef struct s_ast_node
{
	t_ast_node			*left_node;
	t_ast_node			*right_node;
	t_ast_node			*next_ast_node;	//for pipe
	t_cmd_node			*cmd_node;		
	t_redirection		*red;
	int					flag; 	//lexar flag
	int					index;  //redirection index in t_minishell
	char				*str;	//||, &&
}	t_ast_node;

#endif
