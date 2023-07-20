// openGL libraries
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

// my libraries
#include "../include/Engin.h"

// c++ libraries
#include <vector>
#include <cmath>

// namespaces
using namespace std;
using namespace arma;

namespace ENG
{
  void Engin::init(Graph& b)
  {
    d = b.d;
    push_const = 2;
    power_const = 2;
  }
  double Engin::calculate_energy(const vec& state,const vector<Segment>& con)
  {
    double energy = 0;
    for(auto itr = con.begin(); itr != con.end(); itr++)
    {
      vec x = state.subvec(d * itr->id_x, d* itr->id_x+(d-1));
      vec y = state.subvec(d * itr->id_y, d* itr->id_y+(d-1));
      if(itr->existing == 1)
      {
        double en = norm(y - x);
        double dist = itr->dist;
        double t = (-dist * dist + en * en);
        if(t<0)
        {
          t = INFINITY;
        }
        energy += t;
      }
      else
      {
        energy += push_const/ pow(norm(y-x), power_const);
      }
    }

    return energy;
  }
  vec Engin::calculate_der(const vec& state,const vector<Segment>& con, const vector<int>& fixed)
  {
    vec der(state.size(), fill::zeros);
    //cout<<"the number of const: "<<con.size()<<endl;
    double e = calculate_energy(state, con);
    for(auto itr = con.begin(); itr != con.end(); itr++)
    {
      vec d_x, d_y;
      vec Z(d, fill::zeros);
      vec x = state.subvec(itr->id_x * d, itr->id_x * d + (d-1));
      vec y = state.subvec(itr->id_y * d, itr->id_y * d + (d-1));
      if(itr->existing == 1)
      {
        double s = (norm(x-y) - itr->dist)/ 16;
        d_x = s * (y - x)/norm(x-y);
        d_y = s * (x - y)/norm(y-x);
      }
      else
      {
        double s = push_const / pow(norm(x - y), power_const) ;
        d_x = s * (x - y);
        d_y = s * (y - x);
      }
      if(fixed[itr->id_x] == 1)
      der.subvec(itr->id_x * d, itr->id_x * d + (d-1)) += Z;
      else
      der.subvec(itr->id_x * d, itr->id_x * d + (d-1)) += d_x;

      if(fixed[itr->id_y] == 1)
      der.subvec(itr->id_y * d, itr->id_y * d + (d-1)) += Z;
      else
      der.subvec(itr->id_y * d, itr->id_y * d + (d-1)) += d_y;
    }
    return der;
  }
}
