#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

// 各ファイルで書き換えた関数を「使うよ」と宣言する（プロトタイプ宣言）
extern "C" { // C言語ベースで書かれている場合の互換性担保
    void run_genetic_algorithm();
    void run_neural_network();
    void run_tsp();
    void run_reinforcement_learning();
    void run_gradient_descent();
}

int main() {
    // 日本語の文字化け対策（Windows環境用）
    std::clog.rdbuf(nullptr); 
    
    int choice;

    while (true) {
        std::cout << "\n========================================\n";
        std::cout << " 実行したいアルゴリズムを選択してください\n";
        std::cout << "  1: 遺伝的アルゴリズム (genetic-algorithm.cpp)\n";
        std::cout << "  2: ニューラルネットワーク (Neural-Network.cpp)\n";
        std::cout << "  3: 巡回セールスマン問題 (巡回セールスマン.cpp)\n";
        std::cout << "  4: 強化学習 (強化学習.cpp)\n";
        std::cout << "  5: 最急降下法 (最急降下法.cpp)\n";
        std::cout << "  0: プログラムを終了する\n";
        std::cout << "========================================\n";
        std::cout << "選択: ";
        
        if (!(std::cin >> choice)) {
            break; // 数値以外が入力されたら安全に終了
        }

        if (choice == 0) {
            std::cout << "プログラムを終了します。\n";
            break;
        }

        std::cout << "\n----------------------------------------\n";
        switch (choice) {
            case 1:
                run_genetic_algorithm();
                break;
            case 2:
                run_neural_network();
                break;
            case 3:
                run_tsp();
                break;
            case 4:
                run_reinforcement_learning();
                break;
            case 5:
                run_gradient_descent();
                break;
            default:
                std::cout << "正しい番号（0to5）を入力してください。\n";
                break;
        }
        std::cout << "----------------------------------------\n";
    }

    return 0;
}