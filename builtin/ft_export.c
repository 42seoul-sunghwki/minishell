/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:23:12 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/22 12:38:12 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static	int	print_export(t_minishell *minishell)
{
	char	**env;
	int		index;

	index = 0;
	env = tree_to_char(minishell->export);
	while (env[index])
	{
		printf("declare -x %s\n", env[index]);
		free(env[index]);
		index++;
	}
	free(env);
	return (FUNC_SUC);
}

int	ft_export(t_cmd_node *cmd_node, t_minishell *minishell)
{
	int		index;
	int		ret;
	char	*key;
	char	*value;

	index = 0;
	if (cmd_node->str[0] == NULL)
		return (print_export(minishell));
	while (cmd_node->str[++index])
	{
		if (!ft_isalpha(cmd_node->str[index][0]))
			return (err_quote(minishell, cmd_node->str[0],
					cmd_node->str[index], "not a valid identifier"));
		ret = parse_env(cmd_node->str[index], &key, &value);
		if (ret == FUNC_FAIL)
			return (err_quote(minishell, cmd_node->str[0],
					cmd_node->str[index], "not a valid identifier"));
		ret = ft_setenv(minishell->export, key, value);
		if (ret == FUNC_FAIL)
			return (FUNC_FAIL);
		if (value && *value)
			ret = ft_setenv(minishell->env, key, value);
		index++;
	}
	return (FUNC_SUC);
}
