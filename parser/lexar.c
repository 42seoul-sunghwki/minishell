/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:22:56 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/03 17:12:48 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			err_token_finder(char *ptr, int index)
{
	while (ptr[index] != '\0')
	{
		if (ft_isspace(ptr[index]) == TRUE)
			index++;
		else if (ptr[index] == '\"' || ptr[index] == '\'')
			return (index);
		else if (ptr[index] == '(')
			return (index);
		else if (ptr[index] == '<' || ptr[index] == '>')
		{
			if (ptr[index + 1] == ptr[index])
				return (index + 1);
			else
				return (index);
		}
		index++;
	}
	return (index);
}

static int	heredoc_open_fd(t_redirection *red, t_minishell *minishell)
{
	t_tmp_file	*tmp_file;
	
	//add file name
	tmp_file = (t_tmp_file *)malloc(sizeof(t_tmp_file));
	ft_memset((void *)tmp_file, 0, sizeof(t_tmp_file));
	tmp_file->tmp = ft_strjoin(minishell->tmp_file_name, ft_itoa(minishell->tmp_file_counter));
	tmp_file->fd = open(tmp_file->tmp, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (tmp_file->fd == -1) //add file descriptor error
		return (FUNC_SUC); //maybe leak inside
	red->index = minishell->tmp_file_counter;
	tmp_file->eof = ft_strdup(red->str);
	tmp_list_push(tmp_file, minishell);
	return (FUNC_SUC);
}

static int	find_next_token_red(char *ptr, int index, t_redirection *red)
{
	if (ptr[index] == '<')
	{
		ptr[index] = '\0';
		if (ptr[index + 1] == '<')
		{
			red->flag = DB_LT_SIGN;
			index++;
		}
		else
			red->flag = LT_SIGN;
	}
	else
	{
		ptr[index] = '\0';
		if (ptr[index + 1] == '>')
		{
			red->flag = DB_GT_SIGN;
			index++;
		}
		else
			red->flag = GT_SIGN;
	}
	index++;
	return (index);
}

static char *file_name_parser(char *ptr)
{
	t_parse_str	parse_str;
	char		*ret;
	int			index;

	init_parse_str(&parse_str);	
	index = -1;
	while (ptr[++index])
	{
		if (ft_isspace(ptr[index]) == TRUE)
			continue ;
		if (ptr[index] == '\"' || ptr[index] == '\'')
			continue ;
		append_char(&parse_str, ptr[index]);
	}
	ret = ft_strdup(parse_str.str); 
	free_parse_str(&parse_str);
	free(ptr);
	return (ret);
}

static int	lexar_redirect(t_ast_node *node, t_minishell *minishell, int index)
{
	char			*ptr;
	int				start;
	t_redirection	*red;

	ptr = node->cmd_node->str[0]; 
	red = (t_redirection *)malloc(sizeof(t_redirection));
	ft_memset((void *)red, 0, sizeof(t_redirection));
	redirect_node_push(node, red);
	index = find_next_token_red(ptr, index, red);
	start = index;
	index += skip_space(&ptr[index]);
	if (ptr[index] == '\0' || ptr[index] == '<' || ptr[index] == '>')
	{
		node->err_flag = TRUE;
		printf("ptr: %c\n", ptr[index]);
		if (ptr[index] == '\0')
			return (syntax_err_message("newline", NOTDEFINED, -2, minishell));
		else
			return (syntax_err_message(&ptr[index], NOTDEFINED, -2, minishell)); //substring 만드는 부분을 위로 올려서 처리.
	}
	while (ptr[index] != '\0')
	{
		if (ft_isspace(ptr[index]) == TRUE || ptr[index] == '<' || ptr[index] == '>')
			break ;
		index++;
	}
	red->str = ft_substr(&ptr[start], 0, index - start);
	red->str = file_name_parser(red->str);
	ft_strlcat(ptr, &ptr[index], ft_strlen(ptr) + ft_strlen(&ptr[index]) + 1);
	if (red->flag == DB_LT_SIGN)
	{
		node->index = minishell->tmp_file_counter + 1;
		if (heredoc_open_fd(red, minishell) == FUNC_FAIL) //free add required
			return (-2);
	}
	if (red->flag == DB_LT_SIGN || red->flag == DB_GT_SIGN)
		return (start - 3);
	else
		return (start - 2);
}

static int	subshell_recurv_parser(t_ast_node *head, int index, int flag, t_minishell *minishell)
{
	char	*ptr;
	int		tmp;

	ptr = head->cmd_node->str[0]; 	
	tmp = bracket_finder(&ptr[index]);
	if (tmp + index == NOTDEFINED || tmp == index + 1)
	{
		head->err_flag = TRUE;
		return (syntax_err_message(&ptr[index], tmp, FUNC_FAIL, minishell));
	}
	if (flag & STRING_FLAG)
	{
		head->err_flag = TRUE;
		return (syntax_err_message(&ptr[index + 1], tmp - 1, FUNC_FAIL, minishell));
	}
	ptr[tmp + index] = ' ';
	ptr[index] = ' ';
	index += tmp;
	tmp = index;
	while (TRUE)
	{
		tmp += skip_space(&ptr[tmp]);
		if (ptr[tmp] == '\0' || ptr[tmp] == '<' || ptr[tmp] == '>')
		{
			head->flag = BRACKET_FLAG;
			return (tmp);
		}
		else if (ptr[tmp] == '(')
			return (syntax_err_message(&ptr[tmp], tmp + 1, FUNC_FAIL, minishell));
		else
		{
			head->err_flag = TRUE;
			return (syntax_err_message(&ptr[tmp], NOTDEFINED, FUNC_FAIL, minishell)); //adhoc
		}
	}
	return (tmp);
}

//check redirection
int	lexar(t_ast_node *node, t_minishell *minishell)
{
	char		*ptr;
	char		**cmd_str;
	int			index;
	int			str_flag;
	int			tmp;
	
	index = -1;
	str_flag = FALSE;
	ptr = node->cmd_node->str[0];
	printf("lexar ptr: %s\n", ptr);
	while (ptr[++index])
	{
		index += skip_space(&ptr[index]);
		if (ptr[index] == '\0')
			break ;
		if (ptr[index] == '\"' || ptr[index] == '\'')
		{
			tmp = finder(&ptr[index + 1], ptr[index]);
			if (tmp == NOTDEFINED)
				return (syntax_err_message(ptr, NOTDEFINED, FUNC_FAIL, minishell));
			index += tmp + 1;
			continue ;
		}
		if (ptr[index] == '<' || ptr[index] == '>')
		{
			index = lexar_redirect(node, minishell, index);
			if (index == -2)
				return (FUNC_FAIL);
			continue ;
		}
		if (ptr[index] == '(')
		{
			tmp = subshell_recurv_parser(node, index, str_flag, minishell);
			if (tmp == FUNC_FAIL)
				return (FUNC_FAIL);
			str_flag |= BRACKET_FLAG;
			index = tmp - 1; //error?
			continue ;
		}
		str_flag |= STRING_FLAG;
	}
	if (str_flag & BRACKET_FLAG)
	{
		tmp = recurv_parser(node, minishell);
		node->flag |= BRACKET_FLAG;
		return (tmp);
	}
	cmd_str = string_parser(ptr, minishell);
	free_2d_str(node->cmd_node->str); 
	node->cmd_node->str = cmd_str;
	return (FUNC_SUC);
}
