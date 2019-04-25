# LiDar-data-analysis
### Team members:
Jianfei Ma, Ruoyang Song
### Abstract: 
This repository contains our research about calculating the buttress volume of a tree point cloud data. It includes our failed experiments, codes for calculating the volume, and the [final report](https://github.com/ruoyangsong/LiDar-data-analysis/blob/master/report/point_cloud_analysis.pdf)
.
### Dependency:
PCL libarary is necessary to run our C++ programs. To install, you can download the source code from http://www.pointclouds.org/downloads/, but you also need to manually compile it. Or you can simpily use `brew install pcl`.

### Proposed Method:
1. Convert point cloud to .pcd format: `python convertToPcd.py`
2. Run Poisson Reconstruction: <br>
`cd poissonReconstruction/` <br>
`cmake .` <br>
`make` <br>
`./poisson_reconstruction [input filename(pcd)] [output filename(obj)]`
3. Calculat Volume: <br>
`cd meshVolume` <br>
`cmake .` <br>
`make` <br>
`./mesh_volume [input filename(obj)]`

 
