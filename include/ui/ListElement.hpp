#ifndef UI_LIST_HPP
#define UI_LIST_HPP

#include <ui/ColoredElement.hpp>
#include <memory>
#include <limits.h>

/**
 * No support for cropping.
 */
class ListElement: public ColoredElement{
public:
    ListElement(
        const ui::pfloat& top, 
        const ui::pfloat& left, 
        const ui::pfloat& height, 
        const ui::pfloat& width
    ): ColoredElement(top, left, height, width){}

    //virtual void Render(const RenderSystem&);

    /*virtual bool OnMouseDown(const sf::Mouse::Button& button, float xw, float yh);

    virtual bool OnMouseUp(const sf::Mouse::Button& button, float xw, float yh);

    virtual bool OnMouseMove(float xw, float yh);*/

    virtual bool OnMouseScroll(float delta, float xw, float yh);

    /**
     * Inserts the element into the list and returns an id that can be used to access or remove the element. 
     */
    int InsertElement(std::shared_ptr<Element> element);

    /**
     * Remove the element with the id returned by InsertElement.
     */
    void RemoveElement(int id);

    /**
     * Returns the element with the id returned by InsertElement.
     */
    std::shared_ptr<Element> GetElement(int id);

    /**
     * Set the amount of space between elements.
     */
    void SetSpacing(const ui::pfloat&);

    /**
     * Returns constant reference to the map of elements. 
     */
    const std::map<int, std::shared_ptr<Element>>& GetElements() const;

    /**
     * Removes all elements from the element list.
     */
    void ClearElements();

    virtual void SetPosition(ui::pfloat x, ui::pfloat y);

    virtual void SetTop(ui::pfloat top);

    virtual void SetLeft(ui::pfloat left);

    virtual void SetSize(ui::pfloat w, ui::pfloat h);

    virtual void SetHeight(ui::pfloat height);

    virtual void SetWidth(ui::pfloat width);

    virtual void OnWindowResize();

    virtual void SetOffsetX(const ui::pfloat& ox);
    virtual void SetOffsetX();

    virtual void SetOffsetY(const ui::pfloat& oy);
    virtual void SetOffsetY();

    virtual void SetCropArea(const ui::CropArea& a);
    virtual void SetCropArea();

    virtual void Hide();
    virtual void Show();

private:
    int nextId_ = INT_MIN;
    std::map<int, std::shared_ptr<Element>> elements_;
    ui::pfloat scrollOffset_;
    ui::pfloat spacing_ = 1 VH;
    float scrollMultiplier_ = 5000.0;

    void updateValues();

    ui::CropArea calcCropArea() const;
};

#endif