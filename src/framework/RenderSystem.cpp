#include <SFML/Graphics.hpp>
#include <gameplay/Physics.hpp>
#include <framework/RenderSystem.hpp>


//relative rectangle

void RenderSystem::RenderRect(sf::Color color, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h) const {
    float xx = 0.01F * x * (x.p ? WW : HH);
    float yy = 0.01F * y * (y.p ? WW : HH);
    float ww = 0.01F * w * (w.p ? WW : HH);
    float hh = 0.01F * h * (h.p ? WW : HH);
    sf::RectangleShape rect({1, 1});
    rect.setPosition(xx, yy);
    rect.setScale(ww, hh);
    rect.setFillColor(color);
    window_.draw(rect);
}

//game rectangle

void RenderSystem::RenderRect(sf::Color color, ph::tfloat x, ph::tfloat y, ph::tfloat w, ph::tfloat h, ph::tfloat rot, const Camera& camera) const {
    
    sf::View view = window_.getDefaultView();
    sf::RectangleShape rect({1, 1});
    rect.setOrigin(0.5F, 0.5F);

    float xw = x.Lerp(ALPHA) / ph::FullscreenPlayArea;
    float yw = y.Lerp(ALPHA) / ph::FullscreenPlayArea;
    float hw = h.Lerp(ALPHA) / ph::FullscreenPlayArea;
    float ww = w.Lerp(ALPHA) / ph::FullscreenPlayArea;

    float cxw = camera.x.Lerp(ALPHA) / ph::FullscreenPlayArea;
    float cyw = camera.y.Lerp(ALPHA) / ph::FullscreenPlayArea;

    rect.setPosition(0.5F * WW + xw * WW, 0.5F * HH - yw * WW);
    rect.rotate(rot.Lerp(ALPHA));
    rect.scale(WW * ww, WW * hw);
    rect.setFillColor(color);

    view.zoom(camera.zoom.Lerp(ALPHA));
    view.rotate(camera.rot.Lerp(ALPHA));
    view.setCenter(0.5F * WW + cxw * WW, 0.5F * HH - cyw * WW);
    
    window_.setView(view);
    window_.draw(rect);
    window_.setView(window_.getDefaultView());
}

//relative oval

void RenderSystem::RenderOval(sf::Color color, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h) const {
    float xx = 0.01F * x * (x.p ? WW : HH);
    float yy = 0.01F * y * (y.p ? WW : HH);
    float ww = 0.01F * w * (w.p ? WW : HH);
    float hh = 0.01F * h * (h.p ? WW : HH);
    sf::CircleShape circ(1);
    circ.setPosition(xx, yy);
    circ.setScale(ww, hh);
    circ.setFillColor(color);
    window_.draw(circ);
}

//game oval

void RenderSystem::RenderOval(sf::Color color, ph::tfloat x, ph::tfloat y, ph::tfloat w, ph::tfloat h, ph::tfloat rot, const Camera& camera) const {
    
    sf::View view = window_.getDefaultView();
    sf::CircleShape circ(0.5F);
    circ.setOrigin(0.5F, 0.5F);

    float xw = x.Lerp(ALPHA) / ph::FullscreenPlayArea;
    float yw = y.Lerp(ALPHA) / ph::FullscreenPlayArea;
    float hw = h.Lerp(ALPHA) / ph::FullscreenPlayArea;
    float ww = w.Lerp(ALPHA) / ph::FullscreenPlayArea;

    float cxw = camera.x.Lerp(ALPHA) / ph::FullscreenPlayArea;
    float cyw = camera.y.Lerp(ALPHA) / ph::FullscreenPlayArea;

    circ.setPosition(0.5F * WW + xw * WW, 0.5F * HH - yw * WW);
    circ.rotate(rot.Lerp(ALPHA));
    circ.scale(WW * ww, WW * hw);
    circ.setFillColor(color);

    view.zoom(camera.zoom.Lerp(ALPHA));
    view.rotate(camera.rot.Lerp(ALPHA));
    view.setCenter(0.5F * WW + cxw * WW, 0.5F * HH - cyw * WW);
    
    window_.setView(view);
    window_.draw(circ);
    window_.setView(window_.getDefaultView());
}


// relative text

void RenderSystem::RenderText(const std::string& text, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h, sf::Color color, FontID id) const {
    float xx = 0.01F * x * (x.p ? WW : HH);
    float yy = 0.01F * y * (y.p ? WW : HH);
    float ww = 0.01F * w * (w.p ? WW : HH);
    float hh = 0.01F * h * (h.p ? WW : HH);
    sf::Text t(text, resourceManager_.GetFont(id), (unsigned int)hh);
    t.setOrigin((ww - t.getLocalBounds().width) * -0.5F, hh * 0.25F);
    t.setPosition(xx, yy);
    t.setFillColor(color);
    window_.draw(t);
}

//game text

void RenderSystem::RenderText(const std::string& text, ph::tfloat x, ph::tfloat y, ph::tfloat h, ph::tfloat rot, const Camera& camera, sf::Color color, FontID id) const {

    sf::View view = window_.getDefaultView();
    float xw = x.Lerp(ALPHA) / ph::FullscreenPlayArea;
    float yw = y.Lerp(ALPHA) / ph::FullscreenPlayArea;
    float hw = h.Lerp(ALPHA) / ph::FullscreenPlayArea;

    sf::Text t(text, resourceManager_.GetFont(id), (unsigned int)(hw * WW));
    t.setOrigin(t.getLocalBounds().width / 2, t.getLocalBounds().height);

    float cxw = camera.x.Lerp(ALPHA) / ph::FullscreenPlayArea;
    float cyw = camera.y.Lerp(ALPHA) / ph::FullscreenPlayArea;

    t.setPosition(0.5F * WW + xw * WW, 0.5F * HH - yw * WW);
    t.rotate(rot.Lerp(ALPHA));
    t.setFillColor(color);

    view.zoom(camera.zoom.Lerp(ALPHA));
    view.rotate(camera.rot.Lerp(ALPHA));
    view.setCenter(0.5F * WW + cxw * WW, 0.5F * HH - cyw * WW);
    
    window_.setView(view);
    window_.draw(t);
    window_.setView(window_.getDefaultView());

}

// relative sprite

void RenderSystem::RenderSprite(SpriteID id, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h, sf::Color color) const {
    sf::Sprite sp = resourceManager_.GetSprite(id);
    float xx = 0.01F * x * (x.p ? WW : HH);
    float yy = 0.01F * y * (y.p ? WW : HH);
    float ww = 0.01F * w * (w.p ? WW : HH);
    float hh = 0.01F * h * (h.p ? WW : HH);
    sp.setPosition(xx, yy);
    sp.scale(ww / sp.getLocalBounds().width, hh / sp.getLocalBounds().height);
    window_.draw(sp);
}

// game sprite

void RenderSystem::RenderSprite(SpriteID id, ph::tfloat x, ph::tfloat y, ph::tfloat h, ph::tfloat rot, const Camera& camera) const {

    sf::View view = window_.getDefaultView();
    sf::Sprite sp = resourceManager_.GetSprite(id);
    float spw = sp.getLocalBounds().width;
    float sph = sp.getLocalBounds().height;
    sp.setOrigin(spw / 2, sph / 2);

    float xw = x.Lerp(ALPHA) / ph::FullscreenPlayArea;
    float yw = y.Lerp(ALPHA) / ph::FullscreenPlayArea;
    float hw = h.Lerp(ALPHA) / ph::FullscreenPlayArea;
    float ww = hw * (spw / sph);

    float cxw = camera.x.Lerp(ALPHA) / ph::FullscreenPlayArea;
    float cyw = camera.y.Lerp(ALPHA) / ph::FullscreenPlayArea;

    sp.setPosition(0.5F * WW + xw * WW, 0.5F * HH - yw * WW);
    sp.rotate(rot.Lerp(ALPHA));
    sp.scale(WW * ww / spw, WW * hw / sph);

    view.zoom(camera.zoom.Lerp(ALPHA));
    view.rotate(camera.rot.Lerp(ALPHA));
    view.setCenter(0.5F * WW + cxw * WW, 0.5F * HH - cyw * WW);
    
    window_.setView(view);
    window_.draw(sp);
    window_.setView(window_.getDefaultView());

}