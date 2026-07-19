#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_STATES 100 // 任意に対応できる最大状態数

static void run_td_learning() {
    double alpha, gamma;
    int N;
    double V[MAX_STATES + 2];
    int path_len;
    int path[1000];
    int repeats;

    printf("\n【1. TD学習モード】\n");
    printf("通常状態の数 N を入力してください (S1toSN): ");
    if (scanf("%d", &N) != 1 || N <= 0 || N > MAX_STATES) {
        printf("無効な入力です。\n");
        return;
    }

    printf("学習率αを入力してください (例: 0.1): ");
    scanf("%lf", &alpha);
    printf("割引率γを入力してください (例: 1.0で割引率なし): ");
    scanf("%lf", &gamma);

    printf("初期状態の価値を入力してください (S1 to S%d):\n", N);
    for (int i = 1; i <= N; i++) {
        printf("  S%d: ", i);
        scanf("%lf", &V[i]);
    }

    printf("\n移動する状態の「数」を入力してください。\n");
    printf(" (例: S3からS4への1回移動なら「2」): ");
    scanf("%d", &path_len);

    printf("移動の順番をスペース区切りで入力してください (G1=0, S1=1, ..., S%d=%d, G2=%d)\n", N, N, N + 1);
    for (int i = 0; i < path_len; i++) {
        scanf("%d", &path[i]);
    }

    printf("\nこの移動を何回繰り返しますか？\n");
    scanf("%d", &repeats);

    V[0] = 0.0;
    V[N + 1] = 0.0;

    for (int r = 0; r < repeats; r++) {
        for (int i = 0; i < path_len - 1; i++) {
            int s = path[i];
            int s_next = path[i + 1];
            double reward = (s_next == N + 1) ? 100.0 : 0.0;
            V[s] = V[s] + alpha * (reward + gamma * V[s_next] - V[s]);
        }
    }

    printf("\n================ 答え ================\n");
    printf("移動後の S1toS%d の価値: ", N);
    for (int i = 1; i <= N; i++) {
        printf("%.4f%s", V[i], (i == N) ? "" : " ");
    }
    printf("\n");
    printf("======================================\n");
}

static void run_q_learning() {
    double alpha, gamma;
    int N;
    double Q[MAX_STATES + 2][2];

    printf("\n【2. Q学習モード】\n");
    printf("通常状態の数 N を入力してください (S1toSN): ");
    if (scanf("%d", &N) != 1 || N <= 0 || N > MAX_STATES) {
        printf("無効な入力です。\n");
        return;
    }

    printf("学習率αを入力してください (例: 0.1): ");
    scanf("%lf", &alpha);
    printf("割引率γを入力してください (例: 0.9): ");
    scanf("%lf", &gamma);

    printf("初期の行動価値(Q値)を入力してください:\n");
    Q[0][0] = 0.0; Q[0][1] = 0.0;
    Q[N + 1][0] = 0.0; Q[N + 1][1] = 0.0;

    for (int i = 1; i <= N; i++) {
        printf("  S%d [左]へ行く行動: ", i);
        scanf("%lf", &Q[i][0]);
        printf("  S%d [右]へ行く行動: ", i);
        scanf("%lf", &Q[i][1]);
    }

    int q_mode;
    printf("\nQ学習の種類を選んでください:\n");
    printf("  1: 特定の状態・特定の行動を1ステップだけ更新する\n");
    printf("  2: ゴールに到達するまでグリーディ方策で自動移動・更新する\n");
    printf("選択: ");
    scanf("%d", &q_mode);

    switch (q_mode) {
    case 1: {
        int target_state, action_type;
        printf("\n更新を行いたい現在の状態を入力してください (1 to %d): ", N);
        scanf("%d", &target_state);

        printf("どのように行動しますか？ (0: 左へ行く, 1: 右へ行く, 2: グリーディ方策に従う): ");
        scanf("%d", &action_type);

        int action = action_type;
        if (action_type == 2) {
            action = (Q[target_state][0] > Q[target_state][1]) ? 0 : 1;
            printf(" -> ※現在のQ値に基づき「%s」が選択されました。\n", (action == 0) ? "左" : "右");
        }

        int next_state = (action == 0) ? target_state - 1 : target_state + 1;
        double reward = (action == 1 && next_state == N + 1) ? 100.0 : 0.0;

        double max_q_next = 0.0;
        if (next_state != 0 && next_state != N + 1) {
            max_q_next = (Q[next_state][0] > Q[next_state][1]) ? Q[next_state][0] : Q[next_state][1];
        }

        double current_q = Q[target_state][action];
        Q[target_state][action] = current_q + alpha * (reward + gamma * max_q_next - current_q);

        printf("\n================ 答え ================\n");
        printf("ピンポイントで変化した後の値: %.4f\n", Q[target_state][action]);
        printf("--------------------------------------\n");
        break;
    }
    case 2: {
        int current_state;
        printf("\nスタートする状態を入力してください (例: 3): ");
        scanf("%d", &current_state);

        while (current_state != 0 && current_state != N + 1) {
            int action = (Q[current_state][0] > Q[current_state][1]) ? 0 : 1;
            int next_state = (action == 0) ? current_state - 1 : current_state + 1;
            double reward = (action == 1 && next_state == N + 1) ? 100.0 : 0.0;

            double max_q_next = 0.0;
            if (next_state != 0 && next_state != N + 1) {
                max_q_next = (Q[next_state][0] > Q[next_state][1]) ? Q[next_state][0] : Q[next_state][1];
            }

            double current_q = Q[current_state][action];
            Q[current_state][action] = current_q + alpha * (reward + gamma * max_q_next - current_q);

            current_state = next_state;
        }
        printf("\n================ 答え ================\n");
        break;
    }
    default:
        printf("正しい番号を入力してください。\n");
        break;
    }

    printf("更新後のすべての状態のQ値一覧:\n");
    printf("（コピー用形式: 左S1toSN、次に右S1toSNの順に半角スペース区切り）\n\n");
    for (int i = 1; i <= N; i++) {
        printf("%.4f ", Q[i][0]);
    }
    for (int i = 1; i <= N; i++) {
        printf("%.4f", Q[i][1]);
        if (i < N) printf(" ");
    }
    printf("\n======================================\n");
}

static void run_epsilon_greedy() {
    double epsilon;
    int N;
    double V[MAX_STATES + 2];

    printf("\n【3. εグリーディ方策 確率計算モード】\n");
    printf("通常状態の数 N を入力してください (S1toSN): ");
    if (scanf("%d", &N) != 1 || N <= 0 || N > MAX_STATES) {
        printf("無効な入力です。\n");
        return;
    }

    printf("ε(イプシロン)の値を入力してください (例: 0.1): ");
    scanf("%lf", &epsilon);

    printf("現在の状態価値を入力してください (S1 to S%d):\n", N);
    V[0] = 0.0;
    V[N + 1] = 100.0;
    for (int i = 1; i <= N; i++) {
        printf("  S%d: ", i);
        scanf("%lf", &V[i]);
    }

    int current_state, target_state;
    printf("\nエージェントが現在いる状態を入力してください (1 to %d): ", N);
    scanf("%d", &current_state);
    printf("移動先の状態を入力してください (例: S1なら「1」): ");
    scanf("%d", &target_state);

    double v_left = V[current_state - 1];
    double v_right = V[current_state + 1];

    int is_target_left = (target_state < current_state);
    double probability = 0.0;

    if (v_left > v_right) {
        probability = is_target_left ? (1.0 - epsilon / 2.0) : (epsilon / 2.0);
    }
    else if (v_left < v_right) {
        probability = is_target_left ? (epsilon / 2.0) : (1.0 - epsilon / 2.0);
    }
    else {
        probability = 0.5;
    }

    printf("\n================ 答え ================\n");
    printf("状態S%d に移動する確率: %.4f\n", target_state, probability);
    printf("======================================\n");
}

static void run_greedy_td_simulation() {
    double alpha, gamma;
    int N;
    double V[MAX_STATES + 2];

    printf("\n【4. TD学習 自動グリーディ移動シミュレーション】\n");
    printf("通常状態の数 N を入力してください (S1toSN): ");
    if (scanf("%d", &N) != 1 || N <= 0 || N > MAX_STATES) return;

    printf("学習率αを入力してください (例: 0.1): ");
    scanf("%lf", &alpha);
    printf("割引率γを入力してください (例: 0.9): ");
    scanf("%lf", &gamma);

    printf("現在の状態価値を入力してください (S1 to S%d):\n", N);
    for (int i = 1; i <= N; i++) {
        printf("  S%d: ", i);
        scanf("%lf", &V[i]);
    }

    int current_state;
    printf("\nスタートする状態を入力してください (例: 3): ");
    scanf("%d", &current_state);

    V[0] = 0.0;
    V[N + 1] = 0.0;

    printf("\n--- 移動ログ ---\n");
    int steps = 0;
    while (current_state != 0 && current_state != N + 1 && steps < 1000) {

        double reward_left = (current_state - 1 == 0) ? 0.0 : 0.0;
        double v_next_left = (current_state - 1 == 0) ? 0.0 : V[current_state - 1];
        double q_left = reward_left + gamma * v_next_left;

        double reward_right = (current_state + 1 == N + 1) ? 100.0 : 0.0;
        double v_next_right = (current_state + 1 == N + 1) ? 0.0 : V[current_state + 1];
        double q_right = reward_right + gamma * v_next_right;

        int next_state = (q_left > q_right) ? current_state - 1 : current_state + 1;
        double reward = (next_state == current_state - 1) ? reward_left : reward_right;
        double v_next = (next_state == current_state - 1) ? v_next_left : v_next_right;

        if (next_state == 0) {
            printf("ステップ %d: S%d ➔ G1 (報酬: %.1f)\n", steps + 1, current_state, reward);
        }
        else if (next_state == N + 1) {
            printf("ステップ %d: S%d ➔ G2 (報酬: %.1f)\n", steps + 1, current_state, reward);
        }
        else {
            printf("ステップ %d: S%d ➔ S%d (報酬: %.1f)\n", steps + 1, current_state, next_state, reward);
        }

        V[current_state] = V[current_state] + alpha * (reward + gamma * v_next - V[current_state]);

        current_state = next_state;
        steps++;
    }

    printf("\n================ 答え ================\n");
    printf("ゴール到達後の S1toS%d の状態価値関数:\n", N);
    for (int i = 1; i <= N; i++) {
        printf("%.4f%s", V[i], (i == N) ? "" : " ");
    }
    printf("\n======================================\n");
}

extern "C" void run_reinforcement_learning() {
    int mode;
    while (1) {
        printf("\n========================================\n");
        printf(" 解きたい問題の番号を選んでください\n");
        printf("  1: TD学習（指定ルートで状態価値更新）\n");
        printf("  2: Q学習 （行動価値の更新）\n");
        printf("  3: εグリーディ方策（移動確率の計算）\n");
        printf("  4: TD学習（自動グリーディ移動・ゴールまで更新）\n");
        printf("  0: プログラムを終了する\n");
        printf("========================================\n");
        printf("選択: ");

        if (scanf("%d", &mode) != 1) {
            while (getchar() != '\n'); // 入力エラー時におかしくなるのを防ぐ
            printf("数値を入力してください。\n");
            continue;
        }

        if (mode == 0) {
            printf("終了します。\n");
            break;
        }

        switch (mode) {
        case 1:
            run_td_learning();
            break;
        case 2:
            run_q_learning();
            break;
        case 3:
            run_epsilon_greedy();
            break;
        case 4:
            run_greedy_td_simulation();
            break;
        default:
            printf("正しい番号を入力してください。\n");
            break;
        }
    }
}