#include "../app/FileManager.h"
bool FileManader::is_open() {
    return open_;
}
void FileManader::open(sf::Font& font) {
    open_ = true;
    input.SetStart();
    input.set_text("");
    wnd = new sf::RenderWindow(sf::VideoMode(500, 500), "FileManager");
    sf::Vector2f size;
    size = { (float)wnd->getSize().x / (float)1.1, (float)wnd->getSize().y / (float)6 };
    input.SetFont(font);
    WindowTitle.setFont(font);
    WindowTitle.setCharacterSize(35);
    WindowTitle.setFillColor(sf::Color::Black);
    WindowTitle.setString("File Manager");
    input.SetSize({ size.x, size.y * (float)1.5 });
    btn.SetSize(size);
    btn2.SetSize(size);
    btn.SetBackColor(sf::Color(141, 159, 135));
    btn2.SetBackColor(sf::Color(141, 159, 135));
    input.SetBackColor(sf::Color(205, 198, 165));
    btn.SetText("Save", sf::Color::Black, font);
    btn2.SetText("Input", sf::Color::Black, font);
    btn.SetPosition({(float) wnd->getSize().x * (float) 0.05, (float) wnd->getSize().y * (float) 0.6});
    btn2.SetPosition({(float) wnd->getSize().x * (float) 0.05, (float) wnd->getSize().y * (float) 0.8});
    input.SetPosition({(float) wnd->getSize().x * (float) 0.05, (float) wnd->getSize().y * (float) 0.3});
    WindowTitle.setPosition({(float) wnd->getSize().x * (float)0.5 - WindowTitle.getLocalBounds().width / 2, (float) wnd->getSize().y * (float) 0.1});
    std::string title = "File name:";
    input.SetTitle(font, title);
}
void FileManader::EventManager(sf::Event &event, sf::Font& font) {
    if (event.type == sf::Event::Closed) {
        wnd->close();
        open_ = false;
    }
    if (event.type == sf::Event::Resized) {
        sf::Vector2f windowSize = sf::Vector2f(event.size.width, event.size.height);
        wnd->setView(sf::View(sf::Vector2f(windowSize.x / 2.f,windowSize.y / 2.f), sf::Vector2f(windowSize)));
        sf::Vector2f size;
        size = { (float)wnd->getSize().x / (float)1.1, (float)wnd->getSize().y / (float)6 };
        btn.SetSize(size);
        btn2.SetSize(size);
        input.SetSize({ size.x, size.y * (float)1.5 });
        btn.SetPosition({(float) wnd->getSize().x * (float) 0.05, (float) wnd->getSize().y * (float) 0.6});
        btn2.SetPosition({(float) wnd->getSize().x * (float) 0.05, (float) wnd->getSize().y * (float) 0.8});
        input.SetPosition({(float) wnd->getSize().x * (float) 0.05, (float) wnd->getSize().y * (float) 0.3});
        WindowTitle.setPosition({(float) wnd->getSize().x * (float) 0.5 - WindowTitle.getLocalBounds().width / 2, (float) wnd->getSize().y * (float) 0.1});
        std::string title = "File name:";
        input.SetTitle(font, title);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        input.setActive(input.isMousOver(*wnd));
    }
    input.enter(event);
    if (btn.isMouseOver(*wnd)) {
        std::ofstream file(input.get_text());
        file << OutputString;
        file.close();
        Close();
    }
    if (btn2.isMouseOver(*wnd)) {
        std::ifstream file(input.get_text());
        if (!file) {
            input.set_text("file not found");
        } else {
            file >> str_input;
            Close();
        }
    }
}
void FileManader::Close() {
    input.set_text("");
    wnd->close();
    open_ = false;
}
void FileManader::Draw() {
    wnd->clear(sf::Color::White);
    btn.Draw_To(*wnd);
    btn2.Draw_To(*wnd);
    input.Draw_To(*wnd);
    wnd->draw(WindowTitle);
    wnd->display();
}
void FileManader::SetOutput(std::string &str) {
    OutputString = str;
}
std::string FileManader::getInput() {
    std::string res = str_input;
    str_input.clear();
    return res;
}
