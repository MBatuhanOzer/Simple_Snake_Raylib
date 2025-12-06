class Food {
public:
    Vector2 position;
    Texture2D texture;

    Food(std::deque<Vector2> snakeBody) {
        position = GenerateRandomPos(snakeBody);
    }

    void Draw() {
        DrawRectangle(offset + position.x * cellSize, offset + position.y * cellSize, cellSize, cellSize, RED);
    }

    Vector2 GenerateRandomPos(std::deque<Vector2> snakeBody) {
        Vector2 pos;
        while (true) {
            float x = GetRandomValue(0, cellWidthCount - 1);
            float y = GetRandomValue(0, cellHeightCount - 1);
            pos = { x, y };

            bool onSnake = false;
            for (Vector2 part : snakeBody) {
                if (Vector2Equals(part, pos)) {
                    onSnake = true;
                    break;
                }
            }
            if (!onSnake) return pos;
        }
        return pos;
    }
};