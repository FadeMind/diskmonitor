#ifndef APPEARANCE_H
#define APPEARANCE_H

#include "ui_appearance.h"

class Appearance : public QWidget, public Ui::Appearance
{
public:
    explicit Appearance(QWidget *parent); 
};



#endif //APPEARANCE_H
