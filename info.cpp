#include <iostream>

using namespace std;



int proba(float ALL[], int number, float sp,int par,int cur,float prob,int depth){
	int nuh;
	if(depth==number){
		ALL[cur]+=prob;
		//cout<<"pos "<<cur<<" prob "<<prob<<"\n";
	} else{
		if(par>0){
			par--;
			depth++;
			//nuh = proba(ALL,number,sp,cur+1,prob*sp,depth);
			nuh = proba(ALL,number,sp,par,cur,prob,depth);
		} else {
			depth++;
			nuh = proba(ALL,number,sp,par,cur+1,prob*sp,depth);
			nuh = proba(ALL,number,sp,par,cur,prob*(1-sp),depth);
		}
	}
	return 0;
}

float search(int my_base,int my_coin_number,int my_coin_power,float my_sp_r,int my_par, int en_base, int en_coin_number,int en_coin_power, float en_sp_r,int en_par,int step){
	int nuh;
	if(en_coin_number==0)
		return 1;
	if(my_coin_number==0)
		return 0;
	float victory=0;
	float draw=0;
	float lose=0;
	float *MY=new float[my_coin_number+1];
	float *EN=new float[en_coin_number+1];
	float my_sp=(50+my_sp_r)/100;
	float en_sp=(50+en_sp_r)/100;
	
	
	
	for(int i=0;i<=my_coin_number;i++){
		MY[i]=0;
	} nuh = proba(MY,my_coin_number,my_sp,my_par,0,1,0);
	for(int i=0;i<=en_coin_number;i++){
		EN[i]=0;
	} nuh = proba(EN,en_coin_number,en_sp,en_par,0,1,0);
	cout<<"\n\nStep: "<<step<<"\n\n";
	step++;
	cout<<"My probabilities to drop \n";
	for(int i=0;i<=my_coin_number;i++)
		cout<<i<<" coins = "<<MY[i]*100<<"%\n";
	cout<<"Enemy probabilities to drop \n";
	for(int i=0;i<=en_coin_number;i++)
		cout<<i<<" coins = "<<EN[i]*100<<"%\n";
	
	
	
	for(int i=0;i<=my_coin_number;i++){
		for(int j=0;j<=en_coin_number;j++){
			int my_res=my_base+i*my_coin_power;
			int en_res=en_base+j*en_coin_power;
			if(my_res>en_res)
				victory += MY[i] * EN[j];
			if(my_res==en_res)
				draw += MY[i]*EN[j];
			if(my_res<en_res)
				lose += MY[i]*EN[j];
		}
	}
	
	delete[] MY;
	delete[] EN;
	
	
	cout<<"victory: "<<victory<<"\ndraw: "<<draw<<"\nlose: "<<lose<<"\n";
	victory = victory/(1-draw);
	lose = lose/(1-draw);
	if(draw==1) victory = search(my_base,my_coin_number,my_coin_power,my_sp_r,my_par-my_coin_number,en_base,en_coin_number,en_coin_power,en_sp_r,en_par-en_coin_number,step);
	if(victory>0)victory = victory * search(my_base,my_coin_number,my_coin_power,my_sp_r,my_par-my_coin_number,en_base,en_coin_number-1,en_coin_power,en_sp_r,en_par-en_coin_number,step);
	if(lose>0)lose = lose * (search(my_base,my_coin_number-1,my_coin_power,my_sp_r,my_par-my_coin_number,en_base,en_coin_number,en_coin_power,en_sp_r,en_par-en_coin_number,step));
	
	return victory+lose;
}
int main(){
	int repeat=1;
	while(repeat==1){
		int my_base;int my_coin_number;int my_coin_power;float my_sp; int en_base;int en_coin_number;int en_coin_power;float en_sp;int my_par;int en_par;
		cout<<"Enter info: \n my base, my coin number, my coin power, my sanity, my paralazis \n";
		cin>>my_base>>my_coin_number>>my_coin_power>>my_sp>>my_par;
		cout<<"Enter info: \n enemy base, enemy coin number, enemy coin power, enemy sanity, enemy paralazis \n";
		cin>>en_base>>en_coin_number>>en_coin_power>>en_sp>>en_par;
		float result;
		result = search(my_base,my_coin_number,my_coin_power,my_sp,my_par,en_base,en_coin_number,en_coin_power,en_sp,en_par,1);
		cout<<"Rate of succes: "<<result*100<<"%\n to repeat enter 1: ";
		cin>>repeat;
	}
}
