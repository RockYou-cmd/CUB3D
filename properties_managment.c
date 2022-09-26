#include "cub3d.h"

void	check_extention(char *file, char *extention)
{
	int file_len;
	int extention_len;

	file_len = ft_strlen(file);
	extention_len = ft_strlen(extention);
	if (file_len <= extention_len)
		end_game("extention problem");
	if (ft_strcmp(file + (file_len - extention_len), extention))
		end_game("extention problem");
}

char	*fill_wall(int (*arr)[6], int n, char *str)
{
	(*arr)[n] = 1;
	check_extention(str, ".ppm");
	return (ft_strdup(str));
}

void	ft_striteri2(char **s, void (*f)(char))
{
	unsigned int	i;
	int j;

	if (s == NULL)
		end_game("colors problem");
	j = 0;
	if (s)
	{
		while (s[j])
		{
			i = 0;
			while (s[j][i])
			{
				(*f)(s[j][i]);
				i++;
			}
			j++;
		}
	}
}

void	check_digit(char c)
{
	if (!ft_isdigit(c))
		end_game("colors are not digits");
}


void fill_color(int (*arr)[6], int n, int (*colors)[3], char **str)
{
	char **colors_str;
	int count;
	int i;
	char *line;

	i = 1;
	line = ft_strdup("");
	while (str[i])
	{
		line = ft_strjoin(line, str[i]);
		i++;
	}
	colors_str = ft_split(line, ',');
	free(line);
	
	ft_striteri2(colors_str, check_digit);
	count = 0;
	while (colors_str[count] != NULL)
		count++;
	if (count != 3)
		end_game("colors problem");
	(*arr)[n] = 1;
	(*colors)[0] = ft_atoi(colors_str[0]);
	(*colors)[1] = ft_atoi(colors_str[1]);
	(*colors)[2] = ft_atoi(colors_str[2]);
	free_2d_arr(colors_str);
	count = 0;
	while (count < 3)
	{
		if ((*colors)[count] > 255 || (*colors)[count] < 0)
			end_game("colors out of range");
		count++;
	}
}

static int	count_prop(char **prop)
{
	int i;

	i = 0;
	if (!prop)
		return (0);
	while (prop[i])
	{
		i++;
	}
	return (i);
}

void	free_2d_arr(char **arr)
{
	int i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

t_props pars_props(t_list_map *list)
{
	int arr[6];
	t_props props;
	char **prop;
	int count = 6;
	int i = 0;
	char *line;

	while (count && list)
	{
		line = ft_strtrim(list->line, "\n");
		prop = ft_split(line, ' ');
		free(line);
		if (count_prop(prop) == 2 && ft_strcmp(prop[0], "NO") == 0)
			props.no = fill_wall(&arr, NO, prop[1]);
		else if (count_prop(prop) == 2 && ft_strcmp(prop[0], "SO") == 0)
			props.so = fill_wall(&arr, SO, prop[1]);
		else if (count_prop(prop) == 2 && ft_strcmp(prop[0], "WE") == 0)
			props.we = fill_wall(&arr, WE, prop[1]);
		else if (count_prop(prop) == 2 && ft_strcmp(prop[0], "EA") == 0)
			props.ea = fill_wall(&arr, EA, prop[1]);
		else if (count_prop(prop) >= 2 && ft_strcmp(prop[0], "F") == 0)
			fill_color(&arr, F, &props.f, prop);
		else if (count_prop(prop) >= 2 && ft_strcmp(prop[0], "C") == 0)
			fill_color(&arr, C, &props.c, prop);
		free_2d_arr(prop);
		list = list->next;
		count--;
	}
	while (!count && arr[i] == 1)
		i++;
	if (i != 6)
		end_game("map");
	return (props);
}

void	delete_props(t_list_map **list)
{
	int count = 6;
	while (count)
	{
		delete_node(list, *list);
		count--;
	}
}

void	print_props(t_props props)
{
	printf("NO :: %s\n", props.no);
	printf("SO :: %s\n", props.so);
	printf("WE :: %s\n", props.we);
	printf("EA :: %s\n", props.ea);
	printf("F::: R: %d, G: %d, B: %d\n", props.f[0], props.f[1], props.f[2]);
	printf("C::: R: %d, G: %d, B: %d\n", props.c[0], props.c[1], props.c[2]);
	printf("PLD:: %d", props.player_l_d);
}