#include "ShapeFun.h"

void ShapeFun::Compute1DLagrangeShapeFun(const double &xi,const vector<double> &nodes)
{
    _DetJac=0.0;
    switch (GetShapeFunNums())
    {
        case 2:
        {
            (*this)(1,0)=0.5*(1.0-xi);
            (*this)(1,1)=-0.5;

            (*this)(2,0)=0.5*(1.0+xi);
            (*this)(2,1)=0.5;
            break;
        }
        case 3:
        {
            (*this)(1,0)= 0.5*xi*(xi-1.0);
            (*this)(1,1)= 0.5*(2.0*xi-1.0);

            (*this)(2,0)=-(xi + 1.0)*(xi - 1.0);
            (*this)(2,1)=-2.0*xi;

            (*this)(3,0)= 0.5*xi*(xi + 1.0);
            (*this)(3,1)= 0.5*(2.0*xi + 1.0);
            break;
        }
        case 4:
        {
            (*this)(1,0)=-(3.0*xi+1.0)*(3.0*xi-1.0)*(    xi-1.0)/16.0;
            (*this)(2,0)= (3.0*xi+3.0)*(3.0*xi-1.0)*(3.0*xi-3.0)/16.0;
            (*this)(3,0)=-(3.0*xi+3.0)*(3.0*xi+1.0)*(3.0*xi-3.0)/16.0;
            (*this)(4,0)= (    xi+1.0)*(3.0*xi+1.0)*(3.0*xi-1.0)/16.0;
            
            (*this)(1,1)=-27.0*xi*xi/16.0+9.0*xi/8.0+ 1.0/16.0;
            (*this)(2,1)= 81.0*xi*xi/16.0-9.0*xi/8.0-27.0/16.0;
            (*this)(3,1)=-81.0*xi*xi/16.0-9.0*xi/8.0+27.0/16.0;
            (*this)(4,1)= 27.0*xi*xi/16.0+9.0*xi/8.0- 1.0/16.0;
            break;
        }
        default:
            break;
    }

    _dxdxi=0.0;_dydxi=0.0;_dzdxi=0.0;
    for(int i=1;i<=GetShapeFunNums();i++)
    {
        _dxdxi+=(*this)(i,1)*nodes[i-1];
        // _dydxi+=(*this)(i,1)*nodes[i];
        // _dzdxi+=(*this)(i,1)*nodes[i];
        // cout<<(*this)(i,1)<<" "<<nodes[i-1]<<endl;
    }
    // cout<<endl;
    _DetJac=sqrt(_dxdxi*_dxdxi+_dydxi*_dydxi+_dzdxi*_dzdxi);

    if(abs(_DetJac)<1.0e-13)
    {
        cout<<"*** Error: singular element in 1D case!!!"<<endl;
        abort();
    }

    for(int i=1;i<=GetShapeFunNums();i++)
    {
        (*this)(i,1)=(*this)(i,1)/_DetJac;
    }
}