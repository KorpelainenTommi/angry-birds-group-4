#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <gameplay/Physics.hpp>
#include <framework/RenderSystem.hpp>
#include <utility>


void RenderSystem::CameraDraw(const sf::Drawable& shape, const Camera& camera) const {

    //Create copies of the current view
    sf::View view = window_.getView();
    sf::View v = view;

    //Scale x and y from world => screen, translate left-top origin to middle of the screen
    float cxw = camera.x / ph::fullscreenPlayArea;
    float cyw = camera.y / ph::fullscreenPlayArea;
    v.zoom(camera.zoom);
    v.rotate(camera.rot);
    v.setCenter(0.5F * WW + cxw * WW, 0.5F * HH - cyw * WW);
    window_.setView(v);
    window_.draw(shape);
    window_.setView(view);
}

sf::Vector2f RenderSystem::GetRelativeCoords(sf::Vector2f coords, const Camera& camera) const {
    //Copied from cameradraw, test how the camera would translate coords
    sf::View view = window_.getView();
    sf::View v = view;
    float cxw = camera.x / ph::fullscreenPlayArea;
    float cyw = camera.y / ph::fullscreenPlayArea;
    v.zoom(camera.zoom);
    v.rotate(camera.rot);
    v.setCenter(0.5F * WW + cxw * WW, 0.5F * HH - cyw * WW);
    coords.x = 0.5F * WW + (coords.x / ph::fullscreenPlayArea) * WW;
    coords.y = 0.5F * HH - (coords.y / ph::fullscreenPlayArea) * WW;
    sf::Vector2i pixels = window_.mapCoordsToPixel(coords,v);
    return sf::Vector2f(((float)pixels.x)/WW,((float)pixels.y)/HH);
}


void RenderSystem::RenderRelative(sf::Shape& shape, const sf::Color& color, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h) const {
    //Map VW and VH to range [0,1]
    float xx = 0.01F * x * (x.p ? WW : HH);
    float yy = 0.01F * y * (y.p ? WW : HH);
    float ww = 0.01F * w * (w.p ? WW : HH);
    float hh = 0.01F * h * (h.p ? WW : HH);
    shape.setPosition(xx, yy);
    shape.setScale(ww, hh);
    shape.setFillColor(color);
    window_.draw(shape);
}

void RenderSystem::RenderRelativeCrop(sf::Shape& shape, const sf::Color& color, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h, const ui::CropArea& cropArea) const {
    sf::View view = window_.getView();
    sf::View v = view;

    //Calculate a viewport based on cropArea pos, scale and shape
    float viewPortX = 0.01F * (cropArea.left.p ? cropArea.left : cropArea.left / ui::aspectRatio);
    float viewPortY = 0.01F * (cropArea.top.p ? cropArea.top * ui::aspectRatio : cropArea.top);
    float viewPortW = 0.01F * (cropArea.width.p ? cropArea.width : cropArea.width / ui::aspectRatio);
    float viewPortH = 0.01F * (cropArea.height.p ? cropArea.height * ui::aspectRatio : cropArea.height);

    //Cannot transform if 0 determinant, so force min size
    if(viewPortW < 0.000001F) viewPortW = 0.000001F;
    if(viewPortH < 0.000001F) viewPortH = 0.000001F;

    //Viewport crops rendering, but also transforms drawables. Calculate and apply an inverse transformation
    float wScale = 1 / viewPortW;
    float hScale = 1 / viewPortH;

    //translation
    float cx = wScale * 0.01F * cropArea.left * (cropArea.left.p ? WW : HH);
    float cy = hScale * 0.01F * cropArea.top * (cropArea.top.p ? WW : HH);

    //scale
    float xx = wScale * 0.01F * x * (x.p ? WW : HH) - cx;
    float yy = hScale * 0.01F * y * (y.p ? WW : HH) - cy;
    float ww = wScale * 0.01F * w * (w.p ? WW : HH);
    float hh = hScale * 0.01F * h * (h.p ? WW : HH);

    v.setViewport({viewPortX, viewPortY, viewPortW, viewPortH});

    shape.setPosition(xx, yy);
    shape.setScale(ww, hh);
    shape.setFillColor(color);

    window_.setView(v);
    window_.draw(shape);
    window_.setView(view);
}

void RenderSystem::RenderAbs(sf::Shape& shape, const sf::Color& color, ph::tfloat x, ph::tfloat y, ph::tfloat w, ph::tfloat h, ph::tfloat rot, const Camera& camera) const {
    //Interpolate between last, and current physics position (so we get an inbetween)
    float xw = x.Lerp(ALPHA) / ph::fullscreenPlayArea;
    float yw = y.Lerp(ALPHA) / ph::fullscreenPlayArea;
    float hw = h.Lerp(ALPHA) / ph::fullscreenPlayArea;
    float ww = w.Lerp(ALPHA) / ph::fullscreenPlayArea;
    shape.setOrigin(0.5F, 0.5F);
    shape.setPosition(0.5F * WW + xw * WW, 0.5F * HH - yw * WW);
    shape.rotate(rot.Lerp(ALPHA));
    shape.scale(WW * ww, WW * hw);
    shape.setFillColor(color);
    CameraDraw(shape, camera);
}

//relative rectangle

void RenderSystem::RenderRect(const sf::Color& color, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h) const {
    sf::RectangleShape rect({1, 1});
    RenderRelative(rect, color, x, y, w, h);
}

void RenderSystem::RenderRect(const sf::Color& color, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h, const ui::CropArea& cropArea) const {
    sf::RectangleShape rect({1, 1});
    RenderRelativeCrop(rect, color, x, y, w, h, cropArea);
}

//game rectangle

void RenderSystem::RenderRect(const sf::Color& color, ph::tfloat x, ph::tfloat y, ph::tfloat w, ph::tfloat h, ph::tfloat rot, const Camera& camera) const {
    sf::RectangleShape rect({1, 1});
    RenderAbs(rect, color, x, y, w, h, rot, camera);
}

//relative oval

void RenderSystem::RenderOval(const sf::Color& color, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h) const {
    sf::CircleShape circ(0.5F);
    RenderRelative(circ, color, x, y, w, h);
}

void RenderSystem::RenderOval(const sf::Color& color, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h, const ui::CropArea& cropArea) const {
    sf::CircleShape circ(0.5F);
    RenderRelativeCrop(circ, color, x, y, w, h, cropArea);
}

//game oval

void RenderSystem::RenderOval(const sf::Color& color, ph::tfloat x, ph::tfloat y, ph::tfloat w, ph::tfloat h, ph::tfloat rot, const Camera& camera) const {
    sf::CircleShape circ(0.5F);
    RenderAbs(circ, color, x, y, w, h, rot, camera);
}


// relative text

void RenderSystem::RenderText(const std::string& text, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h, const sf::Color& color, FontID id, ui::TextAlign textAlign) const {
    float xx = 0.01F * x * (x.p ? WW : HH);
    float yy = 0.01F * y * (y.p ? WW : HH);
    float ww = 0.01F * w * (w.p ? WW : HH);
    float hh = 0.01F * h * (h.p ? WW : HH);
    sf::Text t(text, resourceManager_.GetFont(id), (unsigned int)hh);

    //Calculate origin based on text length
    if(textAlign == ui::TextAlign::center) t.setOrigin((ww - t.getLocalBounds().width) * -0.5F, hh * 0.25F);
    else if(textAlign == ui::TextAlign::right) t.setOrigin(t.getLocalBounds().width - ww, hh * 0.25F);
    else t.setOrigin(0, hh * 0.25F);
    t.setPosition(xx, yy);
    t.setFillColor(color);
    window_.draw(t);
}

void RenderSystem::RenderText(const std::string& text, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h,
const ui::CropArea& cropArea, const sf::Color& color, FontID id, ui::TextAlign textAlign) const {
    sf::View view = window_.getView();
    sf::View v = view;

    float viewPortX = 0.01F * (cropArea.left.p ? cropArea.left : cropArea.left / ui::aspectRatio);
    float viewPortY = 0.01F * (cropArea.top.p ? cropArea.top * ui::aspectRatio : cropArea.top);
    float viewPortW = 0.01F * (cropArea.width.p ? cropArea.width : cropArea.width / ui::aspectRatio);
    float viewPortH = 0.01F * (cropArea.height.p ? cropArea.height * ui::aspectRatio : cropArea.height);

    if(viewPortW < 0.000001F) viewPortW = 0.000001F;
    if(viewPortH < 0.000001F) viewPortH = 0.000001F;

    float wScale = 1 / viewPortW;
    float hScale = 1 / viewPortH;
    float fontScale = viewPortH / viewPortW;

    float cx = wScale * 0.01F * cropArea.left * (cropArea.left.p ? WW : HH);
    float cy = hScale * 0.01F * cropArea.top * (cropArea.top.p ? WW : HH);

    float xx = wScale * 0.01F * x * (x.p ? WW : HH) - cx;
    float yy = hScale * 0.01F * y * (y.p ? WW : HH) - cy;
    float ww = wScale * 0.01F * w * (w.p ? WW : HH);
    float hh = hScale * 0.01F * h * (h.p ? WW : HH);

    v.setViewport({viewPortX, viewPortY, viewPortW, viewPortH});

    //Font origin here is wrong by a very small margin (noticeable on very long strings)
    //Not sure where the error is, but this is close enough to not be a problem

    sf::Text t(text, resourceManager_.GetFont(id), (unsigned int)hh);
    if(textAlign == ui::TextAlign::center) t.setOrigin((ww / fontScale - t.getLocalBounds().width) * -0.5F, hh * 0.25F);
    else if(textAlign == ui::TextAlign::right) t.setOrigin(t.getLocalBounds().width - ww / fontScale, hh * 0.25F);
    else t.setOrigin(0, hh * 0.25F);

    t.setScale(fontScale, 1);
    t.setPosition(xx, yy);
    t.setFillColor(color);

    window_.setView(v);
    window_.draw(t);
    window_.setView(view);
}

ui::pfloat RenderSystem::MeasureText(const std::string& text, ui::pfloat h, ui::pfloat::P p, FontID id) const {
    float hh = 0.01F * h * (h.p ? WW : HH);
    sf::Text t(text, resourceManager_.GetFont(id), (unsigned int)hh);
    if(p == ui::pfloat::vw) return (100.0F * t.getLocalBounds().width / WW) VW;
    else return (100.0F * t.getLocalBounds().width / HH) VH;
}

//game text

void RenderSystem::RenderText(const std::string& text, ph::tfloat x, ph::tfloat y, ph::tfloat h, ph::tfloat rot, const Camera& camera, const sf::Color& color, FontID id) const {

    float xw = x.Lerp(ALPHA) / ph::fullscreenPlayArea;
    float yw = y.Lerp(ALPHA) / ph::fullscreenPlayArea;
    float hw = h.Lerp(ALPHA) / ph::fullscreenPlayArea;

    sf::Text t(text, resourceManager_.GetFont(id), (unsigned int)(hw * WW));
    t.setOrigin(t.getLocalBounds().width / 2, t.getLocalBounds().height);
    t.setPosition(0.5F * WW + xw * WW, 0.5F * HH - yw * WW);
    t.rotate(rot.Lerp(ALPHA));
    t.setFillColor(color);

    CameraDraw(t, camera);

}

// relative sprite

void RenderSystem::RenderSprite(SpriteID id, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h, const sf::Color& color) const {
    sf::Sprite sp = resourceManager_.GetSprite(id);
    float xx = 0.01F * x * (x.p ? WW : HH);
    float yy = 0.01F * y * (y.p ? WW : HH);
    float ww = 0.01F * w * (w.p ? WW : HH);
    float hh = 0.01F * h * (h.p ? WW : HH);
    sp.setPosition(xx, yy);
    sp.scale(ww / sp.getLocalBounds().width, hh / sp.getLocalBounds().height);
    sp.setColor(color);
    window_.draw(sp);
}

void RenderSystem::RenderSprite(SpriteID id, ui::pfloat x, ui::pfloat y, ui::pfloat w, ui::pfloat h, const ui::CropArea& cropArea, const sf::Color& color) const {
    sf::Sprite sp = resourceManager_.GetSprite(id);
    sf::View view = window_.getView();
    sf::View v = view;

    float viewPortX = 0.01F * (cropArea.left.p ? cropArea.left : cropArea.left / ui::aspectRatio);
    float viewPortY = 0.01F * (cropArea.top.p ? cropArea.top * ui::aspectRatio : cropArea.top);
    float viewPortW = 0.01F * (cropArea.width.p ? cropArea.width : cropArea.width / ui::aspectRatio);
    float viewPortH = 0.01F * (cropArea.height.p ? cropArea.height * ui::aspectRatio : cropArea.height);

    if(viewPortW < 0.000001F) viewPortW = 0.000001F;
    if(viewPortH < 0.000001F) viewPortH = 0.000001F;

    float wScale = 1 / viewPortW;
    float hScale = 1 / viewPortH;

    float cx = wScale * 0.01F * cropArea.left * (cropArea.left.p ? WW : HH);
    float cy = hScale * 0.01F * cropArea.top * (cropArea.top.p ? WW : HH);

    float xx = wScale * 0.01F * x * (x.p ? WW : HH) - cx;
    float yy = hScale * 0.01F * y * (y.p ? WW : HH) - cy;
    float ww = wScale * 0.01F * w * (w.p ? WW : HH);
    float hh = hScale * 0.01F * h * (h.p ? WW : HH);

    v.setViewport({viewPortX, viewPortY, viewPortW, viewPortH});

    sp.setPosition(xx, yy);
    sp.setScale(ww / sp.getLocalBounds().width, hh / sp.getLocalBounds().height);
    sp.setColor(color);

    window_.setView(v);
    window_.draw(sp);
    window_.setView(view);
}



// game sprite

void RenderSystem::RenderSprite(SpriteID id, ph::tfloat x, ph::tfloat y, ph::tfloat h, ph::tfloat rot, const Camera& camera) const {
    
    sf::Sprite sp = resourceManager_.GetSprite(id);
    float spw = sp.getLocalBounds().width;
    float sph = sp.getLocalBounds().height;
    sp.setOrigin(spw / 2, sph / 2);

    float xw = x.Lerp(ALPHA) / ph::fullscreenPlayArea;
    float yw = y.Lerp(ALPHA) / ph::fullscreenPlayArea;
    float hw = h.Lerp(ALPHA) / ph::fullscreenPlayArea;
    float ww = hw * (spw / sph);

    sp.setPosition(0.5F * WW + xw * WW, 0.5F * HH - yw * WW);
    sp.rotate(rot.Lerp(ALPHA));
    sp.scale(WW * ww / spw, WW * hw / sph);

    CameraDraw(sp, camera);

}
