#include "../../includes/minishell.h"

char	*ft_strdup_char(char c)
{
	char	*copy;

	copy = malloc(sizeof(char) * 2);
	if (copy == NULL)
		return (NULL);
	copy[0] = c;
	copy[1] = '\0';
	return (copy);
}

char	*ft_strjoin_char(char const *s1, char c)
{
	int		i;
	size_t	len1;
	char	*newstring;

	if (!s1 && !c)
		return (NULL);
	if (!s1)
		return (ft_strdup_char(c));
	if (!c)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	newstring = malloc((len1 + 2) * sizeof(char));
	if (!newstring)
		return (NULL);
	i = -1;
	while (s1[++i])
		newstring[i] = s1[i];
	newstring[len1] = c;
	len1++;
	newstring[len1] = '\0';
	return (newstring);
}
