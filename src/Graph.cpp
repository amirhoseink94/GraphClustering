// openGL libraries
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

// my libraries
#include "../include/Graph.h"

// c++ libraries
#include <vector>
#include <random>


// namespaces
using namespace std;
using namespace arma;

void Graph::init(int dim)
{
  d = dim;
  load_from_file();
}

void Graph::move_randomly()
{
  for(int i=0;i<N_points;i++)
  {
    if(fixed[i]==0)
    {
      vec ran = arma::randu(d)-0.5;
      state.subvec(d*i,d*i+(d-1))+=ran;
    }
  }
}

void Graph::apply_force_1()
{
  vec n(d);
  n(0)=1;
  n(1)=0;
  n(2)=1;
  for(int i=0;i<N_points;i++)
  {
    if(fixed[i]==0)
    {
      n = state.subvec(d*i,d*i+(d-1));
      n(1)=0;
      vec f = n / norm(n);
      state.subvec(d*i,d*i+(d-1))+=f;
    }
  }
}
void Graph::apply_force_2()
{
  vec n(d);
  n(0)=1;
  n(1)=0;
  n(2)=1;
  for(int i=0;i<N_points;i++)
  {
    if(fixed[i]==0)
    {
      n = state.subvec(d*i,d*i+(d-1));
      n(1)=0;
      n(0) = -n(0);
      vec f = n / norm(n);
      state.subvec(d*i,d*i+(d-1))+=f;
    }
  }
}
void Graph::apply_force_3()
{
  vec c(d, fill::zeros);
  for(int i=0;i<N_points;i++)
  {
    c+=state.subvec(d*i,d*i+(d-1));
  }
  c = c / N_points;
  cout<<endl<<c<<endl;
  for(int i=0;i<N_points;i++)
  {
    //if(fixed[i]==0)
    //{
    vec n = state.subvec(d*i,d*i+(d-1)) - c;
    vec f = n / norm(n);
    state.subvec(d*i,d*i+(d-1))+=f;
    //}
  }
}

//==============================================================================

void Graph::load_from_file()
{
  string load_out;
  ifstream reader("Generator/constraints.txt");
  cout<<"the load has started"<<endl;
  reader>>load_out;
  reader>>N_points;
  cout<<load_out<<N_points<<endl;
  reader>>load_out;
  reader>>N_constraints;
  cout<<load_out<<N_constraints<<endl;


  state = vec(d * N_points, fill::zeros);
  vec Z(d, fill::zeros);
  fixed.resize(N_points);
  for(int i=0; i< N_constraints; i++)
  {
    int x, y, e;
    double d;
    reader>> x >> y >> d >> e;
    Segment temp(x, y, d, e);
    segments.push_back(temp);
  }
  cout<<"the fisrt part is done"<<endl;
  reader>>load_out;
  for(int i=0; i < N_points; i++)
  {
    double x, y, z, f;
    reader>>x>>y>>z>>f;
    vec p(d, fill::zeros);
    p(0) = x;
    p(1) = y;
    p(2) = z;
    fixed[i] = f;

    state.subvec(d * i, d * i +(d-1)) = p;
  }
  cout<<"the second part is done"<<endl;
  reader.close();
}

double Graph::generateRandomNumber(double x)
{
    // Set up random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0, x);

    // Generate a random number between 0 and x
    double randomNumber = dis(gen);
    return randomNumber;
}


void Graph::draw_Graph()
{
  glColor3ub(255, 255, 255);
  for(auto itr = segments.begin(); itr != segments.end(); itr++)
  {
    vec p1 = state.subvec(3*itr->id_x, 3*itr->id_x+2);
    vec p2 = state.subvec(3*itr->id_y, 3*itr->id_y+2);
    glColor3ub(255, 255, 255);
    //glPointSize(5);
    glBegin(GL_POINTS);
    glVertex3f(p1(0), p1(1), p1(2));
    glEnd();
    glBegin(GL_POINTS);
    glVertex3f(p2(0), p2(1), p2(2));
    glEnd();
    if(itr->existing == 1)
      glColor3ub(255, 255, 255);
    else
      glColor3ub(120, 120, 120);
    glBegin(GL_LINES);
    glVertex3f(p1(0), p1(1), p1(2));
    glVertex3f(p2(0), p2(1), p2(2));
    glEnd();
  }
}

Graph& Graph::operator= (const Graph& obj)
{
  return *this;
}

void Graph::generate_random()
{
  ofstream writer("Generator/constraints_tree.txt");
}
