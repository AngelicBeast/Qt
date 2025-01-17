#ifndef CLOUD_SEGMENTATION_H
#define CLOUD_SEGMENTATION_H

#include "types.h"
#include "Ply.hpp"
#include "Visualization_Tools.h"
#include<fstream>
#include<utility>
#include<cmath>

using std::vector;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

using I::misc::Ply;
typedef unsigned char byte;

const CGAL::Color RED(255, 0, 0);
const CGAL::Color BLACK(0,0,0);
const CGAL::Color WHITE(255,255,255);

const double PI = 3.141592;

inline double distance_point_d(Point_d p1,Point_d p2){return sqrt(pow(p1.x()-p2.x(),2)+pow(p1.y()-p2.y(),2)+pow(p1.z()-p2.z(),2));}
inline bool my_sort_function (std::pair< int , double > i, std::pair< int , double> j){return ( i.second > j.second );}



inline double g(double x, double tau){
	return (x/(tau*tau))*exp((-x*x)/(2*tau*tau));
}





inline std::pair<long long,float> stofi_(string str){
	if(str.find('.')!=string::npos){
		return std::make_pair(0L, stof(str));
	}
	else{
		return std::make_pair(stoll(str),0.0);
	}
}


class Cloud_segmentation
{
	
	struct HPoint {
		Point_d position;
		Vector_3 normal;
		int primitive_index=-1;
		int cluster_index = -1;
		//test
		CGAL::Color color;
		long long galaxyID = -1;
		long long lastProgenitorId = -1;
		long long descendantId = -1;
		long long haloID = -1;
		long long subHaloID = -1;
		long long fofID = -1;
		long long treeId = -1;
		long long firstProgenitorId = -1;
		long long nextProgenitorId = -1;
		long long type = -1;
		long long snapnum = -1;
		float redshift = -1;
		float centralMvir = -1;
		long long phkey = -1;
		float x = -1;
		float y = -1;
		float z = -1;
		long long zIndex = -1;
		long long ix = -1;
		long long iy = -1;
		long long iz = -1;
		float velX = -1;
		float velY = -1;
		float velZ = -1;
		long long np = -1;
		float mvir = -1;
		float rvir = -1;
		float vvir = -1;
		float vmax = -1;
		float coldGas = -1;
		float stellarMass = -1;
		float bulgeMass = -1;
		float hotGas = -1;
		float ejectedMass = -1;
		float blackHoleMass = -1;
		float metalsColdGas = -1;
		float metalsStellarMass = -1;
		float metalsBulgeMass = -1;
		float metalsHotGas = -1;
		float metalsEjectedMass = -1;
		float sfr = -1;
		float sfrBulge = -1;
		float xrayLum = -1;
		float diskRadius = -1;
		float coolingRadius = -1;
		float mag_b = -1;
		float mag_v = -1;
		float mag_r = -1;
		float mag_i = -1;
		float mag_k = -1;
		float mag_bBulge = -1;
		float mag_vBulge = -1;
		float mag_rBulge = -1;
		float mag_iBulge = -1;
		float mag_kBulge = -1;
		float mag_bDust = -1;
		float mag_vDust = -1;
		float mag_rDust = -1;
		float mag_iDust = -1;
		float mag_kDust = -1;
		float massWeightedAge = -1;
		long long random = -1;
		double R_squared = -1;
		double cluster_density = -1;

		
		
		// bool operator<(const HPoint& other) const {
		// 	return density < other.density; 
		// }

		// bool operator>(const HPoint& other) const {
		// 	return density > other.density; 
		// }

		// bool operator==(const HPoint& other) const {
		// 	return density == other.density; 
		// }

	};


 

public:

	vector<HPoint> HPS;
	std::vector < std::vector < int > > spherical_neighborhood;
	std::vector < std::vector < int > > plane_point_index;
	std::vector< std::vector< int > > line_point_index;
	std::vector < Plane_3 > extracted_planes;
	std::vector < Line > extracted_lines;
	std::vector< Line > best_fit_lines;
	bounding_3 BBox_scan;
	double BBox_diagonal;
	std::vector < std::pair < int , double > > vector_pairs; 

	std::vector< bounding_2 > list_bbox_2d;
	std::vector<Point_d> list_centroid;
	std::vector< double > list_areas;
	bool normal_provided;

	//For clustering strategy 1:
	std::vector< std::vector< int > > cluster_indices;
	std::vector< Point_d > cluster_centroids;
	vector< Polyhedron > cluster_spheres;

	//For Mean shift Clustering
	std::vector<Point_d> cluster_centers;
	std::vector< std::vector< int > > cluster_indices_mean_shift;

	



bool load_ply_file(string filename){
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
	// normal_provided = false;
	cout<<"Loading";
	std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return false;
    }

    std::string line;
    bool header = true;
    int vertexCount = 0;

	int i=0;
    while (std::getline(file, line)) {
        if (header) {
            if (line.find("element vertex") != std::string::npos) {
                std::istringstream iss(line);
                std::string element, vertex;
                iss >> element >> vertex >> vertexCount;
                cout<<"vertex count: "<<vertexCount<<"\n";
            }
            if (line == "end_header") {
                header = false;
				HPS.resize(vertexCount);
            }
        } 
		else {
            std::istringstream iss(line);
			string x_,y_,z_;
			iss>>galaxyID_>>lastProgenitorId_>>descendantId_>>haloID_>>subHaloID_>>fofID_>>treeId_>>firstProgenitorId_>>nextProgenitorId_>>type_>>snapnum_>>redshift_>>centralMvir_>>phkey_>>x_>>y_>>z_>>zIndex_>>ix_>>iy_>>iz_>>velX_>>velY_>>velZ_>>np_>>mvir_>>rvir_>>vvir_>>vmax_>>coldGas_>>stellarMass_>>bulgeMass_>>hotGas_>>ejectedMass_>>blackHoleMass_>>metalsColdGas_>>metalsStellarMass_>>metalsBulgeMass_>>metalsHotGas_>>metalsEjectedMass_>>sfr_>>sfrBulge_>>xrayLum_>>diskRadius_>>coolingRadius_>>mag_b_>>mag_v_>>mag_r_>>mag_i_>>mag_k_>>mag_bBulge_>>mag_vBulge_>>mag_rBulge_>>mag_iBulge_>>mag_kBulge_>>mag_bDust_>>mag_vDust_>>mag_rDust_>>mag_iDust_>>mag_kDust_>>massWeightedAge_>>random_;		
			
			
            HPS[i].galaxyID = stofi_(galaxyID_).first != 0 ? stofi_(galaxyID_).first : stofi_(galaxyID_).second;
			HPS[i].lastProgenitorId = stofi_(lastProgenitorId_).first != 0 ? stofi_(lastProgenitorId_).first : stofi_(lastProgenitorId_).second;
			HPS[i].descendantId = stofi_(descendantId_).first != 0 ? stofi_(descendantId_).first : stofi_(descendantId_).second;
			HPS[i].haloID = stofi_(haloID_).first != 0 ? stofi_(haloID_).first : stofi_(haloID_).second;
			HPS[i].subHaloID = stofi_(subHaloID_).first != 0 ? stofi_(subHaloID_).first : stofi_(subHaloID_).second;
			HPS[i].fofID = stofi_(fofID_).first != 0 ? stofi_(fofID_).first : stofi_(fofID_).second;
			HPS[i].treeId = stofi_(treeId_).first != 0 ? stofi_(treeId_).first : stofi_(treeId_).second;
			HPS[i].firstProgenitorId = stofi_(firstProgenitorId_).first != 0 ? stofi_(firstProgenitorId_).first : stofi_(firstProgenitorId_).second;
			HPS[i].nextProgenitorId = stofi_(nextProgenitorId_).first != 0 ? stofi_(nextProgenitorId_).first : stofi_(nextProgenitorId_).second;
			HPS[i].type = stofi_(type_).first != 0 ? stofi_(type_).first : stofi_(type_).second;
			HPS[i].snapnum = stofi_(snapnum_).first != 0 ? stofi_(snapnum_).first : stofi_(snapnum_).second;
			HPS[i].redshift = stofi_(redshift_).first != 0 ? stofi_(redshift_).first : stofi_(redshift_).second;
			HPS[i].centralMvir = stofi_(centralMvir_).first != 0 ? stofi_(centralMvir_).first : stofi_(centralMvir_).second;
			HPS[i].phkey = stofi_(phkey_).first != 0 ? stofi_(phkey_).first : stofi_(phkey_).second;
			HPS[i].x = stofi_(x_).first != 0 ? stofi_(x_).first : stofi_(x_).second;
			HPS[i].y = stofi_(y_).first != 0 ? stofi_(y_).first : stofi_(y_).second;
			HPS[i].z = stofi_(z_).first != 0 ? stofi_(z_).first : stofi_(z_).second;
			HPS[i].zIndex = stofi_(zIndex_).first != 0 ? stofi_(zIndex_).first : stofi_(zIndex_).second;
			HPS[i].ix = stofi_(ix_).first != 0 ? stofi_(ix_).first : stofi_(ix_).second;
			HPS[i].iy = stofi_(iy_).first != 0 ? stofi_(iy_).first : stofi_(iy_).second;
			HPS[i].iz = stofi_(iz_).first != 0 ? stofi_(iz_).first : stofi_(iz_).second;
			HPS[i].velX = stofi_(velX_).first != 0 ? stofi_(velX_).first : stofi_(velX_).second;
			HPS[i].velY = stofi_(velY_).first != 0 ? stofi_(velY_).first : stofi_(velY_).second;
			HPS[i].velZ = stofi_(velZ_).first != 0 ? stofi_(velZ_).first : stofi_(velZ_).second;
			HPS[i].np = stofi_(np_).first != 0 ? stofi_(np_).first : stofi_(np_).second;
			HPS[i].mvir = stofi_(mvir_).first != 0 ? stofi_(mvir_).first : stofi_(mvir_).second;
			HPS[i].rvir = stofi_(rvir_).first != 0 ? stofi_(rvir_).first : stofi_(rvir_).second;
			HPS[i].vvir = stofi_(vvir_).first != 0 ? stofi_(vvir_).first : stofi_(vvir_).second;
			HPS[i].vmax = stofi_(vmax_).first != 0 ? stofi_(vmax_).first : stofi_(vmax_).second;
			HPS[i].coldGas = stofi_(coldGas_).first != 0 ? stofi_(coldGas_).first : stofi_(coldGas_).second;
			HPS[i].stellarMass = stofi_(stellarMass_).first != 0 ? stofi_(stellarMass_).first : stofi_(stellarMass_).second;
			HPS[i].bulgeMass = stofi_(bulgeMass_).first != 0 ? stofi_(bulgeMass_).first : stofi_(bulgeMass_).second;
			HPS[i].hotGas = stofi_(hotGas_).first != 0 ? stofi_(hotGas_).first : stofi_(hotGas_).second;
			HPS[i].ejectedMass = stofi_(ejectedMass_).first != 0 ? stofi_(ejectedMass_).first : stofi_(ejectedMass_).second;
			HPS[i].blackHoleMass = stofi_(blackHoleMass_).first != 0 ? stofi_(blackHoleMass_).first : stofi_(blackHoleMass_).second;
			HPS[i].metalsColdGas = stofi_(metalsColdGas_).first != 0 ? stofi_(metalsColdGas_).first : stofi_(metalsColdGas_).second;
			HPS[i].metalsStellarMass = stofi_(metalsStellarMass_).first != 0 ? stofi_(metalsStellarMass_).first : stofi_(metalsStellarMass_).second;
			HPS[i].metalsBulgeMass = stofi_(metalsBulgeMass_).first != 0 ? stofi_(metalsBulgeMass_).first : stofi_(metalsBulgeMass_).second;
			HPS[i].metalsHotGas = stofi_(metalsHotGas_).first != 0 ? stofi_(metalsHotGas_).first : stofi_(metalsHotGas_).second;
			HPS[i].metalsEjectedMass = stofi_(metalsEjectedMass_).first != 0 ? stofi_(metalsEjectedMass_).first : stofi_(metalsEjectedMass_).second;
			HPS[i].sfr = stofi_(sfr_).first != 0 ? stofi_(sfr_).first : stofi_(sfr_).second;
			HPS[i].sfrBulge = stofi_(sfrBulge_).first != 0 ? stofi_(sfrBulge_).first : stofi_(sfrBulge_).second;
			HPS[i].xrayLum = stofi_(xrayLum_).first != 0 ? stofi_(xrayLum_).first : stofi_(xrayLum_).second;
			HPS[i].diskRadius = stofi_(diskRadius_).first != 0 ? stofi_(diskRadius_).first : stofi_(diskRadius_).second;
			HPS[i].coolingRadius = stofi_(coolingRadius_).first != 0 ? stofi_(coolingRadius_).first : stofi_(coolingRadius_).second;
			HPS[i].mag_b = stofi_(mag_b_).first != 0 ? stofi_(mag_b_).first : stofi_(mag_b_).second;
			HPS[i].mag_v = stofi_(mag_v_).first != 0 ? stofi_(mag_v_).first : stofi_(mag_v_).second;
			HPS[i].mag_r = stofi_(mag_r_).first != 0 ? stofi_(mag_r_).first : stofi_(mag_r_).second;
			HPS[i].mag_i = stofi_(mag_i_).first != 0 ? stofi_(mag_i_).first : stofi_(mag_i_).second;
			HPS[i].mag_k = stofi_(mag_k_).first != 0 ? stofi_(mag_k_).first : stofi_(mag_k_).second;
			HPS[i].mag_bBulge = stofi_(mag_bBulge_).first != 0 ? stofi_(mag_bBulge_).first : stofi_(mag_bBulge_).second;
			HPS[i].mag_vBulge = stofi_(mag_vBulge_).first != 0 ? stofi_(mag_vBulge_).first : stofi_(mag_vBulge_).second;
			HPS[i].mag_rBulge = stofi_(mag_rBulge_).first != 0 ? stofi_(mag_rBulge_).first : stofi_(mag_rBulge_).second;
			HPS[i].mag_iBulge = stofi_(mag_iBulge_).first != 0 ? stofi_(mag_iBulge_).first : stofi_(mag_iBulge_).second;
			HPS[i].mag_kBulge = stofi_(mag_kBulge_).first != 0 ? stofi_(mag_kBulge_).first : stofi_(mag_kBulge_).second;
			HPS[i].mag_bDust = stofi_(mag_bDust_).first != 0 ? stofi_(mag_bDust_).first : stofi_(mag_bDust_).second;
			HPS[i].mag_vDust = stofi_(mag_vDust_).first != 0 ? stofi_(mag_vDust_).first : stofi_(mag_vDust_).second;
			HPS[i].mag_rDust = stofi_(mag_rDust_).first != 0 ? stofi_(mag_rDust_).first : stofi_(mag_rDust_).second;
			HPS[i].mag_iDust = stofi_(mag_iDust_).first != 0 ? stofi_(mag_iDust_).first : stofi_(mag_iDust_).second;
			HPS[i].mag_kDust = stofi_(mag_kDust_).first != 0 ? stofi_(mag_kDust_).first : stofi_(mag_kDust_).second;
			HPS[i].massWeightedAge = stofi_(massWeightedAge_).first != 0 ? stofi_(massWeightedAge_).first : stofi_(massWeightedAge_).second;
			HPS[i].random = stofi_(random_).first != 0 ? stofi_(random_).first : stofi_(random_).second;
			
			HPS[i].position = Point_d(HPS[i].x,HPS[i].y,HPS[i].z);
			HPS[i].color = CGAL::Color((int) 128,(int) 128,(int) 128);
			i++;

            if (--vertexCount == 0) {
				
                break;
            }
        }
    }
	// cout<<HPS[0].x<<" "<<HPS[0].y<<" "<<HPS[0].z<<"\n";
	// cout<<HPS[0].position.x()<<"\n";
    file.close();
    return true;
}

bool load_points(string filename,bool color_)
	{
		cout<<"Loading ";
		cout <<filename;

		HPS.clear();
		Ply ply;
		normal_provided=false;

		if (!ply.open(filename,true)){ return false;}
		
		for (Ply::ElementsIterator it = ply.elements_begin(); it != ply.elements_end(); ++it){
			const Ply::Element& element = *it;
			

			if (element.name() != "vertex"){
				if (!ply.skip(element)){ ply.close(); return false;}
				continue;
			}

			/* Check the properties are what we expect */
			if ((element.property(0).name() != "x")||(element.property(1).name() != "y")||(element.property(2).name() != "z")){cerr << "Unexpected vertex properties in the PLY file" << endl; ply.close(); return false;}

		
			size_t num_vertices = element.count();
			HPS.resize(num_vertices);

			

		if (element.num_properties() == 6 && !color_) {
				normal_provided=true;
				for (size_t i=0; i<num_vertices; i++){
					double x,y,z;
					double nx,ny,nz;

					if ((!ply.read(element.property(0), x))||(!ply.read(element.property(1), y))||(!ply.read(element.property(2), z))){cerr << "error while reading (pos) vertex " << i+1 << endl; ply.close(); return false;}	
					if ((!ply.read(element.property(3), nx))||(!ply.read(element.property(4), ny))||(!ply.read(element.property(5), nz))){cerr << "error while reading attribut " << i+1 << endl; ply.close(); return false; }

					HPS[i].position = Point_d(x,y,z);
					HPS[i].normal = Vector_3(nx,ny,nz);
				}
			}
		else if(element.num_properties() == 6 && color_){
			normal_provided=false;
				for (size_t i=0; i<num_vertices; i++){
					double x,y,z;
					int r,g,b;

					if ((!ply.read(element.property(0), x))||(!ply.read(element.property(1), y))||(!ply.read(element.property(2), z))){cerr << "error while reading (pos) vertex " << i+1 << endl; ply.close(); return false;}	
					if ((!ply.read(element.property(3), r))||(!ply.read(element.property(4), g))||(!ply.read(element.property(5), b))){cerr << "error while reading attribut " << i+1 << endl; ply.close(); return false; }

					HPS[i].position = Point_d(x,y,z);
					CGAL::Color clr((int) r,(int) g,(int) b);
					HPS[i].color = clr;
				}
		}

			else if (element.num_properties() == 3) {
				for (size_t i=0; i<num_vertices; i++){
					double x,y,z;

					if ((!ply.read(element.property(0), x))||(!ply.read(element.property(1), y))||(!ply.read(element.property(2), z))){cerr << "error while reading (pos) vertex " << i+1 << endl; ply.close(); return false;}	
				
					HPS[i].position = Point_d(x,y,z);

					if(i%10000==0) cout<<i/10000<<"  ";
				}
			}

			


			else if (element.num_properties() == 7) {
				normal_provided=false;
				for (size_t i=0; i<num_vertices; i++){
					double x,y,z;
					int r,g,b,alpha;

					if ((!ply.read(element.property(0), x))||(!ply.read(element.property(1), y))||(!ply.read(element.property(2), z))){cerr << "error while reading (pos) vertex " << i+1 << endl; ply.close(); return false;}	
					if ((!ply.read(element.property(3), r))||(!ply.read(element.property(4), g))||(!ply.read(element.property(5), b))||(!ply.read(element.property(6), alpha))){cerr << "error while reading attribut " << i+1 << endl; ply.close(); return false; }

					HPS[i].position = Point_d(x,y,z);
					HPS[i].color = CGAL::Color(r,g,b);
				}
			}


			else {cerr << "Unexpected vertex properties in the PLY file" << endl; ply.close(); return false;}
		}

		ply.close();


		cout<<" ("<<HPS.size()<<" points)"<<endl;   
		return true;
	}



bool save_PC_ball(char* filename, double size, double step)
	{
		vector<Polyhedron> vec_poly;
		vector<CGAL::Color> vec_color;

		for(int i=0;i<HPS.size();i++){
				Polyhedron P=createSpherette(HPS[i].position,size,step);
				vec_poly.push_back(P);
				vec_color.push_back(HPS[i].color);
		}

	
	save_listpolyhedron2ply(vec_poly,filename, vec_color);

		return true;
	}


bool Cloud_segmentation::sort_point_by_planarity(){
	
	cout<<endl<<"start sort";
	
	for(int i=0; i<(int)HPS.size();i++){
		
		std::list<Point_d> list_points; list_points.push_back(HPS[i].position);
		
		Plane_3 optimal_plane;
		for(int it=0;it<(int)spherical_neighborhood[i].size();it++) list_points.push_back(HPS[spherical_neighborhood[i][it]].position);

		double var=linear_least_squares_fitting_3(list_points.begin(),list_points.end(),optimal_plane, CGAL::Dimension_tag<0>());
		
		std::pair<int,double> pair_temp;
		pair_temp.first=i;
		pair_temp.second=var;
		vector_pairs.push_back(pair_temp);

	}

	std::sort(vector_pairs.begin(),vector_pairs.end(),my_sort_function);

	//visu
	std::vector < Point_d > pointis;
	std::vector < CGAL::Color > coloris;

	for(int i=0; i<(int)vector_pairs.size();i++){
		double rate=(double)255*i/vector_pairs.size();
		CGAL::Color col(255,255-(int)rate, 255-(int)rate);
		pointis.push_back(HPS[vector_pairs[i].first].position);
		coloris.push_back(col);
	}
	char *n_colored= "pc_col.ply";
	colorpointset2ply(n_colored,pointis, coloris);

	cout<<" -> end sort"<<endl;
return true;
}



bool Cloud_segmentation::Compute_Knearest_neighbors(int K)
	{

		cout<<"Computing the K-nearest neighbors";

		spherical_neighborhood.clear();

		// cout<<HPS.size();
		//1-Neighborhood computation and reset the attributes of the structure points
		std::map<Point_d,int> map_indice_point;

		for(int i=0;i<HPS.size();i++){
			std::vector < int > plane_index_list_tmp;   //Why?
			Point_d pt=HPS[i].position;
			map_indice_point[pt]=i;
		}
		

		std::list<Point_d> list_points;
		for(int i=0;i<(int)HPS.size();i++){
			Point_d pt=HPS[i].position;
			// cout<<pt.x()<<pt.y()<<pt.z()<<"\n";
			list_points.push_back(pt);
		}
		

		Tree tree(list_points.begin(), list_points.end());
		// cout<<list_points.size()<<"\n";
		

		for(int i=0;i<(int)HPS.size();i++){
			Point_d query=HPS[i].position;
			
			Neighbor_search search(tree, query, K+1);
			// cout<<"here\n";
			

			std::vector < int > index_of_neighbors;
			for(Neighbor_search::iterator it = search.begin(); it != search.end(); ++it){
				//if(std::sqrt(it->second)<0.5){
					std::map<Point_d,int>::iterator iter =map_indice_point.begin();
					iter= map_indice_point.find(it->first);
					if( iter != map_indice_point.end() && iter->second!=i ) index_of_neighbors.push_back(iter->second);
				//}else{break;}
			}
			spherical_neighborhood.push_back(index_of_neighbors);
		}
		

		//2-creation of the bounding box
		BBox_scan = CGAL::bounding_box(list_points.begin(), list_points.end());
		BBox_diagonal=sqrt( pow(BBox_scan.xmax()-BBox_scan.xmin(),2) +  pow(BBox_scan.ymax()-BBox_scan.ymin(),2) +  pow(BBox_scan.zmax()-BBox_scan.zmin(),2) );
	
		cout<<endl<<endl;
		

		return true;
	}


bool Cloud_segmentation::compute_normal()
	{
		int nb_max_neighbors=10;
		for(int k=0;k<(int)HPS.size();k++){

			std::list<Point_d> list_pts;
			list_pts.push_back(HPS[k].position);

			for(int n=0;n<(int)spherical_neighborhood[k].size();n++){
				
				if(n<nb_max_neighbors){
					Point_d pt_temp=HPS[spherical_neighborhood[k][n]].position;
					list_pts.push_back(pt_temp);
				}
				else break;
			}
			
			Plane_3 plane_temp;
			double average_distance=linear_least_squares_fitting_3(list_pts.begin(),list_pts.end(),plane_temp, CGAL::Dimension_tag<0>());

			Vector_3 normal_temp=plane_temp.orthogonal_vector();

		//	int 
		/*	for(int n=0;n<(int)spherical_neighborhood[k].size();n++){
				if(k>spherical_neighborhood[k][n] && n<nb_max_neighbors){
					int index_neighbor=spherical_neighborhood[k][n];
					if(HPS[index_neighbor].normal * normal_temp <0 ) normal_temp=-normal_temp;
				break;
				}
				else break;
			}*/

			FT normal_temp_norm=1/sqrt(normal_temp.squared_length());
			HPS[k].normal = normal_temp_norm*normal_temp;
		}


		//normal re-orientation

		std::vector<bool> is_proceeded;
		for(int i=0; i<(int)HPS.size();i++) is_proceeded.push_back(false);
		int conti=0;
		
		for(int i=0; i<(int)HPS.size();i++){

			if(!is_proceeded[i]){

				is_proceeded[i]=true;

				if(spherical_neighborhood[i].size()>1){
				
				conti++;
			//	cout<<conti<<"  ";

				//initialization containers
				std::vector < int > index_container_former_ring; index_container_former_ring.push_back(i);
				std::list < int > index_container_current_ring;

				//propagation
				bool propagation=true;
				do{

					propagation=false;
					if(conti<10) cout<<index_container_former_ring.size()<<"  ";
					for(int k=0;k<(int)index_container_former_ring.size();k++){

						int point_index=index_container_former_ring[k];
						Vector_3 point_normal=HPS[point_index].normal;

						int Nb_neigh=std::min((double)spherical_neighborhood[point_index].size(),10.);
						//int Nb_neigh=spherical_neighborhood[point_index].size();

						for(int it=0;it<Nb_neigh;it++){

							int neighbor_index=spherical_neighborhood[point_index][it];
							
							if( !is_proceeded[neighbor_index]){
									
									Vector_3 neighbor_normal=HPS[neighbor_index].normal;
									if((point_normal*neighbor_normal) < 0) HPS[neighbor_index].normal = -neighbor_normal;
									if(HPS[point_index].normal*HPS[neighbor_index].normal < 0) cout<<" PB!! ";
									is_proceeded[neighbor_index]=true;
									propagation=true;
									index_container_current_ring.push_back(neighbor_index);	
							}
						}
					}
				

					//update containers
					index_container_former_ring.clear();
					for(std::list < int >::iterator it = index_container_current_ring.begin(); it != index_container_current_ring.end(); ++it){
						index_container_former_ring.push_back(*it);
						//index_container.push_back(*it);
					}
					index_container_current_ring.clear();

				}while(propagation);
				if(conti<10) cout<<endl<<endl;

				}
			} 
		}

		for(int k=0;k<(int)HPS.size();k++) {HPS[k].color=BLACK;}

		for(int k=0;k<(int)HPS.size();k++){
			for(int n=0;n<(int)spherical_neighborhood[k].size();n++){
				if( HPS[spherical_neighborhood[k][n]].normal * HPS[k].normal < 0  ){
					HPS[spherical_neighborhood[k][n]].color=RED;
					HPS[k].color = RED; //CGAL::Color(1, 0, 0);
				}
			}
		}



		return true;
	}



void compute_best_fit_lines(){
	for(int i=0;i<(int) HPS.size();i++){
		Line best_fit_line;
		std::list< Point_d > listp;
		for(int k:spherical_neighborhood[i]){
			listp.push_back(HPS[k].position);
		}
		HPS[i].R_squared = linear_least_squares_fitting_3(listp.begin(),listp.end(),best_fit_line, CGAL::Dimension_tag<0>());
		int r = 255 * pow((HPS[i].R_squared),2), g = 0, b = 0;
		CGAL::Color clr ((int) r,(int) g,(int) b);
		HPS[i].color = clr;
		best_fit_lines.push_back(best_fit_line);
	}
	return;
}


bool Cloud_segmentation::linear_fitting(float epsilon, int Nmin){
	cout<<"Linear Fiting \n";
	line_point_index.clear();
	extracted_lines.clear();

	for(int i=0; i<(int)HPS.size();i++) HPS[i].primitive_index=-1;
	int class_index=-1;
	compute_best_fit_lines();

	int nb_points_10percent=HPS.size()/10;
		
	for(int i=0; i<(int)HPS.size();i++){
		if(i%nb_points_10percent==0) cout<<". ";

		if(HPS[i].primitive_index==-1){

				//update the index of primitive
				class_index++;
				HPS[i].primitive_index=class_index;

				int conti=0; 	//for accelerate least_square fitting 

				//characteristics of the seed
				// Vector_3 normal_seed=HPS[i].normal;
				Point_d pt_seed=HPS[i].position;
				Line optimal_line = best_fit_lines[i];

				

				//initialization containers
				std::vector < int > index_container; index_container.push_back(i);
				std::vector < int > index_container_former_ring; index_container_former_ring.push_back(i);
				std::list < int > index_container_current_ring;

				//propagation
				bool propagation=true;
				do{

					propagation=false;

					for(int k=0;k<(int)index_container_former_ring.size();k++){

						int point_index=index_container_former_ring[k];

						int Nb_neigh=(int)spherical_neighborhood[point_index].size();   //changed from std::min((double)spherical_neighborhood[point_index].size(),10.)
						for(int it=0;it<Nb_neigh;it++){

							int neighbor_index=spherical_neighborhood[point_index][it];
							
							if( HPS[neighbor_index].primitive_index==-1 ){
								
								Point_d neighbor=HPS[neighbor_index].position;
								// Point_d neighbor_projection=optimal_plane.projection(neighbor); 
								// double distance=distance_point_d(neighbor,neighbor_projection);

								if(sqrt(CGAL::squared_distance(neighbor,optimal_line)) < epsilon ){ 

									HPS[neighbor_index].primitive_index=class_index;
									propagation=true;
									index_container_current_ring.push_back(neighbor_index);
									conti++;

									if( (conti<50 && conti%10==0) || (conti>50 && conti%500==0)){
										std::list < Point_d > listp;
										for(int pm=0;pm<(int)index_container.size();pm++){
											int yyh=index_container[pm];
											Point_d ptza=HPS[yyh].position;
											listp.push_back(ptza);
										}

										Line reajusted_line;
										double average_distance=linear_least_squares_fitting_3(listp.begin(),listp.end(),reajusted_line, CGAL::Dimension_tag<0>());
										optimal_line=reajusted_line;

									}
								}
							}
						}
					}

					//update containers
					index_container_former_ring.clear();
					for(std::list < int >::iterator it = index_container_current_ring.begin(); it != index_container_current_ring.end(); ++it){
						index_container_former_ring.push_back(*it);
						index_container.push_back(*it);
					}
					index_container_current_ring.clear();

				//	if(index_container.size()>40) propagation=false;

				}while(propagation);
				

				//A: reject inlier with distance to optimal line > epsilon  + test the number of inliers -> reject if inferior to Nmin 
				std::vector < Point_d > listp;
				for(int k=0; k<(int)index_container.size(); k++){
					int yy=index_container[k];
					Point_d pt=HPS[yy].position;
					listp.push_back(pt);
				}

				Line final_line;
				double erro=linear_least_squares_fitting_3(listp.begin(),listp.end(),final_line, CGAL::Dimension_tag<0>());

				std::vector < int > index_container_tmp;
				for(int k=0; k<(int)index_container.size(); k++){
					Point_d inlier=HPS[index_container[k]].position;
					// Point_d pt_projected=plane_found.projection(inlier); 
					double distance= sqrt(squared_distance(inlier,final_line));

					if(distance < epsilon) index_container_tmp.push_back(index_container[k]);
					else HPS[index_container[k]].primitive_index=-1;
				}
			
				if(index_container_tmp.size()>=Nmin) line_point_index.push_back(index_container_tmp);
				//end A
				
					
				
				//or B: just test the number of inliers -> reject if inferior to Nmin
			/*	if(index_container.size()>=Nmin){
					plane_point_index.push_back(index_container);
				}*/
				//end B
			

				else{ 
					class_index--;
					HPS[i].primitive_index=-1;
					for(int k=0;k<(int)index_container.size();k++) HPS[index_container[k]].primitive_index=-1; 
				}
		} 
		

	}
	compute_error(0,"C:/Users/smaheshw/Code/exemple/results-1.txt");
	// cluster_removal(epsilon,Nmin)
	return true;


}


std::vector< Polyhedron > Cloud_segmentation::display_lines_as_cylinders(float radius){
	std::vector< Polyhedron > Cylinders;
	int sz = line_point_index.size();
	for(int i=0;i<sz;i++){
		Line line = extracted_lines[i];
		std::vector< Point_d > projection_of_points;
		for(int j:line_point_index[i]){
			Point_d actual_point = HPS[j].position;
			Point_d pt_projection = line.projection(actual_point);
			projection_of_points.push_back(pt_projection);
		}
		Point_d centre = projection_of_points[0];
		Point_d pt1 = projection_of_points[1];
		double norm1 = distance_point_d(centre,pt1);
		Vector_3 right((pt1.x() - centre.x())/norm1,(pt1.y() - centre.y())/norm1,(pt1.z() - centre.z())/norm1);
		Vector_3 left((centre.x() - pt1.x())/norm1, (centre.y() - pt1.y())/norm1, (centre.z() - pt1.z())/norm1);
		std::vector< std::pair< Point_d, double > > right_pts = {std::make_pair(pt1,norm1)};
		std::vector< std::pair< Point_d, double > > left_pts;
		for(int i=2;i< (int) projection_of_points.size();i++){
			double norm2 = distance_point_d(centre,projection_of_points[i]);
			Vector_3 v((projection_of_points[i].x() - centre.x())/norm2, (projection_of_points[i].y() - centre.y())/norm2, (projection_of_points[i].z() - centre.z())/norm2);
			if(v * right > 0.95)
				right_pts.push_back(std::make_pair(projection_of_points[i],norm2));
			else
				left_pts.push_back(std::make_pair(projection_of_points[i],norm2));
			
		}
		Point_d max_right = centre, max_left = centre;
		double max_dist_right = 0, max_dist_left = 0;
		for(auto p: right_pts){
			if(p.second > max_dist_right){
				max_right = p.first;
				max_dist_right = p.second;
			}
		}

		for(auto p: left_pts){
			if(p.second > max_dist_left){
				max_left = p.first;
				max_dist_left = p.second;
			}
		}
		Polyhedron P = createCylinder(max_right, max_left, radius);
		Cylinders.push_back(P);

	}
	return Cylinders;
}
	


bool Cloud_segmentation::region_growing(float epsilon, int Nmin){
				
		cout<<"Region growing ";

		//Initialization structures
		plane_point_index.clear();
		extracted_planes.clear();
		list_centroid.clear();
		list_areas.clear();

		double maximal_deviation_of_normals=0.75; //default 0.75 // abs(cos angle) minimal between normal of the considered point and normal of the growing plane (better to be close to 1 when Nmin is high)

		//Initialization structures
		plane_point_index.clear();

		for(int i=0; i<(int)HPS.size();i++) HPS[i].primitive_index=-1;
		
		int class_index=-1;
	
		// for each point, if not inliers yet..
		int nb_points_10percent=HPS.size()/10;
		
		for(int i=0; i<(int)HPS.size();i++){
			if(i%nb_points_10percent==0) cout<<". ";

		/*for(int iz=0; iz<(int)vector_pairs.size();iz++){
			if(iz%nb_points_10percent==0) cout<<". ";	
			int i=vector_pairs[iz].first;*/

			if(HPS[i].primitive_index==-1){

				//update the index of primitive
				class_index++;
				HPS[i].primitive_index=class_index;

				int conti=0; 	//for accelerate least_square fitting 

				//characteristics of the seed
				Vector_3 normal_seed=HPS[i].normal;
				Point_d pt_seed=HPS[i].position;
				Plane_3 optimal_plane(pt_seed,normal_seed);

				//initialization containers
				std::vector < int > index_container; index_container.push_back(i);
				std::vector < int > index_container_former_ring; index_container_former_ring.push_back(i);
				std::list < int > index_container_current_ring;

				//propagation
				bool propagation=true;
				do{

					propagation=false;

					for(int k=0;k<(int)index_container_former_ring.size();k++){

						int point_index=index_container_former_ring[k];

						int Nb_neigh=std::min((double)spherical_neighborhood[point_index].size(),10.);
						for(int it=0;it<Nb_neigh;it++){

							int neighbor_index=spherical_neighborhood[point_index][it];
							
							if( HPS[neighbor_index].primitive_index==-1 ){
								
								Point_d neighbor=HPS[neighbor_index].position;
								Point_d neighbor_projection=optimal_plane.projection(neighbor); 
								double distance=distance_point_d(neighbor,neighbor_projection);

								if( distance<epsilon && abs( HPS[neighbor_index].normal * optimal_plane.orthogonal_vector() ) > maximal_deviation_of_normals) { 

									HPS[neighbor_index].primitive_index=class_index;
									propagation=true;
									index_container_current_ring.push_back(neighbor_index);
									conti++;

									if( (conti<50 && conti%10==0) || (conti>50 && conti%500==0)){
										std::list < Point_d > listp;
										for(int pm=0;pm<(int)index_container.size();pm++){
											int yyh=index_container[pm];
											Point_d ptza=HPS[yyh].position;
											listp.push_back(ptza);
										}

									Plane_3 reajusted_plane;
									double average_distance=linear_least_squares_fitting_3(listp.begin(),listp.end(),reajusted_plane, CGAL::Dimension_tag<0>());
									optimal_plane=reajusted_plane;

									}
								}
							}
						}
					}

					//update containers
					index_container_former_ring.clear();
					for(std::list < int >::iterator it = index_container_current_ring.begin(); it != index_container_current_ring.end(); ++it){
						index_container_former_ring.push_back(*it);
						index_container.push_back(*it);
					}
					index_container_current_ring.clear();

				//	if(index_container.size()>40) propagation=false;

				}while(propagation);
				

				//A: reject inlier with distance to optimal plane > epsilon  + test the number of inliers -> reject if inferior to Nmin 
				std::vector < Point_d > listp;
				for(int k=0; k<(int)index_container.size(); k++){
					int yy=index_container[k];
					Point_d pt=HPS[yy].position;
					listp.push_back(pt);
				}

				Plane_3 plane_found;
				double erro=linear_least_squares_fitting_3(listp.begin(),listp.end(),plane_found, CGAL::Dimension_tag<0>());

				std::vector < int > index_container_tmp;
				for(int k=0; k<(int)index_container.size(); k++){
					Point_d inlier=HPS[index_container[k]].position;
					Point_d pt_projected=plane_found.projection(inlier); 
					double distance=sqrt(pow(inlier.x()-pt_projected.x(),2)+pow(inlier.y()-pt_projected.y(),2)+pow(inlier.z()-pt_projected.z(),2));

					if(distance < epsilon) index_container_tmp.push_back(index_container[k]);
					else HPS[index_container[k]].primitive_index=-1;
				}
			
				if(index_container_tmp.size()>=Nmin) plane_point_index.push_back(index_container_tmp);
				//end A
				
					
				
				//or B: just test the number of inliers -> reject if inferior to Nmin
			/*	if(index_container.size()>=Nmin){
					plane_point_index.push_back(index_container);
				}*/
				//end B
			

				else{ 
					class_index--;
					HPS[i].primitive_index=-1;
					for(int k=0;k<(int)index_container.size();k++) HPS[index_container[k]].primitive_index=-1; 
				}
			} 
		}

	/*	double error_fitting=0;
		int count_error_fitting=0;

		for(int i=0; i<(int)plane_point_index.size();i++){
			
			Point_d centroid(0.,0.,0.);
			std::vector < Point_d > listp;
			for(int k=0; k<(int)plane_point_index[i].size(); k++){
				int yy=plane_point_index[i][k];
				Point_d pt=HPS[yy].position;
				listp.push_back(pt);
				centroid=CGAL::barycenter(centroid, k, pt,1);
			}
			Plane_3 plane;
			double erro=linear_least_squares_fitting_3(listp.begin(),listp.end(),plane, CGAL::Dimension_tag<0>());
			extracted_planes.push_back(plane);
			list_centroid.push_back(centroid);
			list_areas.push_back((double)plane_point_index[i].size()/100);
		}

		for(int i=0; i<(int)plane_point_index.size();i++){
			for(int k=0; k<(int)plane_point_index[i].size();k++){
				int ind=plane_point_index[i][k];
				Point_d pt=HPS[ind].position;
				Point_d ptp=extracted_planes[i].projection(pt);
				error_fitting+=distance_point_d(pt,ptp);
				count_error_fitting++;
			}
		}

		cout<<endl<<"-> "<<plane_point_index.size()<<" primitives,  mean error= "<<(double) error_fitting/count_error_fitting<<" , recovering: "<<(double)count_error_fitting/HPS.size()<<endl<<endl;
*/
		compute_error(1);
		return true;
	}







bool compute_error(bool planes,string out_file_txt = ""){  

		double error_fitting=0;
		int count_error_fitting=0;

		if(planes){
			for(int i=0; i<(int)plane_point_index.size();i++){
				
				Point_d centroid(0.,0.,0.);
				std::vector < Point_d > listp;
				for(int k=0; k<(int)plane_point_index[i].size(); k++){
					int yy=plane_point_index[i][k];
					Point_d pt=HPS[yy].position;
					listp.push_back(pt);
					centroid=CGAL::barycenter(centroid, k, pt,1);
				}
				Plane_3 plane;
				double erro=linear_least_squares_fitting_3(listp.begin(),listp.end(),plane, CGAL::Dimension_tag<0>());
				extracted_planes.push_back(plane);
				list_centroid.push_back(centroid);
				list_areas.push_back((double)plane_point_index[i].size()/100);
			}

			for(int i=0; i<(int)plane_point_index.size();i++){
				for(int k=0; k<(int)plane_point_index[i].size();k++){
					int ind=plane_point_index[i][k];
					Point_d pt=HPS[ind].position;
					Point_d ptp=extracted_planes[i].projection(pt);
					error_fitting+=distance_point_d(pt,ptp);
					count_error_fitting++;
				}
			}

			cout<<endl<<"-> "<<plane_point_index.size()<<" primitives,  mean error= "<<(double) error_fitting/count_error_fitting<<" , recovering: "<<(double)count_error_fitting/HPS.size()<<endl<<endl;

			return true;
		}

		else{
			for(int i=0; i<(int)line_point_index.size();i++){
				
				Point_d centroid(0.,0.,0.);
				std::vector < Point_d > listp;
				for(int k=0; k<(int)line_point_index[i].size(); k++){
					int yy=line_point_index[i][k];
					Point_d pt=HPS[yy].position;
					listp.push_back(pt);
					centroid=CGAL::barycenter(centroid, k, pt,1);
				}
				Line optimal_line;
				double erro=linear_least_squares_fitting_3(listp.begin(),listp.end(),optimal_line, CGAL::Dimension_tag<0>());
				extracted_lines.push_back(optimal_line);
				list_centroid.push_back(centroid);
				list_areas.push_back((double)line_point_index[i].size()/100);
			}

			for(int i=0; i<(int)line_point_index.size();i++){
				for(int k=0; k<(int)line_point_index[i].size();k++){
					int ind=line_point_index[i][k];
					Point_d pt=HPS[ind].position;
					// Point_d ptp=extracted_lines[i].projection(pt);
					error_fitting+=squared_distance(pt,extracted_lines[i]);
					count_error_fitting++;
				}
			}

			cout<<endl<<"-> "<<line_point_index.size()<<" primitives,  mean error= "<<(double) error_fitting/count_error_fitting<<" , recovering: "<<(double)count_error_fitting/HPS.size()<<endl<<endl;
			if(out_file_txt != ""){
				std::ofstream obj(out_file_txt,std::ios::app);
				obj<<line_point_index.size()<<" "<<(double) error_fitting/count_error_fitting<<" "<<(double)count_error_fitting/HPS.size()<<"\n";
			}


			return true;
		}
}








Vector_3 Cloud_segmentation::regularization_normales(Vector_3 normale ,double cos_vertical){
	
	double vz=cos_vertical;
	double A=1-cos_vertical*cos_vertical;
	double B= 1+(normale.y()*normale.y())/(normale.x()*normale.x());
	double vx=sqrt(A/B); 
	if(normale.x()<0)  vx=-vx;
	double vy=vx*(normale.y()/normale.x()); 

	Vector_3 res(vx,vy,vz);
	FT norm=(1/sqrt(res.squared_length()));
	res=norm*res;

	return res;
}



Vector_3 Cloud_segmentation::regularization_normales_from_prior(Vector_3 normal_parent, Vector_3 normal,double cos_vertical){
	
	double vz=cos_vertical;
	double vx,vy;

	if(normal_parent.x()!=0){ 
		double a = (normal_parent.y()*normal_parent.y())/(normal_parent.x()*normal_parent.x()) + 1;
		double b = 2*normal_parent.y()*normal_parent.z()*vz/normal_parent.x();
		double c= vz*vz-1;

		if(4*a*c > b*b) return regularization_normales(normal,cos_vertical); 
		else {
			double delta = sqrt(b*b-4*a*c);
			double vy1= (-b-delta)/(2*a);
			double vy2= (-b+delta)/(2*a);

			if( abs(normal.y()-vy1) < abs(normal.y()-vy2) ) vy= vy1;
			else vy= vy2;

			vx= (-normal_parent.y()*vy-normal_parent.z()*vz)/normal_parent.x();
		}
	}
	else if(normal_parent.y()!=0){
		vy=-normal_parent.z()*vz/normal_parent.y();
		vx=sqrt(1-vz*vz-vy*vy); if ( normal.x() <0 ) vx=-vx;
	}

	else{
		return regularization_normales(normal,cos_vertical); 
	}

	Vector_3 res(vx,vy,vz);
	FT norm=std::max(1e-5,1./sqrt(res.squared_length()));
	res=norm*res;
	return res;
}



/*bool Cloud_segmentation::update_bbox_2d(){

	list_bbox_2d.clear();

	for(int i=0;i<plane_point_index.size();i++){
		
		std::list<Point_2d> list_2d;
		Plane_3 optimal_plane=extracted_planes[i];

		Vector_3 vortho=optimal_plane.orthogonal_vector();
		Vector_3 b1=optimal_plane.base1();
		Vector_3 b2=optimal_plane.base2();
		FT norme1=sqrt(pow(b1.x(),2)+pow(b1.y(),2)+pow(b1.z(),2)); if(norme1<1e-7){norme1=1e-7;}
		FT norme2=sqrt(pow(b2.x(),2)+pow(b2.y(),2)+pow(b2.z(),2)); if(norme2<1e-7){norme2=1e-7;}
		Vector_3 vb1=(1/norme1)*b1;
		Vector_3 vb2=(1/norme2)*b2;

		for(int kk=0;kk<plane_point_index[i].size();kk++){
					int index=plane_point_index[i][kk];
					Point_d pt=HPS[index].position;

					Point_d ptp=optimal_plane.projection(pt);
					FT X1=vb1.x()*ptp.x()+vb1.y()*ptp.y()+vb1.z()*ptp.z();
					FT X2=vb2.x()*ptp.x()+vb2.y()*ptp.y()+vb2.z()*ptp.z();
					Point_2d ptp2(X1,X2);
					list_2d.push_back(ptp2);
		}
		list_bbox_2d.push_back(CGAL::bounding_box(list_2d.begin(), list_2d.end()));
				
	}

return true;
}

*/
bool Cloud_segmentation::detection_regularities_new(double epsilon, double tolerance_coplanarity){
		


	// find pairs of epsilon-parallel primitives and store them in table_parallel 
	std::vector < std::vector < bool > > table_parallel; 
	for( int i=0;i<extracted_planes.size(); i++){  
		std::vector < bool > table_parallel_tmp; 
		for( int j=0;j<extracted_planes.size(); j++){ 
			
			Vector_3 v1=extracted_planes[i].orthogonal_vector();
			Vector_3 v2=extracted_planes[j].orthogonal_vector();
			
			if( abs(v1*v2)>1.-epsilon && i!=j) table_parallel_tmp.push_back(true); 
			else table_parallel_tmp.push_back(false); 
		}
		table_parallel.push_back(table_parallel_tmp);
	}
	


// clustering the parallel primitives and store them in list_parallel_planes
// & compute the normal, size and cos angle to the vertical of each cluster, and store that in list_cluster_normales, list_cluster_angle and list_cluster_area
	std::vector < std::vector < int > > list_parallel_planes;
	std::vector < Vector_3 > list_cluster_normales;
	std::vector < double > list_cluster_cosangle_vertical; 
	std::vector < double > list_cluster_area;
	std::vector < bool > is_available; for( int i=0;i<extracted_planes.size();i++) is_available.push_back(true);
	for( int i=0;i<extracted_planes.size();i++){

		if(is_available[i]){

			is_available[i]=false;

			//initialization containers
			std::vector < int > index_container_parallel; index_container_parallel.push_back(i);
			std::vector < int > index_container_former_ring_parallel; index_container_former_ring_parallel.push_back(i);
			std::list < int > index_container_current_ring_parallel;

			//propagation over the pairs of epsilon-parallel primitives
			bool propagation=true;
			Vector_3 cluster_normal=extracted_planes[i].orthogonal_vector();
			double cumulated_area=list_areas[i];
			
			do{
				propagation=false;

				for(int k=0;k<(int)index_container_former_ring_parallel.size();k++){

					int plane_index=index_container_former_ring_parallel[k];

					for(int it=0;it<(int)table_parallel[plane_index].size();it++){
						
						Vector_3 normal_it=extracted_planes[it].orthogonal_vector();

						if( table_parallel[plane_index][it] && is_available[it] && abs(normal_it*cluster_normal)>1.-epsilon ){	
							
							propagation=true;
							index_container_current_ring_parallel.push_back(it);
							is_available[it]=false;
							
							if(cluster_normal*normal_it <0) normal_it=-normal_it; 
							cluster_normal=(FT)cumulated_area*cluster_normal+(FT)list_areas[it]*normal_it;
							FT norm=1./sqrt(cluster_normal.squared_length()); 
							cluster_normal=norm*cluster_normal;
							cumulated_area+=list_areas[it];
						}	
					}
				}

				//update containers
				index_container_former_ring_parallel.clear();
				for(std::list < int >::iterator it = index_container_current_ring_parallel.begin(); it != index_container_current_ring_parallel.end(); ++it){
					index_container_former_ring_parallel.push_back(*it);
					index_container_parallel.push_back(*it);
				}
				index_container_current_ring_parallel.clear();

			}while(propagation);
			
			list_parallel_planes.push_back(index_container_parallel);
			list_cluster_normales.push_back(cluster_normal);
			list_cluster_area.push_back(cumulated_area);
			Vector_3 v_vertical(0.,0.,1.);
			list_cluster_cosangle_vertical.push_back(abs(v_vertical*cluster_normal)); 
		}
	}
	is_available.clear();






//discovery orthogonal relationship between clusters 
std::vector < std::vector < bool > > group_planes_orthogonal;
for( int i=0;i<list_parallel_planes.size(); i++){  std::vector < bool > gp_tmp; for( int j=0;j<list_parallel_planes.size(); j++) gp_tmp.push_back(false); group_planes_orthogonal.push_back(gp_tmp);}

for(int i=0; i<group_planes_orthogonal.size();i++){
	for(int j=0; j<group_planes_orthogonal.size();j++){

		if( i!=j && abs(list_cluster_normales[i]*list_cluster_normales[j])<epsilon){
			group_planes_orthogonal[i][j]=true; 
			group_planes_orthogonal[j][i]=true;
		}
	}
}





//clustering the vertical cosangle and store their centroids in cosangle_centroids and the centroid index of each cluster in list_cluster_index 
std::vector < double > cosangle_centroids;
std::vector < int > list_cluster_index; for( int i=0;i<list_cluster_cosangle_vertical.size(); i++) list_cluster_index.push_back(-1);
int mean_index=0;
for( int i=0;i<list_cluster_cosangle_vertical.size(); i++){
	if(list_cluster_index[i]<0){
		list_cluster_index[i]=mean_index;
		double mean=list_cluster_area[i]*list_cluster_cosangle_vertical[i];
		double mean_area=list_cluster_area[i];
		for(int j=i+1; j<list_cluster_cosangle_vertical.size(); j++){
			if( list_cluster_index[j]<0 && abs(list_cluster_cosangle_vertical[j]-mean/mean_area)<epsilon ){
				list_cluster_index[j]=mean_index;
				mean_area+=list_cluster_area[j];
				mean+=list_cluster_area[j]*list_cluster_cosangle_vertical[j];
			}
		}
		mean_index++;
		mean/=mean_area;
		cosangle_centroids.push_back(mean);
	}
}
//desactive Z-verticalité
for( int i=0;i<cosangle_centroids.size(); i++) {
	if(cosangle_centroids[i]<epsilon) cosangle_centroids[i]=0;
	else if(cosangle_centroids[i]>1.-epsilon) cosangle_centroids[i]=1;
}
for(int i=0; i<group_planes_orthogonal.size();i++) list_cluster_cosangle_vertical[i]=cosangle_centroids[list_cluster_index[i]];
	





//display console
/*
cout<<endl<<endl<<"clusters of parallel primitives:";
for(int i=0; i<list_parallel_planes.size();i++){
	cout<<endl<<i<<" -> ";
	for(int j=0; j<list_parallel_planes[i].size();j++) cout<<list_parallel_planes[i][j]<<"  ";
}

cout<<endl<<endl<<"pairs of orthogonal clusters:";
for(int i=0; i<group_planes_orthogonal.size();i++){
	cout<<endl<<i<<" -> ";
	for(int j=0;j<group_planes_orthogonal.size();j++){
		if(group_planes_orthogonal[i][j]) cout<<j<<"  ";
	}
	cout<<"     -> "<<list_cluster_cosangle_vertical[i]<<"  -> "<<cosangle_centroids[list_cluster_index[i]];
}
*/


//find subgraphs of mutually orthogonal clusters (store index of clusters in subgraph_clusters), and select the cluster of largest area
std::vector < std::vector < int > > subgraph_clusters;
std::vector < int > subgraph_clusters_max_area_index;
std::vector < bool > is_free; for(int i=0; i<list_parallel_planes.size();i++) is_free.push_back(true);
for(int i=0; i<list_parallel_planes.size();i++){
	if(is_free[i]){

			is_free[i]=false;
			double max_area=list_cluster_area[i];
			int index_max_area=i;

			//initialization containers
			std::vector < int > index_container; index_container.push_back(i);
			std::vector < int > index_container_former_ring; index_container_former_ring.push_back(i);
			std::list < int > index_container_current_ring;

			//propagation
			bool propagation=true;
			do{
				propagation=false;

				//neighbors
				for(int k=0;k<(int)index_container_former_ring.size();k++){

					int cluster_index=index_container_former_ring[k];

					for(int j=0;j<group_planes_orthogonal[cluster_index].size();j++){
						if(group_planes_orthogonal[cluster_index][j] && is_free[j]){ 	
							propagation=true;
							index_container_current_ring.push_back(j);
							is_free[j]=false;

							if(max_area<list_cluster_area[j]){
								max_area=list_cluster_area[j];
								index_max_area=j;
							}
						}	
					}
				}

				//update containers
				index_container_former_ring.clear();
				for(std::list < int >::iterator it = index_container_current_ring.begin(); it != index_container_current_ring.end(); ++it){
					index_container_former_ring.push_back(*it);
					index_container.push_back(*it);
				}
				index_container_current_ring.clear();

			}while(propagation);
			subgraph_clusters.push_back(index_container);
			subgraph_clusters_max_area_index.push_back(index_max_area);
	}
}
is_free.clear();


//create subgraphs of mutually orthogonal clusters in which the largest cluster is excluded and store in subgraph_clusters_prop
std::vector < std::vector < int > > subgraph_clusters_prop;
for(int i=0;i<subgraph_clusters.size(); i++){
	int index=subgraph_clusters_max_area_index[i];
	std::vector < int > subgraph_clusters_prop_temp;
	for(int j=0;j<subgraph_clusters[i].size(); j++){
		if(subgraph_clusters[i][j]!=index) subgraph_clusters_prop_temp.push_back(subgraph_clusters[i][j]);
	}
	subgraph_clusters_prop.push_back(subgraph_clusters_prop_temp);
}



//display console
/*
for(int i=0;i<subgraph_clusters_prop.size(); i++){
	cout<<endl<<endl<<"subgraph "<<i<<" ("<<subgraph_clusters_max_area_index[i]<<" max area): ";
	for(int j=0;j<subgraph_clusters_prop[i].size(); j++) cout<<subgraph_clusters_prop[i][j]<<"  ";
}
*/


//regularization of cluster normals : in eachsubgraph, we start from the largest area cluster and we propage over the subgraph by regularizing the normals of the clusters accorting to orthogonality and cosangle to vertical
std::vector< bool > cluster_is_available; 
for( int i=0;i<list_cluster_cosangle_vertical.size();i++) cluster_is_available.push_back(true);

for(int i=0; i<subgraph_clusters_prop.size();i++){
	
	int index_current=subgraph_clusters_max_area_index[i];
	Vector_3 vec_current=regularization_normales(list_cluster_normales[index_current],list_cluster_cosangle_vertical[index_current]);
	list_cluster_normales[index_current]=vec_current;
	cluster_is_available[index_current]=false;

			//initialization containers
			std::vector < int > index_container; index_container.push_back(index_current);
			std::vector < int > index_container_former_ring; index_container_former_ring.push_back(index_current);
			std::list < int > index_container_current_ring;

			//propagation
			bool propagation=true;
			do{
				propagation=false;

				//neighbors
				for(int k=0;k<(int)index_container_former_ring.size();k++){

					int cluster_index=index_container_former_ring[k];

					for(int j=0;j<group_planes_orthogonal[cluster_index].size();j++){
						
						if(group_planes_orthogonal[cluster_index][j] && cluster_is_available[j]){ 	
							
							propagation=true;
							index_container_current_ring.push_back(j);
							cluster_is_available[j]=false;

							Vector_3 new_vect=regularization_normales_from_prior(list_cluster_normales[cluster_index], list_cluster_normales[j], list_cluster_cosangle_vertical[j]);
							list_cluster_normales[j]=new_vect;
						}
					}	
				}
			
				//update containers
				index_container_former_ring.clear();
				for(std::list < int >::iterator it = index_container_current_ring.begin(); it != index_container_current_ring.end(); ++it){
					index_container_former_ring.push_back(*it);
					index_container.push_back(*it);
				}
				index_container_current_ring.clear();
			}while(propagation);
}



//recompute optimal plane for each primitive after normal regularization
for(int i=0; i<list_cluster_normales.size();i++){

	Vector_3 vec_reg=list_cluster_normales[i];

	for(int j=0; j<list_parallel_planes[i].size();j++){
		int index_prim=list_parallel_planes[i][j];
		Point_d pt_reg=extracted_planes[index_prim].projection(list_centroid[index_prim]);
		if( extracted_planes[index_prim].orthogonal_vector() * vec_reg < 0) vec_reg=-vec_reg;
		Plane_3 plane_reg(pt_reg,vec_reg);
		
		if( abs(extracted_planes[index_prim].orthogonal_vector()*plane_reg.orthogonal_vector()) > 1. - epsilon) extracted_planes[index_prim]=plane_reg;
	}
}





//detecting co-planarity and store in list_coplanar_prim
std::vector< std::vector< std::vector < int > > > list_coplanar_prim;
for(int i=0; i<list_parallel_planes.size();i++){

	std::vector< std::vector < int > > list_coplanar_prim_tmp;
	Vector_3 vec_reg=list_cluster_normales[i];
	std::vector < int > list_cop_index; for( int ip=0;ip<list_parallel_planes[i].size(); ip++) list_cop_index.push_back(-1);
	int cop_index=0;

	for(int j=0; j<list_parallel_planes[i].size();j++){
		int index_prim=list_parallel_planes[i][j];

		if(list_cop_index[j]<0){
			
			std::vector < int > list_coplanar_prim_tmp_tmp;
			list_cop_index[j]=cop_index;
			list_coplanar_prim_tmp_tmp.push_back(index_prim);
			
			Point_d pt_reg=extracted_planes[index_prim].projection(list_centroid[index_prim]);
			Plane_3 plan_reg(pt_reg,vec_reg);

			for(int k=j+1; k<list_parallel_planes[i].size(); k++){
				if( list_cop_index[k]<0){
					
					int index_prim_next=list_parallel_planes[i][k];
					Point_d pt_reg_next=extracted_planes[index_prim_next].projection(list_centroid[index_prim_next]);
					Point_d pt_proj=plan_reg.projection(pt_reg_next);
					double distance=distance_point_d(pt_reg_next,pt_proj);
					
					if(distance<tolerance_coplanarity ){
						list_cop_index[k]=cop_index;
						list_coplanar_prim_tmp_tmp.push_back(index_prim_next);
					}
				}
			}
			list_coplanar_prim_tmp.push_back(list_coplanar_prim_tmp_tmp);
			cop_index++; 
		}
	}
	list_coplanar_prim.push_back(list_coplanar_prim_tmp);
}



//regularize primitive position by computing barycenter of coplanar planes
std::vector < std::vector < int > > list_primitive_reg_index_extracted_planes;
std::vector < Plane_3 > list_primitive_reg;

for(int i=0;i<list_coplanar_prim.size();i++){
	for(int j=0;j<list_coplanar_prim[i].size();j++){

		Point_d pt_bary(0.,0.,0.);
		double area=0;

		for(int k=0; k<list_coplanar_prim[i][j].size();k++){
			int index_prim=list_coplanar_prim[i][j][k];
			Point_d pt_reg=extracted_planes[index_prim].projection(list_centroid[index_prim]);

			pt_bary=barycenter(pt_bary, area,pt_reg,list_areas[index_prim]); 
			area+=list_areas[index_prim];
		}
		Vector_3 vec_reg=extracted_planes[list_coplanar_prim[i][j][0]].orthogonal_vector();

		Plane_3 plane_reg(pt_bary,vec_reg);

		bool is_reg_used=false;
		std::vector< int > list_primitive_reg_index_extracted_planes_tmp1;
		for(int k=0; k<list_coplanar_prim[i][j].size();k++){
			int index_prim=list_coplanar_prim[i][j][k];
			if( abs(extracted_planes[index_prim].orthogonal_vector()*plane_reg.orthogonal_vector()) > 1. - epsilon){
				if(extracted_planes[index_prim].orthogonal_vector()*plane_reg.orthogonal_vector()<0) extracted_planes[index_prim]=plane_reg.opposite();
				else extracted_planes[index_prim]=plane_reg;
				is_reg_used=true;
				list_primitive_reg_index_extracted_planes_tmp1.push_back(index_prim);
			}
			else{
				list_primitive_reg.push_back(extracted_planes[index_prim]);
				std::vector< int > list_primitive_reg_index_extracted_planes_tmp;
				list_primitive_reg_index_extracted_planes_tmp.push_back(index_prim);
				list_primitive_reg_index_extracted_planes.push_back(list_primitive_reg_index_extracted_planes_tmp);
			}
		}
		if(is_reg_used) {
			list_primitive_reg.push_back(plane_reg);
			list_primitive_reg_index_extracted_planes.push_back(list_primitive_reg_index_extracted_planes_tmp1);
		}
	}
}

cout<<endl<<endl<<"NB planes final = "<<list_primitive_reg.size()<<endl<<endl;

compute_error(1);

/*
update_bbox_2d();
std::vector<Polyhedron> vector_polyhedron5;
std::vector<CGAL::Color> vector_color5;

double pas=1.;
double radius_arrow=0.15;
double radius_ball=0.2;
std::vector< CGAL::Color > col_list_parallel;

for(int ia=0; ia<list_parallel_planes.size();ia++){
		
	int red=(int)floor((double)200*rand()/RAND_MAX)+55;
	int green=(int)floor((double)200*rand()/ RAND_MAX)+55;
	int blue=(int)floor((double)200*rand()/ RAND_MAX)+55;
	CGAL::Color col(std::max(0,std::min(255,red)),std::max(0,std::min(255,green)),std::max(0,std::min(255,blue)),120);
	col_list_parallel.push_back(col);
	

	for(int j=0; j<list_parallel_planes[ia].size();j++){
		int i=list_parallel_planes[ia][j];	
		Point_d pt=extracted_planes[i].projection(list_centroid[i]);
		double dx=list_bbox_2d[i].xmax()-list_bbox_2d[i].xmin();
		double dy=list_bbox_2d[i].ymax()-list_bbox_2d[i].ymin();
		double a,b;
		a=dx/2; b=dy/2;

		Polyhedron P=createEllipse(pt,extracted_planes[i].orthogonal_vector() ,3*a/4, 3*b/4,5); 
		vector_polyhedron5.push_back(P);
		vector_color5.push_back(col);

		Point_d pt1(pt.x()+pas*extracted_planes[i].orthogonal_vector().x(),pt.y()+pas*extracted_planes[i].orthogonal_vector().y(),pt.z()+pas*extracted_planes[i].orthogonal_vector().z());
		Polyhedron P1=createArrow(pt,pt1,radius_arrow);
		vector_polyhedron5.push_back(P1);
		vector_color5.push_back(col); 

		Polyhedron P2=createSphere(pt,radius_ball);
		vector_polyhedron5.push_back(P2);
		vector_color5.push_back(col); 


	}
}
char *name_output5= "ellipses_reg.ply";
save_listpolyhedron2ply(vector_polyhedron5,name_output5, vector_color5);
*/

/*
std::vector<Polyhedron> vector_polyhedron2;
std::vector<CGAL::Color> vector_color2;


pas=4.;
radius_arrow=0.3;
radius_ball=0.6;

Point_d pt0(0,0,0);

CGAL::Color ggr(190,190,190);
Polyhedron Pa=createSphere(pt0,radius_ball);
vector_polyhedron2.push_back(Pa);
vector_color2.push_back(ggr);

Point_d pt0a(-pas*1.5/2,0,0);
Point_d pt0b(pas*1.5/2,0,0);
Polyhedron Pb=createDashedCylinder(pt0a,pt0b,radius_arrow/2);
vector_polyhedron2.push_back(Pb);
vector_color2.push_back(ggr);

Point_d pt0c(0,-pas*1.5/2,0);
Point_d pt0d(0,pas*1.5/2,0);
Polyhedron Pc=createDashedCylinder(pt0c,pt0d,radius_arrow/2);
vector_polyhedron2.push_back(Pc);
vector_color2.push_back(ggr);

Point_d pt0e(0,0,-pas*1.5/2);
Point_d pt0f(0,0,pas*1.5/2);
Polyhedron Pd=createDashedCylinder(pt0e,pt0f,radius_arrow/2);
vector_polyhedron2.push_back(Pd);
vector_color2.push_back(ggr);

for(int ia=0; ia<list_parallel_planes.size();ia++){
	
	int i=list_parallel_planes[ia][0];

	bool bisense=false;
	for(int j=0; j<list_parallel_planes[ia].size();j++){
		int kl=list_parallel_planes[ia][j];	
		if(extracted_planes[i].orthogonal_vector()*extracted_planes[kl].orthogonal_vector()<0) bisense=true;
	}

			Point_d pt1(pt0.x()+pas*extracted_planes[i].orthogonal_vector().x(),pt0.y()+pas*extracted_planes[i].orthogonal_vector().y(),pt0.z()+pas*extracted_planes[i].orthogonal_vector().z());
			Polyhedron Ptr=createArrow(pt0,pt1,radius_arrow);
			vector_polyhedron2.push_back(Ptr);
			vector_color2.push_back(col_list_parallel[ia]); 	


			if(bisense){
				Point_d pt1(pt0.x()-pas*extracted_planes[i].orthogonal_vector().x(),pt0.y()-pas*extracted_planes[i].orthogonal_vector().y(),pt0.z()-pas*extracted_planes[i].orthogonal_vector().z());
				Polyhedron Ptr2=createArrow(pt0,pt1,radius_arrow);
				vector_polyhedron2.push_back(Ptr2);
				vector_color2.push_back(col_list_parallel[ia]); 	
			}
	}


char *name_output2= "ellipses_reg_vectors.ply";
save_listpolyhedron2ply(vector_polyhedron2,name_output2, vector_color2);




*/





/*
std::vector<Polyhedron> vector_polyhedron5z;
std::vector<CGAL::Color> vector_color5z;
pas=1.;
radius_arrow=0.15;
radius_ball=0.2;

for(int i= 0; i< list_primitive_reg.size();i++){


	int red=(int)floor((double)126*rand()/RAND_MAX)+130;
	int green=(int)floor((double)126*rand()/ RAND_MAX)+130;
	int blue=(int)floor((double)126*rand()/ RAND_MAX)+130;
	CGAL::Color col(std::max(0,std::min(255,red)),std::max(0,std::min(255,green)),std::max(0,std::min(255,blue)),120);



	for(int e=0;e<list_primitive_reg_index_extracted_planes[i].size();e++){
			
		int index_prim=list_primitive_reg_index_extracted_planes[i][e];	
		Point_d pt=extracted_planes[index_prim].projection(list_centroid[index_prim]);
		double dx=list_bbox_2d[index_prim].xmax()-list_bbox_2d[index_prim].xmin();
		double dy=list_bbox_2d[index_prim].ymax()-list_bbox_2d[index_prim].ymin();
		double a,b;
		a=dx/2; b=dy/2;

		Polyhedron P=createEllipse(pt,extracted_planes[index_prim].orthogonal_vector() ,3*a/4, 3*b/4,5); 
		vector_polyhedron5z.push_back(P);
		vector_color5z.push_back(col);

		Polyhedron P2=createSphere(pt,radius_ball);
		vector_polyhedron5z.push_back(P2);
		vector_color5z.push_back(col); 

	}


}


char *name_output5z= "ellipses_reg_coplanar.ply";
save_listpolyhedron2ply(vector_polyhedron5z,name_output5z, vector_color5z);
*/

return true;
}


void Cloud_segmentation::cluster_detection(float epsilon,float w1,float w2){

	float w_sum = w1+w2;
	w1/=w_sum;
	w2/=w_sum;

	for(int i=0;i<(int) HPS.size();i++){
		int no_of_nearest_neighbours = spherical_neighborhood[i].size();
		vector<int>& neighbor_indices = spherical_neighborhood[i];
		int no_of_pts_in_cluster = 0;
		float sigma_r_squared = 0;
		for(int j:neighbor_indices){
			if(squared_distance(HPS[i].position,HPS[j].position) <= pow(epsilon,2)){
				no_of_pts_in_cluster++;
				sigma_r_squared+=squared_distance(HPS[i].position,HPS[j].position);
			}
		}
		
		float density = no_of_pts_in_cluster == 0 ? 0 : w1*(((float) no_of_pts_in_cluster)/(float) no_of_nearest_neighbours) + w2*(1-(sigma_r_squared/(no_of_pts_in_cluster * pow(epsilon,2) )));
		int r = 255 * density,g=0,b=0;
		CGAL::Color clr((int) r,(int) g,(int) b);
		HPS[i].color = clr;
		HPS[i].cluster_density = density;
		
	}

}


std::pair<int,float> Cloud_segmentation::cluster_fitting_simple(float min_density,float epsilon){
	cout<<"Cluster Fitting...\n";

	//clearing the existing data:
	cluster_indices.clear();
	for(int i=0; i<(int)HPS.size();i++) HPS[i].cluster_index=-1;
	int no_of_pts_in_clusters = 0;
	cluster_centroids.clear();
	cluster_spheres.clear();

	//defining class index for various clusters
	int class_index=-1;

	
	for(int i=0;i < (int) HPS.size(); i++){
		if(HPS[i].cluster_density >= min_density && HPS[i].cluster_index == -1){
			++class_index;
			HPS[i].cluster_index = class_index;
			vector<int> index_container_temp;
			for(int j:spherical_neighborhood[i]){
				if(squared_distance(HPS[i].position,HPS[j].position) && HPS[j].cluster_index == -1) {
					index_container_temp.push_back(j);
					HPS[j].cluster_index = class_index;
				}
			}
			cluster_indices.push_back(index_container_temp);
			no_of_pts_in_clusters+=index_container_temp.size();
		}
	}
	float recovering = ((float) no_of_pts_in_clusters)/((float) HPS.size());
	int no_of_clusters = cluster_indices.size();
	return std::make_pair(no_of_clusters,recovering);

	

}


std::pair<int,float> Cloud_segmentation::cluster_fitting(float min_density,int Nmin, float max_density_diff,float epsilon){
	cout<<"Cluster Fitting...\n";

	std::sort(HPS.begin(), HPS.end(), [](const HPoint& a, const HPoint& b) {
        return a.cluster_density > b.cluster_density;
    });
	Compute_Knearest_neighbors(20); // This can be avoided, for better computational time

	//clearing the existing data:
	cluster_indices.clear();
	for(int i=0; i<(int)HPS.size();i++) HPS[i].cluster_index=-1;
	int no_of_points_in_clusters = 0;

	
	//defining class index for various clusters
	int class_index=-1;

	int nb_points_10percent=HPS.size()/10;

	for(int i=0; i<(int)HPS.size();i++){
		if(i%nb_points_10percent==0) cout<<". ";
		if(HPS[i].cluster_index==-1){

			float density_curr = HPS[i].cluster_density;
			int max_density_index = i;
			if(density_curr<min_density) continue;
			class_index++;
			HPS[i].cluster_index = class_index;
			std::vector < int > index_container; index_container.push_back(i);
			std::vector < int > index_container_former_ring; index_container_former_ring.push_back(i);
			std::list < int > index_container_current_ring;

			bool propagation = true;
			int round = 1;
			do{
				propagation = false;
				for(int k=0;k<(int)index_container_former_ring.size();k++){

						int point_index=index_container_former_ring[k];

						int Nb_neigh=(int)spherical_neighborhood[point_index].size();   //changed from std::min((double)spherical_neighborhood[point_index].size(),10.)
						for(int it=0;it<Nb_neigh;it++){

							int neighbor_index=spherical_neighborhood[point_index][it];
							
							if( HPS[neighbor_index].cluster_index==-1 ){
								
								

								if( ((abs(HPS[max_density_index].cluster_density - HPS[neighbor_index].cluster_density) < max_density_diff) || (abs(HPS[point_index].cluster_density - HPS[neighbor_index].cluster_density) < max_density_diff )) && squared_distance(HPS[neighbor_index].position,HPS[point_index].position) < pow(epsilon,2)/2 && HPS[neighbor_index].cluster_index == -1 ){ 

									HPS[neighbor_index].cluster_index=class_index;
									propagation=true;
									index_container_current_ring.push_back(neighbor_index);
									max_density_index = HPS[max_density_index].cluster_density > HPS[neighbor_index].cluster_density ? max_density_index : neighbor_index;

								}
							}
						}
					}

					//update containers
					index_container_former_ring.clear();
					for(std::list < int >::iterator it = index_container_current_ring.begin(); it != index_container_current_ring.end(); ++it){
						index_container_former_ring.push_back(*it);
						index_container.push_back(*it);
					}
					index_container_current_ring.clear();

			}while(propagation);

			// std::vector < int > index_container_tmp;
			// for(int k=0; k<(int)index_container.size(); k++){
			// 	float density_diff = HPS[max_density_index].cluster_density - HPS[index_container[k]].cluster_density;

			// 	if(density_diff < max_density_diff) index_container_tmp.push_back(index_container[k]);
			// 	else HPS[index_container[k]].cluster_index=-1;
			// }

			// if(index_container_tmp.size()>=Nmin) {
			// 	cluster_indices.push_back(index_container_tmp);
			// 	no_of_points_in_clusters+=index_container_tmp.size();
			// }

			if(index_container.size() >= Nmin){
				cluster_indices.push_back(index_container);
				no_of_points_in_clusters+=index_container.size();
			}


			else{ 
				class_index--;
				HPS[i].cluster_index=-1;
				for(int k=0;k<(int)index_container.size();k++) HPS[index_container[k]].cluster_index=-1; 
			}



		}
	}


	// computing centroids:
	for(auto v:cluster_indices){
		float x_sum = 0, y_sum = 0,z_sum = 0;
		for(int i:v){
			x_sum += HPS[i].position.x();
			y_sum += HPS[i].position.y();
			z_sum += HPS[i].position.z();
		}
		Point_d centroid(x_sum/v.size(),y_sum/v.size(),z_sum/v.size());
		cluster_centroids.push_back(centroid);
		
	}


	//Creating spheres :
	
	
	for(int i=0;i< (int) cluster_centroids.size(); i++){
		vector<int>& pt_indices = cluster_indices[i];
		float avg_dist = 0;  //Changed from max distance
		for(int j=0;j<(int) pt_indices.size();j++){
			float dist = sqrt(squared_distance(HPS[pt_indices[j]].position , cluster_centroids[i]));
			avg_dist+=dist;
		}
		avg_dist/=pt_indices.size();
		cluster_spheres.push_back(createSphere(cluster_centroids[i],avg_dist));
	}

	// std::ofstream obj("C:/Users/smaheshw/Code/exemple/holids.txt");
	// for(int i = 0;i<(int) cluster_indices.size();i++){
	// 	obj<<"Cluster : "<<i+1<<"\n";
	// 	vector<int>& v = cluster_indices[i];
	// 	for(int j:v){
	// 		obj<<HPS[j].haloID<<"\n";
	// 	}
	// 	cout<<"\n";
	// }



	


	int no_of_clusters = cluster_indices.size();
	float recovering = ((float) no_of_points_in_clusters)/((float) HPS.size());
	return std::make_pair(no_of_clusters,recovering);
	

}





Vector_3 Cloud_segmentation::m(Point_d pt, vector<int>& pt_indices, double tau) {
    // Translate point to vector
    Vector_3 x = pt - CGAL::ORIGIN;
    // Prepare storage for weights
    vector<double> g_xis;
    // Compute weights
    for(int i : pt_indices) {
        g_xis.push_back(g(sqrt(squared_distance(pt, HPS[i].position)), tau));
    }

    Vector_3 ans = CGAL::NULL_VECTOR;
    double sum_g_xis = 0;
    // Compute weighted sum of neighbor positions and sum of weights
    for(int i = 0; i < (int)pt_indices.size(); i++) {
        ans = ans + g_xis[i] * (HPS[i].position - CGAL::ORIGIN);
        sum_g_xis += g_xis[i];
    }

    // Ensure sum_g_xis is not zero to avoid division by zero
    if (sum_g_xis != 0) {
        ans = (1 / sum_g_xis) * ans;
    } else {
        // Handle the case where sum_g_xis is zero, which should be rare
        ans = CGAL::NULL_VECTOR;
    }

    // Return the mean shift vector
    return ans - x;
}




Point_d Cloud_segmentation::find_densest_pt(int pt_index, double tau) {
    // Get the k-nearest neighbors for the point at pt_index
    vector<int>& k_nearest_nbrs = spherical_neighborhood[pt_index];
    // Include the point itself in the neighborhood
    k_nearest_nbrs.push_back(pt_index);
	double alpha = 0.1;

    // Initial cluster center is the position of the point itself
    Point_d cluster_center_curr = HPS[pt_index].position;
    // Compute the next cluster center using the mean shift vector
    Point_d cluster_center_next = cluster_center_curr + alpha*m(cluster_center_curr, k_nearest_nbrs, tau);
	cout<<"m: "<<m(cluster_center_next, k_nearest_nbrs, tau)<<"\n";

	//For Debugging: -------
	HPS.push_back(HPoint());
	HPS[(int)HPS.size() - 1].position = cluster_center_next;
	HPS[(int)HPS.size() - 1].color = RED;

	//----------------------


    // Convergence parameters
    int max_itr = 0;
    const int max_iterations = 10000;
    const double convergence_threshold = 1e-4;

    // Iteratively update the cluster center until convergence or maximum iterations
    while (squared_distance(cluster_center_curr, cluster_center_next) > convergence_threshold && max_itr++ < max_iterations && sqrt(squared_distance(cluster_center_next,Point_d (0,0,0))) < 1000) {
        cluster_center_curr = cluster_center_next;
        cluster_center_next = cluster_center_curr + alpha*m(cluster_center_curr, k_nearest_nbrs, tau);
		cout<<"dist: "<<sqrt(squared_distance(cluster_center_next,Point_d (0,0,0)))<<"\n";
		cout<<"m: "<<m(cluster_center_next, k_nearest_nbrs, tau)<<"\n";

		//For Debugging: -------
		HPS.push_back(HPoint());
		HPS[(int)HPS.size() - 1].position = cluster_center_next;
		HPS[(int)HPS.size() - 1].color = RED;
		//----------------------
    }
	cout<<"No. ofiterations: "<<max_itr<<"\n";

    // Remove the point itself from the neighborhood to restore the original state
    k_nearest_nbrs.pop_back();

    // Return the final cluster center
    return cluster_center_next;
}




int Cloud_segmentation::cluster_detection_mean_shift(double tau){

	//clearing memory
	cluster_indices_mean_shift.clear();





	int no_of_points = HPS.size();
	for(int i = 0;i<no_of_points; i++) cluster_centers.push_back(find_densest_pt(i,tau));
	std::vector< std::pair< int,Point_d > > index_centre_pair;
	for(int i=0; i<no_of_points; i++){
		index_centre_pair.push_back(std::make_pair(i,cluster_centers[i]));
	}

	std::ofstream obj("C:/Users/smaheshw/Code/exemple/outputs_mean_shift/lol.txt");

	std::sort(index_centre_pair.begin(), index_centre_pair.end(), [](const std::pair<int, Point_d>& a, const std::pair<int, Point_d>& b) {
        if(a.second.x() != b.second.x()) return a.second.x() > b.second.x();
		else if(a.second.y() != b.second.y()) return a.second.y() > b.second.y();
		else return a.second.z() > b.second.z();
    });


	for(auto v: index_centre_pair){
		obj<<v.first<<" "<<v.second.x()<<" "<<v.second.y()<<" "<<v.second.z()<<" "<<sqrt(squared_distance(v.second,HPS[v.first].position))<<"\n";
	}
	obj.close();
	Point_d curr_point = index_centre_pair[0].second;
	cluster_indices_mean_shift.push_back({index_centre_pair[0].first});
	int sz = 1;
	int no_of_clusters = 0;

	//clearing:
	cluster_centroids.clear();



	for(int i=1;i<no_of_points;i++){
		if(sqrt(squared_distance(curr_point,index_centre_pair[i].second)) < 1e-2) cluster_indices_mean_shift[sz-1].push_back(index_centre_pair[i].first);
		else{
			curr_point = index_centre_pair[i].second;
			if(cluster_indices_mean_shift[sz-1].size() < 7){
				cluster_indices_mean_shift.pop_back();
				sz--;
			}
			cluster_indices_mean_shift.push_back({index_centre_pair[i].first});
			sz++;

		}

		no_of_clusters = cluster_indices_mean_shift.size();
		
		
	}

	// computing centroids:
	for(auto v:cluster_indices_mean_shift){
		float x_sum = 0, y_sum = 0,z_sum = 0;
		for(int i:v){
			x_sum += HPS[i].position.x();
			y_sum += HPS[i].position.y();
			z_sum += HPS[i].position.z();
		}
		Point_d centroid(x_sum/v.size(),y_sum/v.size(),z_sum/v.size());
		cluster_centroids.push_back(centroid);
		
	}



	//creating spheres:
	cluster_spheres.clear();
	for(int i=0;i< (int) cluster_centroids.size(); i++){
		vector<int>& pt_indices = cluster_indices_mean_shift[i];
		float avg_dist = 0;  //Changed from max distance
		for(int j=0;j<(int) pt_indices.size();j++){
			float dist = sqrt(squared_distance(HPS[pt_indices[j]].position , cluster_centroids[i]));
			avg_dist+=dist;
		}
		avg_dist/=pt_indices.size();
		cluster_spheres.push_back(createSphere(cluster_centroids[i],avg_dist));
	}


	return no_of_clusters;

	
	
	
}







protected: 


};


#endif 