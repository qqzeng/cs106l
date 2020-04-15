#include <iostream>
#include <vector>
#include <deque>
#include <fstream>
#include <time.h>
#include <queue>

using namespace std;


/* Exercises in chapter 5, i.e., STL Sequence Containers. */

/***************************** Snake game implementation based on console. ***************************** */

/* number of food pellets that must be eaten to win. */
const int kMaxFood = 20;

/* time for waiting interval. */
const int kWaitInterval = 0.1; //sec

/* command on windows to clear console. */
const string kClearCommand = "CLS";


/* constants for the different tile types. */
const char kEmptyTile = ' ';
const char kWallTile = '#';
const char kFoodTile = '$';
const char kSnakeTile = '*';

/* the struct encoding a point in a two-dimensional grid. */
struct PointTale {
    int row, col;
};

/* the struct containing relevant game information. */
struct SnakeGame {
    /* activity of range for the snake. */
    vector<string> world;

    /* height and width of the world. */
    int num_rows, num_cols;

    /* the snake implemented based on deque. */
    deque<PointTale> snake;

    /* number of points being eaten currently by the snake. */
    int num_eaten;

    /* The current direction of snake. (1,0), (0,1), (-1,0), (0,-1). */
    int dx, dy;
};


/* continue to prompt the use to input the specified file
 * until it being opened successfully. */
void OpenFile(fstream &input) {
    while (true) {
        cout << "Please input the full path name of level information to initialize the game: " << endl;
        string level_info;
        getline(cin, level_info);
        input.open(level_info);
        if (input.fail()) {
            cout << "Error full path name of " << level_info << endl;
            input.clear();
            continue;
        }
        cout << "Open the file successfully." << endl;
        return;
    }
}

/* instantiation of a new point. */
PointTale MakePoint(int row, int col) {
    PointTale pt;
    pt.row = row;
    pt.col = col;
    return pt;
}

void LoadGame(fstream &input, SnakeGame &game) {
    /* load the shape of the world and the head position of the snake. */
    input >> game.num_rows >> game.num_cols;
    game.world.resize(game.num_rows);
    input >> game.dx >> game.dy;

    string dummy; // consume the empty line.
    getline(input, dummy);
    /* load the world information. */
    for (int i = 0; i < game.num_rows; ++i) {
        getline(input, game.world[i]);
        int col = game.world[i].find(kSnakeTile);
        if (col != string::npos) {
            game.snake.push_back(MakePoint(i, col));
        }
    }
    game.num_eaten = 0;
    cout << "Load the game over." << endl;
}

/* initialize some structures about the game. */
void InitializeGame(SnakeGame &game) {
    /* seed the randomizer. */
    srand(static_cast<unsigned int>(time(NULL)));

    fstream input;
    OpenFile(input);
    LoadGame(input, game);

    cout << "Initialize the game over." << endl;
}

/* display the board. */
void PrintWorld(SnakeGame &game) {
    /* clear previous world information. */
//    system(kClearCommand.c_str());
    for (int i = 0; i < game.num_rows; ++i) {
        cout << game.world[i] << endl;
    }
    cout << "Number of eaten food: " << game.num_eaten << endl;
}

/* get next position of head based on current position and direction. */
PointTale GetNextPosition(SnakeGame &game, int dx, int dy) {
    /* get head position. */
    PointTale pt_head = game.snake.front();
    /* get new head position according its current direction vector. */
    /* note to update the position carefully! */
    pt_head.row += dy;
    pt_head.col += dx;
    return pt_head;
}

/* judge whether crashed. */
bool Crashed(PointTale &head, SnakeGame &game) {
    /* crashed by going out the world, hitting the wall or touching its own body. */
    if (head.row < 0 || head.row >= game.num_rows || head.col < 0 || head.col >= game.num_cols)
        return true;
    if (game.world[head.row][head.col] == kWallTile)
        return true;
    if (game.world[head.row][head.col] == kSnakeTile) {
        /* This rules out the situation where the head of the snake just touches the tail of the snake.
         * as this will not caused it to crash.
         * */
        PointTale tail = game.snake.back();
        if (head.row == tail.row && head.col == tail.col) {
            return false;
        }
        return true;
    }
    return false;
}

/* the snake has a chance of #probability to turn direction. */
bool TurnDirectionRandom(double probability) {
    return (rand() / (RAND_MAX + 1.0)) < probability;
}

/* determine the next direction for the snake.*/
void PerformAI(SnakeGame &game) {
    /* probability to turn direction. */
    const double kTurnProb = 0.5;
    /* calculate next position if not turning direction. */
    PointTale pt_next = GetNextPosition(game, game.dx, game.dy);
    /* judge whether hit the wall or need to turn direction explicitly randomly
     * in which situation the snake should turn direction. */
    if (Crashed(pt_next, game) || TurnDirectionRandom(kTurnProb)) {
        int left_dx = -game.dy;
        int left_dy = game.dx;

        int right_dx = game.dy;
        int right_dy = -game.dx;

        PointTale left_pt = GetNextPosition(game, left_dx, left_dy);
        bool can_turn_left = !Crashed(left_pt, game);

        PointTale right_pt = GetNextPosition(game, right_dx, right_dy);
        bool can_turn_right = !Crashed(right_pt, game);

        bool turn_left;
        /* turn left. */
        if (can_turn_left && !can_turn_right) {
            turn_left = true;
        } else if (!can_turn_left && can_turn_right) {
            turn_left = false;
        } else if (can_turn_left && can_turn_right) {
            turn_left = TurnDirectionRandom(0.5);
        } else {
            return; // If we can't turn, don't turn.
        }

        /* update the direction of next move. */
        game.dx = turn_left ? left_dx : right_dx;
        game.dy = turn_left ? left_dy : right_dy;
    }
}

/* produce a random position for the new food.  */
void PlaceFood(SnakeGame &game) {
    while (true) {
        /* produce a random position in the world. */
        int row = rand() % game.num_rows;
        int col = rand() % game.num_cols;
        /* place the food there in case of the specified position being empty. */
        if (game.world[row][col] == kEmptyTile) {
            game.world[row][col] = kFoodTile;
            return;
        }
    }
}

bool MoveSnake(SnakeGame &game) {
    /* obtain the next head position. */
    PointTale next_head = GetNextPosition(game, game.dx, game.dy);
    /* if crashed, then return false to indicate game over.  */
    if (Crashed(next_head, game))
        return false;
    /* judge whether eating a food. */
    bool eat_food = false;
    if (game.world[next_head.row][next_head.col] == kFoodTile)
        eat_food = true;

    /* update the world. */
    game.world[next_head.row][next_head.col] = kSnakeTile;
    if (!eat_food) {
        PointTale pt_tail = game.snake.back();
        game.world[pt_tail.row][pt_tail.col] = kEmptyTile;
    }

    /* snake moves on by one step. */
    game.snake.push_front(next_head);
    if (!eat_food) {
        game.snake.pop_back();
    }

    /* if eating a food successfully, then
     place a new food, and increment the number of food eaten. */
    if (eat_food) {
        ++game.num_eaten;
        PlaceFood(game);
    }
    return true;
}

/* Pause for a specific time interval. */
void Pause() {
    clock_t start_time = clock();
    while (static_cast<double >(clock() - start_time) / CLOCKS_PER_SEC <
           kWaitInterval); // wait until enough time elapsed
}


/* display the result for user. */
void DisplayResult(SnakeGame &game) {
    if (game.num_eaten == kMaxFood) {
        cout << "Success!" << endl;
    } else {
        cout << "Game over! Failed to eat " << kMaxFood << " food." << endl;
    }
}

/* snake game simulation. */
void RunSimulation(SnakeGame &game) {
    /* keep looping until we have win. */
    while (game.num_eaten < kMaxFood) {
        /* display the board. */
        PrintWorld(game);
        /* chose an action by AI. */
        PerformAI(game);
        cout << game.dx << "-" << game.dy << endl;
        /* move the snake and stop if we crashed. */
        if (!MoveSnake(game))
            break;
        /* Pause for a while. */
        Pause();
    }
    /* display the result for user. */
    DisplayResult(game);
}

/* program entry.  Initializes the world, then runs the simulation. */
void SetUp() {
    SnakeGame game;
    InitializeGame(game);
    RunSimulation(game);
}

// F:/workSpaces/cpp/cs106l/chapter_05_STL_Sequence_Containers/level.txt

/**************************************************************************************************/
// Exercise solutions.
/**************************************************************************************************/

/*Exercise 4.*/
/* delete n-th element from vector. */
void DeleteNthElementFromVector(vector<int> &tv, int n) {
    if (n >= tv.size() || n < 0) {
        cerr << "Invalid deleted index." << endl;
        return;
    }
    tv.erase(tv.begin() + n, tv.begin() + n + 1);
}

void TestDelete() {
    vector<int> tv;
    tv.push_back(1);
    tv.push_back(2);
    tv.push_back(3);
    DeleteNthElementFromVector(tv, -1);
    for (size_t i = 0; i < tv.size(); ++i) cout << tv[i] << " ";
    cout << endl;
}


/* Exercise 5. */
vector<string> LinesFromFile(string &file_name) {
    fstream input(file_name);
    if (!input.is_open()) return vector<string>();
    string line;
    vector<string> contents;
    while (getline(input, line)) {
        contents.push_back(line);
    }
    // for test.
    for (size_t i = 0; i < contents.size(); ++i) cout << contents[i] << endl;
    return contents;
}


/* Exercise 6. Insert Sort. (descending order).*/
void InsertSort(vector<int> &values) {
    for (size_t i = 1; i < values.size(); ++i) {
        if (values[i] > values[i - 1]) {
            int tmp = values[i];
            size_t j = i - 1;
            while (j >= 0 && tmp > values[j]) {
                values[j + 1] = values[j];
                --j;
            }
            values[j + 1] = tmp;
        }
    }
}

/* Exercise 6 - Selection Sort. (descending order). */
size_t SelectLargestIndex(size_t i, const vector<int> &values) {
    size_t largest_index = i;
    for (size_t j = i; j < values.size(); ++j) {
        if (values[j] > values[largest_index]) {
            largest_index = j;
        }
    }
    return largest_index;
}

void SelectionSort(vector<int> &values) {
    for (size_t i = 0; i < values.size() - 1; ++i) {
        size_t largest_index = SelectLargestIndex(i, values);
        swap(values[largest_index], values[i]);
    }
}

void TestSort() {
    const size_t kVectorSize = 10;
    vector<int> values(kVectorSize);
    /* seed the randomizer. */
    srand(static_cast<unsigned int>(time(NULL)));
    for (size_t i = 0; i < values.size(); ++i) {
        values[i] = rand() % 100;
    }
    for (size_t i = 0; i < values.size(); ++i) cout << values[i] << " ";
    cout << endl;
//    SelectionSort(values);
    InsertSort(values);
    cout << "After being sorted: " << endl;
    for (size_t i = 0; i < values.size(); ++i) {
        cout << values[i] << " ";
        if (i != values.size() - 1 && values[i] < values[i + 1])
            cerr << "Sorting Error for " \
 << values[i] << " and " << values[i + 1] << endl;
    }
    cout << endl;
}


/* Exercise 7. */
void CursorWrite(int val, deque<int> &ring_buffer) {
    if (!ring_buffer.empty()) {
        ring_buffer[0] = val;
    } else {
        ring_buffer.push_front(val);
    }
}

int CursorRead(deque<int> &ring_buffer) {
    return ring_buffer.front();
}

void CursorClockwise(deque<int> &ring_buffer) {
    int tail = ring_buffer.back();
    ring_buffer.push_front(tail);
    ring_buffer.pop_back();
}

void CursorCounterClockwise(deque<int> &ring_buffer) {
    int head = ring_buffer.front();
    ring_buffer.push_back(head);
    ring_buffer.pop_front();
}

void PrintArray(const deque<int> &values) {
    for (size_t i = 0; i < values.size(); ++i) cout << values[i] << " ";
    cout << endl;
}
void TestRingBuffer() {
    const size_t kVectorSize = 5;
    deque<int> ring_buffer(kVectorSize);
    /* seed the randomizer. */
    srand(static_cast<unsigned int>(time(NULL)));
    for (size_t i = 0; i < kVectorSize; ++i) {
//        CursorWrite(rand() % 100, ring_buffer);
        ring_buffer[i] = rand() % 100;
    }
    PrintArray(ring_buffer);
    CursorClockwise(ring_buffer);
    PrintArray(ring_buffer);
    CursorClockwise(ring_buffer);
    PrintArray(ring_buffer);
    CursorCounterClockwise(ring_buffer);
    PrintArray(ring_buffer);
    CursorWrite(rand() % 100, ring_buffer);
    PrintArray(ring_buffer);
    CursorCounterClockwise(ring_buffer);
    CursorClockwise(ring_buffer);
    CursorClockwise(ring_buffer);
    PrintArray(ring_buffer);
}


/* Exercise 8. */
void GetRandomString(string &s, const int len) {
    srand(static_cast<unsigned int>(time(NULL)));
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

void TestReserve() {
    const int iteration_num = 30000000;
    const int str_num = 15;
    vector<string> vs1; // 15.339
    vector<string> vs2; // 12.945
    vs2.reserve(iteration_num);
    deque<string> deq1; // 13.263
    clock_t start_time = clock();
    for (int i = 0; i < iteration_num; ++i) {
        string s;
        GetRandomString(s, str_num);
        vs2.push_back(s);
    }
    clock_t  end_time = clock();
    cout << "Pushing back " << iteration_num << " elements without calling reserve costs : " << \
         static_cast<double >(end_time-start_time) / CLOCKS_PER_SEC << endl;
}

void VigenereCipher(string &toEncode, queue<int> values)  {
    for(int k = 0; k < toEncode.length(); ++k) {
        toEncode[k] += values.front();
        int key = values.front();
        values.push(key);
        values.pop();
    }
}

void TestVigenereCipherTest(){
    string str = "Thecookiesareinthefridge";
    cout << "String : " << str;
    const int kKeyNumber = 3;
    queue<int> values;
    values.push(1);
    values.push(3);
    values.push(7);
    VigenereCipher(str, values);
    cout << " encoded as : " << str << endl;
}


int main() {
    TestVigenereCipherTest();
//    TestReserve();
//    TestRingBuffer();
//    TestSort();
//    LinesFromFile("F:/workSpaces/cpp/cs106l/chapter_05_STL_Sequence_Containers/level3.txt");
//    TestDelete();
//    SetUp();
    return 0;
}