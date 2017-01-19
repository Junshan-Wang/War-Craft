#include <iostream>
#include <string>
#include <iomanip>
#include <stdio.h>
using namespace std;


int M,N,R,K,hour;
int dragon_life,ninja_life,iceman_life,lion_life,wolf_life;
int dragon_power,ninja_power,iceman_power,lion_power,wolf_power;



//武器类
class Weapon
{
public:
	int force;
	int use_times;
	string name;
};
class sword:public Weapon
{
public:
	sword(int force_) { force=force_*0.2; name="sword";}
};
class arrow:public Weapon
{
public:
	arrow(){ force=R; use_times=3; name="arrow";}
};
class bomb:public Weapon
{
public:
	bomb(){ name="bomb";}
};

Weapon null_;

//武士类
class Warrior
{
public:
	int element;
	int force;
	int number;
	int loyalty;
	double morale;
	string name;
	Weapon *pweapon;
	Weapon *p2weapon;
	Weapon *p3weapon;
	Warrior(){ pweapon=&null_; p2weapon=&null_; p3weapon=&null_;}
	virtual void Attack(Warrior *p){}
	virtual void Hurted(int force_){}
	virtual void FightBack(Warrior *p){}
};
class dragon :public Warrior
{
public:
	dragon(int element_,int force_,int number_,int head_life)
	{
		name="dragon";
		element=element_;
		force=force_;
		number=number_;
		morale=(double)head_life/element;
		if (number%3==0 && force/5!=0) pweapon=new sword(force); 
		else if (number%3==1) pweapon=new bomb();
		else if (number%3==2) pweapon=new arrow();
	}
	virtual void Attack(Warrior *p)
	{
		if (pweapon->name=="sword") 
		{
			p->Hurted(force+(pweapon->force));
			pweapon->force=pweapon->force*0.8;
			if (pweapon->force==0) 
			{
				delete pweapon;
				pweapon=&null_;
			}
		}
		else p->Hurted(force);

		if (p->element>0) 
		{
			morale-=0.2;
			p->FightBack(this);
		}
		else morale+=0.2;
	}
	virtual void Hurted(int force_)
	{
		element=element-force_;
	}
	virtual void FightBack(Warrior *p)
	{
		if (pweapon->name=="sword") 
		{
			p->Hurted(force/2+(pweapon->force));
			pweapon->force=pweapon->force*0.8;
			if (pweapon->force==0) 
			{
				delete pweapon;
				pweapon=&null_;
			}
		}
		else p->Hurted(force/2);

		if (p->element>0) morale-=0.2;
		else morale+=0.2;
	}
};
class ninja:public Warrior
{
public:
	ninja(int element_,int force_,int number_)
	{
		name="ninja";
		element=element_;
		force=force_;
		number=number_;
		if (number%3==0)
		{
			if (force/5!=0) pweapon=new sword(force);
			p2weapon=new bomb();
		}
		else if (number%3==1)
		{
			pweapon=new bomb();
			p2weapon=new arrow();
		}
		else if (number%3==2)
		{
			pweapon=new arrow();
			if (force/5!=0) p2weapon=new sword(force);
		}

	}
	virtual void Attack(Warrior *p)
	{
		if (number%3==0)
		{
			if (pweapon!=&null_)
			{
			p->Hurted(force+pweapon->force);
			pweapon->force=pweapon->force*0.8;
			if (pweapon->force==0) 
			{
				delete pweapon;
				pweapon=&null_;
			}
			}
			else p->Hurted(force);
		}
		else if (number%3==2)
		{
			if (p2weapon!=&null_)
			{
			p->Hurted(force+p2weapon->force);
			p2weapon->force=p2weapon->force*0.8;
			if (p2weapon->force==0) 
			{
				delete p2weapon;
				p2weapon=&null_;
			}
			}
			else p->Hurted(force);
			
		}
		else p->Hurted(force);
		if (p->element>0) p->FightBack(this);
	}
	virtual void Hurted(int force_)
	{
		element=element-force_;
	}
	virtual void FightBack(Warrior *p) //ninja不反击
	{
	}
};
class iceman:public Warrior
{
public:
	iceman(int element_,int force_,int number_)
	{
		name="iceman";
		element=element_;
		force=force_;
		number=number_;
		if (number%3==0 && force/5!=0) pweapon=new sword(force); 
		else if (number%3==1) pweapon=new bomb();
		else if (number%3==2) pweapon=new arrow();
	}
	virtual void Attack(Warrior *p)
	{
		if (pweapon->name=="sword") 
		{
			p->Hurted(force+(pweapon->force));
			pweapon->force=pweapon->force*0.8;
			if (pweapon->force==0) 
			{
				delete pweapon;
				pweapon=&null_;
			}
		}
		else p->Hurted(force);
		if (p->element>0) p->FightBack(this);
	}
	virtual void Hurted(int force_)
	{
		element=element-force_;
	}
	virtual void FightBack(Warrior *p)
	{
		if (pweapon->name=="sword") 
		{
			p->Hurted(force/2+(pweapon->force));
			pweapon->force=pweapon->force*0.8;
			if (pweapon->force==0) 
			{
				delete pweapon;
				pweapon=&null_;
			}
		}
		else p->Hurted(force/2);
	}
};
class lion:public Warrior
{
public:
	lion(int element_,int force_,int number_,int head_life)
	{
		name="lion";
		element=element_;
		force=force_;
		number=number_;
		loyalty=head_life;
	}
	virtual void Attack(Warrior *p)
	{
		p->Hurted(force);
		if (p->element>0) 
		{
			p->FightBack(this);
			loyalty-=K;
		}	
	}
	virtual void Hurted(int force_)
	{
		element=element-force_;
	}
	virtual void FightBack(Warrior *p)
	{
		p->Hurted(force/2);
		if (p->element>0) loyalty-=K;
	}
};
class wolf:public Warrior
{
public:
	wolf(int element_,int force_,int number_)
	{
		name="wolf";
		element=element_;
		force=force_;
		number=number_;
	}
	virtual void Attack(Warrior *p)
	{
		if (pweapon->name=="sword" && p->element>0)
		{
			p->Hurted(force+pweapon->force);
			pweapon->force=pweapon->force*0.8;
			if (pweapon->force==0) 
			{
				delete pweapon;
				pweapon=&null_;
			}
		}
		else p->Hurted(force);

		if (p->element>0) p->FightBack(this);
		else if (p->element<=0)
		{
			if (pweapon==&null_)
			{
			   if (p->pweapon->name=="sword") pweapon=new sword(p->pweapon->force*5);
			   if (p->p2weapon->name=="sword") pweapon=new sword(p->p2weapon->force*5);
			}
			if (p2weapon==&null_)
			{
				if (p->pweapon->name=="arrow") 
				{
					p2weapon=new arrow();
					p2weapon->use_times=p->pweapon->use_times;
				}
			    if (p->p2weapon->name=="arrow") 
				{
					p2weapon=new arrow();
					p2weapon->use_times=p->p2weapon->use_times;
				}
			}
			if (p3weapon==&null_)
			{
				if (p->pweapon->name=="bomb") p3weapon=new bomb;
			   if (p->p2weapon->name=="bomb") p3weapon=new bomb;
			   if (p->p3weapon->name=="bomb") p3weapon=new bomb;
			}
		}
	}
	virtual void Hurted(int force_)
	{
		element=element-force_;
	}
	virtual void FightBack(Warrior *p)
	{
		if (pweapon->name=="sword") 
		{
			p->Hurted(force/2+pweapon->force);
			pweapon->force=pweapon->force*0.8;
			if (pweapon->force==0) 
			{
				delete pweapon;
				pweapon=&null_;
			}
		}
		else p->Hurted(force/2);
		if (p->element<=0)
		{
			if (pweapon==&null_)
			{
			   if (p->pweapon->name=="sword") pweapon=new sword(p->pweapon->force*5);
			   if (p->p2weapon->name=="sword") pweapon=new sword(p->p2weapon->force*5);
			}
			else if (p2weapon==&null_)
			{
				if (p->pweapon->name=="arrow") 
				{
					p2weapon=new arrow();
					p2weapon->use_times=p->pweapon->use_times;
				}
			    if (p->p2weapon->name=="sword") 
				{
					p2weapon=new arrow();
					p2weapon->use_times=p->p2weapon->use_times;
				}
			}
			else if (p3weapon==&null_)
			{
				if (p->pweapon->name=="bomb") p3weapon=new bomb;
			   if (p->p2weapon->name=="bomb") p3weapon=new bomb;
			   if (p->p3weapon->name=="bomb") p3weapon=new bomb;
			}
		}
	}
};

Warrior null;


//城市类
class City
{
public:
	int flag;
	int life;
	int result;
	int continue_times;
	Warrior *p_red;
	Warrior *p_blue; 
	City():flag(0),life(0),result(0),continue_times(0)
	{	
		p_red=&null;
		p_blue=&null;
	}
	void war(int city_number);
	int judge_result(int city_number);
	void begin();
};
//每一个城市发生的战争
void City::war(int city_number)
{
	if (flag==1 || (flag==0 && city_number%2==1))
	{			
		cout<<setw(3)<<setfill('0')<<hour<<":40 red "<<p_red->name<<" "<<p_red->number<<" attacked blue "<<p_blue->name<<" "<<p_blue->number<<" in city "<<city_number<<" with "<<p_red->element<<" elements and force "<<p_red->force<<endl;
		//对lion战前生命值的记录
		int tmp1_element,tmp2_element;
		if (p_blue->name=="lion") tmp1_element=p_blue->element;
		if (p_red->name=="lion") tmp2_element=p_red->element;
		
		p_red->Attack(p_blue);
		
		if (p_blue->element<=0)
		{
			cout<<setw(3)<<setfill('0')<<hour<<":40 blue "<<p_blue->name<<" "<<p_blue->number<<" was killed in city "<<city_number<<endl;
			if (p_blue->name=="lion") p_red->element+=tmp1_element;
			delete p_blue;
			p_blue=&null;
			result=1;
			if (continue_times>=0) continue_times++;
			else continue_times=1;

			if (p_red->name=="dragon" && p_red->morale>0.8) 
				cout<<setw(3)<<setfill('0')<<hour<<":40 red dragon "<<p_red->number<<" yelled in city "<<city_number<<endl;
		}
		else 
		{
			if (p_blue->name!="ninja") 
				cout<<setw(3)<<setfill('0')<<hour<<":40 blue "<<p_blue->name<<" "<<p_blue->number<<" fought back against red "<<p_red->name<<" "<<p_red->number<<" in city "<<city_number<<endl;
			if (p_red->element<=0)
			{
				cout<<setw(3)<<setfill('0')<<hour<<":40 red "<<p_red->name<<" "<<p_red->number<<" was killed in city "<<city_number<<endl;
				if (p_red->name=="lion") p_blue->element+=tmp2_element;
				delete p_red;
				p_red=&null;
				result=2;
				if (continue_times<=0) continue_times--;
				else continue_times=-1;
			}
			else 
			{
				if (p_red->name=="dragon" && p_red->morale>0.8) 
				cout<<setw(3)<<setfill('0')<<hour<<":40 red dragon "<<p_red->number<<" yelled in city "<<city_number<<endl;
				result=0;
				continue_times=0;
			}
		}
	}
	else if(flag==2 || (flag==0 && city_number%2==0))
	{
		cout<<setw(3)<<setfill('0')<<hour<<":40 blue "<<p_blue->name<<" "<<p_blue->number<<" attacked red "<<p_red->name<<" "<<p_red->number<<" in city "<<city_number<<" with "<<p_blue->element<<" elements and force "<<p_blue->force<<endl;
		//对lion战前生命值的记录
		int tmp1_element,tmp2_element;
		if (p_blue->name=="lion") tmp1_element=p_blue->element;
		if (p_red->name=="lion") tmp2_element=p_red->element;

		p_blue->Attack(p_red);

		if (p_red->element<=0)
		{
			cout<<setw(3)<<setfill('0')<<hour<<":40 red "<<p_red->name<<" "<<p_red->number<<" was killed in city "<<city_number<<endl;
			if (p_red->name=="lion") p_blue->element+=tmp2_element;
			delete p_red;
			p_red=&null;
			result=2;
			if (continue_times<=0) continue_times--;
			else continue_times=-1;

			if (p_blue->name=="dragon" && p_blue->morale>0.8) 
				cout<<setw(3)<<setfill('0')<<hour<<":40 blue dragon "<<p_blue->number<<" yelled in city "<<city_number<<endl;
		}
		else 
		{
			if (p_red->name!="ninja")
			    cout<<setw(3)<<setfill('0')<<hour<<":40 red "<<p_red->name<<" "<<p_red->number<<" fought back against blue "<<p_blue->name<<" "<<p_blue->number<<" in city "<<city_number<<endl;
			if (p_blue->element<=0)
			{
				cout<<setw(3)<<setfill('0')<<hour<<":40 blue "<<p_blue->name<<" "<<p_blue->number<<" was killed in city "<<city_number<<endl;
				if (p_blue->name=="lion") p_red->element+=tmp1_element;
				delete p_blue;
				p_blue=&null;
				result=1;
				if (continue_times>=0) continue_times++;
				else continue_times=1;
			}
			else
			{
				if (p_blue->name=="dragon" && p_blue->morale>0.8) 
				cout<<setw(3)<<setfill('0')<<hour<<":40 blue dragon "<<p_blue->number<<" yelled in city "<<city_number<<endl;
				result=0;
				continue_times=0;
			}
		}
	}
}
//判断是否会被杀死
int City::judge_result(int city_number)
{
	if (flag==1 || (flag==0 && city_number%2==1))
	{
		if (p_blue->element-p_red->force<=0) return 2;
		else if (p_red->pweapon->name=="sword" && p_blue->element-p_red->force-p_red->pweapon->force<=0) return 2;
		else if (p_red->p2weapon->name=="sword" && p_blue->element-p_red->force-p_red->p2weapon->force<=0) return 2;
		else
		{
		if (p_blue->name!="ninja" && p_blue->pweapon->name=="sword" && p_red->element-(p_blue->force/2)-(p_blue->pweapon->force)<=0) 
			return 1;
		else if (p_blue->name!="ninja" && p_blue->p2weapon->name=="sword" && p_red->element-(p_blue->force/2)-(p_blue->pweapon->force)<=0) 
			return 1;
		else if (p_blue->name!="ninja" && p_blue->pweapon->name!="sword" && p_blue->p2weapon->name!="sword" && p_red->element-p_blue->force/2<=0)
			return 1;
		else return 0;
		}
	}
	else if (flag==2 || (flag==0 && city_number%2==0))
	{
		if (p_red->element-p_blue->force<=0) return 1;
		else if (p_blue->pweapon->name=="sword" && p_red->element-p_blue->force-p_blue->pweapon->force<=0) return 1;
		else if (p_blue->p2weapon->name=="sword" && p_red->element-p_blue->force-p_blue->p2weapon->force<=0) return 1;
		else
		{
		    if (p_red->name!="ninja" && p_red->pweapon->name=="sword" && p_blue->element-(p_red->force/2)-(p_red->pweapon->force)<=0) 
			    return 2;
		    else if (p_red->name!="ninja" && p_red->p2weapon->name=="sword" && p_blue->element-(p_red->force/2)-(p_red->pweapon->force)<=0) 
			    return 2;
		    else if (p_red->name!="ninja" && p_red->pweapon->name!="sword" && p_red->p2weapon->name!="sword" && p_blue->element-p_red->force/2<=0)
			    return 2;
			else return 0;
		}
	}
}
//初始化city里的数据
void City::begin()
{
	life=0;
	flag=0;
	result=0;
	continue_times=0;
	p_red=&null;
	p_blue=&null;
}

City city[25];

//红司令部
class red_headquarter
{
public:	
	int red_warrior_count;
	int total_element;
	int enemy;
	Warrior *enemy_;
	Warrior *red_warrior[90];
	red_headquarter(int M_):total_element(M_),red_warrior_count(0),enemy(0){ enemy_=&null;}
	void produce_warrior(int hour_);
};
//红司令部武士降生
void red_headquarter::produce_warrior(int hour_)
{
	switch(red_warrior_count%5){
	case 0:
		{ 
			if (total_element>=iceman_life){
				red_warrior_count++;
				total_element=total_element-iceman_life;
				red_warrior[red_warrior_count]=new iceman(iceman_life,iceman_power,red_warrior_count);
				city[0].p_red=red_warrior[red_warrior_count];
				cout<<setw(3)<<setfill('0')<<hour_<<":00 red iceman "<<red_warrior_count<<" born"<<endl;
			}
			else city[0].p_red=&null;
			break;
		}
	case 1:
		{ 
			if (total_element>=lion_life){
				red_warrior_count++;
				total_element=total_element-lion_life;
				red_warrior[red_warrior_count]=new lion(lion_life,lion_power,red_warrior_count,total_element); 
				city[0].p_red=red_warrior[red_warrior_count];
				cout<<setw(3)<<setfill('0')<<hour_<<":00 red lion "<<red_warrior_count<<" born"<<endl;
				cout<<"Its loyalty is "<<red_warrior[red_warrior_count]->loyalty<<endl;
			}
			else city[0].p_red=&null;
			break;
		}
	case 2:
		{ 
			if (total_element>=wolf_life){
				red_warrior_count++;
				total_element=total_element-wolf_life;
				red_warrior[red_warrior_count]=new wolf(wolf_life,wolf_power,red_warrior_count); 
				city[0].p_red=red_warrior[red_warrior_count];
				cout<<setw(3)<<setfill('0')<<hour_<<":00 red wolf "<<red_warrior_count<<" born"<<endl;
			}
			else city[0].p_red=&null;
			break;
		}
	case 3:
		{ 
			if (total_element>=ninja_life){
				red_warrior_count++;
				total_element=total_element-ninja_life;
				red_warrior[red_warrior_count]=new ninja(ninja_life,ninja_power,red_warrior_count); 
				city[0].p_red=red_warrior[red_warrior_count];
				cout<<setw(3)<<setfill('0')<<hour_<<":00 red ninja "<<red_warrior_count<<" born"<<endl;
			}
			else city[0].p_red=&null;
			break;
		}
	case 4:
		{ 
			if (total_element>=dragon_life){
				red_warrior_count++;
				total_element=total_element-dragon_life;
				red_warrior[red_warrior_count]=new dragon(dragon_life,dragon_power,red_warrior_count,total_element); 
				city[0].p_red=red_warrior[red_warrior_count];
				cout<<setw(3)<<setfill('0')<<hour_<<":00 red dragon "<<red_warrior_count<<" born"<<endl;
				printf("Its morale is %.2f\n",red_warrior[red_warrior_count]->morale);
				//cout<<"Its morale is "<<red_warrior[red_warrior_count]->morale<<endl;
			}
			else city[0].p_red=&null;
			break;
		}
	}
}

//蓝司令部
class blue_headquarter
{
public:
	int total_element;
	int warrior_count;
	int enemy;
	Warrior *enemy_;
	Warrior *blue_warrior[90];
	blue_headquarter(int M_):total_element(M_),warrior_count(0),enemy(0){ enemy_=&null;}
	void produce_warrior(int hour_);
};
//蓝司令部武士降生
void blue_headquarter::produce_warrior(int hour_)
{
	switch(warrior_count%5){
	case 0:
		{ 
			if (total_element>=lion_life){
				warrior_count++;
				total_element=total_element-lion_life;
				blue_warrior[warrior_count]=new lion(lion_life,lion_power,warrior_count,total_element); 
				city[N+1].p_blue=blue_warrior[warrior_count];
				cout<<setw(3)<<setfill('0')<<hour_<<":00 blue lion "<<warrior_count<<" born"<<endl;
				cout<<"Its loyalty is "<<blue_warrior[warrior_count]->loyalty<<endl;
			}
			else city[N+1].p_blue=&null;
			break;
		}
	case 1:
		{ 
			if (total_element>=dragon_life){
				warrior_count++;
				total_element=total_element-dragon_life;
      		    blue_warrior[warrior_count]=new dragon(dragon_life,dragon_power,warrior_count,total_element); 
	     		city[N+1].p_blue=blue_warrior[warrior_count];
				cout<<setw(3)<<setfill('0')<<hour_<<":00 blue dragon "<<warrior_count<<" born"<<endl;
				printf("Its morale is %.2f\n",blue_warrior[warrior_count]->morale);
				//cout<<"Its morale is "<<blue_warrior[warrior_count]->morale<<endl;						
			}
			else city[N+1].p_blue=&null;
			break;
		}
	case 2:
		{ 
			if (total_element>=ninja_life){
				warrior_count++;
				total_element=total_element-ninja_life;
				blue_warrior[warrior_count]=new ninja(ninja_life,ninja_power,warrior_count); 
				city[N+1].p_blue=blue_warrior[warrior_count];
				cout<<setw(3)<<setfill('0')<<hour_<<":00 blue ninja "<<warrior_count<<" born"<<endl;
			}
			else city[N+1].p_blue=&null;
			break;
		}
	case 3:
		{ 
			if (total_element>=iceman_life){
				warrior_count++;
				total_element=total_element-iceman_life;
				blue_warrior[warrior_count]=new iceman(iceman_life,iceman_power,warrior_count); 
				city[N+1].p_blue=blue_warrior[warrior_count];
				cout<<setw(3)<<setfill('0')<<hour_<<":00 blue iceman "<<warrior_count<<" born"<<endl;
			}
			else city[N+1].p_blue=&null;
			break;
		}
	case 4:
		{ 
			if (total_element>=wolf_life){
				warrior_count++;
				total_element=total_element-wolf_life;
				blue_warrior[warrior_count]=new wolf(wolf_life,wolf_power,warrior_count); 
				city[N+1].p_blue=blue_warrior[warrior_count];
				cout<<setw(3)<<setfill('0')<<hour_<<":00 blue wolf "<<warrior_count<<" born"<<endl;
			}
			else city[N+1].p_blue=&null;
			break;
		}
	
	}
}


int main()
{
	int T,t;
	int before_red_element,before_blue_element;
	cin>>t;
	for(int t_=1;t_<=t;t_++)
	{
		hour=0;
		cin>>M>>N>>R>>K>>T;
		cin>>dragon_life>>ninja_life>>iceman_life>>lion_life>>wolf_life;
		cin>>dragon_power>>ninja_power>>iceman_power>>lion_power>>wolf_power;
		cout<<"Case "<<t_<<":"<<endl;
        red_headquarter red_head(M);
        blue_headquarter blue_head(M);

		for (int i=0;i<=N+1;i++)
			city[i].begin();
		city[0].life=M;
		city[N+1].life=M;

        for(int min=0;min<=T;min++)
		{
			//武士降生
			if(min%60==0) 
			{ 
				red_head.produce_warrior(hour);				
				blue_head.produce_warrior(hour);
			}
			//lion逃跑
			else if(min%60==5) 
			{		
				for(int i=0;i<=N+1;i++)
				{
					if (city[i].p_red->name=="lion" && city[i].p_red->loyalty<=0) 
					{
						cout<<setw(3)<<setfill('0')<<hour<<":05 red lion "<<city[i].p_red->number<<" ran away"<<endl;
						delete city[i].p_red;
						city[i].p_red=&null;
					}
					if (city[i].p_blue->name=="lion" && city[i].p_blue->loyalty<=0) 
					{
						cout<<setw(3)<<setfill('0')<<hour<<":05 blue lion "<<city[i].p_blue->number<<" ran away"<<endl;
						delete city[i].p_blue;
						city[i].p_blue=&null;
					}
				}
			}
			//武士前进
			else if(min%60==10)
			{
				for (int i=N+1;i>0;i--) 
				{
					city[i].p_red=city[i-1].p_red;
					if (city[i].p_red->name=="iceman" && i%2==0) {
						if (city[i].p_red->element>9)
							city[i].p_red->element-=9;
						else city[i].p_red->element=1;
						city[i].p_red->force+=20;
					}
				}	
				city[0].p_red=&null;
				for (int i=0;i<N+1;i++) 
				{
					city[i].p_blue=city[i+1].p_blue;
					if (city[i].p_blue->name=="iceman" && (N+1-i)%2==0) {
						if (city[i].p_blue->element>9)
							city[i].p_blue->element-=9;
						else city[i].p_blue->element=1;
						city[i].p_blue->force+=20;
					}
				}
				city[N+1].p_blue=&null;

				if (city[0].p_blue!=&null)
				{
					red_head.enemy++;
					cout<<setw(3)<<setfill('0')<<hour<<":10 blue "<<city[0].p_blue->name<<" "<<city[0].p_blue->number<<" reached red headquarter with "<<city[0].p_blue->element<<" elements and force "<<city[0].p_blue->force<<endl;
					if (red_head.enemy==2) cout<<setw(3)<<setfill('0')<<hour<<":10 red headquarter was taken"<<endl;
					red_head.enemy_=city[0].p_blue;
					city[0].p_blue=&null;
				}
				for (int i=1;i<=N;i++)
				{
					if (city[i].p_red!=&null)
						cout<<setw(3)<<setfill('0')<<hour<<":10 red "<<city[i].p_red->name<<" "<<city[i].p_red->number<<" marched to city "<<i<<" with "<<city[i].p_red->element<<" elements and force "<<city[i].p_red->force<<endl;
					if (city[i].p_blue!=&null)
						cout<<setw(3)<<setfill('0')<<hour<<":10 blue "<<city[i].p_blue->name<<" "<<city[i].p_blue->number<<" marched to city "<<i<<" with "<<city[i].p_blue->element<<" elements and force "<<city[i].p_blue->force<<endl;
				}
				if (city[N+1].p_red!=&null)
				{
					blue_head.enemy++;
					cout<<setw(3)<<setfill('0')<<hour<<":10 red "<<city[N+1].p_red->name<<" "<<city[N+1].p_red->number<<" reached blue headquarter with "<<city[N+1].p_red->element<<" elements and force "<<city[N+1].p_red->force<<endl;
					if (blue_head.enemy==2) cout<<setw(3)<<setfill('0')<<hour<<":10 blue headquarter was taken"<<endl;
					blue_head.enemy_=city[N+1].p_red;
					city[N+1].p_red=&null;
				}
				if (red_head.enemy==2 || blue_head.enemy==2) break;
			}
			//城市产生生命元
			else if(min%60==20)
			{
				for (int i=1;i<=N;i++)
					city[i].life+=10;
			}
			//武士取走并传送生命元
			else if(min%60==30)
			{
				for (int i=1;i<=N;i++)
				{
					if (city[i].p_red!=&null && city[i].p_blue==&null)
					{
						cout<<setw(3)<<setfill('0')<<hour<<":30 red "<<city[i].p_red->name<<" "<<city[i].p_red->number<<" earned "<<city[i].life<<" elements for his headquarter"<<endl;
						red_head.total_element+=city[i].life;
						city[i].life=0; 
					}
					else if (city[i].p_blue!=&null && city[i].p_red==&null)
					{
						cout<<setw(3)<<setfill('0')<<hour<<":30 blue "<<city[i].p_blue->name<<" "<<city[i].p_blue->number<<" earned "<<city[i].life<<" elements for his headquarter"<<endl;
						blue_head.total_element+=city[i].life;
						city[i].life=0;
					}
				}
			}
			//arrow放箭
			else if(min%60==35)
			{
				for (int i=1;i<=N;i++)
				{
					if ( city[i].p_red->pweapon->name=="arrow"  && city[i+1].p_blue!=&null && i!=N)
					{
						city[i+1].p_blue->element-=R;
						city[i].p_red->pweapon->use_times--;
						if (city[i].p_red->pweapon->use_times==0) { delete city[i].p_red->pweapon; city[i].p_red->pweapon=&null_;}
						if (city[i+1].p_blue->element>0)
						    cout<<setw(3)<<setfill('0')<<hour<<":35 red "<<city[i].p_red->name<<" "<<city[i].p_red->number<<" shot"<<endl;
						else if(city[i+1].p_blue->element<=0) 
							cout<<setw(3)<<setfill('0')<<hour<<":35 red "<<city[i].p_red->name<<" "<<city[i].p_red->number<<" shot and killed blue "<<city[i+1].p_blue->name<<" "<<city[i+1].p_blue->number<<endl;
					}
					else if ( city[i].p_red->p2weapon->name=="arrow" && city[i+1].p_blue!=&null && i!=N)
					{
						city[i+1].p_blue->element-=R;
						city[i].p_red->p2weapon->use_times--;
						if (city[i].p_red->p2weapon->use_times==0) { delete city[i].p_red->p2weapon; city[i].p_red->p2weapon=&null_;}
						if (city[i+1].p_blue->element>0)
						    cout<<setw(3)<<setfill('0')<<hour<<":35 red "<<city[i].p_red->name<<" "<<city[i].p_red->number<<" shot"<<endl;
						else if(city[i+1].p_blue->element<=0) 
							cout<<setw(3)<<setfill('0')<<hour<<":35 red "<<city[i].p_red->name<<" "<<city[i].p_red->number<<" shot and killed blue "<<city[i+1].p_blue->name<<" "<<city[i+1].p_blue->number<<endl;

					}	
					if ( city[i].p_blue->pweapon->name=="arrow"  && city[i-1].p_red!=&null && i!=1)
					{
						city[i-1].p_red->element-=R;
						city[i].p_blue->pweapon->use_times--;
						if (city[i].p_blue->pweapon->use_times==0) { delete city[i].p_blue->pweapon; city[i].p_blue->pweapon=&null_;}
						if (city[i-1].p_red->element>0)
						    cout<<setw(3)<<setfill('0')<<hour<<":35 blue "<<city[i].p_blue->name<<" "<<city[i].p_blue->number<<" shot"<<endl;
						else if(city[i-1].p_red->element<=0) 
							cout<<setw(3)<<setfill('0')<<hour<<":35 blue "<<city[i].p_blue->name<<" "<<city[i].p_blue->number<<" shot and killed red "<<city[i-1].p_red->name<<" "<<city[i-1].p_red->number<<endl;
					}
					else if ( city[i].p_blue->p2weapon->name=="arrow"  &&city[i-1].p_red!=&null && i!=1)
					{
						city[i-1].p_red->element-=R;
						city[i].p_blue->p2weapon->use_times--;
						if (city[i].p_blue->p2weapon->use_times==0) { delete city[i].p_blue->p2weapon; city[i].p_blue->p2weapon=&null_;}
						if (city[i-1].p_red->element>0)
						    cout<<setw(3)<<setfill('0')<<hour<<":35 blue "<<city[i].p_blue->name<<" "<<city[i].p_blue->number<<" shot"<<endl;
						else if(city[i-1].p_red->element<=0) 
							cout<<setw(3)<<setfill('0')<<hour<<":35 blue "<<city[i].p_blue->name<<" "<<city[i].p_blue->number<<" shot and killed red "<<city[i-1].p_red->name<<" "<<city[i-1].p_red->number<<endl;
					}	
				}
			}
			//使用bomb
			else if(min%60==38)
			{
				for (int i=1;i<=N;i++)
				{
					if ((city[i].p_red->pweapon->name=="bomb" || city[i].p_red->p2weapon->name=="bomb" || city[i].p_red->p3weapon->name=="bomb") && city[i].p_red->element>0 && city[i].p_blue->element>0 && city[i].judge_result(i)==1)
					{
						cout<<setw(3)<<setfill('0')<<hour<<":38 red "<<city[i].p_red->name<<" "<<city[i].p_red->number<<" used a bomb and killed blue "<<city[i].p_blue->name<<" "<<city[i].p_blue->number<<endl;
						delete city[i].p_red;
						city[i].p_red=&null;
						delete city[i].p_blue;
						city[i].p_blue=&null;
					}
					else if ((city[i].p_blue->pweapon->name=="bomb" || city[i].p_blue->p2weapon->name=="bomb" || city[i].p_blue->p3weapon->name=="bomb") && city[i].p_red->element>0 && city[i].p_blue->element>0  && city[i].judge_result(i)==2)
					{
						cout<<setw(3)<<setfill('0')<<hour<<":38 blue "<<city[i].p_blue->name<<" "<<city[i].p_blue->number<<" used a bomb and killed red "<<city[i].p_red->name<<" "<<city[i].p_red->number<<endl;
						delete city[i].p_red;
						city[i].p_red=&null;
						delete city[i].p_blue;
						city[i].p_blue=&null;
					}
				}
			}
			//进行战斗
			else if(min%60==40)
			{
				before_red_element=red_head.total_element;
				before_blue_element=blue_head.total_element;
				//战斗并记录结果、武士战死
				for (int i=1;i<=N;i++)
				{
					city[i].result=0;
					if (city[i].p_red!=&null && city[i].p_blue==&null && city[i].p_red->element<=0) { delete city[i].p_red; city[i].p_red=&null;}
					else if (city[i].p_blue!=&null && city[i].p_red==&null && city[i].p_blue->element<=0) { delete city[i].p_blue; city[i].p_blue=&null;}
					else if (city[i].p_red!=&null && city[i].p_blue!=&null)
					{
					{
						if (city[i].p_red->element>0 && city[i].p_blue->element>0) 
							city[i].war(i);
						else if (city[i].p_red->element<=0 && city[i].p_blue->element>0) 
						{
							city[i].result=2;
							if (city[i].continue_times<=0) city[i].continue_times--;
							else city[i].continue_times=-1;
							if (city[i].p_blue->name=="wolf") city[i].p_blue->Attack(city[i].p_red);   //从被射死的敌人处获得武器
							delete city[i].p_red;
							city[i].p_red=&null;
							if (city[i].p_blue->name=="dragon")
							{
								city[i].p_blue->morale+=0.2;
								if ((city[i].flag==2 || (city[i].flag==0 && i%2==0)) && city[i].p_blue->morale>0.8)
							         cout<<setw(3)<<setfill('0')<<hour<<":40 blue dragon "<<city[i].p_blue->number<<" yelled in city "<<i<<endl;
							}
						}
						else if (city[i].p_blue->element<=0 && city[i].p_red->element>0)
						{
							city[i].result=1;
							if (city[i].continue_times>=0) city[i].continue_times++;
							else city[i].continue_times=1;
							if (city[i].p_red->name=="wolf")  city[i].p_red->Attack(city[i].p_blue);
							delete city[i].p_blue;
							city[i].p_blue=&null;
							if (city[i].p_red->name=="dragon")
							{
								city[i].p_red->morale+=0.2;
								if ((city[i].flag==1 || (city[i].flag==0 && i%2==1)) && city[i].p_red->morale>0.8)
							         cout<<setw(3)<<setfill('0')<<hour<<":40 red dragon "<<city[i].p_red->number<<" yelled in city "<<i<<endl;
							}
						}
						else if (city[i].p_red->element<=0 && city[i].p_blue->element<=0 )
						{
							city[i].result=0;
							delete city[i].p_red;
							city[i].p_red=&null;
							delete city[i].p_blue;
							city[i].p_blue=&null;
						}
					}
					

					    if (city[i].result==1) 
						{
							//获取生命元
							red_head.total_element+=city[i].life;
							cout<<setw(3)<<setfill('0')<<hour<<":40 red "<<city[i].p_red->name<<" "<<city[i].p_red->number<<" earned "<<city[i].life<<" elements for his headquarter"<<endl;
                            city[i].life=0;
							//升旗
							if (city[i].flag!=1 && city[i].continue_times>=2)
							{
								city[i].flag=1;
								cout<<setw(3)<<setfill('0')<<hour<<":40 red flag raised in city "<<i<<endl;
							}
						}
						else if (city[i].result==2) 
						{
							//获取生命元
							blue_head.total_element+=city[i].life;
							cout<<setw(3)<<setfill('0')<<hour<<":40 blue "<<city[i].p_blue->name<<" "<<city[i].p_blue->number<<" earned "<<city[i].life<<" elements for his headquarter"<<endl;
                            city[i].life=0;
							//升旗
							if (city[i].flag!=2 && city[i].continue_times<=-2)
							{
								city[i].flag=2;
								cout<<setw(3)<<setfill('0')<<hour<<":40 blue flag raised in city "<<i<<endl;
							}
						}
					}
				}
				///获胜武士奖励生命元
				for (int i=N;i>=1;i--)
				{
					if (city[i].result==1 && before_red_element>=8 && city[i].p_red!=&null)	
					{
						city[i].p_red->element+=8;
						before_red_element-=8;
						red_head.total_element-=8;
					}
				}
				for (int i=1;i<=N;i++)
				{
					if (city[i].result==2 && before_blue_element>=8 && city[i].p_blue!=&null) 
					{
						city[i].p_blue->element+=8;
						before_blue_element-=8;
						blue_head.total_element-=8;
					}
				}
			}
			//司令部报告生命元数量
			else if(min%60==50)
			{
				cout<<setw(3)<<setfill('0')<<hour<<":50 "<<red_head.total_element<<" elements in red headquarter"<<endl;
				cout<<setw(3)<<setfill('0')<<hour<<":50 "<<blue_head.total_element<<" elements in blue headquarter"<<endl;				
			}
			//武士报告生命元数量
			else if(min%60==55)
			{		
				//红武士报告
				for (int i=1;i<=N;i++)
					if (city[i].p_red!=&null)
					{
						int weapon_flag[3]={0};
						cout<<setw(3)<<setfill('0')<<hour<<":55 red "<<city[i].p_red->name<<" "<<city[i].p_red->number<<" has ";
						if (city[i].p_red->pweapon->name=="arrow")
						{
							cout<<"arrow("<<city[i].p_red->pweapon->use_times<<")";
							weapon_flag[0]=1;
						}
						if (city[i].p_red->p2weapon->name=="arrow") 
						{
							cout<<"arrow("<<city[i].p_red->p2weapon->use_times<<")";
							weapon_flag[0]=1;
						}
						if (city[i].p_red->pweapon->name=="bomb" || city[i].p_red->p2weapon->name=="bomb" || city[i].p_red->p3weapon->name=="bomb") 
						{
							if (weapon_flag[0]==1) cout<<",";
							cout<<"bomb";
							weapon_flag[1]=1;
						}
						if (city[i].p_red->pweapon->name=="sword") 
						{
							if (weapon_flag[1]==1 ||weapon_flag[0]==1) cout<<",";
							cout<<"sword("<<city[i].p_red->pweapon->force<<")";
							weapon_flag[2]=1;
						}
						if (city[i].p_red->p2weapon->name=="sword") 
						{
							if (weapon_flag[1]==1 ||weapon_flag[0]==1) cout<<",";
							cout<<"sword("<<city[i].p_red->p2weapon->force<<")";
							weapon_flag[2]=1;
						}
						if (weapon_flag[0]==0 && weapon_flag[1]==0 && weapon_flag[2]==0)
							cout<<"no weapon"<<endl;
						else cout<<endl;
					}
				if (blue_head.enemy_!=&null) 
				{
					int weapon_flag[3]={0};
					cout<<setw(3)<<setfill('0')<<hour<<":55 red "<<blue_head.enemy_->name<<" "<<blue_head.enemy_->number<<" has ";
					if (blue_head.enemy_->pweapon->name=="arrow")
					{
						cout<<"arrow("<<blue_head.enemy_->pweapon->use_times<<")";
						weapon_flag[0]=1;
					}
					if (blue_head.enemy_->p2weapon->name=="arrow") 
					{
						cout<<"arrow("<<blue_head.enemy_->p2weapon->use_times<<")";
						weapon_flag[0]=1;
					}
					if (blue_head.enemy_->pweapon->name=="bomb" || blue_head.enemy_->p2weapon->name=="bomb" || blue_head.enemy_->p3weapon->name=="bomb") 
					{
						if (weapon_flag[0]==1) cout<<",";
						cout<<"bomb";
						weapon_flag[1]=1;
					}
					if (blue_head.enemy_->pweapon->name=="sword") 
					{
						if (weapon_flag[1]==1 ||weapon_flag[0]==1) cout<<",";
						cout<<"sword("<<blue_head.enemy_->pweapon->force<<")";
						weapon_flag[2]=1;
					}
					if (blue_head.enemy_->p2weapon->name=="sword") 
					{
						if (weapon_flag[1]==1 ||weapon_flag[0]==1) cout<<",";
						cout<<"sword("<<blue_head.enemy_->p2weapon->force<<")";
						weapon_flag[2]=1;
					}
					if (weapon_flag[0]==0 && weapon_flag[1]==0 && weapon_flag[2]==0)
						cout<<"no weapon"<<endl;
					else cout<<endl;
					}
				//蓝武士报告
				if (red_head.enemy_!=&null)
				{
					int weapon_flag[3]={0};
					cout<<setw(3)<<setfill('0')<<hour<<":55 blue "<<red_head.enemy_->name<<" "<<red_head.enemy_->number<<" has ";
					if (red_head.enemy_->pweapon->name=="arrow")
					{
						cout<<"arrow("<<red_head.enemy_->pweapon->use_times<<")";
						weapon_flag[0]=1;
					}
					if (red_head.enemy_->p2weapon->name=="arrow") 
					{
						cout<<"arrow("<<red_head.enemy_->p2weapon->use_times<<")";
						weapon_flag[0]=1;
					}
					if (red_head.enemy_->pweapon->name=="bomb" || red_head.enemy_->p2weapon->name=="bomb" || red_head.enemy_->p3weapon->name=="bomb") 
					{
						if (weapon_flag[0]==1) cout<<",";
						cout<<"bomb";
						weapon_flag[1]=1;
					}
					if (red_head.enemy_->pweapon->name=="sword") 
					{
						if (weapon_flag[1]==1 || weapon_flag[0]==1) cout<<",";
						cout<<"sword("<<red_head.enemy_->pweapon->force<<")";
						weapon_flag[2]=1;
					}
					if (red_head.enemy_->p2weapon->name=="sword") 
					{
						if (weapon_flag[1]==1 ||weapon_flag[0]==1) cout<<",";
						cout<<"sword("<<red_head.enemy_->p2weapon->force<<")";
						weapon_flag[2]=1;
					}
					if (weapon_flag[0]==0 && weapon_flag[1]==0 && weapon_flag[2]==0)
						cout<<"no weapon"<<endl;
					else cout<<endl;
				}
				for (int i=1;i<=N;i++)
					if (city[i].p_blue!=&null)
					{
						int weapon_flag[3]={0};
						cout<<setw(3)<<setfill('0')<<hour<<":55 blue "<<city[i].p_blue->name<<" "<<city[i].p_blue->number<<" has ";
						if (city[i].p_blue->pweapon->name=="arrow")
						{
							cout<<"arrow("<<city[i].p_blue->pweapon->use_times<<")";
							weapon_flag[0]=1;
						}
						if (city[i].p_blue->p2weapon->name=="arrow") 
						{
							cout<<"arrow("<<city[i].p_blue->p2weapon->use_times<<")";
							weapon_flag[0]=1;
						}
						if (city[i].p_blue->pweapon->name=="bomb" || city[i].p_blue->p2weapon->name=="bomb" || city[i].p_blue->p3weapon->name=="bomb") 
						{
							if (weapon_flag[0]==1) cout<<",";
							cout<<"bomb";
							weapon_flag[1]=1;
						}
						if (city[i].p_blue->pweapon->name=="sword") 
						{
							if (weapon_flag[1]==1 || weapon_flag[0]==1) cout<<",";
							cout<<"sword("<<city[i].p_blue->pweapon->force<<")";
							weapon_flag[2]=1;
						}
						if (city[i].p_blue->p2weapon->name=="sword") 
						{
							if (weapon_flag[1]==1 || weapon_flag[0]==1) cout<<",";
							cout<<"sword("<<city[i].p_blue->p2weapon->force<<")";
							weapon_flag[2]=1;
						}
						if (weapon_flag[0]==0 && weapon_flag[1]==0 && weapon_flag[2]==0)
							cout<<"no weapon"<<endl;
						else cout<<endl;
					}
				hour++;
			}
			
		}
	}
	return 0;
}  
