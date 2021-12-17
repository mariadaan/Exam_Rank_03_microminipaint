#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int	printnum(char *name, int num);
int	printchar(char *name, char c);

typedef struct s_info
{
	int		bg_width;
	int		bg_height;
	char	bg_char;
	char	r_empty;
	float	x_empty; // the horizontal position of the top left corner of the rectangle
	float	y_empty; // the vertical position of the top left corner of the rectangle
	float	width_empty; // >0
	float	height_empty; // >0
	char	r_borderrect;

	float	x_filled; // the horizontal position of the top left corner of the rectangle
	float	Y_filled; // the vertical position of the top left corner of the rectangle
	float	width_filled; // >0
	float	height_filled; // >0
	char	r_filledrect;


} t_info;


void print_file(FILE *fp)
{
	char s;
	while((s=fgetc(fp))!=EOF)
	{
		printf("%c",s);
	}
}

int parse_input(FILE *fp, t_info *info)
{
	fscanf(fp, "%d %d %c", &info->bg_width, &info->bg_height, &info->bg_char);
	return (0);
}

void print_square(int width, int height, char c)
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

	matrix = calloc(height, )
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

int main(int argc, char *argv[])
{
	t_info info;
	FILE * fp;
	if (argc != 2)
	{
		write(1, "Error: argument\n", 17);
		return (0);
	}
	char *filename = argv[1];
	fp = fopen(filename, "r");
	// print_file(fp);
	parse_input(fp, &info);
	painting = create_matrix(info.bg_width, info.bg_height, info.bg_char);
	print_square(info.bg_width, info.bg_height, info.bg_char);
	printnum("\nwidth", info.bg_width);
	printnum("\nbg_height", info.bg_height);
	printchar("\nbg_char", info.bg_char);


}