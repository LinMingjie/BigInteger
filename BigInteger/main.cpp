#ifdef LOCAL
#define _CRT_SECURE_NO_WARNINGS
#include<conio.h>
void pause();
#endif

#ifdef DEBUG
#endif

//未完工
//参考 http://blog.csdn.net/wall_f/article/details/8373395
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<climits>
#include<iostream>
#include<algorithm>
#include<functional>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<stack>
#include<string>
using namespace std;
const int MOD = 1e9 + 7;

const int maxn = 1e5 + 5;

using namespace std;

struct BigInteger
{
	static const int BASE = 100000000;
	static const int WIDTH = 8;
	vector<int> s;

	void clean()
	{
		while (s.size() > 1 && !(*s.end()))
			s.pop_back();
	}
	BigInteger(long long num = 0) { *this = num; }
	BigInteger operator = (long long num)
	{
		s.clear();
		do {
			s.push_back(num % BASE);
			num /= BASE;
		} while (num > 0);
		return *this;
	}
	BigInteger operator = (const string& str)
	{
		s.clear();
		int x, len = (str.length() - 1) / WIDTH + 1;
		for (int i = 0; i < len; i++)
		{
			int end = str.length() - i*WIDTH;
			int start = max(0, end - WIDTH);
			sscanf(str.substr(start, end - start).c_str(), "%d", &x);
			s.push_back(x);
		}
		return *this;
	}
	BigInteger operator + (const BigInteger& b) const
	{
		BigInteger c;
		c.s.clear();    //?
		for (int i = 0, g = 0;; i++)
		{
			if (g == 0 && i >= s.size() && i >= b.s.size())
				break;
			int x = g;
			if (i < s.size())
				x += s[i];
			if (i < b.s.size())
				x += b.s[i];
			c.s.push_back(x%BASE);
			g = x / BASE;
		}
		return c;
	}
	BigInteger operator - (const BigInteger& b) const    //要保证a>=b
	{
		BigInteger c;
		c.s.clear();
		for (int i = 0, g = 0; i < s.size(); i++)
		{
			int x = s[i] - g;
			if (i < b.s.size())
				x -= b.s[i];
			if (x >= 0)
				g = 0;
			else
			{
				g = 1;
				x += BASE;
			}
			c.s.push_back(x);
		}
		c.clean();
		return c;
	}
	BigInteger operator * (const BigInteger& b) const
	{
		BigInteger c;
		c.s.resize(s.size() + b.s.size());
		for (int i = 0; i < s.size(); i++)
			for (int j = 0; j < b.s.size(); j++)
				c.s[i + j] += s[i] * b.s[j];
		for (int i = 0; i < c.s.size() - 1; i++)
		{
			c.s[i + 1] += c.s[i] / BASE;
			c.s[i] %= BASE;
		}
		c.clean();
		return c;
	}
	BigInteger operator / (const BigInteger& b) const    //要保证a>b
	{
		BigInteger c, r;    //c商 r余数
		c.s.resize(s.size()); r.s.resize(1, 0);
		for (int i = s.size() - 1; i >= 0; i--)
		{
			if (r.s.size() > 1 || r.s.size() == 1 && !(*r.s.end()))	//r!=0 then r*=10
			{
				r.s.push_back(0);
				for (int j = r.s.size() - 2; j >= 0; j--)
					r.s[j + 1] = r.s[j];
				r.s[0] = s[i];
			}
			else
				r.s[0] = s[i];
			while (r >= b)
			{
				r = r - b;
				c.s[i]++;
			}
		}
		c.clean();
		return c;
	}

	BigInteger operator += (const BigInteger&b)
	{
		*this = *this + b; return *this;
	}
	bool operator < (const BigInteger& b) const
	{
		if (s.size() != b.s.size())
			return s.size() < b.s.size();
		for (int i = s.size() - 1; i >= 0; i--)
			if (s[i] != b.s[i])
				return s[i] < b.s[i];
		return false;    //相等
	}
	bool operator > (const BigInteger& b) const
	{
		return b < *this;
	}
	bool operator <= (const BigInteger& b) const
	{
		return !(b < *this);
	}
	bool operator >= (const BigInteger& b) const
	{
		return !(*this < b);
	}
	bool operator != (const BigInteger& b) const
	{
		return b < *this || *this < b;
	}
	bool operator == (const BigInteger& b) const
	{
		return !(b < *this) && !(*this < b);
	}

};
ostream& operator << (ostream &out, const BigInteger& x)
{
	out << x.s.back();
	for (int i = x.s.size() - 2; i >= 0; i--)
	{
		char buf[20];
		sprintf(buf, "%08d", x.s[i]);
		for (int j = 0; j < strlen(buf); j++)
			out << buf[j];
	}
	return out;
}
istream& operator >> (istream &in, BigInteger& x)
{
	string s;
	if (!(in >> s))
		return in;
	x = s;
	return in;
}

int main()
{
	int t, i; BigInteger A, B, C;
	scanf("%d", &t);
	i = 0;
	while (t--)
	{
		cin >> A >> B;
		cout << "Case " << ++i << ':' << endl
			<< A << " + " << B << " = " << A + B << endl;
		if (t)
			cout << endl;
	}

#ifdef LOCAL
	pause();
#endif

	return 0;
}

#ifdef LOCAL
void pause()
{
	printf("Press any key to continue. . . \n");
	_getch();
}
#endif