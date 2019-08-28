#pragma once

#include <utility>
#include <Wt/WContainerWidget.h>
#include <Wt/WLabel.h>
#include <Wt/WSlider.h>

struct ParameterPack : public Wt::WContainerWidget {
public:
    template<class tCB, class tCap>
    ParameterPack(const tCap& caption, int min, int max, tCB cb, std::function<std::string(int)>  converter = nullptr) : m_converter{std::move(converter)} {
        auto label = addWidget(std::make_unique<Wt::WLabel>());
        label->setText(caption);

        m_slider = addWidget(std::make_unique<Wt::WSlider>());
        m_slider->setRange(min, max);
        m_slider->setNativeControl(true);

        m_slider->changed().connect([this, _cb = std::move(cb)]() {
            _cb(m_slider->value());
            if(m_converter)
                m_value->setText(m_converter(m_slider->value()));
            else
                m_value->setText(std::to_string(m_slider->value()));
        });

        m_value = addWidget(std::make_unique<Wt::WLabel>());
        m_value->setText(std::to_string(m_slider->value()));
    }

    int getSliderValue() const {
        return m_slider->value();
    }

protected:
    Wt::WLabel* m_value = nullptr;
    Wt::WSlider* m_slider = nullptr;
    std::function<std::string(int)> m_converter;
};
