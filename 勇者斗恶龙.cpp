#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<windows.h> 
using namespace std;
char judge ;//judge if exists cundang
ofstream fout;//("d:\\Program Files\\herosave.txt",ios::out);
ofstream fout2;
ifstream fin("herosave.txt",ios::in);
ifstream fin2("d:\\Program Files\\herosave1.txt",ios::in);
class monster;
class boss;
class player{//��� 
	int hp=10;
	int mp=10;
	int atk=5;
	float dfd=1.0;
	int lv=1;
	int exp=0;
	int money=0; 
	public:
		char name[50];
		void printname();
		void printstate();
		void addexp(int ae);
		void gainmoney(int gm);
		void be_hit(int bh);
		void attack(monster * m);
		void set_name(char a[]);
		void set_dfd(double dfd0);
		void set_hp(int hp0);
		void set_mp(int mp0);
		void set_state(int hp0 , int mp0 , int lv0 , int atk0 , int exp0 , int money0 );
		void dclmp(int dmp);
		int chp() {return hp;}
		int cmp() {return mp;}
		int clv() {return lv;}
		int catk() {return atk;}
		int cmy() {return money;}
		int cexp() {return exp;}
		float cdfd() {return dfd;}
	friend class monster ;
	friend class boss ;
}; 
class monster {
	protected:
		char name[20];
		int hp;
		int atk;
		int value;
		int iterator=0;
		int tmpatk=atk;
	public:
		void printname();
		void be_hit(int bh);
		void attack(player * p);
		int chp() {return hp;}
		int catk() {return atk;}
		virtual void bigskill();
		monster (int hp0,int atk0,int value0,char name0[]):hp(hp0),atk(atk0),value(value0){
			strcpy(name,name0);
		}
		int cvalue() {return value;}
	friend class player ;
};
class boss : public monster{
		int tmpatk=atk;
		public:
			void bigskill();
			boss (int hp0,int atk0,int value0,char name0[]): monster(hp0,atk0,value0,name0){}
		friend class player ;
};
void player::set_name(char a[]){
	strcpy(name,a);
	return;
}
void player::set_state(int hp0 , int mp0 , int lv0 , int atk0 , int exp0 , int money0 ){
	hp=hp0;mp=mp0;lv=lv0;atk=atk0;exp=exp0;money=money0;
}
void player::printname(){
	cout<<name;
}
void player::printstate(){
	cout<<"���ߣ�"<< name << " hp:"<< hp<< " mp:"<< mp<< " �ȼ�"<< lv<< " ��Ǯ"<< money<<endl;
 	return;
}
void player::addexp(int ae){
	exp+=ae;
	cout << "������" <<  ae << "�㾭��" << endl ;
	while(exp>=lv*10){
		exp-=lv++*10;
		cout<<"���ߣ���ϲ�������ˣ���ǰ�ȼ���" <<lv<<endl; 
		hp=lv*10;
		mp=lv*10;
		atk=lv*5;
		MessageBox(NULL,"���ߣ���ϲ�������ˣ�","������ʾ",MB_OKCANCEL); 
	}
}
void player::gainmoney(int gm){
	money += gm ;
	if ( gm > 0 ) cout << "������" <<  gm << "���Ǯ" << endl ;
}
void player::dclmp(int dmp){
	mp-=dmp;
}
void player::be_hit(int bh){
	hp-=(int)(bh*dfd);
}
void player::attack(monster * m){
	m->be_hit(atk);
}

void monster::printname(){
	cout<<name; 
}
void monster::be_hit(int bh){
	hp-=bh;
}
void monster::attack(player * p){
	++iterator;
	bigskill();
	p->be_hit(atk);
}
void player::set_dfd(double dfd0){
	dfd = dfd0;
}
void player::set_hp(int hp0){
	hp = hp0 ;
}
void player::set_mp(int mp0){
	mp = mp0 ;
}
void monster::bigskill(){}

void boss::bigskill(){
	if(iterator%5) {
		atk=tmpatk;
		return;
	}
	atk=tmpatk*5;
}
void show_monster(){
	cout << "    ��������        Ѫ��        ������        ����        �״γ��ֵȼ�" << endl ;
	cout << "     ʷ��ķ           15            3       ��ͨ����             1"<< endl ;
	cout << "   ����ʷ��ķ         44           14       ��ͨ����             3"<< endl ;
	cout << "   ����ʷ��ķ        150           33       ��ͨ����             7"<< endl ;
	cout << "      ֩��           220          110       ��ͨ����            13"<< endl ;
	cout << "    ��Һ֩��         280          180       ��ͨ����            20"<< endl ;
	cout << "     ��֩��          630          170       ��ͨ����            23"<< endl ;
	cout << "    ֩�뽫��         650          200       ��ͨ����            27"<< endl ;
	cout << "    ֩��֮��         700          220       ��ͨ����            30"<< endl ;
	cout << "    ����֮Ӱ        1750            4         boss              10"<< endl ;
	cout << "    ����֮ë        2000           40         boss              35"<< endl ;
	return; 
}
void battle(player * p , monster * m){
	if(m->cvalue()==200||m->cvalue()==800)  MessageBox(NULL,"���ߣ���������boss��","Σ����ʾ",MB_OKCANCEL);
	cout << "����" ;
	p->printname() ;
	cout << ",��������" ;
	m->printname(); 
	cout << "\n" ;
	while ( 1 ) {
		cout <<  "���ߣ���ѡ��A.���� B.���� C.�鿴��ǰ״̬ D.����" << endl ;
		char act1 ;
		cin >> act1 ;
		p->set_dfd(1.0);
		switch (act1){
			case 'D':
				cout << "����ʧ��" << endl ;
				break ;
			case 'C':
				p->printstate();
				continue ;
			case 'B':
				p->set_dfd(0.3);
				break;
			case 'A':
				cout << "��ѡ��A.��ͨ������mp-0)" << " B.����ն��mp-" << 3 * p->clv() << "����lv.3������ C.������أ�mp-" << 10 * p->clv() << "����lv.8������  D.ڤ�루mp+" << 7 * p->clv() << "��" << endl ; 
				char act2 ;
				while(1){
					cin >> act2 ;
					switch(act2){
						case 'A':
							p->attack(m);
							cout << "����" ;
							p->printname() ;
							cout << "��" ;
							m->printname();
							 cout << "�����" << p->catk() << "���˺�" << endl ;
							break ;
						case 'B':
							if ( p->cmp() < 3*p->clv()) {
								cout << "mp���㣬�޷���������ն��" << endl ;
								continue ; 
							}
							if ( p->clv() < 3 ){
								cout << "�ȼ����㣬�޷���������ն��" << endl ;
								continue ; 
							} 
							p->dclmp(3*p->clv());
							p->attack(m);
							p->attack(m);
							cout << "����" ;
							p->printname();
							cout << "��" ;
							m->printname();
							cout << "�����" << 2*p->catk() << "���˺�" << endl ;
							break;
						case 'C':
							if ( p->cmp() < 10*p->clv()) {
								cout << "mp���㣬�޷�����������ء�" << endl ;
								continue ; 
							}
							if ( p->clv() < 8 ){
								cout << "�ȼ����㣬�޷�����������ء�" << endl ;
								continue ; 
							} 
							p->dclmp(10*p->clv());
							p->attack(m);
							p->attack(m);
							p->attack(m);
							p->attack(m);
							p->attack(m);
							p->attack(m);
							cout << "����" ;
							p->printname();
							cout << "��" ;
							m->printname();
							cout << "�����" << 6*p->catk() << "���˺�" << endl ;
							break;
						case 'D':
							p->dclmp(0-7*p->clv()) ;
							if ( p->cmp() > 10*p->clv() ) p->set_mp ( 10*p->clv() ) ;
							break ;
						default:
				        	cout << "����Ƿ������������롣"<<endl;
							continue; 	
					}
					break ;	
				}
				break;
			default:
				cout << "����Ƿ������������롣"<<endl;
				continue; 
		}
		if (m->chp()<=0) {
			cout << "���ߣ������" ;
			m->printname(); 
			cout << "���ɵ�Ư����" << endl ;
			p->addexp( m->cvalue() );
			p->gainmoney( m->cvalue() / 2 );
			break ;
		}
		m->attack(p);
		m->printname();
		cout << "���������" <<  (int) (p->cdfd() * m->catk()) << "���˺�" << endl ; 
		if (p->chp() <= 0) break ;
		p->set_dfd(1.0);
	} 	
}
void cure ( player * p ){
	cout << "��ǰ״̬:  " ;
	p->printstate();
	cout << "�������Ƿ�Ҫ����? ���۸�1��Ǯ/2hp��" << endl << "��ѡ�� A.�� B.��" << endl ;
	char act3 ;
	while ( 1 ){
		cin >> act3 ;
		switch(act3){
			case 'A':{
				int tmp0 = p->clv() * 10 - p->chp() ;
				if ( p->cmy() * 2 >= tmp0 ) {
					p->set_hp(p->clv() * 10) ;
					p->gainmoney(-(tmp0+1)/2) ;
					cout << "���ߣ���ָ���" << tmp0 << "��Ѫ����������" << (tmp0+1)/2 << "���Ǯ��" ; 
				}
				else {
					int tmp1 = p->cmy() ;
					p->gainmoney(-tmp1) ;
					p->be_hit(-tmp1*2) ;
					cout << "���ߣ���ָ���" << tmp1*2 << "��Ѫ����������" << tmp1 << "���Ǯ��" ;
				}
				cout << "��ǰhp��" << p->chp() << endl ; 
			}
				break;
			case 'B':
				break;
			default :
				 cout << "����Ƿ������������롣"<<endl;
				 continue; 
		}
		break ;
	}
}
void cundang(player & p) {
	{
					int lv00,exp00,money00,lv11,exp11,money11,hp00,hp11,mp00,mp11;
					char name00[50],name11[50];
					if (!fin) {
						fout.open("herosave.txt",ios::out);
						fout2.open("d:\\Program Files\\herosave1.txt",ios::out);
						cout<<"û�д浵����"<<endl;
						fout.close();
						fout2.close();
						judge = 0 ;
						return;
					}
					else if (!fin2) {
						cout << "�ڲ��浵�ѱ�ɾ������" << endl ;
						fout.open("herosave.txt",ios::out);
						fout2.open("d:\\Program Files\\herosave1.txt",ios::out);
						fout.close();
						fout2.close();
						judge = 0 ;
						return;
					}
					else {
						fin >> hp00 >> mp00 >> lv00 >> exp00 >> money00 >> name00;
						fin2 >> hp11 >> mp11 >> lv11 >> exp11 >> money11 >> name11;
						if(hp00 == hp11 && mp00 == mp11 && lv00==lv11 && exp00==exp11 && money00==money11 && !strcmp(name00,name11)){
							fout.open("herosave.txt",ios::out);
							fout<< hp00 << " " << mp00 << " " << lv00 << " " << exp00 << " " << money00 << name00 << endl ;
							fout2.open("d:\\Program Files\\herosave1.txt",ios::out);
							fout2<< hp00 << " " << mp00 << " " << lv00 << " " << exp00 << " " << money00 << name00 << endl ;
							if(!strcmp(p.name,"*")){
								cout << "���ߣ����������������������ʾ��������Ҫ������"<<endl;
								char nm[50];
								nm[0] = '*';
								cin >> nm+1 ;
								cout << endl ;
								p.set_name(nm);
							}
							judge = 1 ;
						}
						else {
							cout<<"Fuck!You have changed my file!"<<endl;
							fout.open("herosave.txt",ios::out);
							fout2.open("d:\\Program Files\\herosave1.txt",ios::out);
							fout<< 10 << " " << 10 << " " << 1 << " " << 0 << " " << 0<<"*" << endl ;
							fout2<< 10 << " " << 10 << " " << 1 << " " << 0 << " " << 0<<"*" << endl ;
							fin.close();
							fin2.close();
							fout.close();
							fout2.close();
							judge = 2 ;
							return;
						}
					}
					p.set_state(hp00,mp00,lv00,lv00*5,exp00,money00);
					p.set_name(name00);
				}
}
int main(){
	cout << "���ߣ���ӭ������Ϸ\"���߶�����\"" <<endl<<"��ѡ��A.��������֮�� B.�鿴����ͼ�� C.��ȡ�浵 D.��Ϸ���� E.�������� F.�˳���Ϸ"<<endl; 
	char act;
	player p;
	while(1){
		cin >> act ;
		switch(act){
			case 'A':{
				cout << "���ߣ����������������������ʾ��������Ҫ������"<<endl;
				char nm[50];
				nm[0] = '*';
				cin >> nm+1 ;
				cout << endl ;
				p.set_name(nm);
				break;
				}
			case 'B':
				show_monster();
				continue;
			case 'C':
				cundang(p);
				if (judge==0) continue;
				if (judge==2) {
					cin>>act;
					return 0;
				} 
				break;
			case 'D':
				cout << "                ��Ϸ����"<<endl<<"1.�����߰�����ʾ������Ϸ�������Ӧ��Ӣ�Ĵ�д��ĸ��"<<endl
				<<"2.�����Ϊ��ͨ������boss���֡���ͨ����û���κ����ԣ���bossŭ��ֵ��ʱ�ᷢ����ɱ����"<<endl
				<<"3.���ߵ�ÿ��ս������ʱϵͳ���Զ����д浵���´���Ҫ��������֮�ý��ж������ɡ�"<<endl
				<<"4.�����߲�Ҫ˽���޸Ĵ浵��ͼѸ���������������Ը���"<< endl;
				continue;
			case 'E':
				cout<<"���ߣ�Timothy Liu    ʹ�����ԣ�C++    IDE:Dev C++"<<endl;
				continue;
			case 'F':
				return 0;
			default :
				 cout << "����Ƿ������������롣"<<endl;
				 continue; 
		}
		break;
	}
	while(1){
		srand ( ( unsigned ) time ( NULL ) ) ; 
		int rd = rand()%p.clv()+1 ;
		if (rd<=2) {
			monster slime(15,3,8,"ʷ��ķ");
			battle ( & p , & slime ) ;
			if (p.chp() <= 0) break ;
		}
		else if (rd<=6) {
			monster bigslime(44,14,16,"����ʷ��ķ");
			battle ( & p , & bigslime ) ;
			if (p.chp() <= 0) break ;
		}
		else if (rd<=9) {
			monster exslime(150,33,40,"����ʷ��ķ");
			battle ( & p , & exslime ) ;
			if (p.chp() <= 0) break ;
		}
		else if (rd<=12) {
			boss dragon_shadow(1750,4,200,"����֮Ӱ");
			battle ( & p , & dragon_shadow ) ;
			if (p.chp() <= 0) break ;
		}
		else if (rd<=19) {
			monster spider(220,110,75,"֩��");
			battle ( & p , & spider ) ;
			if (p.chp() <= 0) break ;
		}
		else if (rd<=22) { 
			monster poisonous_spider(280,180,150,"��Һ֩��");
			battle ( & p , & poisonous_spider ) ;
			if (p.chp() <= 0) break ;
		}
		else if (rd<=26) {
			monster enormous_spider(630,170,180,"��֩��");
			battle ( & p , & enormous_spider ) ;
			if (p.chp() <= 0) break ;
		}
		else if (rd<=29) {
			monster spidergeneral(650,200,300,"֩�뽫��");
			battle ( & p , & spidergeneral ) ;
			if (p.chp() <= 0) break ;
		}
		else if (rd<=34) {
			monster spiderking(700,220,320,"֩��֮��");
			battle ( & p , & spiderking ) ;
			if (p.chp() <= 0) break ;
		}
		else {
			boss dragon_fur(2000,40,800,"����֮ë");
			battle ( & p , & dragon_fur ) ;
			if (p.chp() <= 0) break ;
		} 
		fout.open("herosave.txt",ios::out);
		fout<< p.chp() << " " << p.cmp() << " " <<p.clv() << " " << p.cexp() << " " << p.cmy() << p.name << endl ;
		fout2.open("d:\\Program Files\\herosave1.txt",ios::out);
		fout2<< p.chp() << " " << p.cmp() << " " <<p.clv() << " " << p.cexp() << " " << p.cmy() << p.name << endl ;
		fin.close();
		fin2.close();
		fout.close();
		fout2.close();
		/*monster slime(15,3,8,"ʷ��ķ");
		battle ( & p , & slime ) ;
		if (p.chp() <= 0) break ;*/
		cure ( & p ) ;
	}
	cout << "��һλ���ߣ�" ;
	p.printname();
	cout << endl << "Ӣ��������" << endl <<"���������Խ�����Ϸ��"; 
	fout.open("herosave.txt",ios::out);
	fout2.open("d:\\Program Files\\herosave1.txt",ios::out);
	fout<< 10 << " " << 10 << " " << 1 << " " << 0 << " " << 0<<"*" << endl ;
	fout2<< 10 << " " << 10 << " " << 1 << " " << 0 << " " << 0<<"*" << endl ;
	fin.close();
	fin2.close();
	fout.close();
	fout2.close();
	cin >> act ;
	return 0;
}
