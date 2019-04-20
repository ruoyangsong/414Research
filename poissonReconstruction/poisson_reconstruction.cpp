#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/features/normal_3d.h>
#include <pcl/features/normal_3d_omp.h>
#include<pcl/surface/mls.h>
#include <pcl/surface/poisson.h>
#include <pcl/io/obj_io.h>
#include<pcl/io/vtk_io.h>
using namespace pcl;
int
main (int argc, char** argv)
{
  PointCloud<PointXYZ>::Ptr cloud (new PointCloud<PointXYZ>);
  PointCloud<PointXYZ>::Ptr cloud_filtered (new PointCloud<PointXYZ>);

  // Fill in the cloud data
  PCDReader reader;
  // Replace the path below with the path where you saved your file
  reader.read<PointXYZ> (argv[1], *cloud);
    
  //Create the filtering object
  StatisticalOutlierRemoval<PointXYZ> sor;
  sor.setInputCloud (cloud);
  sor.setMeanK (50);
  sor.setStddevMulThresh (1.0);
  sor.filter (*cloud_filtered);
  std::cout << "Finish removing noise.\n";
    
  //Estimate normal
  NormalEstimationOMP<PointXYZ, Normal> ne;
  ne.setNumberOfThreads(8);
  ne.setInputCloud(cloud_filtered);
  ne.setRadiusSearch(0.00375);
  Eigen::Vector4f centroid;
  compute3DCentroid(*cloud_filtered, centroid);
  ne.setViewPoint(centroid[0], centroid[1], centroid[2]);
  std::cout << "Finish estimating normal.\n";
    
  PointCloud<Normal>::Ptr cloud_normals(new PointCloud<Normal>());
  ne.compute(*cloud_normals);
  for (size_t i = 0; i < cloud_normals->size(); ++i)
  {
        cloud_normals->points[i].normal_x *= -1;
        cloud_normals->points[i].normal_y *= -1;
        cloud_normals->points[i].normal_z *= -1;
  }

  PointCloud<PointNormal>::Ptr cloud_filtered_normals(new PointCloud<PointNormal>());
  concatenateFields(*cloud_filtered, *cloud_normals, *cloud_filtered_normals);
  //Poisson reconstruction surface
  Poisson<PointNormal> poisson;
  poisson.setDepth(8);
  poisson.setDegree(2);
  poisson.setSamplesPerNode(1.5);
  poisson.setScale(1.25);
  poisson.setIsoDivide(8);
  poisson.setConfidence(0);
  poisson.setManifold(0);
  poisson.setOutputPolygons(0);
  poisson.setSolverDivide(8);
  poisson.setInputCloud(cloud_filtered_normals);
  PolygonMesh mesh;
  poisson.reconstruct(mesh);
  std::cout << "Finish poisson reconstruction.\n";
  io::saveOBJFile(argv[2], mesh);
  std::cout << "Output mesh is stored in " << argv[2] << "\n";
  return (0);
}
