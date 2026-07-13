#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

// ==========================================
// 1. 活性化関数に通す前の値・出力の計算モード
// ==========================================
static void run_feedforward() {
    int n;
    double w[100], x[100], theta;

    printf("\n【1. 出力の計算（前計算・ステップ・シグモイド）】\n");
    printf("入力の数（重みの数）を入力してください (例: 2): ");
    if (scanf("%d", &n) != 1) return;

    printf("重み w1tow%d をスペース区切りで入力してください:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &w[i]);
    }

    printf("閾値 θ を入力してください: ");
    scanf("%lf", &theta);

    printf("入力 x1tox%d をスペース区切りで入力してください:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &x[i]);
    }

    // Σwx - θ の計算
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += w[i] * x[i];
    }
    sum -= theta;

    // ステップ関数とシグモイド関数の計算
    int step_out = (sum >= 0.0) ? 1 : 0;
    double sigmoid_out = 1.0 / (1.0 + exp(-sum));

    printf("\n================ 答え ================\n");
    printf("活性化関数に通す前の値: %.4f\n", sum);
    printf("ステップ関数を用いたときの出力: %d\n", step_out);
    printf("シグモイド関数を用いたときの出力: %.4f\n", sigmoid_out);
    printf("======================================\n");
}

// ==========================================
// 2. 閾値θの逆算（シグモイド関数）モード
// ==========================================
static void run_inverse_sigmoid() {
    int n;
    double w[100], x[100], y;

    printf("\n【2. 閾値θの逆算（シグモイド関数からの逆算）】\n");
    printf("入力の数を入力してください (例: 3): ");
    if (scanf("%d", &n) != 1) return;

    printf("重み w1tow%d をスペース区切りで入力してください:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &w[i]);
    }

    printf("入力 x1〜x%d をスペース区切りで入力してください:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &x[i]);
    }

    printf("出力 y (例: 0.5) を入力してください: ");
    scanf("%lf", &y);

    double sum_wx = 0.0;
    for (int i = 0; i < n; i++) {
        sum_wx += w[i] * x[i];
    }

    // シグモイド関数の逆関数から閾値を求める
    double theta;
    if (y == 0.5) {
        theta = sum_wx; // log(1) は 0 のため
    }
    else {
        theta = sum_wx + log(1.0 / y - 1.0);
    }

    printf("\n================ 答え ================\n");
    printf("このニューロンの閾値θ: %.4f\n", theta);
    printf("======================================\n");
}

// ==========================================
// 3. パーセプトロンの学習（重み・閾値の更新）モード
// ==========================================
static void run_learning() {
    int n, data_num, steps;
    double w[100], theta, alpha;
    double x[100][100], d[100]; // 最大100個のデータまで対応

    printf("\n【3. パーセプトロンの学習（重みと閾値の更新）】\n");
    printf("入力の数を入力してください (例: 2): ");
    if (scanf("%d", &n) != 1) return;

    printf("初期の重み w1tow%d をスペース区切りで入力してください:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &w[i]);
    }

    printf("初期の閾値 θ を入力してください: ");
    scanf("%lf", &theta);

    printf("学習率 α を入力してください (例: 0.1): ");
    scanf("%lf", &alpha);

    printf("教師データの数（パターン数）を入力してください (例: 1 や 4): ");
    scanf("%d", &data_num);

    printf("各教師データを「x1 x2 ... xn d」の順で入力してください:\n");
    for (int i = 0; i < data_num; i++) {
        printf("データ %d: ", i + 1);
        for (int j = 0; j < n; j++) {
            scanf("%lf", &x[i][j]);
        }
        scanf("%lf", &d[i]);
    }

    printf("学習を何回繰り返しますか？ (合計学習回数、例: 1 や 20): ");
    scanf("%d", &steps);

    // 指定された回数だけ学習ループを回す
    for (int step = 0; step < steps; step++) {
        int idx = step % data_num; // 複数データがある場合は順番に適用

        // sum = Σwx - θ
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            sum += w[j] * x[idx][j];
        }
        sum -= theta;

        // ステップ関数で出力 y を計算
        int y = (sum >= 0.0) ? 1 : 0;

        // 更新式: w_i = w_i + α(d - y)x_i,  θ = θ - α(d - y)
        double error = d[idx] - y;
        for (int j = 0; j < n; j++) {
            w[j] = w[j] + alpha * error * x[idx][j];
        }
        theta = theta - alpha * error;
    }

    printf("\n================ 答え ================\n");
    printf("学習後の 重み と 閾値 (w1 ... wn θ):\n");
    for (int i = 0; i < n; i++) {
        printf("%.4f ", w[i]);
    }
    printf("%.4f\n", theta);
    printf("======================================\n");
}

// ==========================================
// メイン関数（メニュー画面）
// ==========================================
extern "C" void run_neural_network() {
    int mode;

    while (1) {
        printf("\n========================================\n");
        printf(" 【ニューラルネットワーク】解きたい問題を選んでください\n");
        printf("  1: 出力の計算（活性化関数に通す前の値・ステップ・シグモイド）\n");
        printf("  2: 閾値の逆算（出力が0.5ぴったりになる問題）\n");
        printf("  3: パーセプトロンの学習（1回学習〜複数回学習）\n");
        printf("  0: メインメニューに戻る\n");
        printf("========================================\n");
        printf("選択: ");

        if (scanf("%d", &mode) != 1) break;

        if (mode == 0) {
            printf("メインメニューに戻ります。\n");
            break;
        }
        else if (mode == 1) {
            run_feedforward();
        }
        else if (mode == 2) {
            run_inverse_sigmoid();
        }
        else if (mode == 3) {
            run_learning();
        }
        else {
            printf("正しい番号を入力してください。\n");
        }
    }
}