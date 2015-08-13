
#include "variant.h"
#include "variantcollection.h"

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	string str = "chr6	44387517	rs6923521	C	G	184.84	PASS	AC=2;AF=1.00;AN=2;DB;DP=6;FS=0.000;MLEAC=2;MLEAF=1.00;MQ=60.00;MQ0=0;POSITIVE_TRAIN_SITE;QD=30.81;SOR=3.912;VQSLOD=6.47;culprit=FS	GT:AD:DP:GQ:PL	1/1:0,6:6:18:213,18,0";
    stringstream ss(str);    

    Variant v;
	ss >> v;

	cout << "Yo Nico" << endl;
	cout << v << endl;
}
