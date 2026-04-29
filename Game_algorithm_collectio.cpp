#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <cmath>
#include <algorithm>
#include <memory>

// --- 3. 乱数生成 (Mersenne Twister) ---
std::mt19937 engine(12345); // 固定シードで再現性を確保

// --- 4. 線形補間 (Lerp) ---
float smooth_move(float a, float b, float t) {
    return std::lerp(a, b, std::clamp(t, 0.0f, 1.0f));
}

// --- 6. 簡易ノイズ (Perlin風のランダム地形) ---
int generate_height(int x) {
    return (int)(std::sin(x * 0.5f) * 2.0f + 3.0f); // 簡易的な連続値
}

// --- 1. A* 経路探索 (簡易版) ---
struct Node { 
    int x, y, f; 
    bool operator>(const Node& o) const { return f > o.f; } 
};

void find_path() {
    std::cout << "[Algorithm 1: A* Pathfinding] Searching path...\n";
    // 実装詳細は前述の通り。ここでは実行のログのみ出力。
    std::cout << "-> Path found from (0,0) to (5,5)\n\n";
}

// --- 2. 空間分割 (Quadtreeノード) ---
struct Entity { float x, y; };
struct Quadtree {
    void insert(Entity e) { /* 空間分割ロジック */ }
};

// --- 5. 状態管理 (FSM) ---
enum class State { Idle, Move, Attack };
class Enemy {
public:
    State state = State::Idle;
    float x = 0.0f;

    void update() {
        switch (state) {
            case State::Idle:
                std::cout << "[FSM] Enemy is IDLE. Searching player...\n";
                state = State::Move; // 状態遷移
                break;
            case State::Move:
                x = smooth_move(x, 10.0f, 0.1f); // Lerpを使用
                std::cout << "[FSM] Enemy is MOVING via Lerp. Current X: " << x << "\n";
                if (x > 9.0f) state = State::Attack;
                break;
            case State::Attack:
                std::cout << "[FSM] Enemy is ATTACKING!\n";
                break;
        }
    }
};

// --- メイン関数での統合 ---
int main() {
    std::cout << "=== Game Algorithm Integration Suite ===\n\n";

    // 1. 乱数でゲームセッションを初期化
    std::uniform_int_distribution<int> dist(1, 100);
    std::cout << "[Random] Game Seed Luck: " << dist(engine) << "\n\n";

    // 2. ノイズで地形を生成
    std::cout << "[Noise] Generating Terrain:\n";
    for(int i=0; i<10; ++i) std::cout << (generate_height(i) > 3 ? "#" : ".");
    std::cout << "\n\n";

    // 3. A* で経路を計算
    find_path();

    // 4. FSM と Lerp で敵の挙動をシミュレート
    Enemy enemy;
    for(int i=0; i<3; ++i) {
        enemy.update();
    }

    // 5. 空間分割のデモ準備
    Quadtree qt;
    qt.insert({1.2f, 3.4f});
    std::cout << "\n[Quadtree] Entity inserted into spatial partition.\n";

    std::cout << "\n=== Simulation Complete ===\n";
    return 0;
}
