//
// Created by twak on 07/10/2019.
//

#include "responsive_layout.h"
#include "responsive_label.h"
#include <iostream>


using namespace std;

// you should probably make extensive changes to this function

void vertical(const QRect &r, ResponsiveLabel * label, int &result_count) {
	if (label == NULL) // null: cast failed on pointer
		cout << "warning, unknown widget class in layout" << endl;
	else if (label->text() == kHomeLink) // left at bottom
		label->setGeometry(0, r.height() - 60, r.width() * 1 / 3-5, 60);
	else if (label->text() == kShoppingBasket) // middle at bottom
		label->setGeometry(r.width() * 1 / 3, r.height() - 60, r.width() * 1 / 3, 60);
	else if (label->text() == kSignIn) // right at bottom
		label->setGeometry(r.width() * 2 / 3+5, r.height() - 60, r.width() * 1 / 3, 60);
	else if (label->text() == kBackButton) // left at the top
		if (r.width() > 540)
			label->setGeometry(r.width() * 1 / 18 + r.x(), 5 + r.y(), r.width() * 1 / 18, 30);
		else
			label->setGeometry(r.x(), 5 + r.y(), r.width() * 1 / 6-5, 30);
	else if (label->text() == kSearchText) // middle at the top
		label->setGeometry(r.width() * 1 / 6, 5, r.width() * 2 / 3, 30);
	else if (label->text() == kNavTabs) // headers go at the top
		label->setGeometry(r.x(), 40 + r.y(), r.width(), 60);
	// only show a search button on small resolution, at the right of the window
	else if (label->text() == kSearchButton)// right at the top
		if (r.width() > 540)
			label->setGeometry(r.width() * 16 / 18 + r.x(), 5 + r.y(), r.width() * 1 / 18, 30);
		else
			label->setGeometry(r.width() * 5 / 6 + 5 + r.x(), 5 + r.y(), r.width() * 1 / 6, 30);
	// fixme: focus-group did not like this behaviour for the search result element.
	else if (label->text() == kScroll) {// scroll area : right of body
		label->setGeometry(r.width()*1/5, 105, r.width() * 4 / 5, r.height()-170);

	}else if (label->text() == kSearchOptions)//left of body
		label->setGeometry(r.x(), 105, r.width() * 1 / 5-5, r.height() - 170);
	else // otherwise: disappear label by moving out of bounds
		label->setGeometry(-1, -1, 0, 0);
}



void ResponsiveLayout::setGeometry(const QRect &r /* our layout should always fit inside r */ ) {

	int result_count = 0;

    QLayout::setGeometry(r);

    // for all the Widgets added in ResponsiveWindow.cpp
    for (int i = 0; i < list_.size(); i++) {

        QLayoutItem *o = list_.at(i);

        try {
            // cast the widget to one of our responsive labels
            ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());
		
			vertical(r, label, result_count);
        }
        catch (bad_cast) {
            // bad_case: cast failed on reference...
            cout << "warning, unknown widget class in layout" << endl;
        }
    }
}

// following methods provide a trivial list-based implementation of the QLayout class
int ResponsiveLayout::count() const {
    return list_.size();
}

QLayoutItem *ResponsiveLayout::itemAt(int idx) const {
    return list_.value(idx);
}

QLayoutItem *ResponsiveLayout::takeAt(int idx) {
    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ResponsiveLayout::addItem(QLayoutItem *item) {
    list_.append(item);
}

QSize ResponsiveLayout::sizeHint() const {
    return minimumSize();
}

QSize ResponsiveLayout::minimumSize() const {
    return QSize(320,320);
}


ResponsiveLayout::~ResponsiveLayout() {
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}
