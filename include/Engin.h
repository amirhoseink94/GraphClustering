#ifndef ENGIN_H
#define ENGIN_H

#include <set>
#include <iostream>
#include <stdio.h>
#include <armadillo>
#include <bits/stdc++.h>
#include <cmath>

#include "Particle.h"
#include "Segment.h"
#include "Face.h"
#include "Graph.h"


using namespace std;
using namespace arma;


namespace ENG{
	class Engin
	{
		public:
		void init(Graph&);
		double calculate_energy(const vec&, const vector<Segment>&);
		vec calculate_der(const vec&, const vector<Segment>&, const vector<int>&);
		private:
		vector<bool> fixed;
		int d;
		double push_const;
		double power_const;
	};
}
#endif
