#include <iostream>
#include <fstream>

using namespace std;

int main(){
	long int numOfLine=0;
	ifstream in("Data3.txt");
	string line;
	long int lIT=0,lSales=0,lAccounting=0,lMedical=0,lBuilding=0,lServices=0;
	long int lOffice=0;
	while(getline(in,line)){
		if(!line.empty()){
			if(line.find("-")==string::npos){
				if(line.find("IT")!=string::npos||line.find("Engineering")!=string::npos||line.find("Project")!=string::npos||line.find("Installation")!=string::npos||line.find("Quality")!=string::npos){
					lIT++;	
				}
				if(line.find("Sales")!=string::npos||line.find("Business")!=string::npos||line.find("Marketing")!=string::npos){
					lSales++;
				}
				if(line.find("Accounting")!=string::npos||line.find("Banking")!=string::npos){
					lAccounting++;
				}
				if(line.find("Medical")!=string::npos||line.find("Education")!=string::npos){
					lMedical++;
				}
				if(line.find("Customer")!=string::npos||line.find("Food")!=string::npos||line.find("Security")!=string::npos||line.find("Manufacturing")!=string::npos){
					lServices++;
				}
				if(line.find("Building")!=string::npos||line.find("Logistics")!=string::npos){
					lBuilding++;
				}
				if(line.find("Administrative")!=string::npos||line.find("Editorial")!=string::npos){
					lOffice++;
				}
				numOfLine++;	
			}
		}	
	}
	float iT=(float)lIT*100/numOfLine;
	float sales=(float)lSales*100/numOfLine;
	float accounting=(float)lAccounting*100/numOfLine;
	float medical=(float)lMedical*100/numOfLine;
	float building=(float)lBuilding*100/numOfLine;
	float services=(float)lServices*100/numOfLine;
	float office=(float)lOffice*100/numOfLine;
	cout << "% IT: " << iT << endl;
	cout << "% Sales: " << sales  << endl;
	cout << "% Accouting: " << accounting << endl;
	cout << "% Medical: " << medical<< endl;
	cout << "% Building: " << building << endl;
	cout << "% Services: " << services << endl;	
	cout << "% Office: " << office << endl;	
	cout << "% Others: " << 100-iT-sales-accounting-medical-building-services-office << endl;
	cout << numOfLine << endl;	
	
	
	in.close();
	return 0;
}