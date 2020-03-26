//
// Created by twak on 14/10/2019.
//

#ifndef RESPONSIVEWINDOW_H
#define RESPONSIVEWINDOW_H

#include <QWidget>

using namespace std;

class ResponsiveWindow: public QWidget {
	//void createScroll(ResponsiveLayout * lay);
public:
    ResponsiveWindow();

protected:
    void createWidgets();
};


#endif //RESPONSIVEWINDOW_H
