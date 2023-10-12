#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int CARROM_PIECE_SIZE = 42;
const int STRIKER_PIECE_SIZE = 50;
SDL_Rect border;
const int GAME_BORDER = 53;
const int POCKET_WIDTH = 45;
const int pieceSize = CARROM_PIECE_SIZE;
const int centerOffset = (SCREEN_WIDTH - pieceSize) / 2;

#include <cmath>

// Maths
// Vector
template <typename T>
class Vector
{
public:
    T x, y;
    T i, j;

    Vector() : x(0), y(0)
    {
        calculateUnitVector();
    }

    Vector(T a, T b) : x(a), y(b)
    {
        calculateUnitVector();
    }

    // Calculate the magnitude of the vector
    T magnitude() const
    {
        return sqrt(x * x + y * y);
    }

    // Normalize the vector
    Vector<T> normalized() const
    {
        T mag = magnitude();
        if (mag != 0)
            return Vector<T>(x / mag, y / mag);
        else
            return *this; // Return as is (avoid division by zero)
    }

    // Overload the addition operator for vector addition
    Vector<T> operator+(const Vector<T> &other) const
    {
        return Vector<T>(x + other.x, y + other.y);
    }

    // Overload the subtraction operator for vector subtraction
    Vector<T> operator-(const Vector<T> &other) const
    {
        return Vector<T>(x - other.x, y - other.y);
    }

private:
    // Calculate unit vector components
    void calculateUnitVector()
    {
        T mag = magnitude();
        if (mag != 0)
        {
            i = x / mag;
            j = y / mag;
        }
        else
        {
            i = 0;
            j = 0;
        }
    }
};
// Scalar multiplication of a vector
template <typename T>
Vector<T> operator*(const Vector<T> &v, T scalar)
{
    return Vector<T>(v.x * scalar, v.y * scalar);
}
// Scalar multiplication of a vector (reverse order)
template <typename T>
Vector<T> operator*(T scalar, const Vector<T> &v)
{
    return v * scalar;
}
template <typename T>
T operator*(const Vector<T> &u, const Vector<T> &v)
{
    return (u.x * v.x + u.y * v.y);
}

template <class T>
void border_collision_checker(T &carromPiece);

// Carrom Pieces
class CarromPiece
{
public:
    int score;
    SDL_Surface *imageSurface;
    SDL_Rect positionRect;
    Vector<int> pieceVelocity;
    SDL_Renderer *rend;
    double radius = (CARROM_PIECE_SIZE / 2.0);
    bool displayPiece;
    bool moving = false;

    CarromPiece() {}

    virtual void initialize()
    {
        // Initial position of the image
        positionRect.x = 0;                 // Center horizontally
        positionRect.y = 0;                 // Center vertically
        positionRect.w = CARROM_PIECE_SIZE; // Width of the rendered image
        positionRect.h = CARROM_PIECE_SIZE; // Height of the rendered image
    }

    virtual void initialize(SDL_Rect destinationRect)
    {
        // Initial position of the image
        positionRect.x = destinationRect.x; // Center horizontally
        positionRect.y = destinationRect.y; // Center vertically
        positionRect.w = destinationRect.w; // Width of the rendered image
        positionRect.h = destinationRect.h; // Height of the rendered image
    }

    template <class T>
    void setPosition(Vector<T> v)
    {
        positionRect.x = v.x; // Center horizontally
        positionRect.y = v.y; // Center vertically
    }

    template <typename T>
    void updatePosition(Vector<T> v)
    {
        positionRect.x += v.x; // Center horizontally
        positionRect.y += v.y; // Center vertically
    }

    void setVelocity()
    {
        pieceVelocity.x = 0;
        pieceVelocity.y = 0;
    }

    template <class T>
    void setVelocity(Vector<T> velocity)
    {
        pieceVelocity.x = int(velocity.x);
        pieceVelocity.y = int(velocity.y);
    }

    bool CheckCollision(const CarromPiece &other) const
    {
        if (displayPiece == true && other.displayPiece == true)
        {
            return (positionRect.x < other.positionRect.x + 45 &&
                    positionRect.x + 45 > other.positionRect.x &&
                    positionRect.y < other.positionRect.y + 45 &&
                    positionRect.y + 45 > other.positionRect.y);
        }
        return false;
    }

    void HandleCollision(CarromPiece &other)
    {
        border_collision_checker(*this);
        border_collision_checker(other);
        if (CheckCollision(other))
        {
            // Calculate the overlap between entities
            float overlapX = (positionRect.x + positionRect.w / 2) - (other.positionRect.x + other.positionRect.w / 2);
            float overlapY = (positionRect.y + positionRect.h / 2) - (other.positionRect.y + other.positionRect.h / 2);

            // Separate the entities based on the overlap
            if (std::abs(overlapX) > std::abs(overlapY))
            {
                positionRect.x += overlapX > 0 ? 1.0f : -1.0f;
                other.positionRect.x -= overlapX > 0 ? 1.0f : -1.0f;
            }
            else
            {
                positionRect.y += overlapY > 0 ? 1.0f : -1.0f;
                other.positionRect.y -= overlapY > 0 ? 1.0f : -1.0f;
            }

            // Swap velocities to simulate elastic collision
            std::swap(pieceVelocity.x, other.pieceVelocity.x);
            std::swap(pieceVelocity.y, other.pieceVelocity.y);
        }
    }

    bool CheckPocket() const
    {
        return (((positionRect.x < GAME_BORDER + POCKET_WIDTH - CARROM_PIECE_SIZE * 1 / 2) && (positionRect.y < GAME_BORDER + POCKET_WIDTH - CARROM_PIECE_SIZE * 1 / 2)) ||                               // Top Left
                ((positionRect.x < GAME_BORDER + POCKET_WIDTH - CARROM_PIECE_SIZE * 1 / 2) && (positionRect.y > SCREEN_HEIGHT - GAME_BORDER - POCKET_WIDTH - CARROM_PIECE_SIZE * 1 / 2)) ||               // Bottom Left
                ((positionRect.x > SCREEN_WIDTH - GAME_BORDER - POCKET_WIDTH - CARROM_PIECE_SIZE * 1 / 2) && (positionRect.y < GAME_BORDER + POCKET_WIDTH - CARROM_PIECE_SIZE * 1 / 2)) ||                // Top Right
                ((positionRect.x > SCREEN_WIDTH - GAME_BORDER - POCKET_WIDTH - CARROM_PIECE_SIZE * 1 / 2) && (positionRect.y > SCREEN_HEIGHT - GAME_BORDER - POCKET_WIDTH - CARROM_PIECE_SIZE * 1 / 2))); // Bottom Left
    }

    void Update()
    {
        if (pieceVelocity.x != 0 && pieceVelocity.y != 0)
        {
            moving = true;
        }
        else
        {
            moving = false;
        }
    }

    void HandlePocket()
    {
        if (CheckPocket())
        {
            displayPiece = false;
        }
    }

    // void updatescore();
};
class Striker : public CarromPiece
{
public:
    SDL_Texture *imageTexture;
    Striker(SDL_Renderer &renderer, bool display = true)
    {
        radius = STRIKER_PIECE_SIZE / 2.0;
        displayPiece = display;
        initialize(renderer);
        setVelocity();
    }
    Striker(SDL_Renderer &renderer, Vector<int> strikerVelocity, bool display = true)
    {
        radius = STRIKER_PIECE_SIZE / 2.0;
        displayPiece = display;
        initialize(renderer);
        setVelocity(strikerVelocity);
    }
    void initialize(SDL_Renderer &renderer)
    {
        imageSurface = IMG_Load("assets/striker.png");
        if (!imageSurface)
        {
            printf("Image could not be loaded! SDL_Error: %s\n", IMG_GetError());
            return;
        }
        imageTexture = SDL_CreateTextureFromSurface(&renderer, imageSurface);
        SDL_FreeSurface(imageSurface);
        // Initial position of the image
        positionRect.x = SCREEN_WIDTH / 2 - 45 / 2; // Center horizontally
        positionRect.y = 20;                        // Center vertically
        positionRect.w = STRIKER_PIECE_SIZE;        // Width of the rendered image
        positionRect.h = STRIKER_PIECE_SIZE;        // Height of the rendered image
    }
};
class White : public CarromPiece
{
public:
    // foul record
    static bool myFoul;
    // turn
    static bool myTurn;
    static int myScore;
    static bool myGame;
    static bool queenavailable;
    // value , total and remaining white pieces
    const int value = 20;
    const int total = 9;
    static int remaining;

    SDL_Texture *imageTexture;
    White(SDL_Renderer &renderer, bool display = true)
    {
        displayPiece = display;
        initialize(renderer);
        setVelocity();
    }
    White(SDL_Renderer &renderer, Vector<int> strikerVelocity, bool display = true)
    {
        displayPiece = display;
        initialize(renderer);
        setVelocity(strikerVelocity);
    }
    void initialize(SDL_Renderer &renderer)
    {
        imageSurface = IMG_Load("assets/white.png");
        if (!imageSurface)
        {
            printf("Image could not be loaded! SDL_Error: %s\n", IMG_GetError());
            return;
        }
        imageTexture = SDL_CreateTextureFromSurface(&renderer, imageSurface);
        SDL_FreeSurface(imageSurface);
        // Initial position of the image
        positionRect.x = SCREEN_WIDTH / 2 - 45 / 2;  // Center horizontally
        positionRect.y = SCREEN_HEIGHT / 2 - 45 / 2; // Center vertically
        positionRect.w = CARROM_PIECE_SIZE;          // Width of the rendered image
        positionRect.h = CARROM_PIECE_SIZE;          // Height of the rendered image
    }
};
class Black : public CarromPiece
{
public:
    // record foul
    static bool myFoul;
    // turn
    static bool myTurn;
    // avaible queen
    static int myScore;
    static bool myGame;
    static bool queenavailable;
    // value, remaining, total
    const int value = 20;
    const int total = 9;
    static int remaining;

    SDL_Texture *imageTexture;
    Black(SDL_Renderer &renderer, bool display = true)
    {
        displayPiece = display;
        initialize(renderer);
        setVelocity();
    }
    Black(SDL_Renderer &renderer, Vector<int> strikerVelocity, bool display = true)
    {
        displayPiece = display;
        initialize(renderer);
        setVelocity(strikerVelocity);
    }
    void initialize(SDL_Renderer &renderer)
    {
        imageSurface = IMG_Load("assets/black.png");
        if (!imageSurface)
        {
            printf("Image could not be loaded! SDL_Error: %s\n", IMG_GetError());
            return;
        }
        imageTexture = SDL_CreateTextureFromSurface(&renderer, imageSurface);
        SDL_FreeSurface(imageSurface);
        // Initial position of the image
        positionRect.x = SCREEN_WIDTH - 100;  // Center horizontally
        positionRect.y = SCREEN_HEIGHT - 100; // Center vertically
        positionRect.w = CARROM_PIECE_SIZE;   // Width of the rendered image
        positionRect.h = CARROM_PIECE_SIZE;   // Height of the rendered image
    }
};
class Queen : public CarromPiece
{
public:
    bool queenAvailable = false;
    SDL_Texture *imageTexture;
    Queen(SDL_Renderer &renderer, bool display = true)
    {
        displayPiece = display;
        initialize(renderer);
        setVelocity();
    }
    Queen(SDL_Renderer &renderer, Vector<int> strikerVelocity, bool display = true)
    {
        displayPiece = display;
        initialize(renderer);
        setVelocity(strikerVelocity);
    }
    void initialize(SDL_Renderer &renderer)
    {
        imageSurface = IMG_Load("assets/queen.png");
        if (!imageSurface)
        {
            printf("Image could not be loaded! SDL_Error: %s\n", IMG_GetError());
            return;
        }
        imageTexture = SDL_CreateTextureFromSurface(&renderer, imageSurface);
        SDL_FreeSurface(imageSurface);
        // Initial position of the image
        positionRect.x = SCREEN_WIDTH - 200;  // Center horizontally
        positionRect.y = SCREEN_HEIGHT - 200; // Center vertically
        positionRect.w = CARROM_PIECE_SIZE;   // Width of the rendered image
        positionRect.h = CARROM_PIECE_SIZE;   // Height of the rendered image
    }
};
// foul
bool White::myFoul = false;
bool Black::myFoul = false;
// Turn selection
bool White::myTurn = true;
bool Black::myTurn = false;
// score
int White::remaining = 9;
int Black::remaining = 9;
// queen avaibalility
bool White::queenavailable = false;
bool Black::queenavailable = false;
// gameover
bool White::myGame = false;
bool Black::myGame = false;
// score initialization
int White::myScore = 0;
int Black::myScore = 0;

template <class T, class U, class V, class W>
void check_pieces(T &striker, U &queen, V &white, W &black, SDL_Renderer *ren)
{
    int testwhite = 0;
    int testblack = 0;
    SDL_Rect newPiecePos{SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 200, CARROM_PIECE_SIZE, CARROM_PIECE_SIZE};
    for (int i = 0; i < 9; i++)
    {
        if (white[i].CheckPocket())
        {
            testwhite += 1;
        }

        if (black[i].CheckPocket())
        {
            testblack += 1;
        }
    }
    White::remaining -= testwhite;
    Black::remaining -= testblack;

    if (striker.CheckPocket())
    {
        if (White::myTurn)
        {
            White::myFoul = true;
            if (White::remaining < 9)
            {
                White::remaining += 1;
                for (int i = 0; i < 9; i++)
                {
                    if (!white[i].displayPiece)
                    {
                        white[i].displayPiece = true;
                        white[i].setPosition(Vector<int>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
                        i = 9;
                        break;
                    }
                }
                White::myFoul = false;
            }
        }
        if (Black::myTurn)
        {
            Black::myFoul = true;
            if (Black::remaining < 9)
            {
                Black::remaining += 1;
                for (int i = 0; i < 9; i++)
                {
                    if (!black[i].displayPiece)
                    {
                        black[i].displayPiece = true;
                        black[i].setPosition(Vector<int>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
                        i = 9;
                        break;
                    }
                }

                Black::myFoul = false;
            }
        }
    }

    // queen pocketing check

    if (queen.CheckPocket())
    {
        if (White::myTurn)
        {
            if (!White::queenavailable)
            {
                White::myFoul = true;
                if (White::remaining < 9)
                {
                    White::remaining += 1;
                    for (int i = 0; i < 9; i++)
                    {
                        if (!white[i].displayPiece)
                        {
                            white[i].displayPiece = true;
                            white[i].setPosition(Vector<int>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
                            i = 9;
                            break;
                        }
                    }
                    White::myFoul = false;
                    queen.displayPiece = true;
                    queen.setPosition(Vector<int>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
                }
            }
            else
            {
                for (int i = 0; i < 9; i++)
                {
                    if (white[i].CheckPocket())
                    {
                        if (i == 8)
                            White::myGame = true;

                        continue;
                    }
                    else
                    {
                        queen.displayPiece = true;
                        queen.setPosition(Vector<int>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
                        break;
                    }
                }
            }
        }
        if (Black::myTurn)
        {
            if (!Black::queenavailable)
            {
                Black::myFoul = true;
                if (Black::remaining < 9)
                {
                    Black::remaining += 1;
                    for (int i = 0; i < 9; i++)
                    {
                        if (!black[i].displayPiece)
                        {
                            black[i].displayPiece = true;
                            black[i].setPosition(Vector<int>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
                            i = 9;
                            break;
                        }
                    }
                    queen.displayPiece = true;
                    queen.setPosition(Vector<int>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
                    Black::myFoul = false;
                }
            }
            else
            {
                for (int i = 0; i < 9; i++)
                {
                    if (black[i].CheckPocket())
                    {
                        if (i == 8)
                            Black::myGame = true;

                        continue;
                    }
                    else
                    {
                        queen.displayPiece = true;
                        queen.setPosition(Vector<int>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
                        break;
                    }
                }
            }
        }
    }
    if (White::remaining == 1)
        White::queenavailable = true;
    White::remaining = 9;

    if (Black::remaining == 1)
        Black::queenavailable = true;
    Black::remaining = 9;

    if (White::remaining == 0)
        White::myGame = true;
    if (Black::remaining == 0)
        Black::myGame = true;
}

template <class T, class U, class V, class W>
void checkgame(T &striker, U &queen, V &white, W &black, SDL_Renderer *ren)
{
    int turncheck;
    std::cout << "turn :" << White::myTurn << std::endl;

    if (White::queenavailable)
    {
        if (queen.CheckPocket() || !queen.displayPiece)
        {
            check_pieces(striker, queen, white, black, ren);
        }
    }
    if (Black::queenavailable)
    {
        if (queen.CheckPocket() || !queen.displayPiece)
        {
            check_pieces(striker, queen, white, black, ren);
        }
    }
}
// score calc
template <class U, class V, class W>
void scoreCalculation(U &queen, V &white, W &black)
{
    if (White::myGame)
    {
        White::myScore = 5 + Black::remaining - 1;
        std::cout << "my score:" << White::myScore << std::endl;
    }
    if (Black::myGame)
    {
        Black::myScore = 5 + White::remaining - 1;
        std::cout << Black::myScore << std::endl;
        std::cout << "my score:" << White::myScore << std::endl;
    }
}

// Physics
template <class T>
void border_collision_checker(T &carromPiece)
{
    // double momentumLoss = 1;
    // Check for collision with screen edges
    if (carromPiece.positionRect.x <= GAME_BORDER || carromPiece.positionRect.x >= SCREEN_WIDTH - carromPiece.positionRect.w - GAME_BORDER)
    {
        if (carromPiece.positionRect.x < GAME_BORDER)
        {
            carromPiece.positionRect.x = GAME_BORDER;
        }
        else if (carromPiece.positionRect.x > SCREEN_WIDTH - carromPiece.positionRect.w - GAME_BORDER)
        {
            carromPiece.positionRect.x = SCREEN_WIDTH - carromPiece.positionRect.w - GAME_BORDER;
        }
        carromPiece.pieceVelocity.x = -carromPiece.pieceVelocity.x; // Reverse X-axis movement direction and apply momentum loss
    }
    if (carromPiece.positionRect.y <= GAME_BORDER || carromPiece.positionRect.y >= SCREEN_HEIGHT - carromPiece.positionRect.h - GAME_BORDER)
    {
        if (carromPiece.positionRect.y < GAME_BORDER)
        {
            carromPiece.positionRect.y = GAME_BORDER;
        }
        else if (carromPiece.positionRect.y > SCREEN_HEIGHT - carromPiece.positionRect.h - GAME_BORDER)
        {
            carromPiece.positionRect.y = SCREEN_HEIGHT - carromPiece.positionRect.h - GAME_BORDER;
        }
        carromPiece.pieceVelocity.y = -carromPiece.pieceVelocity.y; // Reverse Y-axis movement direction and apply momentum loss
    }
}

template <class T, class U, class V, class W, class X>
void movement(T &carromPiece, U &striker, V &queen, W &white, X &black)
{
    double deceleration = 0.00001;
    // Update image position
    carromPiece.positionRect.x += carromPiece.pieceVelocity.x;
    carromPiece.positionRect.y += carromPiece.pieceVelocity.y;

    // Deceleration
    if (carromPiece.pieceVelocity.x > 0)
        carromPiece.pieceVelocity.x -= deceleration;
    else if (carromPiece.pieceVelocity.x < 0)
        carromPiece.pieceVelocity.x += deceleration;
    if (carromPiece.pieceVelocity.y > 0)
        carromPiece.pieceVelocity.y -= deceleration;
    else if (carromPiece.pieceVelocity.y < 0)
        carromPiece.pieceVelocity.y += deceleration;
}
template <class T, class U, class V, class W, class X>
void collide_and_rebound(T &striker, U &queen, V &white, W &black, X &border)
{
    double deceleration = 0.0001;
    movement(striker, striker, queen, white, black);
    movement(queen, striker, queen, white, black);
    for (int i = 0; i < 9; i++)
    {
        movement(white[i], striker, queen, white, black);
        movement(black[i], striker, queen, white, black);
    }
}

// Making life easier
template <class T>
void render_copy(SDL_Renderer &renderer, T carromPiece)
{
    if (carromPiece.displayPiece == true)
    {
        SDL_Rect destRect = {carromPiece.positionRect.x, carromPiece.positionRect.y, carromPiece.positionRect.w, carromPiece.positionRect.h};
        SDL_RenderCopy(&renderer, carromPiece.imageTexture, NULL, &destRect);
    }
}
template <class T, class U, class V, class W>
void cleanup(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *backgroundImageTexture, T striker, U queen, V white, W black)
{
    for (int i = 0; i < 9; i++)
    {
        SDL_DestroyTexture(black[i].imageTexture);
    }
    for (int i = 0; i < 9; i++)
    {
        SDL_DestroyTexture(white[i].imageTexture);
    }
    SDL_DestroyTexture(queen.imageTexture);
    SDL_DestroyTexture(striker.imageTexture);
    SDL_DestroyTexture(backgroundImageTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Quit SDL_image and SDL
    IMG_Quit();
    SDL_Quit();
}
template <typename T, typename U, typename V, typename W>
void newBoardState(T &striker, U white, V black, W &queen)
{

    striker.setPosition(Vector<float>(centerOffset, SCREEN_HEIGHT - STRIKER_PIECE_SIZE - 115));
    queen.setPosition(Vector<float>(centerOffset, centerOffset));

    Vector<float> whitePositions[9] = {
        Vector<float>(centerOffset - pieceSize * 2, centerOffset - pieceSize * 1.15),
        Vector<float>(centerOffset, centerOffset - pieceSize),
        Vector<float>(centerOffset + pieceSize * 1.75, centerOffset - pieceSize * 1.75),

        Vector<float>(centerOffset - pieceSize, centerOffset),
        Vector<float>(centerOffset - pieceSize * 1.15, centerOffset - pieceSize * 2), // UP ko left ko down
        Vector<float>(centerOffset + pieceSize, centerOffset),

        Vector<float>(centerOffset - pieceSize * 1.75, centerOffset + pieceSize * 1.75),
        Vector<float>(centerOffset, centerOffset + pieceSize),
        Vector<float>(centerOffset + pieceSize * 2, centerOffset)};

    Vector<float> blackPositions[9] = {
        Vector<float>(centerOffset - pieceSize, centerOffset - pieceSize),
        Vector<float>(centerOffset, centerOffset - pieceSize * 2.1),
        Vector<float>(centerOffset + pieceSize, centerOffset - pieceSize),

        Vector<float>(centerOffset - pieceSize * 2, centerOffset),
        Vector<float>(centerOffset + pieceSize * 1.15, centerOffset + pieceSize * 2), // Down ko right ko down
        Vector<float>(centerOffset + pieceSize * 2, centerOffset + pieceSize * 1.15),

        Vector<float>(centerOffset - pieceSize, centerOffset + pieceSize),
        Vector<float>(centerOffset, centerOffset + pieceSize * 2.1),
        Vector<float>(centerOffset + pieceSize, centerOffset + pieceSize)};

    for (int i = 0; i < 9; i++)
    {
        white[i].setPosition(whitePositions[i]);
        black[i].setPosition(blackPositions[i]);
    }
}

template <typename T>
void render_copy_handler(SDL_Renderer &renderer, T carromPiece)
{
    if (carromPiece.displayPiece == true)
    {
        render_copy(renderer, carromPiece);
    }
}

int main(int argc, char *argv[])
{
    /*----------------------------------------SDL INITIALIZATION-------------------------------------------------------*/

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    // Initialize SDL_image
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        printf("SDL_image could not initialize! SDL_Error: %s\n", IMG_GetError());
        return 1;
    }
    // Create a window
    SDL_Window *window = SDL_CreateWindow("Moving Image Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    /*-------------------------------------------BACKGROUND IMAGE----------------------------------------------------*/

    border.x = GAME_BORDER;
    border.y = GAME_BORDER;
    border.w = SCREEN_WIDTH - 2 * GAME_BORDER;
    border.h = SCREEN_HEIGHT - 2 * GAME_BORDER;

    /*-------------------------------------------BACKGROUND IMAGE----------------------------------------------------*/

    // Load the second image using SDL_Image
    SDL_Surface *backgroundImageSurface = IMG_Load("assets/board.jpg");
    if (!backgroundImageSurface)
    {
        printf("Second image could not be loaded! SDL_Error: %s\n", IMG_GetError());
        return 1;
    }

    // Convert the second surface to a texture
    SDL_Texture *backgroundImageTexture = SDL_CreateTextureFromSurface(renderer, backgroundImageSurface);
    SDL_FreeSurface(backgroundImageSurface);

    // Initial position and velocity of the second image
    SDL_Rect backgroundDestinationRect;
    backgroundDestinationRect.x = 0;             // X-coordinate of the second image
    backgroundDestinationRect.y = 0;             // Y-coordinate of the second image
    backgroundDestinationRect.w = SCREEN_WIDTH;  // Width of the second image
    backgroundDestinationRect.h = SCREEN_HEIGHT; // Height of the second image
    // Render the second image at the updated position
    SDL_Rect secondDestRect = {backgroundDestinationRect.x, backgroundDestinationRect.y, backgroundDestinationRect.w, backgroundDestinationRect.h};
    SDL_RenderCopy(renderer, backgroundImageTexture, NULL, &secondDestRect);
    // Update the screen
    SDL_RenderPresent(renderer);

    /*-----------------------------------------BOARD PIECES------------------------------------------------------*/

    Striker striker(*renderer);
    White white[9] = {
        White(*renderer),
        White(*renderer),
        White(*renderer),
        White(*renderer),
        White(*renderer),
        White(*renderer),
        White(*renderer),
        White(*renderer),
        White(*renderer)};
    Black black[9] = {
        Black(*renderer),
        Black(*renderer),
        Black(*renderer),
        Black(*renderer),
        Black(*renderer),
        Black(*renderer),
        Black(*renderer),
        Black(*renderer),
        Black(*renderer)};
    Queen queen(*renderer);

    newBoardState(striker, white, black, queen);

    /*-----------------------------------------------------------------------------------------------*/

    // bool moveImage = false; // Flag to track if image movement should start

    bool quit = false;
    SDL_Event e;
    Vector<float> speed(0, 0);
    Vector<float> delPosition(0, 0);
    Vector<int> mouse(0, 0);

    while (!quit)
    {
        SDL_RenderClear(renderer);
        SDL_Rect secondDestRect = {backgroundDestinationRect.x, backgroundDestinationRect.y, backgroundDestinationRect.w, backgroundDestinationRect.h};
        SDL_RenderCopy(renderer, backgroundImageTexture, NULL, &secondDestRect);
        SDL_GetMouseState(&mouse.x, &mouse.y);

        while (SDL_PollEvent(&e) != 0)
        {

            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {

                SDL_GetMouseState(&mouse.x, &mouse.y);
                float speedFactor = 0.1;

                // Calculate direction and speed based on mouse click position
                delPosition.y = mouse.y - striker.positionRect.y;
                delPosition.x = mouse.x - striker.positionRect.x;
                speed.x = speedFactor * delPosition.x;
                speed.y = speedFactor * delPosition.y;
                striker.setVelocity(speed);
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_r:
                    striker.displayPiece = true;
                    if (White::myTurn)
                    {
                        Black::myTurn = true;
                        White::myTurn = false;
                        striker.setPosition(Vector<float>(centerOffset, SCREEN_HEIGHT - STRIKER_PIECE_SIZE - 115));
                    }
                    else if (Black::myTurn)
                    {

                        Black::myTurn = false;
                        White::myTurn = true;
                        striker.setPosition(Vector<float>(centerOffset, SCREEN_HEIGHT - STRIKER_PIECE_SIZE - 115));
                    }
                    break;

                case SDLK_RIGHT:
                    if (striker.positionRect.x <= SCREEN_WIDTH - 215)
                    {
                        striker.updatePosition(Vector<int>(10, 0));
                    }
                    break;
                case SDLK_LEFT:
                    if (striker.positionRect.x >= 165)
                    {
                        striker.updatePosition(Vector<int>(-10, 0));
                    }
                    break;

                default:
                    break;
                }
            }
        }

        if (true)
        {
            // Clear the renderer

            /*-----------------------------------------------------------------------------------------------*/

            // Board and CarromPieces Collision Rebound and Render the image at the updated position
            // bool moving_check = check_moving(striker, queen, white, black);

            collide_and_rebound(striker, queen, white, black, border);

            // Handle collisions between entities
            striker.HandleCollision(queen);
            for (int i = 0; i < 9; ++i)
            {
                striker.HandleCollision(white[i]);
                striker.HandleCollision(black[i]);
                queen.HandleCollision(white[i]);
                queen.HandleCollision(black[i]);
                for (int j = 0; j < 9; ++j)
                {
                    white[i].HandleCollision(white[j]);
                    black[i].HandleCollision(black[j]);
                    white[i].HandleCollision(black[j]);
                    white[i].HandleCollision(queen);
                    black[i].HandleCollision(queen);
                }
            }

            // Handle Pocketting
            striker.HandlePocket();
            queen.HandlePocket();
            for (int i = 0; i < 9; i++)
            {
                white[i].HandlePocket();
                black[i].HandlePocket();
            }

            // Check moving
            striker.Update();
            queen.Update();
            for (int i = 0; i < 9; i++)
            {
                white[i].Update();
                black[i].Update();
            }

            // Handle Rendering
            render_copy_handler(*renderer, striker);
            render_copy_handler(*renderer, queen);
            for (int i = 0; i < 9; i++)
            {
                render_copy_handler(*renderer, white[i]);
            }
            for (int i = 0; i < 9; i++)
            {
                render_copy_handler(*renderer, black[i]);
            }

            // Calculation score and gameover controlling
            check_pieces(striker, queen, white, black, renderer);
            // checkrgame(striker, queen, white, black, renderer);
            if (White::myGame || Black::myGame)
                scoreCalculation(queen, white, black);

            /*-----------------------------------------------------------------------------------------------*/

            // Drawing line segment with ends (200, 200) and mouse cursor
            // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            // SDL_RenderDrawLine(renderer, (striker.positionRect.x + striker.positionRect.w / 2), (striker.positionRect.y + striker.positionRect.h / 2), (mouse.x), (mouse.y));
            // Update the screen
            SDL_RenderPresent(renderer);
        }

        // Delay to control frame rate
        SDL_Delay(16); // ~60 FPS
    }

    /*-----------------------------------------------------------------------------------------------*/

    // Clean up and close SDL
    cleanup(window, renderer, backgroundImageTexture, striker, queen, white, black);
    return 0;
}