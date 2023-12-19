#pragma once
#include "Screen.h"
#include "Singleton.h"
#include "Button.h"
#include "TextBox.h"
#include <fstream>
#include <SFML/Graphics.hpp>

class FileManader : public Singleton<FileManader>{
public:
    bool is_open();
    void open(sf::Font& font);
    void EventManager(sf::Event& event, sf::Font& font);
    void SetOutput(std::string& str);
    void Draw();
    std::string getInput();
    sf::RenderWindow* wnd;
private:
    void Close();
    std::string OutputString;
    std::string str_input;
    sf::Text WindowTitle;
    Button btn;
    Button btn2;
    TextBox input;
    bool open_ = false;
};