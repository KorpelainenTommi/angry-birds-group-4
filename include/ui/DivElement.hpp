#ifndef UI_DIVELEMENT_HPP
#define UI_DIVELEMENT_HPP

#include <ui/ColoredElement.hpp>
#include <limits.h>

class DivElement: public ColoredElement{
public:
    DivElement(
        const ui::pfloat& top, 
        const ui::pfloat& left, 
        const ui::pfloat& height, 
        const ui::pfloat& width
    ): ColoredElement(top, left, height, width){};

    int InsertElement(std::shared_ptr<Element> element);

    void RemoveElement(int id);

    std::shared_ptr<Element> GetElement(int id);

    const std::map<int, std::shared_ptr<Element>>& GetElements() const;

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

    void updateValues();
};

#endif