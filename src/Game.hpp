// Defines the main frame
const int cellSize = 20;
const int cellWidthCount = 60;
const int cellHeightCount = 40;
const int offset = 60;
const int screenWidth = cellSize * cellWidthCount;
const int screenHeight = cellSize * cellHeightCount + offset;

#include "Food.hpp"
#include "Snake.hpp"

class Game {
public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = false;
    int score = 0;
	int bestScore = 0;
    Sound eatSound;
    Sound wallSound;

    Game() {
		FILE* f = fopen("bestscore.txt", "r+");
        if (f != NULL) {
            fscanf(f, "%d", &bestScore);
            fclose(f);
        }
    }

    ~Game() {
		RecordBestScore();
    }

    void DrawPlay() {
		// Background
        ClearBackground(GREEN);

        // Draw Frame
        DrawRectangleLinesEx(Rectangle{ (float)offset - 5, (float)offset - 5, (float)cellSize * cellWidthCount + 10, (float)cellSize * cellHeightCount + 10 }, 5, DARKBROWN);

        // Name text
        DrawText("Snake", offset - 5, 20, 40, BLACK);

        // Score text
        DrawText(TextFormat("Score: %i", score), offset - 5, offset + cellSize * cellHeightCount + 10, 40, DARKGREEN);

		// Draw game objects
        snake.Draw();
        food.Draw();
    }

    void DrawGameOver() {
        DrawText(TextFormat("Best Score: %i", bestScore), (screenWidth / 2) - 50, screenHeight / 2 - 100, 40, DARKPURPLE);
        DrawText(TextFormat("Your Score: %i", score), (screenWidth / 2) - 50, screenHeight / 2 - 50, 40, DARKPURPLE);
        DrawText("GAME OVER", screenWidth / 2 - 50, screenHeight / 2, 40, RED);
        DrawText("Press Space Key to Restart", screenWidth / 2 - 80, screenHeight / 2 + 50, 20, BLUE);

        if (IsKeyPressed(KEY_SPACE)) {
            this->Reset();
        }
    }

    void Update() {
        if (running) {
            snake.Update();
            CheckCollisionWithFood();
            CheckCollisionWithEdges();
            CheckCollisionWithTail();
        }
    }

    void CheckCollisionWithFood() {
        if (Vector2Equals(snake.body[0], food.position)) {
            food.position = food.GenerateRandomPos(snake.body);
            snake.addSegment = true;
            score++;
        }
    }

    void CheckCollisionWithEdges() {
        if (snake.body[0].x == cellWidthCount || snake.body[0].x == -1) {
            GameOver();
        }
        if (snake.body[0].y == cellHeightCount || snake.body[0].y == -1) {
            GameOver();
        }
    }

    void CheckCollisionWithTail() {
        std::deque<Vector2> headlessBody = snake.body;
        headlessBody.pop_front();
        for (Vector2 part : headlessBody) {
            if (Vector2Equals(snake.body[0], part)) {
                GameOver();
            }
        }
    }

    void Reset() {
        snake.Reset();
        food.position = food.GenerateRandomPos(snake.body);
        score = 0;
        running = true;
	}

    void GameOver() {
        if (score > bestScore) {
            bestScore = score;
		}
        running = false;
    }

    void RecordBestScore() {
		FILE* f = fopen("bestscore.txt", "r+");
        if (f == NULL) {
            f = fopen("bestscore.txt", "w");
            fprintf(f, "%d", bestScore);
            fclose(f);
            return;
		}
        int recordedBest;
        fscanf(f, "%d", &recordedBest);
        if (bestScore > recordedBest) {
            freopen("bestscore.txt", "w", f);
            fprintf(f, "%d", score);
        }
		fclose(f);
	}

    int GetBestScore() {
        if (score > bestScore) {
            bestScore = score;
            return bestScore;
        }
        return bestScore;
    }
};

Game init_game() {
    InitWindow(2 * offset + cellSize * cellWidthCount, 2 * offset + cellSize * cellHeightCount, "Snake");
    SetTargetFPS(60);

    Game game = Game();

    return game;
}

void game_loop(Game game) {
    while (true) {
        BeginDrawing();
		ClearBackground(GREEN);
        DrawText("Press Space Key to Start", screenWidth / 2 - 100, screenHeight / 2, 20, BLUE);
        EndDrawing();
        if (IsKeyPressed(KEY_SPACE)) {
            game.running = true;
            break;
		}
    }
    double lastUpdateTime = 0;
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1) {
            game.snake.direction = { 0, -1 };
        }
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1) {
            game.snake.direction = { 0, 1 };
        }
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1) {
            game.snake.direction = { -1, 0 };
        }
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1) {
            game.snake.direction = { 1, 0 };
        }
		// Update game state at fixed intervals
        if (GetTime() - lastUpdateTime > 0.10) {
            game.Update();
            lastUpdateTime = GetTime();
        }

        BeginDrawing();
        game.DrawPlay();
		if (!game.running) game.DrawGameOver();

        EndDrawing();
    }
}
