vector<string>::iterator t;
t=k.begin();
vector<string>metki;
vector<string>def;
vector<string>comand;
string name_file;
vector<string>lo_pos;
int load_p=load_pos(k);
//1)добавить в список
//2)заменить в списке
while(t!=k.end()){
	string r=*t;
	string pob=com_name(r);
	to_lower(pob);
	if(pob==DIRECTIVE[3]){
		name_file=def_load_name(r);to_lower(name_file);
		ifstream cv(name_file);
		if(!cv.is_open()){cout<<"Error input "<<name_file<<" file !\n";cin.get();exit(0);}
	string sr;
	while(!cv.eof()){
		getline(cv,sr);
		/*metki*/
	if(sr.find(':')!=-1){to_upper(sr);
	k.push_back(sr);
		while(!cv.eof()){
			getline(cv,sr);to_upper(sr);
		metki.push_back(sr);}
	}
	/*.def*/
	if(sr.find(DIRECTIVE[2])!=-1){
	def.push_back(sr);}
	/*com*/
	if(sr.find('.')==-1 && sr.find(':')==-1 && sr.find('$')==-1){
		to_upper(sr);
	comand.push_back(sr);}		}			}
	++t;
}
for(int i=0;i<metki.size();i++) {to_upper(metki[i]);k.push_back(metki[i]);}
int nac_p=nac_pos(k);
for(int i=0;i<def.size();i++){to_upper(def[i]);
k.insert(k.begin()+nac_p,def[i]);nac_p++;}
	/*		Вставка команд 	*/
for(int i=0;i<comand.size();i++){
k.insert(k.begin()+load_p,comand[i]);load_p++;}
int tyl=0;

for(int i=0;i<k.size();i++){
	string h=k[i];
if(h.empty()) k.erase(k.begin()+i);	}
	
auto ifg=k.begin();int wers=0;
while(ifg!=k.end()){
	string h=*ifg;
	string bg=DIRECTIVE[3];
	to_upper(bg);
	if(h.find(bg)!=-1) ifg=k.erase(k.begin()+wers);
else {++ifg;wers++;}}
for(int i=0;i<k.size();i++)	to_upper(k[i]);
//show();