#include "NBC.h"
//#include <boost/algorithm/string.hpp>


int main(int argc, char* argv[])
{
	if (argc != 5){
		cout<< "Usuage: 5 arguments, the 1. executable followded by 2. training set, 3. training label, \
		4. test set, 5. tes label " << endl;
		exit(1);
	}

	NBC nbc;

	//Start get Input data
	ifstream traindata(argv[1]);
	ifstream trainlable(argv[2]);
	ifstream testdata(argv[3]);
	ifstream testlable(argv[4]);	
	if(trainlable.is_open() && traindata.is_open()){
		string line, lable;
		int l =-1;

		while (!trainlable.eof()){
			getline(traindata, line, '\n');
			getline(trainlable, lable, '\n');
			istringstream linestr(line);
			vector<int> sample;
			int v = 0;
			if (lable.size() ==0 )
				break;

			l = atoi(lable.c_str());
			//cout << "l: " <<l <<endl;
			nbc.ltrain.push_back(l);
			while(linestr >> v){
				sample.push_back(v);
			}
			nbc.trainset.push_back(sample);
		}
	}

	if(testlable.is_open() && testdata.is_open()){
		string line, lable;
		int l =-1;

		while (!testlable.eof()){
			getline(testdata, line, '\n');
			getline(testlable, lable, '\n');
			istringstream linestr(line);
			vector<int> sample;
			int v = 0;
			if (lable.size() ==0 )
				break;

			l = atoi(lable.c_str());
			//cout << "l: " <<l <<endl;
			nbc.ltest.push_back(l);
			while(linestr >> v){
				sample.push_back(v);
			}
			nbc.testset.push_back(sample);
		}
	}

	traindata.close();
	trainlable.close();
	testdata.close();
	testlable.close();

	// Start Training Naive Baysian Classifier


	nbc.Train(nbc.trainset, nbc.ltrain);

	//nbc.check_Ptable();

	nbc.Test(nbc.testset);

	nbc.Print_confusionMatrix();

	cout<<"total correct: " << nbc.totalCorrect << " , with ratio: " <<double(nbc.totalCorrect)/nbc.totalTest << endl;
/*
	int nlabel = nbc.pltest.size();

	cout << "# of lable: " <<nlabel<<endl;
	nbc.TP = 0;
	nbc.TN = 0;
	nbc.FP = 0;
	nbc.FN = 0;
    for (int n = 0; n<nlabel; n++)
	{
		cout<<"n ="<<n <<", nbc.ltest[n]: " << nbc.ltest[n] << ", nbc.pltest[n] " << nbc.pltest[n] << endl;
		if(nbc.ltest[n] ==1 && nbc.pltest[n] == 1)    nbc.TP+=1;
		if(nbc.ltest[n] ==-1 && nbc.pltest[n] == -1)  nbc.TN+=1;
		if(nbc.ltest[n] ==-1 && nbc.pltest[n] == 1)   nbc.FP+=1;
		if(nbc.ltest[n] ==1 && nbc.pltest[n] == -1)   nbc.FN+=1;
	}

    cout<<nbc.TP<<endl;
	cout<<nbc.FN<<endl;
	cout<<nbc.FP<<endl;
	cout<<nbc.TN<<endl;
*/
}