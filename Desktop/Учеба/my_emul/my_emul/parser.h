vector<string>::iterator t;
string name_st="over.txt";
ifstream wer(name_st);
vector<string>glava;
if(!wer.is_open()) {cout<<"Error input file "<<name_st<<" !!\n";cin.get();exit(0);}
while(!wer.eof()){
string kl;
getline(wer,kl);
glava.push_back(kl);}
t=glava.begin();
/*def*/
while(t!=glava.end()){
	string wq=*t;
	to_lower(wq);
	string pob=com_name(wq);
	if(pob==DIRECTIVE[2]){
		string name=def_name(wq);
		string val=def_val(wq);
		auto q=glava.begin();
		while(q!=glava.end()){
			string r=*q;
			to_lower(r);
			if(r.find(name)!=-1 && r.find(':')==-1 && r.find('.')==-1 && r.find('$')==-1){
			r.replace(r.find(name),val.size(),val);}
		++q;}}
++t;}
t=glava.begin();int p=0;
while(t!=glava.end()){
	string r=*t;
	string pob=com_name(r);to_upper(pob);
	/*ADD*/
	if(pob==SYMTAB[1]){if(debag) cout<<pob<<" : \n";
	int addr=addres(r);ADD(addr);log_file(1,2,addr,pob);if(debag) {cout<<"RX := "<<RX<<endl;cin.get();}}
	/*SUB*/
	if(pob==SYMTAB[2]){if(debag)cout<<pob<<" : \n";
	int addr=addres(r);SUB(addr);log_file(2,2,addr,pob);if(debag){cout<<"RX := "<<RX<<endl;cin.get();}}
	/*INC*/
	if(pob==SYMTAB[3]){if(debag)cout<<pob<<" : \n";
int addr=addres(r);INC(addr);log_file(3,2,addr,pob);if(debag){cout<<"RX := "<<RX<<endl;cin.get();}}
	/*DEC*/
	if(pob==SYMTAB[4]){if(debag)cout<<pob<<" : \n";
int addr=addres(r);DEC(addr);log_file(4,2,addr,pob);if(debag){cout<<"RX := "<<RX<<endl;cin.get();}}
	/*LDR*/
	if(pob==SYMTAB[5]){if(debag)cout<<pob<<" : \n";
	int addr=addres(r);LDR(addr);log_file(5,2,addr,pob);if(debag){cout<<"RX := "<<RX<<endl;cin.get();}}
	/*STR*/
	if(pob==SYMTAB[6]){if(debag)cout<<pob<<" : \n";
	int addr=addres(r);STR(addr);log_file(6,2,addr,pob);if(debag){cout<<"MEM [ "<<addr<<" ] := "<<MEM[addr]<<endl;cin.get();}}
	/*IN*/
if(pob==SYMTAB[7]){if(debag){cout<<endl;cout<<pob<<" : \n";}IN();log_file(7,0,0,pob);if(debag){cout<<"RX := "<<RX<<endl<<endl;cin.get();}}
	/*OUT*/
	if(pob==SYMTAB[8]){if(debag)cout<<pob<<" : \n";OUT();log_file(8,0,0,pob);if(debag){cout<<"RX := "<<RX<<endl;cin.get();}}
	/*JMP*/
	if(pob==SYMTAB[9]){if(debag)cout<<pob<<" : ";
		string metka=met_ka(r);if(debag)cout<<metka<<endl;
		vector<string>::iterator qp;
		qp=glava.begin();
	go_metka(glava,t,metka);log_file(9,1,p,pob);if(debag)cin.get();}
	/*IFZ*/
	if(pob==SYMTAB[10]){if(debag)cout<<pob<<" : \n";
	if(IFZ()){t+=1;log_file(10,0,0,pob);if(debag)cin.get();continue;}
	if(!IFZ()){t+=2;log_file(10,0,0,pob);if(debag)cin.get();continue;}	}
	/*IFN*/
	if(pob==SYMTAB[11]){
	if(IFN()){t+=1;log_file(11,0,0,pob);if(debag)cin.get();continue;}
	if(!IFN()){t+=2;log_file(11,0,0,pob);if(debag)cin.get();continue;}	}
	/*HALT*/
	if(pob==SYMTAB[12]) {log_file(15,0,0,pob);if(debag)cin.get();break;}
	to_lower(pob);
	/*.exit*/
	if(pob==DIRECTIVE[0]){if(debag)cout<<pob<<" : \n";log_file_direct(pob);system("pause");exit(0);}
	/*.offset	*/
	if(pob==DIRECTIVE[1]){if(debag)cout<<pob<<" : \n";
	log_file_direct(pob);
	int u=distance(glava.begin(),t);
	cout<<"POS : "<<u<<endl;if(debag)cin.get();}
	/*.ascii*/
	if(pob==DIRECTIVE[4]){if(debag)cout<<pob<<" : \n";
		log_file_direct(pob);
	cout<<"' "<<char(RX)<<" '"<<endl;if(debag)cin.get();}
++t;p++;}
