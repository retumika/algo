#include <stdio.h>

// 勾配（微分 df(x)/dx = 6x - 6）を計算する関数
//テストのときはここの数値を問題に合わせて変更
double get_gradient(double x) {
    return 6.0 * x - 6.0;
}

int main() {
    double x;          // 現在のxの値
    double alpha;      // 学習率
    int steps;         // 計算回数

    // 各種パラメータの入力
    printf("初期値 x の値を入力してください: ");
    if (scanf("%lf", &x) != 1) return 1;

    printf("学習率 alpha の値を入力してください (例: 0.1): ");
    if (scanf("%lf", &alpha) != 1) return 1;

    printf("最急降下法の計算回数を入力してください (例: 4): ");
    if (scanf("%d", &steps) != 1) return 1;

    printf("\n--- 計算開始 ---\n");
    printf("初期状態: x = %.4f\n", x);

    // 指定された回数だけ最急降下法の更新を繰り返す
    for (int i = 1; i <= steps; i++) {
        double grad = get_gradient(x); // 勾配の計算
        x = x - alpha * grad;          // xの更新式

        // 各ステップの結果を小数点以下第4位まで表示
        printf("%d回目: x = %.4f\n", i, x);
    }

    printf("----------------\n");
    printf("最終結果 (答え): %.4f\n", x);

    return 0;
}