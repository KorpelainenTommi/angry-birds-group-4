#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <memory>
#include <vector>
#include <ui/Element.hpp>
#include <UpdateListener.hpp>
#include <Application.hpp>
#include <queue>

#include <iostream>

class Application;

/// Base class for screens
class Screen : public UpdateListener {
public:
    Screen(Application& app) : app_(app) {}

    virtual ~Screen() = default;

    virtual void Update() {
        //Update all elements
        //for(const auto& e : menu_) e->Update();
        //GameScreen overrides this
    }

    virtual void Render(const RenderSystem& r);

    Application& GetApplication() const { return app_; }

    virtual bool OnMouseDown(const sf::Mouse::Button& button, float xw, float yh);

    virtual bool OnMouseUp(const sf::Mouse::Button& button, float xw, float yh);

    virtual bool OnMouseMove(float xw, float yh);

    virtual bool OnMouseScroll(float delta, float xw, float yh);

    void Confirm(std::string text, const std::function<void(bool)> callBack);

    void DequeueMessage();

protected:
    Application& app_;
    std::vector<std::shared_ptr<Element>> menu_;
    std::queue<std::vector<std::shared_ptr<Element>>> messages_;
};


#endif