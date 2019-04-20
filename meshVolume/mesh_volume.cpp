#include <iostream>
#include <pcl/io/obj_io.h>
#include <pcl/PCLPointCloud2.h>
#include <cmath>

using namespace pcl;

float signedVolumeOfTriangle(pcl::PointXYZ p1, pcl::PointXYZ p2, pcl::PointXYZ p3)
{
    float v321 = p3.x*p2.y*p1.z;
    float v231 = p2.x*p3.y*p1.z;
    float v312 = p3.x*p1.y*p2.z;
    float v132 = p1.x*p3.y*p2.z;
    float v213 = p2.x*p1.y*p3.z;
    float v123 = p1.x*p2.y*p3.z;
    return (1.0f/6.0f)*(-v321 + v231 + v312 - v132 - v213 + v123);
}

int main (int argc, char** argv)
{
  PolygonMesh mesh;
  PointCloud<PointXYZ>::Ptr cloud (new PointCloud<PointXYZ>);
  float vols = 0.0;
  // Fill in the mesh
  io::loadOBJFile(argv[1], mesh);
  fromPCLPointCloud2(mesh.cloud,*cloud);
  for(int triangle=0;triangle<mesh.polygons.size();triangle++)
  {
    pcl::PointXYZ pt1 = cloud->points[mesh.polygons[triangle].vertices[0]];
    pcl::PointXYZ pt2 = cloud->points[mesh.polygons[triangle].vertices[1]];
    pcl::PointXYZ pt3 = cloud->points[mesh.polygons[triangle].vertices[2]];
    vols += signedVolumeOfTriangle(pt1, pt2, pt3);
  }
    
  std::cout << "The volume is: " << vols << "\n";
  return (0);
}
