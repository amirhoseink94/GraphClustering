#ifndef GRAPH_H
#define GRAPH_H

#include <set>
#include <iostream>
#include <stdio.h>
#include <armadillo>
#include <bits/stdc++.h>

#include "Particle.h"
#include "Segment.h"
#include "Face.h"


using namespace std;
using namespace arma;



class Graph
{
	public:
	// the state is the location of all points, the size is d*N_of_points
	vec state;

	// the der is the derivitive of the potential function, again, its size is d*N_of_points
	vec der;

	// in the segment we practically storing all the information about the constraints
	vector<Segment> segments;

	// the current energy, based on the state of the graph
	double energy;

	// the dimention of the vectors that we are goifn to represent the graph with
	int d;

	// number of points
	int N_points;

	// number of constrants, or the number of edges
	int N_constraints;

	// this vector containts the information about if the point is fixed or not!
	vector<int> fixed;

	void init(int /* dimention of the representation */);

	void move_randomly();

	void calculate_der();

	void graph_generator();
	void apply_force_1();
	void apply_force_2();
	void apply_force_3();

	//============================================================================
	bool operator==(const Face& rhs) const;
	Graph& operator= (const Graph& obj);

	// drawing materials for now

	void draw_Graph();
	void print();
	//  Geometry
	void reshape();

	//private:

	double calculate_energy();
	Mat<double> PSPD(const Mat<double>&);

	// file handling
	void load_from_file();
	double generateRandomNumber(double x);

	void generate_Tree();

	//void save_to_file();
private:
	int w;
	int l;


};

#endif
