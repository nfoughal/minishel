/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 00:17:04 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/12 01:59:51 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_p(t_all_list *pp, char *str_repp)
{
	pp->oldstr = pp->p;
	pp->oldstr_len = ft_strlen(pp->oldstr);
	pp->p = malloc(sizeof(char)
			* (pp->oldstr_len - pp->sub_len + pp->repp_len + 1));
	if (!pp->p)
	{
		free(pp->oldstr);
		return ;
	}
	ft_memcpy(pp->p, pp->oldstr, pp->strstr_re - pp->oldstr);
	ft_memcpy(pp->p + (pp->strstr_re - pp->oldstr), str_repp, pp->repp_len);
	ft_memcpy(pp->p + (pp->strstr_re - pp->oldstr) + pp->repp_len,
		pp->strstr_re + pp->sub_len,
		pp->oldstr_len - pp->sub_len - (pp->strstr_re - pp->oldstr));
	ft_memset(pp->p + pp->oldstr_len - pp->sub_len + pp->repp_len, 0, 1);
	free(pp->oldstr);
}

char	*string_replace(char *string, char *sub, char *str_repp)
{
	t_all_list	pp;

	pp.strstr_re = NULL;
	pp.p = NULL;
	pp.oldstr = NULL;
	pp.oldstr_len = 0;
	pp.sub_len = 0;
	pp.repp_len = 0;
	pp.p = ft_strdup(string);
	pp.sub_len = ft_strlen(sub);
	pp.repp_len = ft_strlen(str_repp);
	if (!sub)
		return (NULL);
	if (!str_repp)
		str_repp = "";
	pp.strstr_re = ft_strnstr(pp.p, sub, ft_strlen(pp.p));
	if (pp.strstr_re)
	{
		fill_p(&pp, str_repp);
		pp.strstr_re = ft_strnstr(pp.p, sub, ft_strlen(pp.p));
	}
	return (pp.p);
}

int	if_valid_char(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	return (0);
}

char	*get_string_len(char *str)
{
	str++;
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (str);
		str++;
	}
	return (str);
}

char	*data_replace(char *result, char *str, t_env *env)
{
	int		len;
	char	*substr;

	len = get_string_len(str) - str;
	substr = ft_substr(str, 0, len);
	result = string_replace(result, substr,
			get_value_from_env(env, &substr[1]));
	free(substr);
	return (result);
}
