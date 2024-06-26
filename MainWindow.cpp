#pragma once
#include "MainWindow.h"


extern std::pair<long long, float> stofu_(string str) {
	if (str.find('.') != string::npos) {
		return std::make_pair(0L, stof(str));
	}
	else {
		return std::make_pair(stoll(str), 0.0);
	}
}

MainWindow::MainWindow(QWidget* parent): CGAL::Qt::DemosMainWindow(parent)
{
  setupUi(this);
  this->viewer->setScene(&scene);
  connectActions();
  this->addAboutDemo(":/cgal/help/about_Alpha_shapes_3.html");
  this->addAboutCGAL();

  this->addRecentFiles(this->menuFile, this->actionQuit);
  connect(this, SIGNAL(openRecentFile(QString)),
	  this, SLOT(open(QString)));
}


void
MainWindow::connectActions()
{
  QObject::connect(this->actionLoad_New_File, SIGNAL(triggered()), 
		   this, SLOT(open_file()));

  QObject::connect(this->alphaSlider, SIGNAL(valueChanged(int)), 
		   this, SLOT(alphaChanged(int)));

  QObject::connect(this->alphaBox, SIGNAL(valueChanged(int)),
		   this, SLOT(alphaChanged(int)));

  QObject::connect(this->alphaSlider, SIGNAL(valueChanged(int)), 
		   this->alphaBox, SLOT(setValue(int)));

  QObject::connect(this->alphaBox, SIGNAL(valueChanged(int)), 
		   this->alphaSlider, SLOT(setValue(int)));

  QObject::connect(this, SIGNAL(sceneChanged()), 
		   this->viewer, SLOT(sceneChanged()));

  QObject::connect(this, SIGNAL(alphaChanged()), 
		   this->viewer, SLOT(update()));


  QObject::connect(this->actionQuit, SIGNAL(triggered()), 
		   qApp, SLOT(quit()));

  QObject::connect(this->Density, SIGNAL(clicked()), 
                   this, SLOT(show_Density()));
   
  
}

void
MainWindow::open_file()
{

  QString fileName = QFileDialog::getOpenFileName(this,
						  tr("Open Ply File"),
						  "./data",
                                                  tr("ply files (*.ply)"));

  if(! fileName.isEmpty()){
    open(fileName);
  }
}


void 
MainWindow::alphaChanged(int i)
{
  if (scene.alpha_shape.number_of_alphas() > 0){
    if(i < 100){
      int n = static_cast<int>((i * scene.alpha_shape.number_of_alphas())/ 100);
      if(n == 0) n++;
      scene.alpha_shape.set_alpha(scene.alpha_shape.get_nth_alpha(n));
    } else {
      Alpha_iterator alpha_end_it = scene.alpha_shape.alpha_end();
      scene.alpha_shape.set_alpha((*(--alpha_end_it))+1);
    }
  } else {
    scene.alpha_shape.set_alpha(0);
  }
  viewer->alphaChanged();  
  //Q_EMIT(alphaChanged());

  //viewer->initialize_buffers(); // Reinitialize buffers to update colors
  viewer->update();
}

void
MainWindow::open(QString fileName)
{
  // QApplication::setOverrideCursor(Qt::WaitCursor);
  // scene.alpha_shape.clear();
  // scene.points.clear();
  // std::ifstream ifs(qPrintable(fileName));
  // int n;
  // ifs >> n;
  // Point_3 p;
  // for(int i=0; i<n; i++){
  //   ifs >> p;
  //   scene.points.push_back(p);
  // }
  // timer.reset();
  // timer.start();
  // scene.alpha_shape.make_alpha_shape(scene.points.begin(), scene.points.end());
  // scene.alpha_shape.set_alpha(16);
  // timer.stop();
  

  // alphaSlider->setRange(0,100);
  // alphaSlider->setSliderPosition(50);

  // this->addToRecentFiles(fileName);
  // QApplication::restoreOverrideCursor();
  // viewer->changed();
  // Q_EMIT(sceneChanged());



  string galaxyID_;
	string lastProgenitorId_;
	string descendantId_;
	string haloID_;
	string subHaloID_;
	string fofID_;
	string treeId_;
	string firstProgenitorId_;
	string nextProgenitorId_;
	string type_;
	string snapnum_;
	string redshift_;
	string centralMvir_;
	string phkey_;
	string zIndex_;
	string ix_;
	string iy_;
	string iz_;
	string velX_;
	string velY_;
	string velZ_;
	string np_;
	string mvir_;
	string rvir_;
	string vvir_;
	string vmax_;
	string coldGas_;
	string stellarMass_;
	string bulgeMass_;
	string hotGas_;
	string ejectedMass_;
	string blackHoleMass_;
	string metalsColdGas_;
	string metalsStellarMass_;
	string metalsBulgeMass_;
	string metalsHotGas_;
	string metalsEjectedMass_;
	string sfr_;
	string sfrBulge_;
	string xrayLum_;
	string diskRadius_;
	string coolingRadius_;
	string mag_b_;
	string mag_v_;
	string mag_r_;
	string mag_i_;
	string mag_k_;
	string mag_bBulge_;
	string mag_vBulge_;
	string mag_rBulge_;
	string mag_iBulge_;
	string mag_kBulge_;
	string mag_bDust_;
	string mag_vDust_;
	string mag_rDust_;
	string mag_iDust_;
	string mag_kDust_;
	string massWeightedAge_;
	string random_;


  QApplication::setOverrideCursor(Qt::WaitCursor);
  scene.alpha_shape.clear();
  scene.points.clear();


	cout<<"Loading";

  
	std::ifstream ifs(qPrintable(fileName));


    if (!ifs.is_open()) {
        std::cerr << "Unable to open file " << qPrintable(fileName) << std::endl;
    }

    std::string line;
    bool header = true;
    int vertexCount = 0;

	int i=0;
    while (std::getline(ifs, line)) {
        if (header) {
            if (line.find("element vertex") != std::string::npos) {
                std::istringstream iss(line);
                std::string element, vertex;
                iss >> element >> vertex >> vertexCount;
                cout<<"vertex count: "<<vertexCount<<"\n";
            }
            if (line == "end_header") {
                header = false;
				        C.HPS.resize(vertexCount);
            }
        } 
		else {
            std::istringstream iss(line);
			string x_,y_,z_;
			iss>>galaxyID_>>lastProgenitorId_>>descendantId_>>haloID_>>subHaloID_>>fofID_>>treeId_>>firstProgenitorId_>>nextProgenitorId_>>type_>>snapnum_>>redshift_>>centralMvir_>>phkey_>>x_>>y_>>z_>>zIndex_>>ix_>>iy_>>iz_>>velX_>>velY_>>velZ_>>np_>>mvir_>>rvir_>>vvir_>>vmax_>>coldGas_>>stellarMass_>>bulgeMass_>>hotGas_>>ejectedMass_>>blackHoleMass_>>metalsColdGas_>>metalsStellarMass_>>metalsBulgeMass_>>metalsHotGas_>>metalsEjectedMass_>>sfr_>>sfrBulge_>>xrayLum_>>diskRadius_>>coolingRadius_>>mag_b_>>mag_v_>>mag_r_>>mag_i_>>mag_k_>>mag_bBulge_>>mag_vBulge_>>mag_rBulge_>>mag_iBulge_>>mag_kBulge_>>mag_bDust_>>mag_vDust_>>mag_rDust_>>mag_iDust_>>mag_kDust_>>massWeightedAge_>>random_;		
			
			
      C.HPS[i].galaxyID = stofu_(galaxyID_).first != 0 ? stofu_(galaxyID_).first : stofu_(galaxyID_).second;
			C.HPS[i].lastProgenitorId = stofu_(lastProgenitorId_).first != 0 ? stofu_(lastProgenitorId_).first : stofu_(lastProgenitorId_).second;
			C.HPS[i].descendantId = stofu_(descendantId_).first != 0 ? stofu_(descendantId_).first : stofu_(descendantId_).second;
			C.HPS[i].haloID = stofu_(haloID_).first != 0 ? stofu_(haloID_).first : stofu_(haloID_).second;
			C.HPS[i].subHaloID = stofu_(subHaloID_).first != 0 ? stofu_(subHaloID_).first : stofu_(subHaloID_).second;
			C.HPS[i].fofID = stofu_(fofID_).first != 0 ? stofu_(fofID_).first : stofu_(fofID_).second;
			C.HPS[i].treeId = stofu_(treeId_).first != 0 ? stofu_(treeId_).first : stofu_(treeId_).second;
			C.HPS[i].firstProgenitorId = stofu_(firstProgenitorId_).first != 0 ? stofu_(firstProgenitorId_).first : stofu_(firstProgenitorId_).second;
			C.HPS[i].nextProgenitorId = stofu_(nextProgenitorId_).first != 0 ? stofu_(nextProgenitorId_).first : stofu_(nextProgenitorId_).second;
			C.HPS[i].type = stofu_(type_).first != 0 ? stofu_(type_).first : stofu_(type_).second;
			C.HPS[i].snapnum = stofu_(snapnum_).first != 0 ? stofu_(snapnum_).first : stofu_(snapnum_).second;
			C.HPS[i].redshift = stofu_(redshift_).first != 0 ? stofu_(redshift_).first : stofu_(redshift_).second;
			C.HPS[i].centralMvir = stofu_(centralMvir_).first != 0 ? stofu_(centralMvir_).first : stofu_(centralMvir_).second;
			C.HPS[i].phkey = stofu_(phkey_).first != 0 ? stofu_(phkey_).first : stofu_(phkey_).second;
			C.HPS[i].x = stofu_(x_).first != 0 ? stofu_(x_).first : stofu_(x_).second;
			C.HPS[i].y = stofu_(y_).first != 0 ? stofu_(y_).first : stofu_(y_).second;
			C.HPS[i].z = stofu_(z_).first != 0 ? stofu_(z_).first : stofu_(z_).second;
			C.HPS[i].zIndex = stofu_(zIndex_).first != 0 ? stofu_(zIndex_).first : stofu_(zIndex_).second;
			C.HPS[i].ix = stofu_(ix_).first != 0 ? stofu_(ix_).first : stofu_(ix_).second;
			C.HPS[i].iy = stofu_(iy_).first != 0 ? stofu_(iy_).first : stofu_(iy_).second;
			C.HPS[i].iz = stofu_(iz_).first != 0 ? stofu_(iz_).first : stofu_(iz_).second;
			C.HPS[i].velX = stofu_(velX_).first != 0 ? stofu_(velX_).first : stofu_(velX_).second;
			C.HPS[i].velY = stofu_(velY_).first != 0 ? stofu_(velY_).first : stofu_(velY_).second;
			C.HPS[i].velZ = stofu_(velZ_).first != 0 ? stofu_(velZ_).first : stofu_(velZ_).second;
			C.HPS[i].np = stofu_(np_).first != 0 ? stofu_(np_).first : stofu_(np_).second;
			C.HPS[i].mvir = stofu_(mvir_).first != 0 ? stofu_(mvir_).first : stofu_(mvir_).second;
			C.HPS[i].rvir = stofu_(rvir_).first != 0 ? stofu_(rvir_).first : stofu_(rvir_).second;
			C.HPS[i].vvir = stofu_(vvir_).first != 0 ? stofu_(vvir_).first : stofu_(vvir_).second;
			C.HPS[i].vmax = stofu_(vmax_).first != 0 ? stofu_(vmax_).first : stofu_(vmax_).second;
			C.HPS[i].coldGas = stofu_(coldGas_).first != 0 ? stofu_(coldGas_).first : stofu_(coldGas_).second;
			C.HPS[i].stellarMass = stofu_(stellarMass_).first != 0 ? stofu_(stellarMass_).first : stofu_(stellarMass_).second;
			C.HPS[i].bulgeMass = stofu_(bulgeMass_).first != 0 ? stofu_(bulgeMass_).first : stofu_(bulgeMass_).second;
			C.HPS[i].hotGas = stofu_(hotGas_).first != 0 ? stofu_(hotGas_).first : stofu_(hotGas_).second;
			C.HPS[i].ejectedMass = stofu_(ejectedMass_).first != 0 ? stofu_(ejectedMass_).first : stofu_(ejectedMass_).second;
			C.HPS[i].blackHoleMass = stofu_(blackHoleMass_).first != 0 ? stofu_(blackHoleMass_).first : stofu_(blackHoleMass_).second;
			C.HPS[i].metalsColdGas = stofu_(metalsColdGas_).first != 0 ? stofu_(metalsColdGas_).first : stofu_(metalsColdGas_).second;
			C.HPS[i].metalsStellarMass = stofu_(metalsStellarMass_).first != 0 ? stofu_(metalsStellarMass_).first : stofu_(metalsStellarMass_).second;
			C.HPS[i].metalsBulgeMass = stofu_(metalsBulgeMass_).first != 0 ? stofu_(metalsBulgeMass_).first : stofu_(metalsBulgeMass_).second;
			C.HPS[i].metalsHotGas = stofu_(metalsHotGas_).first != 0 ? stofu_(metalsHotGas_).first : stofu_(metalsHotGas_).second;
			C.HPS[i].metalsEjectedMass = stofu_(metalsEjectedMass_).first != 0 ? stofu_(metalsEjectedMass_).first : stofu_(metalsEjectedMass_).second;
			C.HPS[i].sfr = stofu_(sfr_).first != 0 ? stofu_(sfr_).first : stofu_(sfr_).second;
			C.HPS[i].sfrBulge = stofu_(sfrBulge_).first != 0 ? stofu_(sfrBulge_).first : stofu_(sfrBulge_).second;
			C.HPS[i].xrayLum = stofu_(xrayLum_).first != 0 ? stofu_(xrayLum_).first : stofu_(xrayLum_).second;
			C.HPS[i].diskRadius = stofu_(diskRadius_).first != 0 ? stofu_(diskRadius_).first : stofu_(diskRadius_).second;
			C.HPS[i].coolingRadius = stofu_(coolingRadius_).first != 0 ? stofu_(coolingRadius_).first : stofu_(coolingRadius_).second;
			C.HPS[i].mag_b = stofu_(mag_b_).first != 0 ? stofu_(mag_b_).first : stofu_(mag_b_).second;
			C.HPS[i].mag_v = stofu_(mag_v_).first != 0 ? stofu_(mag_v_).first : stofu_(mag_v_).second;
			C.HPS[i].mag_r = stofu_(mag_r_).first != 0 ? stofu_(mag_r_).first : stofu_(mag_r_).second;
			C.HPS[i].mag_i = stofu_(mag_i_).first != 0 ? stofu_(mag_i_).first : stofu_(mag_i_).second;
			C.HPS[i].mag_k = stofu_(mag_k_).first != 0 ? stofu_(mag_k_).first : stofu_(mag_k_).second;
			C.HPS[i].mag_bBulge = stofu_(mag_bBulge_).first != 0 ? stofu_(mag_bBulge_).first : stofu_(mag_bBulge_).second;
			C.HPS[i].mag_vBulge = stofu_(mag_vBulge_).first != 0 ? stofu_(mag_vBulge_).first : stofu_(mag_vBulge_).second;
			C.HPS[i].mag_rBulge = stofu_(mag_rBulge_).first != 0 ? stofu_(mag_rBulge_).first : stofu_(mag_rBulge_).second;
			C.HPS[i].mag_iBulge = stofu_(mag_iBulge_).first != 0 ? stofu_(mag_iBulge_).first : stofu_(mag_iBulge_).second;
			C.HPS[i].mag_kBulge = stofu_(mag_kBulge_).first != 0 ? stofu_(mag_kBulge_).first : stofu_(mag_kBulge_).second;
			C.HPS[i].mag_bDust = stofu_(mag_bDust_).first != 0 ? stofu_(mag_bDust_).first : stofu_(mag_bDust_).second;
			C.HPS[i].mag_vDust = stofu_(mag_vDust_).first != 0 ? stofu_(mag_vDust_).first : stofu_(mag_vDust_).second;
			C.HPS[i].mag_rDust = stofu_(mag_rDust_).first != 0 ? stofu_(mag_rDust_).first : stofu_(mag_rDust_).second;
			C.HPS[i].mag_iDust = stofu_(mag_iDust_).first != 0 ? stofu_(mag_iDust_).first : stofu_(mag_iDust_).second;
			C.HPS[i].mag_kDust = stofu_(mag_kDust_).first != 0 ? stofu_(mag_kDust_).first : stofu_(mag_kDust_).second;
			C.HPS[i].massWeightedAge = stofu_(massWeightedAge_).first != 0 ? stofu_(massWeightedAge_).first : stofu_(massWeightedAge_).second;
			C.HPS[i].random = stofu_(random_).first != 0 ? stofu_(random_).first : stofu_(random_).second;
			
			C.HPS[i].position = Point_d(C.HPS[i].x,C.HPS[i].y,C.HPS[i].z);


      // Adding the points to the list scene.points
      scene.points.push_back(C.HPS[i].position);



			C.HPS[i].color = CGAL::Color((int) 128,(int) 128,(int) 128);
			i++;

            if (--vertexCount == 0) {
				
                break;
            }
        }
    }

  ifs.close();


  timer.reset();
  timer.start();
  scene.alpha_shape.make_alpha_shape(scene.points.begin(), scene.points.end());
  scene.alpha_shape.set_alpha(16);
  timer.stop();
  

  alphaSlider->setRange(0,100);
  alphaSlider->setSliderPosition(50);

  this->addToRecentFiles(fileName);
  QApplication::restoreOverrideCursor();
  viewer->changed();
  Q_EMIT(sceneChanged());

}


void MainWindow::show_Density()
{
    qDebug() << "Density button clicked!";

    C.Compute_Knearest_neighbors(20);
    C.cluster_detection(0.5, 4, 1);

	cout<<"density computed\n";
	std::vector<CGAL::Color> clrs;
	for (int i = 0; i < (int)C.HPS.size(); i++) {
		clrs.push_back(C.HPS[i].color);
	}
	viewer->changeColors(clrs);

    viewer->initialize_buffers(); // Reinitialize buffers to update colors
	viewer->update();
	
}



