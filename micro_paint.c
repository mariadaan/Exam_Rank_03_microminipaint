#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


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

void print_file(FILE *fp)
{
	char s;
	while((s=fgetc(fp))!=EOF)
	{
		printf("%c",s);
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
	printnum("bg", info->bg_width);
	printnum("return", ret);
	// check if values are valid
	return (0);
}
void draw_empty(t_info *info, char **matrix)
{
	int x_int;
	int y_int;
	int width_int;
	int height_int;

	x_int = ceil(info->x);
	y_int = ceil(info->y);
	width_int = ceil(info->width);
	height_int = ceil(info->height);

	printnum("x_int", x_int);
	printnum("y_int", y_int);
	printnum("width_int", width_int);
	printnum("height_int", height_int);
	printf("\n");

	// horizontal rows
	for (int i_x = info->x; i_x <= width_int; i_x++)
	{
		matrix[y_int][i_x] = info->rect_char;
		matrix[y_int + height_int][i_x] = info->rect_char;
	}

	// vertical columns
	for (int i_y = y_int; i_y <= height_int; i_y++)
	{
		matrix[i_y][x_int] = info->rect_char;
		matrix[i_y][x_int + width_int] = info->rect_char;
	}
}

int alter_matrix(FILE *fp, t_info *info, char **matrix)
{
	while (fscanf(fp, "%c %f %f %f %f %c\n", &info->rect_type, &info->x, &info->y, &info->width, &info->height, &info->rect_char) != EOF)
	{
		if (info->rect_type == 'r')
			draw_empty(info, matrix);
		// else if (info->rect_type == 'R')
		// 	draw_full(info, matrix);
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