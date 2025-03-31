#include <stdio.h>
#include <limits.h>
#include "html.h"

void write_html(char* output_filename, int** graph, int* prev, long long int* dist, int N, int F, int S){
    if (output_filename) {
        FILE* html_file = fopen(output_filename, "w");
        if (html_file) {
            fprintf(html_file, 
                    "<html><head><style>"
                    "body {"
                    "background-image: url('https://www.screentune.com/wp-content/uploads/2019/10/258026.png');"  
                    "background-size: cover;"                        
                    "background-position: center;"                    
                    "background-repeat: no-repeat;"                    
                    "background-attachment: fixed;"                    
                    "}"
                    "table { border-collapse: collapse; width: 70%%; margin: auto; border-radius: 10px;}"
                    "th, td { border: 1px solid black; padding: 6px; text-align: center; background-color:rgb(222, 255, 123);}"
                    "th { background-color:rgb(13, 114, 0); }"
                    ".highlight { background-color:rgb(137, 212, 38); }"
                    "</style></head><body>\n");

            // Матрица смежности
            fprintf(html_file, "<h2 align=\"center\" style=\"color: white\">Adjacency_matrix</h2>\n");
            fprintf(html_file, "<style>td {color: rgb(26, 102, 241)}</style>");
            fprintf(html_file, "<table>\n");
            fprintf(html_file, "<tr><th></th>");
            for (int i = 1; i <= N; i++) {
                fprintf(html_file, "<th>%d</th>", i);
            }
            fprintf(html_file, "</tr>\n");
            for (int i = 1; i <= N; i++) {
                fprintf(html_file, "<tr><th>%d</th>", i);
                for (int j = 1; j <= N; j++) {
                    if (graph[i][j] != 0) {
                        int is_highlighted = 0;
                        for (int v = F; v != -1; v = prev[v]) {
                            if ((v == i && prev[v] == j) || (v == j && prev[v] == i)) {
                                is_highlighted = 1;
                                break;
                            }
                        }
                        if (is_highlighted) {
                            fprintf(html_file, "<td class=\"highlight\">%d</td>", graph[i][j]);
                        } else {
                            fprintf(html_file, "<td>%d</td>", graph[i][j]);
                        }
                    } else {
                        fprintf(html_file, "<td>0</td>");
                    }
                }
                fprintf(html_file, "</tr>\n");
            }
            fprintf(html_file, "</table>\n");

            fprintf(html_file, "<style> h2 {font-family: 'Roboto', sans-serif; background-color: rgba(16, 54, 1, 0.716);padding: 5px;border-radius: 10px;margin: 0 auto;text-align: center;}</style>");

            // Таблица расстояний
            fprintf(html_file, "<h2 align=\"center\" style=\"color: white\">Distances_table || start_point: %d</h2>\n", S);
            fprintf(html_file, "<table>\n");
            fprintf(html_file, "<style>th {color: rgb(26, 102, 241)}");
            fprintf(html_file,        "td {color: rgb(26, 102, 241)}</style>");
            fprintf(html_file, "<tr><th>Vertex</th><th>Distance</th></tr>\n");
            for (int i = 1; i <= N; i++) {
                if (dist[i] == LLONG_MAX) {
                    fprintf(html_file, "<tr><td>%d</td><td>oo</td></tr>\n", i);
                } else if (dist[i] > INT_MAX) {
                    fprintf(html_file, "<tr><td>%d</td><td>INT_MAX+</td></tr>\n", i);
                } else {
                    fprintf(html_file, "<tr><td>%d</td><td>%lld</td></tr>\n", i, dist[i]);
                }
            }
            fprintf(html_file, "</table>\n");

            fprintf(html_file, "</body></html>\n");
            fclose(html_file);
        }
    }

}



