#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>




// “ss‚Ì\‘¢‘Ì
typedef struct {
    int id;
    double x;
    double y;
} City;

double min_dist = 1e9;
int* best_path;

// 2“ssŠÔ‚Ìƒ†[ƒNƒŠƒbƒh‹——£‚ğŒvZ‚·‚éŠÖ”(—á‚ÌŒö®)
double calculate_distance(City a, City b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// ‘S’Tõ‚ÅÅ’ZŒo˜H‚ğŒ©‚Â‚¯‚éÄ‹AŠÖ”
void solve(City cities[], int path[], int visited[], int num_cities, int depth, double current_dist) {
    // ‚·‚×‚Ä‚Ì“ss‚ğ–K–â‚µ‚½ê‡
    if (depth == num_cities) {
        // ÅŒã‚É“ss1io”­“_j‚É–ß‚é‹——£‚ğ‘«‚·
        double total_dist = current_dist + calculate_distance(cities[path[num_cities - 1]], cities[path[0]]);

        // XV
        if (total_dist < min_dist - 1e-7) {
            min_dist = total_dist;
            for (int i = 0; i < num_cities; i++){
                best_path[i] = path[i];
            }
        }
        // ‹——£‚ª“¯‚¶ê‡i‹t‰ñ‚è‚È‚Çj
        else if (fabs(total_dist - min_dist) <= 1e-7) {
            // 2”Ô–Ú‚Ì“ss”Ô†‚ª¬‚³‚¢•û‚ğÌ—p‚·‚é
            if (cities[path[1]].id < cities[best_path[1]].id) {
                for (int i = 0; i < num_cities; i++){
                    best_path[i] = path[i];
                }
            }
        }
        return;
    }

    // Ÿ‚É–K–â‚·‚é“ss‚ğ’Tõ
    for (int i = 1; i < num_cities; i++) {
        if (visited[i] == false) {
            visited[i] = 1;
            path[depth] = i;

            double dist_to_next = calculate_distance(cities[path[depth - 1]], cities[i]);
            solve(cities, path, visited, num_cities, depth + 1, current_dist + dist_to_next);

            visited[i] = 0; // ƒoƒbƒNƒgƒ‰ƒbƒN
        }
    }
}

int main() {
    int num_cities;

    printf("“ss‚Ì”‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢");
    if (scanf("%d", &num_cities) != 1 || num_cities <= 0) {
        printf("–³Œø‚È“ss”‚Å‚·B\n");
        return 1;
    }


    City* cities = (City*)malloc(sizeof(City) * num_cities);
    int* path = (int*)malloc(sizeof(int) * num_cities);
    int* visited = (int*)calloc(num_cities, sizeof(int));
    best_path = (int*)malloc(sizeof(int) * num_cities);

    if (cities == NULL || path == NULL || visited == NULL || best_path == NULL) {
        printf("ƒƒ‚ƒŠ‚ÌŠm•Û‚É¸”s‚µ‚Ü‚µ‚½B\n");
        return 1;
    }

    printf("\nŠe“ss‚Ìƒf[ƒ^‚ğu“ss”Ô† XÀ•W YÀ•Wv‚Ì‡‚É“ü—Í‚µ‚Ä‚­‚¾‚³‚¢B\n");
    printf("iƒXƒy[ƒX‚Ü‚½‚Í‰üs‚Å‹æØ‚Á‚Ä‚­‚¾‚³‚¢j\n");
    for (int i = 0; i < num_cities; i++) {
        printf("“ss %d ‚Ìƒf[ƒ^: ", i + 1);
        scanf("%d %lf %lf", &cities[i].id, &cities[i].x, &cities[i].y);
    }

    // Å‰‚Ì“ss‚Í•K‚¸“ü—Í‚³‚ê‚½Å‰‚Ì“ss
    path[0] = 0;
    visited[0] = 1;

    // ’Tõ
    solve(cities, path, visited, num_cities, 1, 0.0);

    // Œ‹‰Ê‚Ìo—Í
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

    return 0;
}