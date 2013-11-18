#include "NBC.h"



void NBC::Train(const vector< vector<int> > & traindata, const vector<int> & ltrain)
{
	if (0==0.0)
		cout <<"shiba!" <<endl;

	int pc=0;
	int nc = 0;
	int length = traindata.size();
	int width = traindata[1].size();
	this->Total = length;
	this->nFeature = width;
	for (int j =0; j<numClass; j++)
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
	for (int j =0; j<numClass; j++)
	{
		//int d = classCount[j] + nFeature;

		for (int i =0; i<nFeature; i++)
		{	
			this->Ptable[j][i] = this->Ptable[j][i]/classCount[j];
		}
		this->prior.push_back(double(this->classCount[j])/this->Total);
	}
}


void NBC::Test(const vector< vector<int> > & testdata )
{
	this->totalCorrect = 0;
	for (int i = 0 ; i < numClass; ++i){
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
		int plabel=test(testdata[s]);
		//cout<<"#sample = "<<s <<"pl is: "<< plabel <<" l is: " <<ltest[s] <<endl;
		cout<<"for sample #"<<s<<endl;
		cout<<"true idx at : "<< this->ltest[s] <<endl;
		cout<<"pred idx at : "<< plabel<<endl;

		this->pltest.push_back(plabel);
		this->confI[ltest[s]][plabel] +=1;
		this->testClassCount[ltest[s]] +=1;
	}
	//cout<<"aha !"<<endl;
	for (int i = 0 ; i < numClass; ++i){
			vector<double> init;
		for(int j = 0; j< numClass;++j){
			init.push_back(double(this->confI[i][j])/this->testClassCount[i]);
		}
			this->confusionMatrix.push_back(init);
		this->totalCorrect += this->confI[i][i];
	}
}


int NBC::test(const vector<int> &sample)
{

    vector<double> posterior;
    int maxId = 0;
    double max = -9999;
	//cout<<"sample dimension: "<<sample.size()<<endl;

    for (int i = 0 ; i< numClass; ++i){

    	int P = log(this->prior[i]);
		for(int f=0; f<nFeature; ++f)
		{
			double pp = this->Ptable[i][f];
			if (pp < 0.00001)
				pp = 0.00001;
			if (pp > 0.99999)
				pp = 0.99999;

			if (sample[f] == 1)
				P=P + log(pp);
			else if (sample[f] == 0)
				P=P + log(1-pp);

		}
		if(max < P){
			max = P;
			maxId = i;
		}
		posterior.push_back(P);
	}
	
	//for (int i = 0 ; i<numClass; ++i)
	//	cout<<posterior[i]<<", ";
	//cout<<endl;
	return maxId; 
}

void NBC::Print_confusionMatrix()
{
	cout<<"confusionMatrix: "<<endl;
	for (int i = 0 ; i < numClass; ++i){

		for(int j = 0; j< numClass;++j){
			cout<<setw(11)<<this->confusionMatrix[i][j]<<", ";
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




























