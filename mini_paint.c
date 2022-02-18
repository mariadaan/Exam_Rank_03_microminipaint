#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// gcc micro_paint.c printvar.c && ./a.out operation_file.txt

int	printnum(char *name, int num);
int	printchar(char *name, char c);
int	printfloat(char *name, float num);

typedef struct s_info
{
	int		bg_width;
	int		bg_height;
	char	bg_char;

	char	circle_type;
	float	x_center; // the horizontal position of the top left corner of the rectangle
	float	y_center; // the vertical position of the top left corner of the rectangle
	float	radius; // >0
	char	circle_char;

} t_info;

void print_2D(char **array, int height)
{
	for (int i = 0; i < height; i++)
	{
		printf("%s\n", array[i]);
	}
}

char **create_matrix(int width, int height, char c)
{
	char **matrix;
	char *row;

	matrix = calloc(height, sizeof(char *));
	int i_y = 0;
	while (i_y < height)
	{
		row = calloc(width, sizeof(char));
		int i_x = 0;
		while (i_x < width)
		{
			row[i_x] = c;
			i_x++;
		}
		matrix[i_y] = row;
		i_y++;
	}
	return matrix;
}


int is_inside(float value, float start, float end)
{
	if (value >= start && value <= end)
		return (1);
	return (0);
}

int is_border(float value, float start, float end)
{
	if (value < (start + 1) || value > (end - 1))
		return (1);
	return (0);
}

float get_distance(x_center, y_center, x_current, y_current)
{
	return(sqrt((x_center - x_current) * (x_center - x_current) + (y_center - y_current) * (y_center - y_current)));
}

// in rect inside = 2
// border = 1
// out rect = 0
int in_circle(t_info *info, float x_current, float y_current)
{
	float dist = get_distance(info->x_center, info->y_center, x_current, y_current);
	if (dist <= info->radius)
	{
		// hier is ie border of midden
		if ((info->radius - dist) < 1)
			return (1);
		return (2);
	}
	return (0);
}

int draw_circle(t_info *info, char **matrix)
{
	int pos;
	int i_y = 0;
	while (i_y < info->bg_height)
	{
		int i_x = 0;
		while (i_x < info->bg_width)
		{
			pos = in_circle(info, i_x, i_y);
			if (pos == 1) // border
				matrix[i_y][i_x] = info->circle_char;
			else if (pos == 2 && info->circle_type == 'C') // inside
				matrix[i_y][i_x] = info->circle_char;
			i_x++;
		}
		i_y++;
	}
	return (0);
}

int alter_matrix(FILE *fp, t_info *info, char **matrix)
{
	while (fscanf(fp, "%c %f %f %f %c\n", &info->circle_type, &info->x_center, &info->y_center, &info->radius, &info->circle_char) != EOF)
	{
		if (info->circle_type == 'c' || info->circle_type == 'C')
			draw_circle(info, matrix);
		else
		{
			write(1, "Error: Operation file corrupted\n", 32);
			return (1);
		}
	}
	return (0);
}

int get_background(FILE *fp, t_info *info)
{
	int ret;
	ret = fscanf(fp, "%d %d %c\n", &info->bg_width, &info->bg_height, &info->bg_char);
	
	if (is_inside(info->bg_width, 1, 300) && is_inside(info->bg_height, 1, 300) && is_inside(info->bg_char, 32, 126))
		return (0);
	// check if values are valid
	else
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
}

int main(int argc, char *argv[])
{
	t_info info;
	FILE * fp;
	char **matrix;

	if (argc != 2)
	{
		write(1, "Error: argument\n", 17);
		return (0);
	}
	char *filename = argv[1];
	fp = fopen(filename, "r");
	get_background(fp, &info);
	matrix = create_matrix(info.bg_width, info.bg_height, info.bg_char);
	alter_matrix(fp, &info, matrix);
	print_2D(matrix, info.bg_height);
}