/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:17:00 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/01 14:21:46 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	print_error_msg_arg(char *arg, int quote_flag)
{
	if (quote_flag)
	{
		ft_putstr_fd("`", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("\'", STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
}

void	free_error(t_error *error)
{
	if (error->execute_name)
		free(error->execute_name);
	if (error->builtin)
		free(error->builtin);
	if (error->arg)
		free(error->arg);
	if (error->msg)
		free(error->msg);
	free(error);
	error = NULL;
}

t_error	*set_error_msg(char *execute_name, char *builtin, char *arg, char *msg)
{
	t_error	*error;

	error = (t_error *)malloc(sizeof(t_error));
	if (!execute_name)
		error->execute_name = NULL;
	else
		error->execute_name = ft_strdup(execute_name);
	if (!builtin)
		error->builtin = NULL;
	else
		error->builtin = ft_strdup(builtin);
	if (!arg)
		error->arg = NULL;
	else
		error->arg = ft_strdup(arg);
	if (!msg)
		error->msg = NULL;
	else
		error->msg = ft_strdup(msg);
	return (error);
}

int	print_error_msg(t_error *error, int error_num, int quote_flag)
{
	if (error->execute_name)
	{
		ft_putstr_fd(error->execute_name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (error->builtin)
	{
		ft_putstr_fd(error->builtin, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (error->arg)
		print_error_msg_arg(error->arg, quote_flag);
	if (error_num == 0)
		perror(0);
	else
	{
		ft_putstr_fd(error->msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	free_error(error);
	return (error_num);
}

int	cd_error(t_cd *info, t_minishell *minishell, char *command, char *arg)
{
	free(info->cur_path);
	return (builtin_error(minishell, command, arg));
}

int	builtin_error(t_minishell *minishell, char *command, char *arg)
{
	minishell->error = set_error_msg(minishell->execute_name, command, arg, 0);
	print_error_msg(minishell->error, 0, 0);
	return (1);
}
