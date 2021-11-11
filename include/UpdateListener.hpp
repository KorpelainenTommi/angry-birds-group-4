#ifndef UPDATE_LISTENER_HPP
#define UPDATE_LISTENER_HPP

#include <framework/RenderSystem.hpp>
#include <SFML/Window/Event.hpp>

/// A class inheriting UpdateListener can receive updates
class UpdateListener {
public:

    virtual void Update() {}
    virtual void Render(const RenderSystem&) {}

    virtual void OnKeyDown(const sf::Event::KeyEvent&) {}
    virtual void OnKeyUp(const sf::Event::KeyEvent&) {}

    virtual void OnMouseDown(const sf::Event::MouseButtonEvent&) {}
    virtual void OnMouseUp(const sf::Event::MouseButtonEvent&) {}
    virtual void OnMouseMove(const sf::Event::MouseMoveEvent&) {}

    virtual void OnMouseScroll(const sf::Event::MouseWheelScrollEvent&) {}

    virtual void OnTextEntered(const sf::Event::TextEvent&) {}

protected:
    UpdateListener() {}
};


#endif