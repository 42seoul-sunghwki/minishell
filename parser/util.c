/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:33:29 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/27 21:41:03 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*init_ast_node(int child_node)
{
	t_ast_node	*ret;
	t_cmd_node	*node;

	ret = (t_ast_node *)malloc(sizeof(t_ast_node));
	ft_memset((void *)ret, 0, sizeof(t_ast_node));
	if (CMDNODE & child_node)
	{
		node = (t_cmd_node *)malloc(sizeof(t_cmd_node));
		ft_memset((void *)node, 0, sizeof(t_cmd_node));
		ret->cmd_node = node;
	}
	if (LEFTNODE & child_node)
		ret->left_node = init_ast_node(CMDNODE);
	if (RIGHTNODE & child_node)
		ret->right_node = init_ast_node(CMDNODE);
	return (ret);
}

int	syntax_err_message(char *msg, int end, int ret, t_minishell *minishell)
{
	if (end != NOTDEFINED)
		msg[end] = '\0';
	ft_putstr_fd(minishell->execute_name, STDERR_FILENO);
	ft_putstr_fd(": syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (ret);
}

void	redirect_node_push(t_ast_node *node, t_redirection *red)
{
	t_redirection	*tmp;

	if (node->red == NULL)
		node->red = red;
	else
	{
		tmp = node->red;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = red;
	}
}

void	tmp_file_list_push(t_tmp_file *list, t_minishell *minishell)
{
	t_tmp_file	*next;

	if (minishell->tmp_list == NULL)
		minishell->tmp_list = list;
	else
	{
		next = minishell->tmp_list;
		while (next->next)
			next = next->next;
		next->next = list;
	}
	minishell->tmp_file_counter++;
}

int	finder(char *str, char checker)
{
	int	index;

	index = -1;
	while (str[++index])
	{
		if (str[index] == checker)
			return (index);
	}
	return (NOTDEFINED);
}

int	bracket_finder(char *str)
{
	int	count;
	int	index;

	index = -1;
	if (*str == '(')
	{
		count = 1;
		while (str[++index])
		{
			if (str[index] == '(')
				count++;
			if (str[index] == ')')
				count--;
			if (count == 0)
				return (index);
		}
	}
	return (NOTDEFINED);
}

int			skip_space(char *str)
{
	int	index;

	index = 0;
	while (str[index] == ' ' || (str[index] >= 9 && str[index] <= 13))
		index++;
	return (index);
}
