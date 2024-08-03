#include "Fraction.h"
#include "Screen.h"
#include "Button.h"
#include "TextBox.h"
#include "FileManager.h"
#include <thread>
#include <memory>

std::string solve(std::string& str_whole, std::string& str_fractional, std::string& str_period, int p, int q) {
    std::string translate;
    BigInteger whole(str_whole, p);
    if (whole.GetErrors()) {
        return "error";
    }
    whole.translation(q);
    translate = out(translate, whole);
    if (!str_fractional.empty() || !str_period.empty()) {
        bool flag = true;
        if (str_fractional.empty()) {
            flag = false;
            str_fractional = "0";
        }
        BigInteger fractional(str_fractional, p);
        if (fractional.GetErrors()) {
            return "error";
        }
        std::string pw = "10";
        BigInteger den(pw, p);
        den.BinaryExponentiation((int)fractional.get_length());

        Fraction fr(fractional, den);
        if (!str_period.empty()) {
            pw = "10";
            BigInteger period(str_period, p);
            if (period.GetErrors()) {
                return "error";
            }
            BigInteger den_period(pw, p);

            den_period.BinaryExponentiation((int)period.get_length());
            std::string one = "1";
            BigInteger on(one, p);
            den_period -= on;


            if (flag) {
                std::reverse(pw.begin(), pw.end());
                BigInteger shift(pw, p);
                shift.BinaryExponentiation((int)fractional.get_length());
                den_period *= shift;
            }

            fr += Fraction(period, den_period);
        }
        fr.translation(q);
        if (!fr.carry) {
            translate += '.';
            std::vector<BigInteger> res = fr.get_decimal();
            for (int i = 0; i < res.size(); ++i) {
                if (i == fr.start) {
                    translate += '(';
                }
                translate = out(translate, res[i]);
                if (i == fr.finish - 1) {
                    translate += ')';
                }
            }
        } else {
            translate.clear();
            std::string str = "1";
            BigInteger one(str, whole.get_p());
            whole += one;
            translate = out(translate, whole);
        }
    }
    return translate;
}
// функция для button
void onclick(std::shared_ptr<TextBox> enter1, std::shared_ptr<TextBox> enter2, 
            std::shared_ptr<TextBox> enter3, std::shared_ptr<TextBox> out) {
    std::string p = enter2->get_text(), q = enter3->get_text();
    std::string number = enter1->get_text();
    std::string str_whole, str_fractional, str_period;
    if (q.empty() || p.empty()) {
        return;
    }
    bool flag = false, period_f = false;
    for (char i : number) {
        if (i == ')') {
            break;
        }
        if (i == '(') {
            period_f = true;
        } else if (period_f) {
            str_period += i;
        } else if (i == '.' || i == ',') {
            flag = true;
        } else if (flag) {
            str_fractional += i;
        } else {
            str_whole += i;
        }
    }
    out->set_text(solve(str_whole, str_fractional, str_period, std::stoi(p), std::stoi(q)));
}

int main() {
    Screen::GetInstance()->Init();
    sf::RenderWindow* wnd = Screen::GetInstance()->window;

    sf::Font font;
    sf::Text title;
    Button btn;
    Button btn2;
    std::shared_ptr<TextBox> enter1 = std::make_shared<TextBox>();
    std::shared_ptr<TextBox> enter2 = std::make_shared<TextBox>();
    std::shared_ptr<TextBox> enter3 = std::make_shared<TextBox>();
    std::shared_ptr<TextBox> out = std::make_shared<TextBox>();

    font.loadFromFile("3270NerdFontMono-Regular.ttf");
    title.setFont(font);
    enter1->SetFont(font);
    enter2->SetFont(font);
    enter3->SetFont(font);
    out->SetFont(font);

    sf::Vector2f size;
    size = { (float)wnd->getSize().x / (float)1.1, (float)wnd->getSize().y / (float)8 };

    title.setCharacterSize(35);
    enter1->SetSize(size);
    enter2->SetSize(size);
    enter3->SetSize(size);
    out->SetSize(size);
    btn.SetSize({size.x / (float) 2.1, size.y});
    btn2.SetSize({size.x / (float) 2.1, size.y});

    btn.SetText("Translate", sf::Color::Black, font);
    btn2.SetText("FileManager", sf::Color::Black, font);
    title.setString("universal converter");

    btn.SetPosition({(float) wnd->getSize().x * (float) 0.53, (float) wnd->getSize().y * (float) 0.85});
    btn2.SetPosition({(float) wnd->getSize().x * (float) 0.05, (float) wnd->getSize().y * (float) 0.85});
    out->SetPosition({(float) wnd->getSize().x * (float) 0.05, (float) wnd->getSize().y * (float) 0.7});
    enter3->SetPosition({(float) wnd->getSize().x * (float) 0.05, (float) wnd->getSize().y * (float) 0.55});
    enter2->SetPosition({(float) wnd->getSize().x * (float) 0.05, (float) wnd->getSize().y * (float) 0.4});
    enter1->SetPosition({(float) wnd->getSize().x * (float) 0.05, (float) wnd->getSize().y * (float) 0.25});
    title.setPosition({ (float)wnd->getSize().x * (float)0.5 - title.getLocalBounds().width / 2, (float)wnd->getSize().y * (float).1 });

    btn.SetBackColor(sf::Color(141, 159, 135));
    btn2.SetBackColor(sf::Color(141, 159, 135));
    enter1->SetBackColor(sf::Color(205, 198, 165));
    enter2->SetBackColor(sf::Color(205, 198, 165));
    enter3->SetBackColor(sf::Color(205, 198, 165));
    out->SetBackColor(sf::Color(205, 198, 165));
    title.setFillColor(sf::Color::Black);

    std::string TextBoxName = "enter number:";
    enter1->SetTitle(font, TextBoxName);
    TextBoxName = "enter p:";
    enter2->SetTitle(font, TextBoxName);
    TextBoxName = "enter q:";
    enter3->SetTitle(font, TextBoxName);
    TextBoxName = "result:";
    out->SetTitle(font, TextBoxName);

    while (wnd->isOpen()) {

        sf::Event event{};

        while (wnd->pollEvent(event)) {

            enter1->enter(event);
            enter2->enter(event);
            enter3->enter(event);
            out->enter(event);

            // resize window
            if (event.type == sf::Event::Resized) {
                sf::Vector2u windowSize = sf::Vector2u(event.size.width, event.size.height);
                wnd->setView(sf::View(sf::Vector2f((float)windowSize.x / 2.f,(float)windowSize.y / 2.f), sf::Vector2f(windowSize)));
                size = { (float)wnd->getSize().x / (float)1.1, (float)wnd->getSize().y / (float)8 };

                enter1->SetSize(size);
                enter2->SetSize(size);
                enter3->SetSize(size);
                out->SetSize(size);
                btn.SetSize({size.x / (float) 2.1, size.y});
                btn2.SetSize({size.x / (float) 2.1, size.y});

                float Button_shift = size.x - size.x / (float)2.1;

                btn.SetPosition({(float) wnd->getSize().x * (float) 0.05 + Button_shift,
                                 (float) wnd->getSize().y * (float) 0.85});
                btn2.SetPosition({(float) wnd->getSize().x * (float) 0.05, (float) wnd->getSize().y * (float) 0.85});
                out->SetPosition({(float) wnd->getSize().x * (float) 0.05, (float) wnd->getSize().y * (float) 0.7});
                enter3->SetPosition({(float) wnd->getSize().x * (float) 0.05, (float) wnd->getSize().y * (float) 0.55});
                enter2->SetPosition({(float) wnd->getSize().x * (float) 0.05, (float) wnd->getSize().y * (float) 0.4});
                enter1->SetPosition({(float) wnd->getSize().x * (float) 0.05, (float) wnd->getSize().y * (float) 0.25});
                title.setPosition({ (float)wnd->getSize().x * (float)0.5 - title.getLocalBounds().width / 2, (float)wnd->getSize().y * (float).1 });

                std::string str = "enter number:";
                enter1->SetTitle(font, str);
                str = "enter p:";
                enter2->SetTitle(font, str);
                str = "enter q:";
                enter3->SetTitle(font, str);
                str = "result:";
                out->SetTitle(font, str);
                btn.SetText("Translate", sf::Color::Black, font);
                btn2.SetText("FileManager", sf::Color::Black, font);

                enter1->text_size();
                enter2->text_size();
                enter3->text_size();
                out->text_size();
            }
            if (event.type == sf::Event::Closed) {
                wnd->close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !FileManader::GetInstance()->is_open()) {
                enter1->setActive(enter1->isMousOver(*wnd));
                enter2->setActive(enter2->isMousOver(*wnd));
                enter3->setActive(enter3->isMousOver(*wnd));
                out->setActive(out->isMousOver(*wnd));
            }
        }
        wnd->clear(sf::Color::White);
        if (btn.isMouseOver(*wnd) && !FileManader::GetInstance()->is_open()) {
            enter1->SetStart();
            enter2->SetStart();
            enter3->SetStart();
            out->SetStart();
            std::thread t(onclick, enter1, enter2, enter3, out);
            t.detach();
        }
        if (btn2.isMouseOver(*wnd) && !FileManader::GetInstance()->is_open()) {
            std::string res = out->get_text();
            FileManader::GetInstance()->SetOutput(res);
            FileManader::GetInstance()->open(font);
        } else {
            std::string fileinput = FileManader::GetInstance()->getInput();
            if (!fileinput.empty()) {
                enter1->set_text(fileinput);
            }
        }
        btn.Draw_To(*wnd);
        btn2.Draw_To(*wnd);
        enter1->Draw_To(*wnd);
        enter2->Draw_To(*wnd);
        enter3->Draw_To(*wnd);
        out->Draw_To(*wnd);
        wnd->draw(title);
        wnd->display();
        if (FileManader::GetInstance()->is_open()) {
            while (FileManader::GetInstance()->wnd->pollEvent(event)) {
                FileManader::GetInstance()->EventManager(event, font);
            }
            FileManader::GetInstance()->Draw();
        }
    }
    return 0;
}
