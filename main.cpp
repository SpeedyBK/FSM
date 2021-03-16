#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <zconf.h>

using namespace std;

enum class FSM_output { Access_Denied, Access_Granted, No_Output };
enum class States { wait, p, pa, pas, pass, error};

/*!
 * Function to check if a key is pressed.
 * @return "ascii-value" if a key is just pressed, 0 if no key is pressed, or a key is pressed for a longer time.
 */
char readKeyboard();

FSM_output codelock(char input);

int main() {

    /*
     * Parameters to render a window and draw a white circle.
     */
    sf::RenderWindow window(sf::VideoMode(400, 400), "Codelock");
    sf::CircleShape circle(150.f);
    circle.setFillColor(sf::Color::White);
    circle.setPosition(50, 50);

    int index = 0;

    /*
     * Main Loop:
     * -- All the interesting Stuff happens here.
     */
    while (window.isOpen()) {

        sf::Event event;

        /*
         * Check if someone closes the programwindow.
         */
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }


        //---------------------------------------------------------------------------------------
        // Put your code here:

        auto taste = readKeyboard();
        if (taste != 0){
            cout << index++ << ":" << taste << endl;
        }

        auto out = codelock(taste);

        if (out == FSM_output::Access_Granted){
            circle.setFillColor(sf::Color::Green);
        }else if (out == FSM_output::Access_Denied){
            circle.setFillColor(sf::Color::Red);
        }else{
            circle.setFillColor(sf::Color::White);
        }
        //---------------------------------------------------------------------------------------


        /*
         * Draw Stuff on the screen.
         */
        window.clear();
        window.draw(circle);
        window.display();

        /*
         * Slowing down the program a bit to reduce CPU-Load.
         */
        usleep(1000);

    }

    return 0;

}


char readKeyboard(){

    static bool firstPress = true;
    char returnValue;

    for (int k = sf::Keyboard::Key::A; k != sf::Keyboard::Key::Num0; ++k){
        auto ke = static_cast<sf::Keyboard::Key>(k);
        if (sf::Keyboard::isKeyPressed(ke)) {
            if (firstPress) {
                returnValue = (char) (k + 65);
                firstPress = false;
            } else {
                returnValue = 0;
            }
            return returnValue;
        }
    }

    firstPress = true;
    return 0;
}


FSM_output codelock (char input){

    static States State = States::wait;
    FSM_output out = FSM_output::No_Output;

    switch (State){
        case States::wait:
            if (input == 0){
                State = States::wait;
            }else if (input == 'P'){
                State = States::p;
            }else {
                State = States::error;
            }
            out = FSM_output::No_Output;
            break;
        case States::p:
            if (input == 0){
                State = States::p;
            }else if(input == 'A'){
                State = States::pa;
            }else{
                State = States::error;
            }
            out = FSM_output::No_Output;
            break;
        case States::pa:
            if (input == 0){
                State = States::pa;
            }else if(input == 'S'){
                State = States::pas;
            }else {
                State = States::error;
            }
            out = FSM_output::No_Output;
            break;
        case States::pas:
            if (input == 0){
                State = States::pas;
            }else if(input == 'S'){
                State = States::pass;
            }else {
                State = States::error;
            }
            out = FSM_output::No_Output;
            break;
        case States::pass:
            if (input == 0){
                State = States::pass;
            }else {
                State = States::wait;
            }
            out = FSM_output::Access_Granted;
            break;
        case States::error:
            if (input == 0){
                State = States::error;
            }else {
                State = States::wait;
            }
            out = FSM_output::Access_Denied;
            break;
    }

    return out;
}


