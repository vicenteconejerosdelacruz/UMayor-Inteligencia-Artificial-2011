// genetico.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gen_random(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

static const char* frase = NULL;

class sujeto
{
public:
	std::string str;
	unsigned int len;

	sujeto()
	{
		str.clear();
		len = 0;
	}

	sujeto(const sujeto &s)
	{
		len = s.len;
		str = std::string(s.str.c_str());
		((char*)str.data())[len]='\0';
	}

	sujeto& operator=(const sujeto &s)
	{
		len = s.len;
		str = std::string(s.str.c_str());
		((char*)str.data())[len]='\0';
		return *this;
	}

	bool operator!=(const sujeto& s)
	{
		return str != s.str;
	}

	~sujeto()
	{
	}

	bool operator()(const sujeto& s1,const sujeto& s2)
	{ 
		return (s1.valor()<s2.valor());
	}

	void randomMe(size_t slen)
	{
		len = slen;
		str.reserve(len+1);
		str.clear();
		gen_random((char*)str.c_str(),len);
		((char*)str.data())[len]='\0';
	}

	sujeto(const sujeto& s1,const sujeto& s2)
	{
		len = s1.len;
		str.reserve(len+1);
		str.clear();
		cruza(s1,s2);
		((char*)str.data())[len]='\0';
	}

	void cruza(const sujeto& s1,const sujeto& s2)
	{
		for(unsigned int i = 0;i<len;i++)
		{
			char c1 = s1.str[i];
			char c2 = s2.str[i];
			
			char objetivo = frase[i];

			int d1 = c1 - objetivo;
			if(d1<0)
				d1 = -d1;

			int d2 = c2 - objetivo;
			if(d2<0)
				d2 = -d2;

			if(d1 < d2)
			{
				((char*)str.data())[i] = c1;
			}
			else
			{
				((char*)str.data())[i] = c2;
			}
		}

		muta();
	}

	void muta()
	{
		if(rand()%11)
		{
			unsigned int pos = rand()%len;
			pos = std::min(pos,len);
			if(((char*)str.data())[pos] != frase[pos])
			{
				int diff = frase[pos] - ((char*)str.data())[pos];
				if(diff>1)
					diff=1;
				else if(diff<-1)
					diff=-1;

				((char*)str.data())[pos]+=diff;
			}
		}
		((char*)str.data())[len]='\0';
	}

	unsigned int valor() const
	{
		unsigned int ret = 0;

		for(unsigned int i=0;i<len;i++)
		{
			int value = frase[i]-str.c_str()[i];
			if(value<0)
				value = -value;
			ret+= value;
		}
		return ret;
	}
};

typedef std::vector<sujeto> sujetoVec;
typedef sujetoVec::iterator sujetoVecIt;

struct comparasujetos
{
    inline bool operator() (const sujeto& s1, const sujeto& s2)
    {
		return (s1.valor() < s2.valor());
    }
};

int main(int argc, const char* argv[])
{
	sujetoVec poblacion;

	frase = argv[1];
	size_t len = strlen(frase);
	
	srand ( time(NULL) );

	for(unsigned int i=0;i<50;i++)
	{
		sujeto s;
		s.randomMe(len);
		poblacion.push_back(s);
	}	

	std::sort(poblacion.begin(),poblacion.end(),comparasujetos());

	unsigned int index=10000;
	unsigned int mejorValor = 10000000;
	while(poblacion.begin()->valor()!=0 && index-- > 0)
	{
		if(poblacion.begin()->valor()<mejorValor)
		{
			printf("encontre uno mejor %u %s\n",poblacion.begin()->valor(),poblacion.begin()->str.c_str());
		}

		sujetoVec nuevos;
		for(sujetoVecIt it=poblacion.begin();it!=poblacion.end();it++)
		{
			for(sujetoVecIt jt=poblacion.begin();jt!=poblacion.end();jt++)
			{
				if(*it!=*jt) //if(puedenCruzarse(*it,*jt))
				{
					sujeto s(*it,*jt);
					nuevos.push_back(s);
				}
			}
		}

		if(nuevos.size()>0)
		{
			poblacion.insert(poblacion.begin(),nuevos.begin(),nuevos.end());
		}

		std::sort(poblacion.begin(),poblacion.end(),comparasujetos());
		poblacion.erase(poblacion.begin() + 50,poblacion.end());
		for(unsigned int i=0;i<50;i++)
		{
			sujeto s;
			s.randomMe(len);
			poblacion.push_back(s);
		}	
	}

	printf("el mejor %u %s\n",poblacion.begin()->valor(),poblacion.begin()->str.c_str());

	return 0;
}
