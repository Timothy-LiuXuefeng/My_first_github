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
class player{//玩家 
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
	cout<<"勇者："<< name << " hp:"<< hp<< " mp:"<< mp<< " 等级"<< lv<< " 金钱"<< money<<endl;
 	return;
}
void player::addexp(int ae){
	exp+=ae;
	cout << "你获得了" <<  ae << "点经验" << endl ;
	while(exp>=lv*10){
		exp-=lv++*10;
		cout<<"勇者！恭喜你升级了！当前等级：" <<lv<<endl; 
		hp=lv*10;
		mp=lv*10;
		atk=lv*5;
		MessageBox(NULL,"勇者！恭喜你升级了！","升级提示",MB_OKCANCEL); 
	}
}
void player::gainmoney(int gm){
	money += gm ;
	if ( gm > 0 ) cout << "你获得了" <<  gm << "点金钱" << endl ;
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
	cout << "    怪物名称        血量        攻击力        属性        首次出现等级" << endl ;
	cout << "     史莱姆           15            3       普通怪物             1"<< endl ;
	cout << "   巨型史莱姆         44           14       普通怪物             3"<< endl ;
	cout << "   变异史莱姆        150           33       普通怪物             7"<< endl ;
	cout << "      蜘蛛           220          110       普通怪物            13"<< endl ;
	cout << "    毒液蜘蛛         280          180       普通怪物            20"<< endl ;
	cout << "     巨蜘蛛          630          170       普通怪物            23"<< endl ;
	cout << "    蜘蛛将军         650          200       普通怪物            27"<< endl ;
	cout << "    蜘蛛之王         700          220       普通怪物            30"<< endl ;
	cout << "    恶龙之影        1750            4         boss              10"<< endl ;
	cout << "    恶龙之毛        2000           40         boss              35"<< endl ;
	return; 
}
void battle(player * p , monster * m){
	if(m->cvalue()==200||m->cvalue()==800)  MessageBox(NULL,"勇者，你遇到了boss！","危险提示",MB_OKCANCEL);
	cout << "勇者" ;
	p->printname() ;
	cout << ",你遇到了" ;
	m->printname(); 
	cout << "\n" ;
	while ( 1 ) {
		cout <<  "勇者，请选择：A.技能 B.防御 C.查看当前状态 D.逃跑" << endl ;
		char act1 ;
		cin >> act1 ;
		p->set_dfd(1.0);
		switch (act1){
			case 'D':
				cout << "逃跑失败" << endl ;
				break ;
			case 'C':
				p->printstate();
				continue ;
			case 'B':
				p->set_dfd(0.3);
				break;
			case 'A':
				cout << "请选择：A.普通攻击（mp-0)" << " B.二重斩（mp-" << 3 * p->clv() << "）（lv.3开启） C.毁天灭地（mp-" << 10 * p->clv() << "）（lv.8开启）  D.冥想（mp+" << 7 * p->clv() << "）" << endl ; 
				char act2 ;
				while(1){
					cin >> act2 ;
					switch(act2){
						case 'A':
							p->attack(m);
							cout << "勇者" ;
							p->printname() ;
							cout << "对" ;
							m->printname();
							 cout << "造成了" << p->catk() << "点伤害" << endl ;
							break ;
						case 'B':
							if ( p->cmp() < 3*p->clv()) {
								cout << "mp不足，无法发动二重斩。" << endl ;
								continue ; 
							}
							if ( p->clv() < 3 ){
								cout << "等级不足，无法发动二重斩。" << endl ;
								continue ; 
							} 
							p->dclmp(3*p->clv());
							p->attack(m);
							p->attack(m);
							cout << "勇者" ;
							p->printname();
							cout << "对" ;
							m->printname();
							cout << "造成了" << 2*p->catk() << "点伤害" << endl ;
							break;
						case 'C':
							if ( p->cmp() < 10*p->clv()) {
								cout << "mp不足，无法发动毁天灭地。" << endl ;
								continue ; 
							}
							if ( p->clv() < 8 ){
								cout << "等级不足，无法发动毁天灭地。" << endl ;
								continue ; 
							} 
							p->dclmp(10*p->clv());
							p->attack(m);
							p->attack(m);
							p->attack(m);
							p->attack(m);
							p->attack(m);
							p->attack(m);
							cout << "勇者" ;
							p->printname();
							cout << "对" ;
							m->printname();
							cout << "造成了" << 6*p->catk() << "点伤害" << endl ;
							break;
						case 'D':
							p->dclmp(0-7*p->clv()) ;
							if ( p->cmp() > 10*p->clv() ) p->set_mp ( 10*p->clv() ) ;
							break ;
						default:
				        	cout << "输入非法，请重新输入。"<<endl;
							continue; 	
					}
					break ;	
				}
				break;
			default:
				cout << "输入非法，请重新输入。"<<endl;
				continue; 
		}
		if (m->chp()<=0) {
			cout << "勇者，你打倒了" ;
			m->printname(); 
			cout << "，干的漂亮！" << endl ;
			p->addexp( m->cvalue() );
			p->gainmoney( m->cvalue() / 2 );
			break ;
		}
		m->attack(p);
		m->printname();
		cout << "对你造成了" <<  (int) (p->cdfd() * m->catk()) << "点伤害" << endl ; 
		if (p->chp() <= 0) break ;
		p->set_dfd(1.0);
	} 	
}
void cure ( player * p ){
	cout << "当前状态:  " ;
	p->printstate();
	cout << "请问您是否要疗伤? （价格：1金钱/2hp）" << endl << "请选择： A.是 B.否" << endl ;
	char act3 ;
	while ( 1 ){
		cin >> act3 ;
		switch(act3){
			case 'A':{
				int tmp0 = p->clv() * 10 - p->chp() ;
				if ( p->cmy() * 2 >= tmp0 ) {
					p->set_hp(p->clv() * 10) ;
					p->gainmoney(-(tmp0+1)/2) ;
					cout << "勇者，你恢复了" << tmp0 << "点血量，花费了" << (tmp0+1)/2 << "点金钱。" ; 
				}
				else {
					int tmp1 = p->cmy() ;
					p->gainmoney(-tmp1) ;
					p->be_hit(-tmp1*2) ;
					cout << "勇者，你恢复了" << tmp1*2 << "点血量，花费了" << tmp1 << "点金钱。" ;
				}
				cout << "当前hp：" << p->chp() << endl ; 
			}
				break;
			case 'B':
				break;
			default :
				 cout << "输入非法，请重新输入。"<<endl;
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
						cout<<"没有存档！！"<<endl;
						fout.close();
						fout2.close();
						judge = 0 ;
						return;
					}
					else if (!fin2) {
						cout << "内部存档已被删除！！" << endl ;
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
								cout << "勇者，请输入你的姓名（友情提示：姓名不要过长）"<<endl;
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
	cout << "勇者，欢迎来到游戏\"勇者斗恶龙\"" <<endl<<"请选择：A.进入勇者之旅 B.查看怪物图鉴 C.读取存档 D.游戏帮助 E.关于作者 F.退出游戏"<<endl; 
	char act;
	player p;
	while(1){
		cin >> act ;
		switch(act){
			case 'A':{
				cout << "勇者，请输入你的姓名（友情提示：姓名不要过长）"<<endl;
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
				cout << "                游戏帮助"<<endl<<"1.请勇者按照提示进行游戏，输入对应的英文大写字母。"<<endl
				<<"2.怪物分为普通怪物与boss两种。普通怪物没有任何特性，而boss怒气值满时会发动必杀技。"<<endl
				<<"3.勇者的每场战斗结束时系统会自动进行存档，下次若要继续勇者之旅进行读档即可。"<<endl
				<<"4.请勇者不要私自修改存档妄图迅速升级，否则后果自负。"<< endl;
				continue;
			case 'E':
				cout<<"作者：Timothy Liu    使用语言：C++    IDE:Dev C++"<<endl;
				continue;
			case 'F':
				return 0;
			default :
				 cout << "输入非法，请重新输入。"<<endl;
				 continue; 
		}
		break;
	}
	while(1){
		srand ( ( unsigned ) time ( NULL ) ) ; 
		int rd = rand()%p.clv()+1 ;
		if (rd<=2) {
			monster slime(15,3,8,"史莱姆");
			battle ( & p , & slime ) ;
			if (p.chp() <= 0) break ;
		}
		else if (rd<=6) {
			monster bigslime(44,14,16,"巨型史莱姆");
			battle ( & p , & bigslime ) ;
			if (p.chp() <= 0) break ;
		}
		else if (rd<=9) {
			monster exslime(150,33,40,"变异史莱姆");
			battle ( & p , & exslime ) ;
			if (p.chp() <= 0) break ;
		}
		else if (rd<=12) {
			boss dragon_shadow(1750,4,200,"恶龙之影");
			battle ( & p , & dragon_shadow ) ;
			if (p.chp() <= 0) break ;
		}
		else if (rd<=19) {
			monster spider(220,110,75,"蜘蛛");
			battle ( & p , & spider ) ;
			if (p.chp() <= 0) break ;
		}
		else if (rd<=22) { 
			monster poisonous_spider(280,180,150,"毒液蜘蛛");
			battle ( & p , & poisonous_spider ) ;
			if (p.chp() <= 0) break ;
		}
		else if (rd<=26) {
			monster enormous_spider(630,170,180,"巨蜘蛛");
			battle ( & p , & enormous_spider ) ;
			if (p.chp() <= 0) break ;
		}
		else if (rd<=29) {
			monster spidergeneral(650,200,300,"蜘蛛将军");
			battle ( & p , & spidergeneral ) ;
			if (p.chp() <= 0) break ;
		}
		else if (rd<=34) {
			monster spiderking(700,220,320,"蜘蛛之王");
			battle ( & p , & spiderking ) ;
			if (p.chp() <= 0) break ;
		}
		else {
			boss dragon_fur(2000,40,800,"恶龙之毛");
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
		/*monster slime(15,3,8,"史莱姆");
		battle ( & p , & slime ) ;
		if (p.chp() <= 0) break ;*/
		cure ( & p ) ;
	}
	cout << "有一位勇者：" ;
	p.printname();
	cout << endl << "英勇牺牲了" << endl <<"输入任意以结束游戏。"; 
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
