#include "ann.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

double transferFunction(double x);
vector<vector<Neuron> > layers;
void forward_pass(vector<vector<Neuron> > &layers);
void back_pass(vector<vector<Neuron> > &layers);
void initialiseLayers(vector<vector<Neuron> > &layers,vector<double> inputs);
double getRandomWeight();

int main() {
cout<<"hello world"<<endl;
vector<vector<double> > initialInputs ={{0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1}};


initialiseLayers( layers, initialInputs[7]);
forward_pass(layers);
return 0;}

/**
 * passes the data to the next layer in the network
 * @param layers
 */

void forward_pass(vector<vector<Neuron> > &layers){
  cout<<layers.size()<<endl;
    vector<Neuron> prev_layer;
    for(unsigned int i=1;i<layers.size();++i){
        prev_layer=layers[i-1];
        for(unsigned int j=0;j<layers[i].size();++j){

            double input= prev_layer[0].getOutput()*layers[i][j].getWeights()[0]+prev_layer[1].getOutput()*layers[i][j].getWeights()[1];
            //cout<<"outputs "<<prev_layer[0].getOutput()<<" "<<prev_layer[1].getOutput()<<endl;
           cout<<"out"<<i<<" "<<j<<": "<<transferFunction(input)<<" input "<<input<<endl;
            vector<double> inputs={prev_layer[0].getOutput(),prev_layer[1].getOutput()};
            layers[i][j].inputs=inputs;
            layers[i][j].setInput(input);
            layers[i][j].setOutput(transferFunction(input));
        }
    }

}

/**
 * initialise the layers with inputs and random weights
 * @param layers neural network layers
 * @param inputs initial inputs
 */
void initialiseLayers(vector<vector<Neuron> > &layers,vector<double> inputs){

layers.reserve(3);
  //initialise the first layer, set inputs
  std::vector<Neuron> temp;
  std::vector<Neuron> temp1;


for(int i=0;i<3;++i){
Neuron l1;

l1.setInput(inputs[i]);
l1.setOutput(inputs[i]);
temp.push_back(l1);
}

layers.push_back(temp);

// initialise the hidden and output layer with random weights
int numberOfHidden =2;
for (int j=0;j<numberOfHidden;++j){
  std::vector<double> weights={getRandomWeight(),getRandomWeight(),getRandomWeight()};
  Neuron l2(weights);
  temp1.push_back(l2);
}
layers.push_back(temp1);

//initialise the last Neuron with random weights
std::vector<double> weights={getRandomWeight(),getRandomWeight(),getRandomWeight()};

Neuron l3(weights);

std::vector<Neuron> temp2={l3};//temp vector avoids seg_core dump error
layers.push_back(temp2);
cout<<layers.size()<<endl;


}



double transferFunction(double x) {

    return 1/(1+exp(-x));
}

double calcErrorOutput(double output,double target){

 return output*(1-output)*(target-output);
}

double getRandomWeight(){
  srand(time(0));
  double r = ((double) rand() / (RAND_MAX));
//cout<<"random is "<<r<<endl;
  return r;
}
