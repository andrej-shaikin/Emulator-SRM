#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

int RX=0,MEM[256];
int kol=1,lok=0;
ofstream fout("log.txt");
vector<string>k;

string SYMTAB[]={
"NOP","ADD","SUB",
"INC","DEC","LDR",
"STR","IN","OUT",
"JMP","IFZ","IFN","HALT"};

string DIRECTIVE[]={
".exit",".offset",
".def",".load",".ascii"};

void ADD(int addr){
	RX+=MEM[addr];}
void SUB(int addr){
	RX-=MEM[addr];}
void INC(int addr){
	MEM[addr]++;}
void DEC(int addr){
	MEM[addr]--;}
void LDR(int addr){
	RX=MEM[addr];}
void STR(int addr){
	MEM[addr]=RX;}
void IN(){
	printf(">>");scanf_s("%d",&RX);}
void OUT(){
if (RX<32 ) printf("%d{}\n",RX);
else printf("%d{%c}\n",RX,RX);}
bool IFN(){
if(RX<0) return true;
else return false;}
bool IFZ(){
if(RX==0) return true;
else return false;}


void to_upper(string &a){for(int i=0;i<a.size();i++) a[i]=toupper(a[i]);}
string com_name(string ish){
string pob;
for(int i=0;i<ish.size();i++){
if(ish[i]!=' ' && ish[i]!='[' && ish[i]!='\0') pob+=ish[i];
if(ish[i]==' ' || ish[i]=='[' || ish[i]=='\0') break;}
return pob;}
string def_load_name(string r){
	string name_file;
	int we=0,ew=0;
			for(int i=0;i<r.size();i++){
				if(r[i]=='"') {we=i+1;break;}}
			for(int i=we;i<r.size();i++){
				if(r[i]=='"') {ew=i;break;}}
			for(int i=we;i<ew;i++) name_file+=r[i];
		return name_file;}
string def_val(string r){
	string value;
	int we=0,ew=0;
	for(int i=0;i<r.size();i++){
				if(r[i]=='|') {we=i+1;break;}}
			for(int i=we;i<r.size();i++){
				if(r[i]=='|') {ew=i;break;}}
			for(int i=we;i<ew;i++) value+=r[i];
			return value;}
string def_name(string r){
	int we=0,ew=0;
	string name;
			for(int i=0;i<r.size();i++){
				if(r[i]=='<') {we=i+1;break;}}
			for(int i=we;i<r.size();i++){
				if(r[i]=='>') {ew=i;break;}}
			for(int i=we;i<ew;i++) name+=r[i];
		return name;}
void to_lower(string &h){
for(int i=0;i<h.size();i++) h[i]=tolower(h[i]);}
void log_def(string pob,string name,string value,string r){
	if(kol>1) fout<<endl;
	fout<<"----------"<<r<<"---------\n";
	fout<<"Name := "<<name<<endl;
	fout<<"Value := "<<value<<endl;kol++;
fout<<"----------------------------------\n";}
void log_file_direct(string pob){
	if(kol>1) fout<<endl;
fout<<"----------"<<pob<<"------------\n";}
void log_file(char cop,char modrm,int operand,string pob){
	if(kol>1) fout<<endl;
	fout<<"RX := "<<RX<<"\n";
	fout<<"MEM[ "<<operand<<" ] ="<<MEM[operand]<<endl<<"\n";
	fout<<"----------"<<pob<<"------------\n";
	int r=(cop|(modrm<<4)|(operand<<8));
	fout<<"assamble := "<<r<<endl;
	fout<<"cop := "<<(r&0X000F)<<endl;
	fout<<"modrm := "<<((r>>4)&0X0003)<<endl;
	fout<<"operand := "<<(r>>8)<<endl;
	fout<<"-------------------------\n";kol++;}
string met_ka(string r){
	string h;
	int we=0;
	for(int i=0;i<r.size();i++)
		if(r[i]=='$') {we=i+1;break;}
	for(int i=we;i<r.size();i++) h+=r[i];
	h+=':';
		return h;}
int addres(string ish){
	string j;
int we=0,ew=0;
for(int i=0;i<ish.size();i++)
if(ish[i]=='['){we=i+1;break;}

for(int i=we;i<ish.size();i++)
if(ish[i]==']') {ew=i;break;}

for(int i=we;i<ew;i++) j+=ish[i];
int w=atoi(j.c_str());
return w;}
void show(){
	for(int i=0;i<k.size();i++){
		cout<<k[i]<<endl;}
	cout<<endl;}
void go_metka(vector<string>&l,vector<string>::iterator &t,string met_ka){
	vector<string>::iterator qp;
		qp=l.begin();
		while(qp!=l.end()){
			string y=*qp;
			if(y==met_ka){
			t=l.begin();
			advance(t,distance(l.begin(),qp));break;}
		else {++qp;y.erase();}	}
}
int nac_pos(vector<string>&a){
	vector<string>::iterator t;
	t=a.begin();
	int pos=0;
	while(t!=a.end()){
		string e=*t;
		if(e.find('*')!=e.npos) break;
		else {++t;pos++;}	}
	return pos;}
void push(){
string com_file="com.txt";
ifstream fin(com_file);
if(!fin.is_open()) {cout<<"Error input "<<com_file<<" file ! \n";cin.get();exit(0);}
string l;
while(!fin.eof()){
	getline(fin,l);to_upper(l);k.push_back(l);}}
int load_pos(vector<string>&a){
	vector<string>::iterator t;
	t=a.begin();int pos=0;
	while(t!=a.end()){
		string w=*t;to_lower(w);
		if(w.find(DIRECTIVE[3])!=w.npos) break;
		else {++t;pos++;}}
	return pos;}
void del_load(vector<string>&k,string name){
	vector<string>::iterator a;
	a=k.begin();int pos=0;
	while(a!=k.end()){
		string w=*a;
		to_lower(w);
		if(w.find(DIRECTIVE[3])!=w.npos && w.find(name)!=w.npos){
			k.erase(k.begin()+pos);}
		else {++a;pos++;}}
		show();}
void show_vect(vector<string>&a){
	for(int i=0;i<a.size();i++) cout<<a[i]<<endl;cout<<endl;}
void viv_file(vector<string>&a){
	ofstream konecn_file("over.txt");
	auto it=a.begin();
	while(it!=a.end()){
		konecn_file<<*it<<endl;
		++it;}
}


void init(){
	for(int i=0;i<256;i++) MEM[i]=0;
#include "push_1.h"
	viv_file(k);
	}

int main(){
	setlocale(0,"");
	for(int i=0;i<256;i++) MEM[i]=0;
	bool debag=false;
	cout<<"Запустить в режиме отладки ? (1/0) ";
	int vib;cin>>vib;if(vib==1) debag=true;cout<<endl;
	if(debag) fout<<"\t\tРежим отладки \n\n";
	push();
	init();
	#include "parser.h"
	cout<<endl;
	system("pause");}