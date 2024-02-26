/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:37:09 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/26 11:31:42 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../main.h"

# define OPTION_FLAG 1
# define PATH_TYPE 2
# define NO_DOT_RELATIVE 4

# define FUNC_SUC	0
# define FUNC_FAIL	1

typedef struct s_minishell	t_minishell;
typedef struct s_ast_node	t_ast_node;
typedef struct s_cmd_node	t_cmd_node;
/* cd_flag : 0 is default L can be L or P */
typedef struct s_cd
{
	int			cd_flag;
	int			directory_index;
	char		execute_name;
	char		*home_dir;
	char		*cur_path;
	char		*directory;
	char		*cdpath;
	char		**path_arr;
	char		*check_str;
	struct stat	file_stat;
}	t_cd;

/* bulitin.c */
int		process_builtin(t_cmd_node *cmd_node, t_minishell *minishell);

/* ft_echo.c */
void	print_echo(char **str, int nflag);
int		ft_echo(t_cmd_node *cmd_node);
int		ft_isspace(int c);

/* ft_cd.c */
int		ft_cd(t_cmd_node *cmd_node, t_minishell *minishell);

/* ft_echo.c*/
int		ft_echo(t_cmd_node *cmd_node);

/* ft_env.c */
int		ft_env(t_minishell *minishell);

/* ft_export.c */
int		ft_export(t_cmd_node *cmd_node, t_minishell *minishell);

/* ft_pwd.c */
int		ft_pwd(t_cmd_node *node, t_minishell *minishell);

/* ft_unset.c */
int		ft_unset(t_cmd_node *cmd_node, t_minishell *minishell);

/* util.c */
int		err_no_quote(t_minishell *minishell, char *builtin,
			char *arg, char *msg);
int		err_quote(t_minishell *minishell, char *builtin, char *arg, char *msg);

#endif
