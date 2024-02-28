/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsepar <minsepar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:52:19 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/27 20:45:14 by minsepar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

static char	*parse_value(char *env, int size, int index, t_minishell *minishell)
{
	char	*value;
	char	*tmp;

	if (ft_strlen(env) != (size_t)size)
	{
		if (env[index + 1] == '\0')
		{
			value = (char *)malloc(sizeof(char) * 1);
			value[0] = '\0';
		}
		else
		{
			tmp = ft_strdup(&env[index + 1]);
			value = env_parse_value(tmp, minishell);
			free(tmp);
		}
		env[index] = '=';
	}
	else
		value = NULL;
	return (value);
}

int	parse_env(char *env, char **key, char **value, t_minishell *minishell)
{
	int		index;
	int		size;

	index = -1;
	size = ft_strlen(env);
	while (env[++index])
	{
		if (env[index] == '=')
		{
			if (index == 0)
				return (FUNC_FAIL);
			env[index] = '\0';
			break ;
		}
	}
	*key = env_parse_value(env, minishell);
	*value = parse_value(env, size, index, minishell);
	return (FUNC_SUC);
}

void	exchange_node_key_value(t_tree_node *n, t_tree_node *t)
{
	char	*key;
	char	*value;

	key = n->key;
	value = n->value;
	n->key = t->key;
	n->value = t->value;
	t->key = key;
	t->value = value;
}

char	*key_value_to_str(t_tree_node *node, int quote_flag)
{
	char	*ret;
	char	*tmp;

	if (node->value == NULL)
		ret = ft_strdup(node->key);
	else if (quote_flag)
	{
		if (node->value[0] == '\0')
			return (ft_strjoin(node->key, "=\"\""));
		else
		{
			tmp = ft_strjoin(node->key, "=\"");
			ret = ft_strjoin(tmp, node->value);
			free(tmp);
			tmp = ft_strjoin(ret, "\"");
			free(ret);
			ret = tmp;
		}
	}
	else
	{
		if (node->value[0] == '\0')
			return (ft_strjoin(node->key, "="));
		else
		{
			tmp = ft_strjoin(node->key, "=");
			ret = ft_strjoin(tmp, node->value);
			free(tmp);
		}
	}
	return (ret);
}

char 	*env_parse_value(char *str, t_minishell *minishell)
{
	t_parse_str	parse_str;

	init_parse_str(&parse_str);
	while (*str)
	{
		if (*str == '\'')
			parse_single_quote(&parse_str, &str);
		else if (*str == '\"')
			parse_double_quote(&parse_str, &str, minishell);
		else if (*str == '$')
			parse_env_var(&parse_str, &str, 0, minishell);
		else
			parse_single_char(&parse_str, &str, 0, minishell);
	}
	return (parse_str.str);
}
