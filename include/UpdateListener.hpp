#ifndef UPDATE_LISTENER_HPP
#define UPDATE_LISTENER_HPP

#include <framework/RenderSystem.hpp>
#include <SFML/Window/Event.hpp>

/// A class inheriting UpdateListener can receive updates
class UpdateListener {
public:

    virtual void Update() {}
    virtual void Render(const RenderSystem&) {}

    virtual bool OnKeyDown(const sf::Event::KeyEvent&) { return false; }
    virtual bool OnKeyUp(const sf::Event::KeyEvent&) { return false; }

    virtual bool OnMouseDown(const sf::Event::MouseButtonEvent&) { return false; }
    virtual bool OnMouseUp(const sf::Event::MouseButtonEvent&) { return false; }
    virtual bool OnMouseMove(const sf::Event::MouseMoveEvent&) { return false; }

    virtual bool OnMouseScroll(const sf::Event::MouseWheelScrollEvent&) { return false; }

    virtual bool OnTextEntered(const sf::Event::TextEvent&) { return false; }

protected:
    UpdateListener() {}
};


#endif