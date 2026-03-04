The book : https://unglueit-files.s3.amazonaws.com/ebf/ee0225ec966b4910a0882f4e388c8bdf.pdf

# SFML and Visual Studio
- First, you must download the SFML SDK from the [download page](https://www.sfml-dev.org/download.php).
![image](https://github.com/user-attachments/assets/13abfba7-11ea-4c75-b7ad-1b21904a2074)
![image](https://github.com/user-attachments/assets/a263ee7a-65e9-4674-8646-0b6292e9c733)

#include <SFML/Graphics.hpp>
```cpp
int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
```
# System module
## Handling time
A sf::Time value can be constructed from different source units: seconds, milliseconds and microseconds.
```cpp
sf::Time t1 = sf::microseconds(10000);
sf::Time t2 = sf::milliseconds(10);
sf::Time t3 = sf::seconds(0.01f);
```
Measuring time :
```cpp
sf::Clock clock; // starts the clock
...
sf::Time elapsed1 = clock.getElapsedTime();
std::cout << elapsed1.asSeconds() << std::endl;
clock.restart();
...
sf::Time elapsed2 = clock.getElapsedTime();
std::cout << elapsed2.asSeconds() << std::endl;
```
# Window module
Windows in SFML are defined by the sf::Window class. A window can be created and opened directly upon construction:
```cpp
#include <SFML/Window.hpp>

int main()
{
    sf::Window window(sf::VideoMode(800, 600), "My window");

    ...

    return 0;
}
```
- The first argument, the video mode, defines the size of the window (the inner size, without the title bar and borders). Here, we create a window with a size of 800x600 pixels.
- The second argument is simply the title of the window.
- This constructor accepts a third optional argument: a style, which allows you to choose which decorations and features you want.
![image](https://github.com/user-attachments/assets/7e3fffeb-4908-486e-803f-ffe8381c5b0b)

## Bringing the window to life
- If you try to execute the code above with nothing in place of the "...", you will hardly see something. First, because the program ends immediately. Second, because there's no event handling -- so even if you added an endless loop to this code, you would see a dead window, unable to be moved, resized, or closed.
```cpp
#include <SFML/Window.hpp>

int main()
{
    sf::Window window(sf::VideoMode(800, 600), "My window");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}
```
## Playing with the window
- Of course, SFML allows you to play with your windows a bit. Basic window operations such as changing the size, position, title or icon are supported, but unlike dedicated GUI libraries (Qt, wxWidgets), SFML doesn't provide advanced features. SFML windows are only meant to provide an environment for OpenGL or SFML drawing.
```cpp
// change the position of the window (relatively to the desktop)
window.setPosition(sf::Vector2i(10, 50));

// change the size of the window
window.setSize(sf::Vector2u(640, 480));

// change the title of the window
window.setTitle("SFML window");

// get the size of the window
sf::Vector2u size = window.getSize();
unsigned int width = size.x;
unsigned int height = size.y;

// check whether the window has the focus
bool focus = window.hasFocus();

...
```
Refer to https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Window.php for more details!
## Controlling the framerate
Sometimes, when your application runs fast, you may notice visual artifacts such as tearing. The reason is that your application's refresh rate is not synchronized with the vertical frequency of the monitor, and as a result, the bottom of the previous frame is mixed with the top of the next one.
The solution to this problem is to activate vertical synchronization. It is automatically handled by the graphics card, and can easily be switched on and off with the setVerticalSyncEnabled function:
```cpp
window.setVerticalSyncEnabled(true); // call it once, after creating the window
```
After this call, your application will run at the same frequency as the monitor's refresh rate.
In other situations, you may also want your application to run at a given framerate, instead of the monitor's frequency. This can be done by calling setFramerateLimit: 
```cpp
window.setFramerateLimit(60); // call it once, after creating the window
```
# Events
Before dealing with events, it is important to understand what the sf::Event type is, and how to correctly use it. sf::Event is a union, which means that only one of its members is valid at a time (remember your C++ lesson: all the members of a union share the same memory space). The valid member is the one that matches the event type, for example event.key for a KeyPressed event. Trying to read any other member will result in an undefined behavior (most likely: random or invalid values). It is important to never try to use an event member that doesn't match its type.

sf::Event instances are filled by the pollEvent (or waitEvent) function of the sf::Window class. Only these two functions can produce valid events, any attempt to use an sf::Event which was not returned by successful call to pollEvent (or waitEvent) will result in the same undefined behavior that was mentioned above.

To be clear, here is what a typical event loop looks like:
```cpp
sf::Event event;

// while there are pending events...
while (window.pollEvent(event))
{
    // check the type of the event...
    switch (event.type)
    {
        // window closed
        case sf::Event::Closed:
            window.close();
            break;

        // key pressed
        case sf::Event::KeyPressed:
            ...
            break;

        // we don't process other types of events
        default:
            break;
    }
}
```
## The Closed event
The sf::Event::Closed event is triggered when the user wants to close the window, through any of the possible methods the window manager provides ("close" button, keyboard shortcut, etc.). This event only represents a close request, the window is not yet closed when the event is received.

Typical code will just call window.close() in reaction to this event, to actually close the window. However, you may also want to do something else first, like saving the current application state or asking the user what to do. If you don't do anything, the window remains open.

There's no member associated with this event in the sf::Event union.
```cpp
if (event.type == sf::Event::Closed)
    window.close();
```
## The Resized event
```cpp
if (event.type == sf::Event::Resized)
{
    std::cout << "new width: " << event.size.width << std::endl;
    std::cout << "new height: " << event.size.height << std::endl;
}
```
## The LostFocus and GainedFocus events
The sf::Event::LostFocus and sf::Event::GainedFocus events are triggered when the window loses/gains focus, which happens when the user switches the currently active window. When the window is out of focus, it doesn't receive keyboard events.

This event can be used e.g. if you want to pause your game when the window is inactive.

There's no member associated with these events in the sf::Event union.
```cpp
if (event.type == sf::Event::LostFocus)
    myGame.pause();

if (event.type == sf::Event::GainedFocus)
    myGame.resume();
```
## The MouseEntered and MouseLeft event
The sf::Event::MouseEntered and sf::Event::MouseLeft events are triggered when the mouse cursor enters/leaves the window.

There's no member associated with these events in the sf::Event union.
```cpp
if (event.type == sf::Event::MouseEntered)
    std::cout << "the mouse cursor has entered the window" << std::endl;

if (event.type == sf::Event::MouseLeft)
    std::cout << "the mouse cursor has left the window" << std::endl;
```
## The JoystickButtonPressed and JoystickButtonReleased events
The sf::Event::JoystickButtonPressed and sf::Event::JoystickButtonReleased events are triggered when a joystick button is pressed/released.

SFML supports up to 8 joysticks and 32 buttons.

The member associated with these events is event.joystickButton, it contains the identifier of the joystick and the index of the pressed/released button.
```cpp
if (event.type == sf::Event::JoystickButtonPressed)
{
    std::cout << "joystick button pressed!" << std::endl;
    std::cout << "joystick id: " << event.joystickButton.joystickId << std::endl;
    std::cout << "button: " << event.joystickButton.button << std::endl;
}
```
# Keyboard, mouse and joystick
## Keyboard
```cpp
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
{
    // left key is pressed: move our character
    character.move(-1.f, 0.f);
}
```
```cpp
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
{
    // right key is pressed: move our character
    character.move(1.f, 0.f);
}
```
## Mouse
```cpp
if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
{
    // left mouse button is pressed: shoot
    gun.fire();
}
```
You can also get and set the current position of the mouse, either relative to the desktop or to a window:
```cpp
// get the global mouse position (relative to the desktop)
sf::Vector2i globalPosition = sf::Mouse::getPosition();

// get the local mouse position (relative to a window)
sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window is a sf::Window
```
```cpp
// set the mouse position globally (relative to the desktop)
sf::Mouse::setPosition(sf::Vector2i(10, 50));

// set the mouse position locally (relative to a window)
sf::Mouse::setPosition(sf::Vector2i(10, 50), window); // window is a sf::Window
```
## Joystick
```cpp
if (sf::Joystick::isConnected(0))
{
    // joystick number 0 is connected
    ...
}
```
# Graphics module
To draw the entities provided by the graphics module, you must use a specialized window class: sf::RenderWindow. This class is derived from sf::Window, and inherits all its functions. Everything that you've learnt about sf::Window (creation, event handling, controlling the framerate, mixing with OpenGL, etc.) is applicable to sf::RenderWindow as well.

On top of that, sf::RenderWindow adds high-level functions to help you draw things easily. In this tutorial we'll focus on two of these functions: clear and draw. They are as simple as their name implies: clear clears the whole window with the chosen color, and draw draws whatever object you pass to it.

Here is what a typical main loop looks like with a render window:
```cpp
#include <SFML/Graphics.hpp>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);

        // end the current frame
        window.display();
    }

    return 0;
}
```
## Position, rotation, scale: Transforming entities
### Position
```cpp
// 'entity' can be a sf::Sprite, a sf::Text, a sf::Shape or any other transformable class

// set the absolute position of the entity
entity.setPosition(10.f, 50.f);

// move the entity relatively to its current position
entity.move(5.f, 5.f);

// retrieve the absolute position of the entity
sf::Vector2f position = entity.getPosition(); // = (15, 55)
```
### Rotation
```cpp
// 'entity' can be a sf::Sprite, a sf::Text, a sf::Shape or any other transformable class

// set the absolute rotation of the entity
entity.setRotation(45.f);

// rotate the entity relatively to its current orientation
entity.rotate(10.f);

// retrieve the absolute rotation of the entity
float rotation = entity.getRotation(); // = 55
```
### Scale
```cpp
// 'entity' can be a sf::Sprite, a sf::Text, a sf::Shape or any other transformable class

// set the absolute scale of the entity
entity.setScale(4.f, 1.6f);

// scale the entity relatively to its current scale
entity.scale(0.5f, 0.5f);

// retrieve the absolute scale of the entity
sf::Vector2f scale = entity.getScale(); // = (2, 0.8)
```
### Origin
```cpp
// 'entity' can be a sf::Sprite, a sf::Text, a sf::Shape or any other transformable class

// set the origin of the entity
entity.setOrigin(10.f, 20.f);

// retrieve the origin of the entity
sf::Vector2f origin = entity.getOrigin(); // = (10, 20)
```
### Transforming your own classes
```cpp
class MyGraphicalEntity : public sf::Transformable
{
    // ...
};

MyGraphicalEntity entity;
entity.setPosition(10.f, 30.f);
entity.setRotation(110.f);
entity.setScale(0.5f, 0.2f);
```
### Bounding boxes
After transforming entities and drawing them, you might want to perform some computations using them e.g. checking for collisions.

SFML entities can give you their bounding box. The bounding box is the minimal rectangle that contains all points belonging to the entity, with sides aligned to the X and Y axes.

```cpp
// get the bounding box of the entity
sf::FloatRect boundingBox = entity.getGlobalBounds();

// check collision with a point
sf::Vector2f point = ...;
if (boundingBox.contains(point))
{
    // collision!
}

// check collision with another box (like the bounding box of another entity)
sf::FloatRect otherBox = ...;
if (boundingBox.intersects(otherBox))
{
    // collision!
}
```
The function is named getGlobalBounds because it returns the bounding box of the entity in the global coordinate system, i.e. after all of its transformations (position, rotation, scale) have been applied.
There's another function that returns the bounding box of the entity in its local coordinate system (before its transformations are applied): getLocalBounds. This function can be used to get the initial size of an entity, for example, or to perform more specific calculations.
