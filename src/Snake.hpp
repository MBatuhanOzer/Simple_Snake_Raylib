class Snake {
public:
    std::deque<Vector2> body = { Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9} };
	Vector2 direction = { 1, 0 };   
    std::deque<Vector2> inputs;
    bool addSegment = false;

    void Draw() {
        for (unsigned int i = 0; i < body.size(); i++) {
            float x = body[i].x;
            float y = body[i].y;
            Color segmentColor = (i == 0) ? DARKGREEN: DARKGRAY; 
            DrawRectangle(offset + x * cellSize, offset + y * cellSize, cellSize, cellSize, segmentColor);

            DrawRectangleLines(offset + x * cellSize, offset + y * cellSize, cellSize, cellSize, GREEN);
        }
    }

    void Update() {
        if (!inputs.empty()) {
            direction = inputs.front();
            inputs.pop_front();
        }
        body.push_front(Vector2Add(body[0], direction));
        if (addSegment) {
			addSegment = false;
        }
        else {
            body.pop_back();
		}
    }

    void Reset() {
        body = { Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9} };
		inputs.clear();
        direction = {1, 0};
    }
};
