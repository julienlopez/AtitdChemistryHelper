#include "recipecomposer.hpp"

#include "utils.hpp"

#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>

namespace
{

void clearLayout(QLayout* layout)
{
    while(layout->count() > 0)
    {
        auto* item = layout->itemAt(0);
        if(item)
        {
            if(item->widget()) item->widget()->deleteLater();
            if(item->layout())
            {
                clearLayout(item->layout());
                item->layout()->deleteLater();
            }
            layout->removeItem(item);
        }
    }
}

class Box : public QGroupBox
{
public:
    Box(QWidget* parent = nullptr)
        : QGroupBox(tr("Requirement"), parent)
    {
        auto* lay = new QHBoxLayout;

        m_prop_cb = new QComboBox;
        m_prop_cb->addItems(Utils::propertyNames());
        lay->addWidget(m_prop_cb);

        m_value_cb = new QComboBox;
        m_value_cb->addItems({"-----", "----", "---", "--", "++", "+++", "++++", "+++++"});
        lay->addWidget(m_value_cb);

        setLayout(lay);
    }

    virtual ~Box() = default;

    QString toString() const
    {
        return m_prop_cb->currentText() + " (" + m_value_cb->currentText() + ")";
    }

private:
    QComboBox* m_prop_cb;
    QComboBox* m_value_cb;
};

class InnerWidget : public QWidget
{
public:
    InnerWidget(QWidget* parent = nullptr)
        : QWidget(parent)
    {
        setFixedHeight(100);
        m_layout = new QHBoxLayout;

        setLayout(m_layout);
    }

    virtual ~InnerWidget() = default;

    QString recipe() const
    {
        QStringList lst;
        std::transform(std::begin(m_boxes), std::end(m_boxes), std::back_inserter(lst), std::mem_fn(&Box::toString));
        return lst.join(" ");
    }

public slots:
    void clear()
    {
        clearLayout(m_layout);
    }

    void addBox()
    {
        auto* new_box = new Box;
        m_boxes << new_box;
        m_layout->addWidget(new_box);
    }

private:
    QHBoxLayout* m_layout;
    QVector<Box*> m_boxes;
};
} // namespace

RecipeComposer::RecipeComposer(QWidget* parent)
    : QWidget(parent)
{
    auto* inner_w = new InnerWidget;

    setFixedHeight(100);
    auto* lay = new QHBoxLayout;

    auto* b = new QPushButton(tr("Clear"));
    connect(b, &QPushButton::clicked, inner_w, &InnerWidget::clear);
    lay->addWidget(b);

    lay->addWidget(inner_w);
    lay->addStretch();

    b = new QPushButton(tr("+"));
    connect(b, &QPushButton::clicked, inner_w, &InnerWidget::addBox);
    lay->addWidget(b);

    b = new QPushButton(tr("Search"));
    connect(b, &QPushButton::clicked, [=]() { emit newRecipe(inner_w->recipe()); });
    lay->addWidget(b);

    setLayout(lay);
}
