#include "include/console.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>

#define null NULL
using std::cout;
using std::cin;

struct nums
{
	double i;
	char o;
	struct nums *nxt;
	struct nums *per;
};

typedef struct nums nums;

nums *fst;
void calculate(nums *);
void freemem(nums *);
void fstcalculates(nums *);
void sndcalculates(nums *);
void trdcalculates(nums *);
void lstcalculates(nums *);
void getnum(nums *);
int main()
{
	cout << "Enter the expression and right after pression \'=\', The result will appear.\n";
	fst = (nums *)malloc(sizeof(nums));
	fst->nxt = null;
	fst->per = null;
	nums *ctrl = fst;
	while(1)
	{
		getnum(ctrl);
		if(ctrl->o == '(')
			if(ctrl->i == 0 && ctrl == fst)
				ctrl->i = 1;
		if(ctrl != fst && (ctrl->per->o == 'r' || ctrl->per->o == 'R') && ctrl->i < 0)
		{
			cout<<"\n\nSorry!\nThis program can not calculate the root of negative numbers.\nAny key to exit...";
			getch();
			return 1;
		}
		if(ctrl->o == '=')
			break;
		if(ctrl == fst)
		{
			ctrl = (nums *)malloc(sizeof(nums));
			fst->nxt = ctrl;
			ctrl->nxt = null;
			ctrl->per = fst;
		}
		else
		{
			ctrl->nxt = (nums *)malloc(sizeof(nums));
			ctrl->nxt->per = ctrl;
			ctrl = ctrl->nxt;
			ctrl->nxt = null;
		}
	}
	cout<<"\n\n";
	ctrl = fst;
	while(ctrl != null)
	{
		if(ctrl != fst && ctrl->per->o == ')')
		{
			cout<<ctrl->o<<' ';
			ctrl = ctrl->nxt;
			continue;
		}
		if(ctrl->i >= 0)
			cout<<ctrl->i<<' '<<ctrl->o<<' ';
		else
			cout<<'('<<ctrl->i<<')'<<' '<<ctrl->o<<' ';
		ctrl = ctrl->nxt;
	}
	ctrl = fst;
	int nop = 0;
	nums *lp = null;
	while(ctrl != null)
	{	
		if(ctrl->o == '(')
		{
			nop++;
			lp = ctrl;
		}
		ctrl = ctrl->nxt;
	}
	ctrl = lp;
	while(nop > 0)
	{
		fstcalculates(ctrl);
		if(nop > 1)
		{
			while(ctrl->o != '(')
				ctrl = ctrl->per;
		}
		nop--;
	}
	ctrl = fst;
	sndcalculates(ctrl);
	ctrl = fst;
	trdcalculates(ctrl);
	ctrl = fst;
	lstcalculates(ctrl);
	cout<<fst->i;
	getch();
	cout << "\n";
	return 0;
}
void calculate(nums *ctrl)
{
	nums *t = ctrl->nxt;
	switch(ctrl->o)
	{
		case 'r':
		case 'R':
			while(ctrl->nxt->o == 'r' || ctrl->nxt->o == 'R')
				ctrl = ctrl->nxt;
			while(ctrl != fst && (ctrl->per->o == 'r' || ctrl->per->o == 'R'))
			{
				ctrl->i = pow(ctrl->nxt->i,(1.0 / ctrl->i));
				freemem(ctrl);
				ctrl = ctrl->per;
			}
			ctrl->i = pow(t->i,(1.0 / ctrl->i));
			break;
		case '^':
			while(ctrl->nxt->o == '^')
				ctrl = ctrl->nxt;
			while(ctrl != fst && ctrl->per->o == '^')
			{
				ctrl->i = pow(ctrl->i,ctrl->nxt->i);
				freemem(ctrl);
				ctrl = ctrl->per;
			}
			ctrl->i = pow(ctrl->i,ctrl->nxt->i);
			break;
		case '*':
			ctrl->i *= t->i;
			break;
		case '/':
			ctrl->i /= t->i;
			break;
		case '+':
			ctrl->i += t->i;
			break;
		case '-':
			ctrl->i -= t->i;
			break;
	}
	freemem(ctrl);
}
void freemem(nums *ctrl)
{
	nums *t = ctrl->nxt;
	ctrl->o = t->o;
	ctrl->nxt = t->nxt;
	if(t->nxt != null)
		t->nxt->per = ctrl;
	t->nxt = null;
	t->per = null;
	free(t);
}
void fstcalculates(nums *ctrl)
{
	ctrl->o = '*';
	ctrl = ctrl->nxt;
	nums *t = ctrl;
	sndcalculates(ctrl);
	ctrl = t;
	trdcalculates(ctrl);
	ctrl = t;
	lstcalculates(ctrl);
	if(t->nxt != null)
	{
		ctrl->o = ctrl->nxt->o;
		t = ctrl->nxt;
		ctrl->nxt = t->nxt;
		if(t->nxt != null)
			t->nxt->per = ctrl;
		t->nxt = null;
		t->per = null;
		free(t);
	}
}
void sndcalculates(nums *ctrl)
{
	while(ctrl != null && ctrl->o != ')')
	{
		if(ctrl->o == '^')
		{
			calculate(ctrl);
			continue;
		}
		else if(ctrl->o == 'r' || ctrl->o == 'R')
		{
			calculate(ctrl);
			continue;
		}
		ctrl = ctrl->nxt;
	}
}
void trdcalculates(nums *ctrl)
{
	while(ctrl != null && ctrl->o != ')')
	{	
		if(ctrl->o == '*')
		{
			calculate(ctrl);
			continue;
		}
		else if(ctrl->o == '/')
		{
			calculate(ctrl);
			continue;
		}
		ctrl = ctrl->nxt;
	}
}
void lstcalculates(nums *ctrl)
{
	while(ctrl != null && ctrl->o != ')')
	{	
		if(ctrl->o == '+')
		{
			calculate(ctrl);
			continue;
		}
		else if(ctrl->o == '-')
		{
			calculate(ctrl);
			continue;
		}
		ctrl = ctrl->nxt;
	}
}
void getnum(nums *n)
{
	n->o = null;
	n->i = 0.0;
	char t;
	int i = -1,i2 = -1;
	int real[35];
	int imag[60];
	bool isq = false;
	int r = 1;
	double a = 0.1;
	bool isneg = false;
	while(1)
	{
		t = getche();
		if(t == '\b')
		{
			if((i == -1 && isq == false) || (i2 == -1 && isq == true))
				if(n == fst)
					continue;
				else
				{
					cout<<n->per->o;
					continue;
				}
			if(isq == false)
			{
				i--;
				if(i + 1 > 0)
					r /= 10;
				cout<<" \b";
			}
			if(isq == true)
			{
				i2--;
				if(i2 + 1 > 0)
					a *= 10;
				cout<<" \b";
			}
		}
		else if(i == -1 && t == '-')
			isneg = true;
		else if(isdigit(t))
		{
			if(isq == false)
			{
				i++;
				real[i] = t - 48;
				if(i > 0)
					r *= 10;
			}
			else
			{
				i2++;
				imag[i2] = t - 48;
				if(i2 > 0)
					a *= 0.1;
			}
		}
		else if(t == '.' && isq == false)
			isq = true;
		else if(t == '+' || t == '-' || t == '*' || t == '/' || t == 'r' || t == 'R' || t == '^'
				|| t == '(' || t == ')' || t == '=')		
					n->o = t;

		else
			cout<<"\b \b";
		if(n->o != null)
			break;
	}
	int j = 0;
	while(real[j] == 0 && i > 0)
	{
		j++;
		r /= 10;
	}
	while(r >= 1 && i > -1)
	{
		n->i += static_cast<double>(real[j] * r);
		if(r == 1)
			r = 0;
		else
			r /= 10;
		j++;
	}
	if(isneg == true)
		n->i *= -1;
	j = i2;
	if(isq == true)
	{
		while(j >= 0)
		{
			if(isneg == false)
				n->i += static_cast<double>(imag[j] * a);
			else
				n->i -= static_cast<double>(imag[j] * a);
			a *= 10;
			j--;
		}
	}
}
