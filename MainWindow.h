#pragma once
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "typedefs.h"
#include "ui_MainWindow.h"
#include <CGAL/Qt/DemosMainWindow.h>
#include <QSlider>
#include <QFileDialog>
#include "cloud_segmentation.h"
class QWidget;




class MainWindow : public CGAL::Qt::DemosMainWindow, private Ui::MainWindow
{
  Q_OBJECT

  public:
  MainWindow(QWidget* parent = 0);

  void connectActions();


  Scene scene;
  Timer timer;
  Cloud_segmentation C; 

public Q_SLOTS:
  void show_Density();
  virtual void open(QString fileName);
  void open_file();
  void alphaChanged(int i);

  Q_SIGNALS:
  void sceneChanged();
  void alphaChanged();

};




#endif
