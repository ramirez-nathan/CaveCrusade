#pragma once
#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;

class MessageBox {

public:

    MessageBox()
    {
        //t_messageBox.loadFromFile("assets/message_boxes/messagebox.png");
        //s_messageBox.setTexture(t_messageBox);
        Pixel.loadFromFile("assets/message_boxes/Pixel.ttf");
        MessageBox_text.setFont(Pixel);
    }

    void setText(String text, int x, int y, int size)
    {
        MessageBox_text.setFillColor(Color::White);
        MessageBox_text.setPosition(x, y);
        MessageBox_text.setString(text);
        MessageBox_text.setCharacterSize(size);
    }

    void drawMessageBox(RenderWindow& window)
    {
        if (visible == true)
        {
            window.draw(s_messageBox);
            window.draw(MessageBox_text);
        }
    }


    void updateText(String UpdateText, String UpdateText2, String UpdateText3, Event& event)
    {

        if (event.type == event.KeyReleased)
        {
            if (event.key.code == Keyboard::Space)
            {
                if (currentText <= 2)
                    currentText++;

            }
        }

        switch (currentText)
        {
        case 0: MessageBox_text.setString(UpdateText); break;
        case 1: MessageBox_text.setString(UpdateText2); break;
        case 2: MessageBox_text.setString(UpdateText3); break;
        }

    };


private:
    Texture t_messageBox;
    Sprite  s_messageBox;
    Font Pixel;
    Text MessageBox_text;

    bool visible = true;

    int currentText = 0;
};