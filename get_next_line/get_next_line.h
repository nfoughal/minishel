/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:37:07 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/03 01:33:33 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 5

# include<unistd.h>
# include<stdlib.h>

char	*fft_strjoin(char *s1, char *s2);
size_t	fft_strlen(char *s);
int		fft_strchr(char *s, int c);
char	*fft_strdup(char *s1);
char	*get_next_line(int fd);
char	*read_record(int fd, char *record);
char	*get_line(char *record);
char	*new_record(char *record);
#endif
