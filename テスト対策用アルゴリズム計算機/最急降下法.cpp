#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

static double get_gradient(double x) {
    return 6.0 * x - 6.0;
}

extern "C" void run_gradient_descent() {
    double x;
    double alpha;
    int steps;

    printf("初期値 x の値を入力してください: ");
    if (scanf("%lf", &x) != 1) return;

    printf("学習率 alpha の値を入力してください (例: 0.1): ");
    if (scanf("%lf", &alpha) != 1) return;

    printf("最急降下法の計算回数を入力してください (例: 4): ");
    if (scanf("%d", &steps) != 1) return;

    printf("\n--- 計算開始 ---\n");
    printf("初期状態: x = %.4f\n", x);

    for (int i = 1; i <= steps; i++) {
        double grad = get_gradient(x);
        x = x - alpha * grad;

        printf("%d回目: x = %.4f\n", i, x);
    }

    printf("----------------\n");
    printf("最終結果 (答え): %.4f\n", x);
}