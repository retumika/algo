#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// ==========================================
// 1. TD学習（状態価値Vの更新）用の関数
// ==========================================
void run_td_learning() {
    double alpha, gamma;
    double V[7], initial_S[6];
    int path_len;
    int path[100];
    int repeats;

    printf("\n【1. TD学習モード】\n");
    printf("学習率αを入力してください (例: 0.1): ");
    scanf("%lf", &alpha);
    printf("割引率γを入力してください (例: 0.9 または 1.0): ");
    scanf("%lf", &gamma);

    printf("初期状態の価値を入力してください (S1〜S5):\n");
    for (int i = 1; i <= 5; i++) {
        printf("  S%d: ", i);
        scanf("%lf", &initial_S[i]);
    }

    printf("\n移動する状態の「数」を入力してください。\n");
    printf(" (例: S3からS4への1回移動なら「2」、S3->S2->S1...G2の移動なら「8」): ");
    scanf("%d", &path_len);

    printf("移動の順番をスペース区切りで入力してください (G1=0, S1=1, ..., S5=5, G2=6)\n");
    printf(" (例: S3からS4なら「3 4」、問題2の経路なら「3 2 1 2 3 4 5 6」): ");
    for (int i = 0; i < path_len; i++) {
        scanf("%d", &path[i]);
    }

    printf("\nこの移動を何回繰り返しますか？\n");
    printf(" (例: 1回だけなら「1」、無限回(収束)なら「1000」など): ");
    scanf("%d", &repeats);

    // 初期化
    V[0] = 0.0;     // G1
    V[6] = 100.0;   // G2 (+100点)
    for (int i = 1; i <= 5; i++) V[i] = initial_S[i];

    // TD学習の実行
    for (int r = 0; r < repeats; r++) {
        for (int i = 0; i < path_len - 1; i++) {
            int s = path[i];
            int s_next = path[i + 1];
            double reward = 0.0; // 移動中の報酬は0（G2の価値100を直接参照する）

            // TD更新式: V(S) = V(S) + α * (R + γ * V(S') - V(S))
            V[s] = V[s] + alpha * (reward + gamma * V[s_next] - V[s]);
        }
    }

    printf("\n================ 答え ================\n");
    if (path_len == 2 && repeats == 1) {
        printf("移動後の 状態 S%d の価値: %.4f\n", path[0], V[path[0]]);
    }
    else if (repeats > 1) {
        printf("無限回繰り返した後の 状態 S1 の価値: %.4f\n", V[1]);
    }
    else {
        printf("移動後の S1〜S5 の価値: %.4f %.4f %.4f %.4f %.4f\n", V[1], V[2], V[3], V[4], V[5]);
    }
    printf("======================================\n");
}


// ==========================================
// 2. Q学習（行動価値Qの更新）用の関数
// ==========================================
void run_q_learning() {
    double alpha, gamma;
    double Q[7][2]; // [状態0〜6][行動0:左, 1:右]

    printf("\n【2. Q学習モード】\n");
    printf("学習率αを入力してください (例: 0.1): ");
    scanf("%lf", &alpha);
    printf("割引率γを入力してください (例: 0.9): ");
    scanf("%lf", &gamma);

    printf("初期の行動価値(Q値)を入力してください:\n");
    Q[0][0] = 0.0; Q[0][1] = 0.0; // G1
    Q[6][0] = 0.0; Q[6][1] = 0.0; // G2
    for (int i = 1; i <= 5; i++) {
        printf("  S%d [左]へ行く行動: ", i);
        scanf("%lf", &Q[i][0]);
        printf("  S%d [右]へ行く行動: ", i);
        scanf("%lf", &Q[i][1]);
    }

    int target_state, action_type;
    printf("\n更新を行いたい現在の状態を入力してください (1〜5): ");
    scanf("%d", &target_state);

    printf("どのように行動しますか？ (0: 左へ行く, 1: 右へ行く, 2: グリーディ方策に従う): ");
    scanf("%d", &action_type);

    int action = action_type;
    // グリーディ方策（最大Q値の行動を選ぶ）
    if (action_type == 2) {
        action = (Q[target_state][0] > Q[target_state][1]) ? 0 : 1;
        printf(" -> ※現在のQ値に基づき「%s」が選択されました。\n", (action == 0) ? "左" : "右");
    }

    // 移動先の決定と報酬
    int next_state = (action == 0) ? target_state - 1 : target_state + 1;
    double reward = (action == 1 && next_state == 6) ? 100.0 : 0.0;

    // 次の状態の最大Q値の取得
    double max_q_next = 0.0;
    if (next_state != 0 && next_state != 6) {
        max_q_next = (Q[next_state][0] > Q[next_state][1]) ? Q[next_state][0] : Q[next_state][1];
    }

    // Q値の更新
    double current_q = Q[target_state][action];
    double new_q = current_q + alpha * (reward + gamma * max_q_next - current_q);

    printf("\n================ 答え ================\n");
    printf("変化した後の値: %.4f\n", new_q);
    printf("======================================\n");
}


// ==========================================
// 3. εグリーディ方策の確率計算用の関数
// ==========================================
void run_epsilon_greedy() {
    double epsilon;
    double V[7];

    printf("\n【3. εグリーディ方策 確率計算モード】\n");
    printf("ε(イプシロン)の値を入力してください (例: 0.1): ");
    scanf("%lf", &epsilon);

    printf("現在の状態価値を入力してください (S1〜S5):\n");
    V[0] = 0.0;     // G1
    V[6] = 100.0;   // G2
    for (int i = 1; i <= 5; i++) {
        printf("  S%d: ", i);
        scanf("%lf", &V[i]);
    }

    int current_state, target_state;
    printf("\nエージェントが現在いる状態を入力してください (1〜5): ");
    scanf("%d", &current_state);
    printf("移動先の状態を入力してください (例: S1なら「1」): ");
    scanf("%d", &target_state);

    // 左右の価値を比較
    double v_left = V[current_state - 1];
    double v_right = V[current_state + 1];

    // 目的の移動先が左か右か判定
    int is_target_left = (target_state < current_state);
    double probability = 0.0;

    if (v_left > v_right) {
        // 左の価値が高い場合
        probability = is_target_left ? (1.0 - epsilon / 2.0) : (epsilon / 2.0);
    }
    else if (v_left < v_right) {
        // 右の価値が高い場合
        probability = is_target_left ? (epsilon / 2.0) : (1.0 - epsilon / 2.0);
    }
    else {
        // 価値が同じ場合はランダム(50%)
        probability = 0.5;
    }

    printf("\n================ 答え ================\n");
    printf("状態S%d に移動する確率: %.4f\n", target_state, probability);
    printf("======================================\n");
}


// ==========================================
// メイン関数（メニュー画面）
// ==========================================
int main() {
    int mode;

    while (1) {
        printf("\n========================================\n");
        printf(" 解きたい問題の番号を選んでください\n");
        printf("  1: TD学習（状態価値の更新）\n");
        printf("  2: Q学習 （行動価値の更新）\n");
        printf("  3: εグリーディ方策（移動確率の計算）\n");
        printf("  0: プログラムを終了する\n");
        printf("========================================\n");
        printf("選択: ");

        if (scanf("%d", &mode) != 1) break;

        if (mode == 0) {
            printf("終了します。\n");
            break;
        }
        else if (mode == 1) {
            run_td_learning();
        }
        else if (mode == 2) {
            run_q_learning();
        }
        else if (mode == 3) {
            run_epsilon_greedy();
        }
        else {
            printf("正しい番号を入力してください。\n");
        }
    }

    return 0;
}