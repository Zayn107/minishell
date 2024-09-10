#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	bool			s1_no_end;
	bool			s2_no_end;
	size_t			ind;
	unsigned char	*s1_cp;
	unsigned char	*s2_cp;

	s1_no_end = true;
	s2_no_end = true;
	ind = 0;
	s1_cp = (unsigned char *) s1;
	s2_cp = (unsigned char *) s2;
	while (ind < n
		&& s1_no_end
		&& s2_no_end)
	{
		if (s1_cp[ind] == '\0')
			s1_no_end = false;
		if (s2_cp[ind] == '\0')
			s2_no_end = false;
		if (s1_cp[ind] != s2_cp[ind])
			return ((int) s1_cp[ind] - (int) s2_cp[ind]);
		ind++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

char	*ft_strchr(const char *str, int c)
{
	int		ind;
	int		str_len;

	str_len = 0;
	ind = 0;
	while (str[str_len])
		str_len++;
	while (ind < str_len +1)
	{
		if ((char)c == str[ind])
			return ((char *) &str[ind]);
		ind++;
	}
	return (NULL);
}

int	main(void)
{
	char	*str1 = "var=1234";
	char	*str2 = "var";
	char	*ptr_equal;
	int		l_var;


	char	*ptr_equal1;
	char	*ptr_equal2;
	int		l_var1;
	int		l_var2;

	ptr_equal1 = ft_strchr(str1, '=');
	ptr_equal2 = ft_strchr(str2, '=');
	if (NULL != ptr_equal1)
	{
		l_var1 = ptr_equal1 - str1;
		l_var2 = ptr_equal2 - str2;
		if (l_var1 == l_var2)
			if ((0 == ft_strncmp(str1, str2, l_var1)))
				return (true) ;
	}
	return (false) ;
}