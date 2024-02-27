/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:38:39 by minsepar          #+#    #+#             */
/*   Updated: 2024/02/27 21:02:52 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INNER_PARSER_H
# define INNER_PARSER_H

# include "../main.h"

typedef struct s_minishell	t_minishell;

typedef struct s_parse_str
{
	char	*str;
	size_t	malloc_size;
	size_t	cursor;
	int		asterisk_flag;
}	t_parse_str;

typedef struct s_str_node
{
	char				*str;
	struct s_str_node	*next;
	struct s_str_node	*prev;
}	t_str_node;

typedef struct s_str_list
{
	int			size;
	t_str_node	*head;
	t_str_node	*tail;
}	t_str_list;

typedef struct s_inner_parser
{
	int	i;
	int	j;
	int	start_index;
	int	match;
}	t_inner_parser;

/* argument_parser.c */
void	parse_single_char(t_parse_str *parse_str, char **str,
		int in_quote, t_minishell *minishell);
void	parse_double_quote(t_parse_str *parse_str, char **str, t_minishell *minishell);
void	parse_single_quote(t_parse_str *parse_str, char **str);
void	parse_single_word(char **str, t_str_list *str_list,
		t_minishell *minishell);

/* argument_parser_str_list.c */
void	enqueue(t_str_list *str_list, t_str_node *str_node);
t_str_node	*dequeue(t_str_list *str_list);
void	add_string_node(t_str_list *str_list, t_parse_str *parse_str);
char	**list_to_char_arr(t_str_list *str_list);
t_str_node	*create_node(char *str);
t_str_node	*pop(t_str_list *list);

/* argument_parser_utils.c */
void	free_parse_str(t_parse_str *parse_str);
void	init_parse_str(t_parse_str *parse_str);
void	init_str_node(t_str_node *str_node);
void	init_str_list(t_str_list *str_list);
void	append_char(t_parse_str *parse_str, char c);
void	parse_dollar_sign(t_parse_str *parse_str, char **str,
		int in_quote, t_minishell *minishell);
char	**string_parser(char *str, t_minishell *minishell);
void	parse_env_var(t_parse_str *parse_str, char **str, int in_quote,
	t_minishell *minishell);
char	*easy_cat(char *s1, char *s2);

#endif
