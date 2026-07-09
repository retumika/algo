#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int id;
    double x;
    double y;
} City;

static double min_dist = 1e9;
static int* best_path;

static double calculate_distance(City a, City b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

static void solve(City cities[], int path[], int visited[], int num_cities, int depth, double current_dist) {
    if (depth == num_cities) {
        double total_dist = current_dist + calculate_distance(cities[path[num_cities - 1]], cities[path[0]]);

        if (total_dist < min_dist - 1e-7) {
            min_dist = total_dist;
            for (int i = 0; i < num_cities; i++) {
                best_path[i] = path[i];
            }
        }
        else if (fabs(total_dist - min_dist) <= 1e-7) {
            if (cities[path[1]].id < cities[best_path[1]].id) {
                for (int i = 0; i < num_cities; i++) {
                    best_path[i] = path[i];
                }
            }
        }
        return;
    }

    for (int i = 1; i < num_cities; i++) {
        if (visited[i] == 0) {
            visited[i] = 1;
            path[depth] = i;

            double dist_to_next = calculate_distance(cities[path[depth - 1]], cities[i]);
            solve(cities, path, visited, num_cities, depth + 1, current_dist + dist_to_next);

            visited[i] = 0;
        }
    }
}

extern "C" void run_tsp() {
    int num_cities;

    printf("“sŽs‚Ì”‚ð“ü—Í‚µ‚Ä‚­‚¾‚³‚¢: ");
    if (scanf("%d", &num_cities) != 1 || num_cities <= 0) {
        printf("–³Œø‚È“sŽs”‚Å‚·B\n");
        return;
    }

    City* cities = (City*)malloc(sizeof(City) * num_cities);
    int* path = (int*)malloc(sizeof(int) * num_cities);
    int* visited = (int*)calloc(num_cities, sizeof(int));
    best_path = (int*)malloc(sizeof(int) * num_cities);

    if (cities == NULL || path == NULL || visited == NULL || best_path == NULL) {
        printf("ƒƒ‚ƒŠ‚ÌŠm•Û‚ÉŽ¸”s‚µ‚Ü‚µ‚½B\n");
        return;
    }

    printf("\nŠe“sŽs‚Ìƒf[ƒ^‚ðu“sŽs”Ô† XÀ•W YÀ•Wv‚Ì‡‚É“ü—Í‚µ‚Ä‚­‚¾‚³‚¢B\n");
    for (int i = 0; i < num_cities; i++) {
        printf("“sŽs %d ‚Ìƒf[ƒ^: ", i + 1);
        scanf("%d %lf %lf", &cities[i].id, &cities[i].x, &cities[i].y);
    }

    path[0] = 0;
    visited[0] = 1;

    min_dist = 1e9; // •¡”‰ñŽÀsŽž‚ÌƒŠƒZƒbƒg—p
    solve(cities, path, visited, num_cities, 1, 0.0);

    printf("\nÅ’ZŒo˜H‚Ì‹——£: %.4f\n", min_dist);
    printf("“š‚¦: ");
    for (int i = 0; i < num_cities; i++) {
        printf("%d", cities[best_path[i]].id);
        if (i < num_cities - 1) printf(" ");
    }
    printf("\n");

    free(cities);
    free(path);
    free(visited);
    free(best_path);
}