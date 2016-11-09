//
// breakout.c
//
// Computer Science 50
// Problem Set 3
// Tom Rodrigues tomjrodrigues@gmail.com 31-5-2015

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle width
#define PADWIDTH 80

// paddle height
#define PADHEIGHT 10

// ball diameter
#define BALLDIA 20

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // wait for click before starting
    waitForClick();
    
    // initial xvelocity
    double xvelocity = drand48() * 2;

    // initial yvelocity
    double yvelocity = 2.0;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        /*
        * Update Scoreboard
        */
        updateScoreboard(window, label, points);
      
        /*
        * Regular Ball Movement & Bounce
        */
        move(ball, xvelocity, yvelocity);
        
        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            xvelocity = -xvelocity;
        }
        
        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            xvelocity = -xvelocity;
        }
            
        // bounce off top edge of window
        else if (getY(ball) <=0)
        {
            yvelocity = -yvelocity;
        }
       
        // bounce off bottom edge of window
        else if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            setLocation(ball, WIDTH / 2 - (BALLDIA / 2), HEIGHT / 2 - (BALLDIA / 2));
            setLocation(paddle, WIDTH / 2 - PADWIDTH / 2, HEIGHT - (HEIGHT * .1));
            lives--;
            waitForClick();
        }

        // linger before moving again
        pause(10);
        
        /*
        * Collisions & Bouncing
        */
        GObject object = detectCollision(window, ball);
 
        if (object != NULL)
        {    
            if (object == paddle)
            {
                yvelocity = -yvelocity;
            }
            else if (strcmp(getType(object), "GRect") == 0)
            {
                yvelocity = -yvelocity;
                removeGWindow(window, object);
                bricks--;
                points++;
            }
        }
        
        /*
        * Paddle Movement
        */
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle follows top cursor
                double x = getX(event) - getWidth(paddle) / 2;
                setLocation(paddle, x, (HEIGHT - (HEIGHT * .1)));
            }
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of rainbow bricks.
 */
void initBricks(GWindow window)
{
    for (int i = 0; i < ROWS; i++)
    {
        char* colors[] = {"RED", "ORANGE", "YELLOW", "GREEN", "CYAN"};
        for (int j = 0; j < COLS; j++)
        {
            GRect brick = newGRect(6 + (j * 39), 20 + (14 * i), 35, 10);
            setFilled(brick, true);
            setColor(brick, colors[i]);
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH / 2 - (BALLDIA / 2), HEIGHT / 2 - (BALLDIA / 2), BALLDIA, BALLDIA);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(WIDTH / 2 - PADWIDTH / 2, HEIGHT - (HEIGHT * .1), PADWIDTH, PADHEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "RED");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel(" ");
    setFont(label, "SansSerif-50");
    setColor(label, "BLACK");
    add(window, label);
    
    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
