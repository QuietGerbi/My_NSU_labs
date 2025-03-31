#include <stdio.h>
#include <math.h>
#include "constants.h"
#include "svg_function.h"

#define M_PI 3.14159265358979323846

void save_edges_to_svg(Edge* saved_edges, int edges_num, int vertex_count) {
    const int width = 1920;
    const int height = 1080;
    const int margin = 50;
    const int point_radius = 10;
    
    FILE* svg_file = fopen("result.svg", "w");
    if (!svg_file) {
        perror("Failed to create SVG file");
        return;
    }

    double center_x = width / 2.0;
    double center_y = height / 2.0;
    double radius = fmin(width, height) / 2.0 - margin;
    

    fprintf(svg_file, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
    fprintf(svg_file, "<svg width=\"%d\" height=\"%d\" xmlns=\"http://www.w3.org/2000/svg\">\n", width, height);
    fprintf(svg_file, "<rect width=\"100%%\" height=\"100%%\" fill=\"white\" />\n");
    
    //Рёбра графа
    for (int i = 0; i < edges_num; i++) {
        int u = saved_edges[i].u;
        int v = saved_edges[i].v;
        
        double angle_u = 2 * M_PI * (u-1) / vertex_count;
        double angle_v = 2 * M_PI * (v-1) / vertex_count;
        
        double x1 = center_x + radius * sin(angle_u);
        double y1 = center_y + radius * cos(angle_u);
        double x2 = center_x + radius * sin(angle_v);
        double y2 = center_y + radius * cos(angle_v);
        
        fprintf(svg_file, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" "
               "stroke=\"black\" stroke-width=\"2\" />\n", x1, y1, x2, y2);
    }
    
    //Вершины графааа
    for (int i = 1; i <= vertex_count; i++) {
        double angle = 2 * M_PI * (i-1) / vertex_count;
        double x = center_x + radius * sin(angle);
        double y = center_y + radius * cos(angle);
        
        fprintf(svg_file, "<circle cx=\"%.2f\" cy=\"%.2f\" r=\"%d\" fill=\"green\" />\n", 
               x, y, point_radius);
        fprintf(svg_file, "<text x=\"%.2f\" y=\"%.2f\" font-size=\"12\" text-anchor=\"middle\" "
                          "dominant-baseline=\"middle\" fill=\"white\">%d</text>\n", x, y, i);
    }
    
    fprintf(svg_file, "</svg>");
    fclose(svg_file);
}


