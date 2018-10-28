#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main()
{
int i,j,k,l;
//float lat, lon, zed;
int nx, ny, nz, nxy, n, minx, maxx, miny, maxy, minz, maxz;
double number, dx, dy, dz;
vector <double> read;
string model,params,name;
ifstream fileIn;
fstream outFile;

//good example of simple line break for long lines below:
cout <<"enter parameter file: \n 0.nx \n 1.ny \n 2.nz\
 \n 3.min-x \n 4.max-x \n 5.min-y \n 6.max-y \n 7.min-z \n 8.max-z" <<endl;
getline(cin,params);
fileIn.open(params.c_str());
while(!fileIn.eof())
  {
    fileIn >> number;
    read.push_back(number);
    i++;
  }
nx = read[0];
ny = read[1];
nz = read[2];
nxy = nx*ny;
n = nx*ny*nz;
minx = read[3];
maxx = read[4];
dx = maxx-minx;
dx = dx/nx;
miny = read[5];
maxy = read[6];
dy = maxy-miny;
dy = dy/ny;
minz = read[7];
maxz = read[8];
dz = maxz-minz;
dz = -dz/nz; //going from bottom (max-z/min-radius) to top(min-z/max-radius)
read.clear();
fileIn.close();

cout <<"enter model vector to extract for plotting: " <<endl;
getline(cin,model);
fileIn.open(model.c_str());
while(!fileIn.eof())
  {
    fileIn >> number;
    read.push_back(number); //read is now the %∂Vp vector
    i++;
  }
fileIn.close();

cout <<"enter output file name:" << endl;
getline(cin,name);

//***FIX****
//matrix containing all plotting info. cols = lon; lat; depth; %∂Vp ***FIX****
//***FIX****

cout << "constructing volume matrix for plotting now" << endl;
MatrixXd M(n,4);
//loop over volume one column at a time now
l=0;
for(i=0;i<nx;i++) //x is outer loop
{
  for(j=0;j<ny;j++) //y is middle loop
  {
    for(k=0;k<nz;k++) //z is inner loop
    {
      M(l,0) = maxz + k*dz;
      M(l,1) = miny + j*dy;
      M(l,2) = minx + i*dx;
      M(l,3) = read[l];
      l = l+1;
    }
  }
}


//output file
cout << "saving new file as " << name << " now" << endl;
outFile.open(name.c_str(), ios_base::out);
outFile << M;
outFile.close();

return 0;
}
