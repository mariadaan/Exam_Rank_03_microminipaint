# micro_paint
1. open operation file using fopen
2. create struct with 9 values 
- int		bg_width;
- int		bg_height;
- char		bg_char;
- char		rect_type;
- float		x; // the horizontal position of the top left corner of the rectangle
- float		y; // the vertical position of the top left corner of the rectangle
- float		width; // >0
- float		height; // >0
- char		rect_char;
3. save background info in first 3 values using fscanf
4. create matrix with this background info
5. loop over rectangles
- while (fscanf(fp, "%c %f %f %f %f %c\n", &info->rect_type, &info->x, &info->y, &info->width, &info->height, &info->rect_char) != EOF)
6. loop over pixels
- draw rect in matrix by going over all coordinates in the matrix and check if the pixel is in a rectangle. 
- check if pixel is border or not
- change pixel to rect_char
7. print matrix
