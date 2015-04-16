#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
using namespace std;

class DataSlot{
	public:
		string value;
		//int key;
	public:
		DataSlot();
		DataSlot(string lb);
		~DataSlot();
		friend istream& operator >> (istream& s, DataSlot& dS);
		friend ostream& operator << (ostream& s, DataSlot& dS);
};

DataSlot::DataSlot(){
	value="";
	//key=0;
}

DataSlot::DataSlot(string lb){
	value=lb;
/*	int hash=0;
	for(int i=0;i<lb.length();i++){
		hash=hash+(int)lb[i];
	}
	key=hash;*/
}

DataSlot::~DataSlot(){

}

istream& operator >> (istream& s, DataSlot& dS){
	cout << "\n Enter value: "; cin >> dS.value;
	return s;
}

ostream& operator << (ostream& s, DataSlot& dS){
	cout <<dS.value << " - " <<endl;// dS.key;
	return s;
}

class Data{
	public:
		string data1;
		string data2;
	public:
		Data();
		Data(string s1,string s2);
		~Data();
		friend istream& operator >> (istream& s, Data& da);
		friend ostream& operator << (ostream& s, Data& da);

};

Data::Data(){
	data1="";
	data2="";
}

Data::Data(string s1,string s2){
	data1=s1;
	data2=s2;
}

Data::~Data(){

}

istream& operator >> (istream& s, Data& da){
	cout << "\n Enter Data1: "; cin >> da.data1;
	cout << "Enter Data2: "   ; cin >> da.data2;
	return s;
}

ostream& operator << (ostream& s, Data& da){
	cout <<da.data1 <<" - " << da.data2 << endl;
	return s;
}

class DataUrl{
	public:
		string url;
	public:
		DataUrl();
		~DataUrl();
};

DataUrl::DataUrl(){

}

DataUrl::~DataUrl(){

}
class Element{
	public:
		//Data da;
		//DataUrl dUrl;
		string eURL;
		Element *prev;
		Element *next;
	public:
		Element();
		//Element(Data d);
		//Element(DataUrl dU);
		Element(string sURL);
		~Element();
};


Element::Element(){
	prev=NULL;
	next=NULL;
}


/*Element::Element(Data dt){
	da=dt;
	prev=NULL;
	next=NULL;
}*/

/*Element::Element(DataUrl dU){
	dUrl=dU;
	prev=NULL;
	next=NULL;
}*/

Element::Element(string sURL){
	eURL=sURL;
	prev=NULL;
	next=NULL;
}


Element::~Element(){

}

class ElementHash{
	public:
		ElementHash* next;
		ElementHash* prev;
		string wTitle;
		string wAddress;
		string wRegion;
		string wPostal;
	public:
		ElementHash();
		~ElementHash();
};

ElementHash::ElementHash(){
	next=NULL;
	prev=NULL;
	wTitle="";
	wAddress="";
	wRegion="";
	wPostal="";
}

ElementHash::~ElementHash(){

}


class Slot{
	public:
		string URL;
		Slot* next;
		Slot* prev;
		ElementHash* headE;
		long int sizeSlot;
	public:
		Slot();
		Slot(string sURL);
		~Slot();
		void insertElement(ElementHash* e);
		void removeElement(ElementHash* e);
};

Slot::Slot(){
	string URL="";
	next=NULL;
	prev=NULL;
	headE=NULL;
	sizeSlot=0;
}
Slot::Slot(string sURL){
	URL=sURL;
	next=NULL;
	prev=NULL;
	headE=NULL;
	sizeSlot=0;
}
Slot::~Slot(){
	while(this->headE!=NULL)
		removeElement(this->headE);
}

void Slot::insertElement(ElementHash* x){
	x->next=this->headE;
	this->headE=x;
	if(x->next!=NULL){
		x->next->prev=x;
	}
	sizeSlot++;
}


void Slot::removeElement(ElementHash* x){
	if(x->next!=NULL)
		x->next->prev=x->prev;
	if(x->prev!=NULL)
		x->prev->next=x->next;
	else
		this->headE=x->next;
	delete x;
	sizeSlot--;
}



class HashMap{
	private:
		long int size;
		Slot* head;
	public:
		HashMap();
		~HashMap();
		int getSize() const;
		void insert(Slot* s);
		void insert(Slot*s, Element* x);
		void remove(Slot* s);
		void remove(Slot* s,Element* x);
		void display();
		void displayAllSlot();
		void displayNFirstSlot(int n);
		void displayAllKeyOfSlot(string slotID);
		void displayNFirstElementOfSlot(string slotID,int n);
		void addURL(string sURL);
		bool findURL(string sURL);
		long int hashFunction(string sURL);
		void insertElement();
		void displayAllSlotNE();
		void readOutput();
};


HashMap::HashMap(){
	size=0;
	head=NULL;
}


HashMap::~HashMap(){
	
}

void HashMap::addURL(string sURL){
	Slot* tempS=new Slot;
	tempS->URL=sURL;
	insert(tempS);
}

bool HashMap::findURL(string sURL){
	Slot* tempS=this->head;
	while(tempS!=NULL && sURL!=tempS->URL){ //dSlot.value){
		tempS=tempS->next;
	}
	if(tempS==NULL){
		return false;
	}
	else
		return true;
}
void HashMap::insert(Slot* s){
	s->next=this->head;
	this->head=s;
	if(s->next!=NULL)
		s->next->prev=s;
	size++;
}

int HashMap::getSize() const{
	return size;
}



void HashMap::insertElement(){
	string line1;
	ifstream f("E:\\temp.htm");
	ofstream outfile("output1.txt");
	bool begin_tag=false;
	while (getline(f,line1)){
		string tmp; // strip whitespaces from the beginning
		for (int i = 0; i < line1.length(); i++){
			if (line1[i] == ' ' && tmp.size() == 0){
			}
			else{
				tmp += line1[i];
			}
		}
		if (tmp == "<div class=\"lpfJobTitle\">"){
			begin_tag = true;
			continue;
		}
		else if (tmp == "<div class=\"jobApply fnt4\">"){
			begin_tag = false;
		}

		if (begin_tag){
			if(tmp.find("<span itemprop=\"title\">")!=string::npos&&tmp.find("</span>")!=string::npos){
				const size_t start_pos = line1.find("title");
				string temp = line1.substr(start_pos+7);
				const size_t stop_pos = temp.find("</span>");
				string title = temp.substr(0, stop_pos);
				outfile << title << "*";
		}

			if(tmp.find("<span itemprop=\"addressLocality\">")!=string::npos&&tmp.find("</span>")!=string::npos){
				size_t start_pos = line1.find("addressLocality");
				string temp = line1.substr(start_pos+17);
				size_t stop_pos = temp.find("</span>");
				string address = temp.substr(0, stop_pos);
				outfile << address << "*";
				temp=temp.substr(temp.find("addressRegion"),string::npos);
				string region=temp.substr(temp.find("addressRegion")+15,2);
				outfile << region << "*";
				if(temp.find("postalCode")!=string::npos){
					string postal=temp.substr(temp.find("postalCode")+12,5);
					outfile << postal << "*" << endl;
				}
				else{
					string postal="EMPTY";
					cout << postal << endl;
					outfile <<postal << "*" << endl;
				}	
			}
		}
	}
}

void HashMap::readOutput(){
	ifstream readOut("output1.txt");
	string line2;
	Slot* tempS=this->head;
	
	while(getline(readOut,line2)){
		if(!line2.empty()){
		ElementHash* tempE=new ElementHash;
		string temp1;
		size_t stop=line2.find("*");
		tempE->wTitle=line2.substr(0,stop);
		temp1=line2.substr(stop+1,string::npos);
		tempE->wAddress=temp1.substr(0,temp1.find("*"));
		temp1=temp1.substr(temp1.find("*")+1,string::npos);
		tempE->wRegion=temp1.substr(0,temp1.find("*"));
		temp1=temp1.substr(temp1.find("*")+1,string::npos);
		tempE->wPostal=temp1.substr(0,temp1.find("*"));
		tempS->insertElement(tempE);
		}
  }
}

void HashMap::displayAllSlotNE(){
	Slot* tempS=this->head;
	ElementHash* tempE;
	while(tempS!=NULL){
		cout << tempS->URL << endl;
		tempE=tempS->headE;
		while(tempE!=NULL){
			cout << tempE->wTitle << " " << tempE->wAddress << " " << tempE->wRegion << " " << tempE->wPostal << endl;
			tempE=tempE->next;
		}
		tempS=tempS->next;
	}
}

void HashMap::displayAllSlot(){
	Slot* tempS=this->head;
	while(tempS!=NULL){
		//cout << tempS->dSlot << endl;
		cout << tempS->URL << endl;
		tempS=tempS->next;
	}
}

/*void HashMap::displayNFirstSlot(int n){
	Slot* tempS;
	tempS=this->head;
	for(int i=0;i<n;i++){
		//cout << tempS->dSlot << endl;
		cout << tempS->url << endl;
		tempS=tempS->next;
	}
}

void HashMap::displayAllKeyOfSlot(string slotID){
	Slot* tempS;
	tempS=this->head;
	while(tempS!=NULL&&tempS->url!=slotID){
		tempS=tempS->next;
	}
	if(tempS==NULL){
		cout << "Cannot find slot" <<endl;
	}
	else{
		cout <<"All key of " <<tempS->url << endl;
		Element* tempE=tempS->head;
		while(tempE!=NULL){
			//cout << tempE->da << endl;
			cout << tempE->dUrl.url << endl;
			tempE=tempE->next;
		}
	}

}

void HashMap::displayNFirstElementOfSlot(string slotID,int n){
	Slot* tempS;
	tempS=this->head;
	while(tempS!=NULL&&tempS->url!=slotID){
		tempS=tempS->next;
	}
	if(tempS==NULL){
		cout << "Cannot Find Slot" <<endl;
	}
	else{
		Element* tempE=tempS->head;
		for(int i=0;i<n;i++){
			//cout <<tempE->da << endl;
			cout << tempE->dUrl.url << endl;
			tempE=tempE->next;
		}
	}
}*/

class LinkList{
	public:
		Element* headList;
	public:
		LinkList();
		~LinkList();
		void removeFirst();
		void removeElement(Element* e);
		void addElement(string sURL);
		void displayLinkList();
		string getDataFirstElement();
		void popFirstElement();
		bool isListEmpty();
};
LinkList::LinkList(){
	headList=NULL;
}

LinkList::~LinkList(){
	while(this->headList!=NULL){
		removeElement(this->headList);
	}

}

string LinkList::getDataFirstElement(){
	return this->headList->eURL;
}
bool LinkList::isListEmpty(){
	if(headList==NULL){
		return true;
	}
	else
		return false;
}

void LinkList::popFirstElement(){
	removeElement(this->headList);
}

void LinkList::addElement(string sURL){
	Element* tempE=new Element;
	tempE->eURL=sURL;
	tempE->next=this->headList;
	this->headList=tempE;
	if(tempE->next!=NULL){
		tempE->next->prev=tempE;
	}
}

void LinkList::removeElement(Element* e){
	if(e->next!=NULL) //if not the last one
			e->next->prev=e->prev;
		if(e->prev!=NULL) //if not the first one
			e->prev->next=e->next;
		else
			this->headList=e->next;
		delete e;
}

void LinkList::displayLinkList(){
	Element* tempE=headList;
	while(tempE!=NULL){
		cout << tempE->eURL << endl;
		tempE=tempE->next;
	}
}

class Crawler{
	public:
		LinkList urlToVisit;
		HashMap urlVisited;
	public:
		Crawler();
		~Crawler();
		bool listEmpty();
		void crawling();
		void read(string sURL);
		void addURL(string sURL);

};

Crawler::Crawler(){
//	urlToVisit=NULL;
//	urlVisited=NULL;
}

Crawler::~Crawler(){

}

bool Crawler::listEmpty(){
	return urlToVisit.isListEmpty();
}

void Crawler::crawling(){
	string urlPath=urlToVisit.getDataFirstElement();
	urlToVisit.popFirstElement();
	read(urlPath);
}

void Crawler::read(string sURL){
	system(("curl -o index1.html "+sURL).c_str());
	ifstream file("index1.html");
	urlVisited.insertElement();
	for (string line;(getline(file,line));){
	    // process line
		if ((line.find("<a href=\"http://jobs.monster.com/l") != std::string::npos) &&(line.find(".aspx" ) != std::string::npos)){
		    const size_t start_pos = line.find("href");
		    string temp = line.substr(start_pos+6);
		    const size_t stop_pos = temp.find("\"");
		    string result = temp.substr(0, stop_pos);
		    //cout << result << endl;
		    if(urlVisited.findURL(result)==false){
		    	addURL(result);
		    }
		}
	}
}

void Crawler::addURL(string sURL){
	urlToVisit.addElement(sURL);
	urlVisited.addURL(sURL);
}

int main(){
	/*Crawler cr;

	cr.addURL("http://jobs.monster.com");
	while(cr.listEmpty()==false && cr.urlVisited.getSize()<150){
		cr.crawling();
	}

	cr.urlVisited.displayAllSlot();*/
	
	HashMap* hm=new HashMap;
	
	hm->addURL("abc");
	hm->readOutput();
	hm->displayAllSlotNE();

	return 0;
}






/*int main(){
//	char* s=new char[80];
	string s="http://jobs.monster.com";
	system(("curl -o index.html "+s).c_str());
	ifstream file("index.html");
	    if ( !file.is_open() ) {
	        cerr << "Failed to open file." << endl;
	        return (EXIT_FAILURE);
	    }
	    for (string line;(getline(file,line));){
	        // process line
			if ((line.find("<a href=") != std::string::npos) &&(line.find(".aspx" ) != std::string::npos)){
			    const size_t start_pos = line.find("href");
			    string temp = line.substr(start_pos+6);
			    const size_t stop_pos = temp.find("\"");
			    string result = temp.substr(0, stop_pos);
			    cout << result << endl;
			}
	    }



	return 0;


}*/
