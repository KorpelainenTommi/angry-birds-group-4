#include <SFML/Graphics.hpp>
#include <gameplay/Physics.hpp>
#include <framework/RenderSystem.hpp>



void RenderSystem::RenderRect(sf::Color color, float xw, float yh, float ww, float hh) const {
    sf::RectangleShape rect({1, 1});
    rect.setPosition(xw * WW, yh * HH);
    rect.setScale(ww * WW, hh * HH);
    rect.setFillColor(color);
    window_.draw(rect);
}


void RenderSystem::RenderText(const std::string& text, float xw, float yh, float ww, float hh, sf::Color color, FontID id) const {
    float height = hh * HH;
    sf::Text t(text, resourceManager_.GetFont(id), (unsigned int)height);
    t.setOrigin((ww * WW - t.getLocalBounds().width) * -0.5F, height * 0.25F);
    t.setPosition(xw * WW, yh * HH);
    t.setFillColor(color);
    window_.draw(t);
}

void RenderSystem::RenderSprite(SpriteID id, float xw, float yh, float ww, float hh, sf::Color color) const {
    sf::Sprite sp = resourceManager_.GetSprite(id);
    sp.setPosition(xw * WW, yh * HH);
    sp.scale(ww * WW / sp.getLocalBounds().width, hh * HH / sp.getLocalBounds().height);
    window_.draw(sp);
}

void RenderSystem::RenderSprite(SpriteID id, float xm, float ym, float hm, float rot, const Camera& camera) const {

    sf::View view = window_.getDefaultView();
    sf::Sprite sp = resourceManager_.GetSprite(id);
    float spw = sp.getLocalBounds().width;
    float sph = sp.getLocalBounds().height;
    sp.setOrigin(spw / 2, sph / 2);

    float xw = xm / ph::FullscreenPlayArea;
    float yw = ym / ph::FullscreenPlayArea;
    float hw = hm / ph::FullscreenPlayArea;
    float ww = hw * (spw / sph);

    float cxw = camera.xm / ph::FullscreenPlayArea;
    float cyw = camera.ym / ph::FullscreenPlayArea;

    sp.setPosition(0.5F * WW + xw * WW, 0.5F * HH - yw * WW);
    sp.rotate(rot);
    sp.scale(WW * ww / spw, WW * hw / sph);

    view.zoom(camera.zoom);
    view.rotate(camera.rot);
    view.setCenter(0.5F * WW + cxw * WW, 0.5F * HH - cyw * WW);
    
    window_.setView(view);
    window_.draw(sp);
    window_.setView(window_.getDefaultView());

}