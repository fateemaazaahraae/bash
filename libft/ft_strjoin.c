/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazaz <fbazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:08:15 by fbazaz            #+#    #+#             */
/*   Updated: 2024/08/05 13:37:50 by fbazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_strjoin - Allocates and returns a new  string, which is the result of 
 * 				the concatenation of ’s1’ and ’s2’.
 * @s1: The prefix string.
 * @s2: The suffix string.
 * 
 * Return: The new string or NULL.
 */

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	size_t	len1;
	char	*newstring;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	newstring = malloc((len1 + ft_strlen(s2) + 1) * sizeof(char));
	if (!newstring)
		return (NULL);
	i = -1;
	while (s1[++i])
		newstring[i] = s1[i];
	i = -1;
	while (s2[++i])
	{
		newstring[len1] = s2[i];
		len1++;
	}
	newstring[len1] = '\0';
	return (newstring);
}

/* #include <stdio.h>
int main()
{
	char *res;
	res = ft_strjoin("hello", "world");
	printf("%s", res);
} */