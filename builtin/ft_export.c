/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:23:12 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/09 12:18:25 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static	int	print_export(t_minishell *minishell)
{
	char	**env;
	int		index;

	index = 0;
	env = ft_charenv(minishell->export, TRUE);
	while (env[index])
	{
		ft_printf("declare -x %s\n", env[index]);
		free(env[index]);
		index++;
	}
	free(env);
	env = NULL;
	return (FUNC_SUC);
}

static	int	free_key_value_msg(t_minishell *minishell,
		char *key, char *value, int print_flag)
{
	if (key)
		free(key);
	if (value)
		free(value);
	if (print_flag == TRUE)
	{
		print_error_msg(minishell->error, 1, TRUE);
		minishell->error = NULL;
		return (FUNC_FAIL);
	}
	else
	{
		free_error(minishell->error);
		minishell->error = NULL;
		return (FUNC_FAIL);
	}
}

static	int	put_env(t_cmd_node *cmd_node, t_minishell *minishell, int index)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	minishell->error = set_error_msg(minishell->execute_name,
			cmd_node->str[0], cmd_node->str[index], "not a valid identifier");
	if (parse_env(cmd_node->str[index], &key, &value, minishell) == FUNC_FAIL)
		return (free_key_value_msg(minishell, key, value, TRUE));
	index = 0;
	if (!(key[index] == '_' || ft_isalpha(key[index])))
		return (free_key_value_msg(minishell, key, value, TRUE));
	while (key[++index])
	{
		if (!(key[index] == '_' || ft_isalpha(key[index])
				|| ft_isdigit(key[index])))
			return (free_key_value_msg(minishell, key, value, TRUE));
	}
	if (ft_setenv(minishell->export, key, value) == FUNC_FAIL)
		return (free_key_value_msg(minishell, key, value, FALSE));
	if (value)
		ft_setenv(minishell->env, key, value);
	free_key_value_msg(minishell, key, value, FALSE);
	return (FUNC_SUC);
}

int	ft_export(t_cmd_node *cmd_node, t_minishell *minishell)
{
	int		index;
	int		tmp;

	index = 0;
	tmp = 0;
	if (!cmd_node || !cmd_node->str || !cmd_node->str[1])
		return (print_export(minishell));
	while (cmd_node->str[++index])
	{
		if (put_env(cmd_node, minishell, index) | tmp)
			tmp = FUNC_FAIL;
	}
	return (tmp);
}
