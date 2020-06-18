#pragma once

#include "SFML/Graphics.hpp"

#include "Murphy/Core.h"

#include "Geometry.h"

namespace Murphy::M2D
{
    class MURPHY_API Shape : public Drawable
    {
    public:
        Shape() {}
        virtual ~Shape() {}
        inline virtual unsigned int GetPointCount() const = 0;
    };

    class MURPHY_API Rect : public Shape
    {
    public:
        Rect() {}
        virtual ~Rect() {}

        void SetSize(float x, float y);
        void SetSize(Vector2F& size);
        Vector2F GetSize() const;

        inline virtual unsigned int GetPointCount() const override { return 4; }

        virtual void Draw(Renderer& renderer) const override
        {/*
            Vector2F size = GetSize();
            sf::RectangleShape sfRect(sf::Vector2f(size.X, size.Y));
            sfRect.setFillColor(sf::Color::Green);
            sf::RenderWindow* window = (sf::RenderWindow*)renderer.GetWindow()->GetPlatformWindow();
            window->draw(sfRect);*/
        }
    private:
        Vector2F m_Size;
    };
}