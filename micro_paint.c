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

	char	rect_type;
	float	x; // the horizontal position of the top left corner of the rectangle
	float	y; // the vertical position of the top left corner of the rectangle
	float	width; // >0
	float	height; // >0
	char	rect_char;

} t_info;

void print_2D(char **array, int height)
{
	for (int i = 0; i < height; i++)
	{
		printf("%s\n", array[i]);
	}
}

void print_matrix(int width, int height, char c)
{
	int i_y = 0;

	while (i_y < height)
	{
		int i_x = 0;
		while (i_x < width)
		{
			write(1, &c, 1);
			i_x++;
		}
		write(1, "\n", 1);
		i_y++;
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

int get_background(FILE *fp, t_info *info)
{
	int ret;
	ret = fscanf(fp, "%d %d %c\n", &info->bg_width, &info->bg_height, &info->bg_char);
	// check if values are valid
	return (0);
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


// in rect inside = 2
// border = 1
// out rect = 0
int in_rect(t_info *info, float x_current, float y_current)
{
	float x_start = info->x;
	float x_end = info->x + info->width;
	float y_start = info->y;
	float y_end = info->y + info->height;

	// printf("\n\n");
	// printfloat("x_current", x_current);
	// printfloat("x_start", x_start);
	// printfloat("x_end", x_end);
	// printf("\n");
	// printfloat("y_current", y_current);
	// printfloat("y_start", y_start);
	// printfloat("y_end", y_end);


	// hier is ie border of midden
	if (is_inside(x_current, x_start, x_end) && is_inside(y_current, y_start, y_end))
	{
		// hier nog checken of het border of midden is
		if (is_border(x_current, x_start, x_end) || is_border(y_current, y_start, y_end))
			return (1);
		return (2);
	}
	return (0);
}

int draw_rect(t_info *info, char **matrix)
{
	int pos;
	int i_y = 0;
	while (i_y < info->bg_height)
	{
		int i_x = 0;
		while (i_x < info->bg_width)
		{
			pos = in_rect(info, i_x, i_y);
			if (pos == 1) // border
				matrix[i_y][i_x] = info->rect_char;
			else if (pos == 2 && info->rect_type == 'R') // inside
				matrix[i_y][i_x] = info->rect_char;
			i_x++;
		}
		i_y++;
	}
	return (0);
}

int alter_matrix(FILE *fp, t_info *info, char **matrix)
{
	while (fscanf(fp, "%c %f %f %f %f %c\n", &info->rect_type, &info->x, &info->y, &info->width, &info->height, &info->rect_char) != EOF)
	{
		if (info->rect_type == 'r' || info->rect_type == 'R')
			draw_rect(info, matrix);
		else
		{
			write(1, "Error: Operation file corrupted\n", 32);
			return (0);
		}
	}
	return (0);
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