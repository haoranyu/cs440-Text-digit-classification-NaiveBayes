#ifndef __NBC_H__
#define __NBC_H__
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>	
#include <map>
using namespace std;
//#define numClass 10
class NBC
{
	public:
		void Train(const vector< vector<int> > & traindata, const vector<int> & ltrain);

		void Test(const vector< vector<int> > & testdata);

		int test(const vector<int> &sample);
		void confusionOutput(int C, int D);

		void Print_confusionMatrix();
		void Print_Ptable();
		void set_numClass (int & nC);

		//void check_Ptable();
		
		int nFeature, Total, TP, TN, FP, FN, totalCorrect, totalTest, numClass;
		vector< vector<int> >	trainset, testset ;
		vector< vector<double> > Ptable;
		//vector<double> classPercent;
		vector<int> ltrain, ltest, pltest, classCount, testClassCount;

		
	private:
		map<int, map<int, double> > pcp, ncp;		
		vector<double> prior;
		vector<vector <int> > confI;
		vector<vector <double> > confusionMatrix;

};

#endif
