#include <stdio.h>
#include <math.h>
#include "constants.h"
#include "svg_function.h"

#define M_PI 3.14159265358979323846

int is_in_mst(Edge* saved_edges, int edges_num, int u, int v) {
    for (int i = 0; i < edges_num; i++) {
        if ((saved_edges[i].u == u && saved_edges[i].v == v) ||
            (saved_edges[i].u == v && saved_edges[i].v == u)) {
            return 1;
        }
    }
    return 0;
}

int get_weight(Edge* all_edges, int all_edges_num, int u, int v) {
    for (int i = 0; i < all_edges_num; i++) {
        if ((all_edges[i].u == u && all_edges[i].v == v) ||
            (all_edges[i].u == v && all_edges[i].v == u)) {
            return all_edges[i].weight;
        }
    }
    return 0;
}

void save_edges_to_svg(Edge* saved_edges, int edges_num, int vertex_count, Edge* all_edges, int all_edges_num) {
    const int width = 800;
    const int height = 600;
    const int margin = 50;
    const int point_radius = 10;
    const int text_offset = 20;
    
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
    
    for (int i = 0; i < all_edges_num; i++) {
        int u = all_edges[i].u;
        int v = all_edges[i].v;
        int weight = get_weight(all_edges, all_edges_num, u, v);
        
        double angle_u = 2 * M_PI * (u-1) / vertex_count;
        double angle_v = 2 * M_PI * (v-1) / vertex_count;
        
        double x1 = center_x + radius * sin(angle_u);
        double y1 = center_y + radius * cos(angle_u);
        double x2 = center_x + radius * sin(angle_v);
        double y2 = center_y + radius * cos(angle_v);
        
        double mid_x = (x1 + x2) / 2 + text_offset * cos((angle_u + angle_v)/2);
        double mid_y = (y1 + y2) / 2 + text_offset * sin((angle_u + angle_v)/2);
        
        const char* color = is_in_mst(saved_edges, edges_num, u, v) ? "black" : "red";
        const char* style = is_in_mst(saved_edges, edges_num, u, v) ? "" : "stroke-dasharray=\"8,4\"";
        
        fprintf(svg_file, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" "
               "stroke=\"%s\" stroke-width=\"2\" %s />\n", 
               x1, y1, x2, y2, color, style);
        
        fprintf(svg_file, "<text x=\"%.2f\" y=\"%.2f\" font-size=\"12\" text-anchor=\"middle\" "
               "fill=\"%s\">%d</text>\n", mid_x, mid_y, color, weight);
    }
    
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

