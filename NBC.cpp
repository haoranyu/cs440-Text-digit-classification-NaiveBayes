#include "NBC.h"
//#define LONG_MIN   (-2147483647L - 1)

void NBC::set_numClass (int & nC){
	this->numClass = nC;
}

void NBC::Train(const vector< vector<int> > & traindata, const vector<int> & ltrain)
{
	
	int length = traindata.size();
	int width = traindata[1].size();
	this->Total = length;
	this->nFeature = width;
	cout << "# of nFeature: "<< nFeature<<endl;

	for (int j =0; j<this->numClass; j++)
	{
		vector<double> init;
		for (int i =0; i<this->nFeature; i++)
		{	
			init.push_back(0);
		}
		this->Ptable.push_back(init);
		this->classCount.push_back(0);
	}
	for (int j =0; j<length; j++)
	{
		for (int i =0; i<width; i++)
		{
			if (traindata[j][i] == 1)
				this->Ptable[ltrain[j] ][i]+=1.0;
		}
		this->classCount[ltrain[j]] +=1;
	}
	for (int j =0; j< (this->numClass); j++)
	{
		//int d = classCount[j] + nFeature;
		for (int i =0; i<nFeature; i++)
		{	
			this->Ptable[j][i] = this->Ptable[j][i]/classCount[j];
		}
		this->prior.push_back(double(this->classCount[j])/this->Total);
	}

	//cout <<"prior: "<<endl;
	//for (int k = 0; k < (this->prior).size(); k++)
	//	cout<<this->prior[k] <<", ";
	//cout<<endl;	
}

void NBC::Test(const vector< vector<int> > & testdata )
{
	this->totalCorrect = 0;
	for (int i = 0 ; i < this->numClass; ++i){
		vector<int> init;
		for(int j = 0; j< numClass;++j)
		{
			init.push_back(0);
		}
		this->confI.push_back(init);
		this->testClassCount.push_back(0);
	}

	int length = testdata.size();
	this->totalTest = length;
	int width = testdata[1].size();	

	for (int s = 0; s<length; s++)
	{		
		//cout<<"for sample #"<<s<<endl;
		int plabel=test(testdata[s]);
		//cout<<"#sample = "<<s <<"pl is: "<< plabel <<" l is: " <<ltest[s] <<endl;

		//cout<<"true idx at : "<< this->ltest[s] <<endl;
		//cout<<"pred idx at : "<< plabel<<endl;
		this->pltest.push_back(plabel);
		this->confI[ltest[s]][plabel] +=1;
		this->testClassCount[ltest[s]] +=1;
	}
	//cout<<"aha !"<<endl;
	for (int i = 0 ; i < (this->numClass); ++i){
		vector<double> init;
		//cout<<"testClassCount " <<this->testClassCount[i]<<endl;
		for(int j = 0; j< (this->numClass);++j){
			//cout <<"confI count "<< this->confI[i][j] <<endl;
			init.push_back(double(this->confI[i][j])/this->testClassCount[i]);
		}
		this->confusionMatrix.push_back(init);
		this->totalCorrect += this->confI[i][i];
	}
}


int NBC::test(const vector<int> &sample)
{

    vector<long double> posterior;
    int maxId = 0;
    long double max = -999999;
	//cout<<"sample dimension: "<<sample.size()<<endl;

    for (int i = 0 ; i< (this->numClass); ++i){

    	long double P = log(this->prior[i]);
    	//cout<<"prior: "<<this->prior[i]<<endl;
		for(int f=0; f<nFeature; ++f)
		{
			long double pp = this->Ptable[i][f];
			//cout<<"pp: "<<pp<<endl;
			if (pp <0.00001)
				pp = 0.00001;
			if (pp >0.99999)
				pp = 0.99999;
			//cout<<"feature: "<<sample[f]<<endl;
			if (sample[f] == 1){
				//cout<<"P: "<<P<<", log (pp)"<<log(pp)<<endl;
				P=P + log(pp);
				//cout<<"P: "<<P<<endl;
			}
			else if (sample[f] == 0){
				//cout<<"P: "<<P<<", log (1-pp)"<<log(pp)<<endl;
				P=P + log(1-pp);
				//cout<<"P: "<<P<<endl;
			}

		}
		if(max < P){
			max = P;
			maxId = i;
		}
		posterior.push_back(P);
	}

	//cout<<"posterior: "<<endl;

	//for (int k = 0 ; k < posterior.size();++k){
	//	cout<<posterior[k]<<", ";
	//}
	//cout<<endl;
	
	//for (int i = 0 ; i<numClass; ++i)
	//	cout<<posterior[i]<<", ";
	//cout<<endl;
	return maxId; 
}

void NBC::confusionOutput(int C, int D)
{
	cout<<"\n\n"<<endl;

	double P1, P2, OD;
	P1 = P2 = OD =0.0;
	cout<<"High confusion rate to classify class " <<C <<" as class " <<D <<"is "<<this->confusionMatrix[C][D] <<endl;
	vector<double> PP1, PP2, OOD;
	for (int i=0; i < nFeature; ++i)
	{
		double _p1 = Ptable[C][i];
		double _p2 = Ptable[D][i];
		if (_p1 < 0.0001) _p1 =0.0001;
		if (_p2 < 0.0001) _p2 =0.0001;
		PP1.push_back(log(_p1));
		PP2.push_back(log(_p2));
		OOD.push_back(log(_p1) - log(_p2));
	}
	cout<<"log likelihood for class 1" <<endl;
	for (int i=0; i < nFeature; ++i)
	{
		cout<<PP1[i]<< " ";
	}
	cout<<endl;
	cout<<"log likelihood for class 2" <<endl;
	for (int i=0; i < nFeature; ++i)
	{
		cout<<PP2[i]<< " ";
	}
	cout<<endl;
	cout<<"log odds ratio" <<endl;
	for (int i=0; i < nFeature; ++i)
	{
		cout<<OOD[i]<< " ";
	}
	cout<<endl;

}

void NBC::Print_confusionMatrix()
{
	cout<<"confusionMatrix: "<<endl;
	for (int i = 0 ; i < (this->numClass); ++i){

		for(int j = 0; j< (this->numClass);++j){
			cout<<setw(11)<<this->confusionMatrix[i][j]<<", ";
		}
		cout<<endl;
	}
}

void NBC::Print_Ptable()
{
	cout<<"Ptable: "<<endl;
	for (int i = 0 ; i < (this->numClass); ++i){

		for(int j = 0; j< this->nFeature ;++j){
			cout<<setw(5)<<this->Ptable[i][j]<<", ";
		}
		cout<<endl;
	}
}


/*

void NBC::check_Ptable()
{
	cout<<"check_Ptable: "<<endl;
	for (int i = 0 ; i < numClass; ++i){
		double sum = 0;
		for(int j = 0; j< this->nFeature; ++j){
			//cout<< Ptable[i][j]<<", ";
			sum+= Ptable[i][j];
		}
		cout<<"row sum is :" << sum <<endl;
	}
}*/




























