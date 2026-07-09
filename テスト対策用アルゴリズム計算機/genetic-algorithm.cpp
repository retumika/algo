#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void run_crossover() {
    char str1[100], str2[100];
    int type;
    printf("\n【交叉モード】\n");
    printf("個体1の遺伝子を入力 (例: 1010101): ");
    scanf("%s", str1);
    printf("個体2の遺伝子を入力 (例: 1110000): ");
    scanf("%s", str2);

    printf("\n交叉のタイプを選んでください:\n");
    printf("  1: 奇数番目(1,3,5...)の遺伝子を交換\n");
    printf("  2: 一点交叉\n");
    printf("  3: 二点交叉 (※交叉後の状態から「前」を求める場合もこれを選びます)\n");
    printf("選択: ");
    scanf("%d", &type);

    int len = (int)strlen(str1);

    if (type == 1) {
        for (int i = 0; i < len; i += 2) {
            char tmp = str1[i];
            str1[i] = str2[i];
            str2[i] = tmp;
        }
    }
    else if (type == 2) {
        int pt;
        printf("交叉する場所（何番目以降か）を入力 (例: 3): ");
        scanf("%d", &pt);
        for (int i = pt - 1; i < len; i++) {
            char tmp = str1[i];
            str1[i] = str2[i];
            str2[i] = tmp;
        }
    }
    else if (type == 3) {
        int pt1, pt2;
        printf("交叉する2つの場所をスペース区切りで入力 (例: 3 6): ");
        scanf("%d %d", &pt1, &pt2);
        for (int i = pt1 - 1; i < pt2; i++) {
            char tmp = str1[i];
            str1[i] = str2[i];
            str2[i] = tmp;
        }
    }

    printf("\n================ 答え ================\n");
    printf("%s %s\n", str1, str2);
    printf("======================================\n");
}

void run_mutation() {
    char str[100];
    int num;
    printf("\n【突然変異モード】\n");
    printf("個体の遺伝子を入力: ");
    scanf("%s", str);

    printf("変異させる箇所の「数」を入力 (例: 2): ");
    scanf("%d", &num);

    printf("変異させる場所をスペース区切りで入力 (例: 1 5): ");
    for (int i = 0; i < num; i++) {
        int pt;
        scanf("%d", &pt);
        int idx = pt - 1;
        if (str[idx] == '0') str[idx] = '1';
        else if (str[idx] == '1') str[idx] = '0';
    }

    printf("\n================ 答え ================\n");
    printf("%s\n", str);
    printf("======================================\n");
}

void run_roulette() {
    int num;
    double fit, max_fit = 0, sum = 0;

    printf("\n【ルーレット選択モード】\n");
    printf("個体の数を入力してください (例: 4): ");
    scanf("%d", &num);

    printf("各個体の適応度を入力してください:\n");
    for (int i = 0; i < num; i++) {
        printf("  個体%d: ", i + 1);
        scanf("%lf", &fit);
        sum += fit;
        if (fit > max_fit) max_fit = fit;
    }

    double prob = max_fit / sum;

    printf("\n================ 答え ================\n");
    printf("選択される確率が最も高い個体の選択確率: %.4f\n", prob);
    printf("======================================\n");
}

void run_tournament() {
    double n;
    printf("\n【トーナメント選択（サイズ2・重複なし）モード】\n");
    printf("集団数を入力してください (例: 8): ");
    scanf("%lf", &n);

    double prob = 2.0 / n;

    printf("\n================ 答え ================\n");
    printf("選択される確率が最も高い個体の選択確率: %.4f\n", prob);
    printf("======================================\n");
}

extern "C" void run_genetic_algorithm() {
    int mode;

    while (1) {
        printf("\n========================================\n");
        printf(" 解きたい問題の番号を選んでください\n");
        printf("  1: 交叉（奇数番目 / 一点交叉 / 二点交叉）\n");
        printf("  2: 突然変異\n");
        printf("  3: ルーレット選択\n");
        printf("  4: トーナメント選択\n");
        printf("  0: プログラムを終了する\n");
        printf("========================================\n");
        printf("選択: ");

        if (scanf("%d", &mode) != 1) break;

        if (mode == 0) {
            printf("終了します。\n");
            break;
        }
        else if (mode == 1) {
            run_crossover();
        }
        else if (mode == 2) {
            run_mutation();
        }
        else if (mode == 3) {
            run_roulette();
        }
        else if (mode == 4) {
            run_tournament();
        }
        else {
            printf("正しい番号を入力してください。\n");
        }
    }
}