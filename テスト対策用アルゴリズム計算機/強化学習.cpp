#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define ALPHA 0.5   // 学習率
#define GAMMA 1.0   // 割引率

// ユーザーに入力を求める関数
void input_initial_values(double initial_S[]) {
    printf("初期状態の価値を入力してください（例: 3 13 33 43 73）:\n");
    for (int i = 1; i <= 5; i++) {
        printf("S%d: ", i);
        scanf("%lf", &initial_S[i]);
    }
}

// 状態価値関数を初期化（セット）する関数
void init_values(double V[], double initial_S[]) {
    V[0] = 0.0;   // G1 (初期値 0)
    V[6] = 100.0; // G2 (図にある通り +100点に固定)

    // ユーザーが最初に入力した値を配列にコピー
    for (int i = 1; i <= 5; i++) {
        V[i] = initial_S[i];
    }
}

// 1エピソードを実行する関数
void run_episode(double V[]) {
    // S3(3) -> S2(2) -> S1(1) -> S2(2) -> S3(3) -> S4(4) -> S5(5) -> G2(6)
    int path[] = { 3, 2, 1, 2, 3, 4, 5, 6 };
    int path_length = 8;

    for (int i = 0; i < path_length - 1; i++) {
        int s = path[i];     // 現在の状態
        int s_next = path[i + 1]; // 次の状態

        double reward = 0.0;
        
        // TD誤差の計算 ( reward(0) + 1.0 * V[s_next] - V[s] )
        double td_error = reward + GAMMA * V[s_next] - V[s];

        // 状態価値の更新
        V[s] = V[s] + ALPHA * td_error;
    }
}

int main() {
    double V[7];
    double initial_S[6]; // ユーザーが入力した初期値を一時保存する配列

    // 最初に1回だけユーザーに入力を求める
    input_initial_values(initial_S);
    printf("\n");

    // --- 問題1のシミュレーション ---
    init_values(V, initial_S);
    run_episode(V);

    printf("--- 問題1の答え (1回移動後のS1~S5) ---\n");
    printf("%.4f %.4f %.4f %.4f %.4f\n\n", V[1], V[2], V[3], V[4], V[5]);


    // --- 問題2のシミュレーション ---
    init_values(V, initial_S);

    // 収束するまで（100回など）エピソードを繰り返す
    for (int episode = 0; episode < 100; episode++) {
        run_episode(V);
    }

    printf("--- 問題2の答え (無限回繰り返した後のS1) ---\n");
    printf("%.4f\n", V[1]);

    return 0;
}