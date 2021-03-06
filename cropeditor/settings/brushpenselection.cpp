#include "brushpenselection.hpp"
#include "ui_brushpenselection.h"

#include <QCheckBox>
#include <QColorDialog>
#include <QDoubleSpinBox>
#include <QInputDialog>
#include <QSlider>
#include <cropeditor/cropview.hpp>
#include <settings.hpp>

BrushPenSelection::BrushPenSelection(CropScene *scene) : QDialog(), ui(new Ui::BrushPenSelection) {
    ui->setupUi(this);
    ui->cosmetic->setChecked(scene->pen().isCosmetic());
    ui->widthSlider->setValue(scene->pen().width());
    ui->widthSpinner->setValue(scene->pen().widthF());
    this->setFocus();
    pen = scene->pen().color();
    brush = scene->brush().color();
    this->scene = scene;
}

BrushPenSelection::~BrushPenSelection() {
    delete ui;
}

void BrushPenSelection::on_penColor_clicked(bool) {
    pen = QColorDialog::getColor(pen, this, "Pen Color");
}

void BrushPenSelection::on_brushColor_clicked(bool) {
    brush = QColorDialog::getColor(brush, this, "Brush Color");
}

void BrushPenSelection::on_buttonBox_accepted() {
    scene->pen().setColor(pen);
    scene->pen().setCosmetic(ui->cosmetic->isChecked());
    scene->pen().setWidthF(ui->widthSpinner->value());
    scene->brush().setColor(brush);
    settings::settings().setValue("penColor", scene->pen().color());
    settings::settings().setValue("penCosmetic", scene->pen().isCosmetic());
    settings::settings().setValue("penWidth", scene->pen().widthF());
    settings::settings().setValue("brushColor", scene->brush().color());
    close();
}

void BrushPenSelection::on_buttonBox_rejected() {
    close();
}

void BrushPenSelection::on_widthSlider_sliderMoved(int position) {
    ui->widthSpinner->setValue(position / 100.);
}

void BrushPenSelection::on_widthSpinner_valueChanged(double arg) {
    ui->widthSlider->setValue(arg * 100);
}
