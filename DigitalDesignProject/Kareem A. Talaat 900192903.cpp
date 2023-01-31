//Project by Kareem A. Mohamed Talaat 900192903
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct minterms
{
	int data;
	bool seen = false;
};

bool check_Duplicate(int & c, vector<int> & d)
{
	for (int i = 0; i < d.size(); i++)
	{
		if (d[i] == c)
		{
			return true;
		}
	}
	return false;
}


void get_input(minterms ** n)
{
	vector<int> d;
	
	string c;
	int temp2;
	int s;
	int temp;
	cout << "please enter the total number of minterms: ";
	cin >> c;
	while (c.length()>1 || c < "0" || c > "8")
	{
		c.clear();
		cout << "Invalid!" << endl << "Please enter a valid total number of minterms: ";
		cin >> c;
		cout << endl;
	}
	cout << endl;
	s = stoi(c);
	if (s == 8)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j =0; j < 4; j++)
			{
				n[i][j].data = 1;
			}
		}
		return;
	}
	if (s == 0)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				n[i][j].data = 0;
			}
		}
		return;
	}
	c.clear();
	
	for (int i = 0; i < s ; i++)
	{
		
		cout << "Please enter the #" << i + 1 << "th minterm (from 0 to 7): ";
		cin >> c;
		if (!(c.length() > 1 || c < "0" || c > "7"))
		{
			temp = stoi(c);
		}
		cout << endl;
		while (c.length()>1 || c <"0" || c > "7" || check_Duplicate(temp, d) == true)
		{
			c.clear();
			cout << "Invalid!" << endl << "Please enter a valid number of minterm (from 0 to 7) for the #" << i + 1 << "th minterm :";
			cin >> c;
			if (!(c.length() > 1 || c < "0" || c > "7"))
			{
				temp = stoi(c);
			}
			
			cout << endl;
		}
		
		temp2 = stoi(c);
		d.push_back(temp);
		switch (temp2)
		{
		case 0:
			n[0][0].data = 1;
			break;
		case 1:
			n[1][0].data = 1;
			break;
		case 2:
			n[0][1].data = 1;
			break;
		case 3:
			n[1][1].data = 1;
			break;
		case 4:
			n[0][3].data = 1;
			break;
		case 5:
			n[1][3].data = 1;
			break;
		case 6:
			n[0][2].data = 1;
			break;
		case 7:
			n[1][2].data = 1;
			break;

		default:
			break;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (n[i][j].data != 1)
			{
				n[i][j].data = 0;
			}
		}
	}

}

void show_kmap(minterms ** n)
{
	cout << "kmap = " << endl << endl << "  AB" << endl;
	
	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			cout << "C ";
		}
		if (i == 1)
		{
			cout << "  ";
		}
		for (int j = 0; j < 4; j++)
		{
			cout << n[i][j].data << "    ";
		}
		cout << endl;

	}
}

vector<string> Generate_Boolean_Exp(minterms** n)
{
	vector<string> possible;
	
	bool check = true;
	
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (n[i][j].data != 1)
			{
				check = false;
			}
		}
	}
	if (check == true)
	{
		cout << "F = 1";
		possible.push_back("True");
		return possible;
	}
	check = true;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (n[i][j].data == 1)
			{
				check = false;
			}
		}
	}
	if (check == true)
	{
		cout << "F = 0";
		possible.push_back("False");
		return possible;
	}
	
	for (int i = 0; i < 2; i++)
	{
		check = true;
		for (int k = 0; k < 4; k++)
		{
			if (n[i][k].data == 0)
			{
				check = false;
			}
		}
		if (check)
		{
			possible.push_back("**" + to_string(i));
			for (int j = 0; j < 4; j++)
			{
				n[i][j].seen = true;
			}
		}

	}
	check = true;
	int unseens = 0;
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			unseens = 0;
			check = (n[i][j].data == 1  && n[i][j + 1].data == 1 &&  n[i + 1][j].data == 1 &&  n[i + 1][j + 1].data == 1);
			if (n[i][j].seen == false) unseens++;
			if (n[i][j+1].seen == false) unseens++;
			if (n[i+1][j].seen == false) unseens++;
			if (n[i+1][j+1].seen == false) unseens++;

			if (check && unseens >=1 )
			{
				if (j==0)
				{
					possible.push_back(to_string(j)+"**");
				}
				if (j==1)
				{
					possible.push_back("*"+to_string(j)+"*");
				}
				if (j==2)
				{
					possible.push_back(to_string(j-1)+"**");
				}
				n[i][j].seen = true;
				n[i][j + 1].seen = true;
				n[i + 1][j].seen = true;
				n[i + 1][j + 1].seen = true;
			}
		}
		check = true;
		unseens = 0;
	}
	check = (n[0][0].data == 1  && n[1][0].data == 1  && n[0][3].data == 1  && n[1][3].data == 1 );
	if (n[0][0].seen == false) unseens++;
	if (n[1][0].seen == false) unseens++;
	if (n[0][3].seen == false) unseens++;
	if (n[1][3].seen == false) unseens++;
	if (check && unseens >= 1)
	{
		possible.push_back("*0*");
		n[0][0].seen = true;
		n[1][0].seen = true;
		n[0][3].seen = true;
		n[1][3].seen = true;
	}
	check = true;
	unseens = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			unseens = 0;
			check = (n[i][j].data == 1 && n[i][j + 1].data == 1 );
			if (n[i][j].seen == false) unseens++;
			if (n[i][j + 1].seen == false) unseens++;
			
			if (check && unseens>=1)
			{
				if (j == 0)
				{
					possible.push_back(to_string(j)+"*"+to_string(i));

				}
				if (j == 1)
				{
					possible.push_back("*"+to_string(j)+to_string(i));
				}
				if (j == 2)
				{
					possible.push_back(to_string(j-1)+"*"+to_string(i));
				}
				n[i][j].seen = true;
				n[i][j + 1].seen = true;
			}
		}
		check = true;
		unseens = 0;
	}
	for (int i = 0; i < 2; i++)
	{
		unseens = 0;
		check = (n[i][0].data == 1  && n[i][3].data == 1 );
		if (n[i][0].seen == false) unseens++;
		if (n[i][3].seen == false) unseens++;
		
		if (check && unseens >= 1)
		{
			possible.push_back("*0"+to_string(i));
			n[i][0].seen = true;
			n[i][3].seen = true;
		}
		check = true;
		unseens = 0;
	}

	for (int i = 0; i < 4; i++)
	{
		unseens = 0;
		check = (n[0][i].data == 1  && n[1][i].data == 1 );
		if (n[0][i].seen == false) unseens++;
		if (n[1][i].seen == false) unseens++;
		
		if (check && unseens >= 1)
		{
			if (i == 0)
			{
				possible.push_back("00*");
				
			}
			if (i == 1)
			{
				possible.push_back("01*");
			}
			if (i == 2)
			{
				possible.push_back("11*");
			}
			if (i == 3)
			{
				possible.push_back("10*");
			}
			n[0][i].seen = true;
			n[1][i].seen = true;
		}
		check = true;
		unseens = 0;
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j<4; j++)
		{
			check = (n[i][j].data == 1 && n[i][j].seen == false);
			if (check)
			{
				if (j == 0)
				{
					possible.push_back("00"+to_string(i));
				}
				if (j == 1)
				{
					possible.push_back("01" + to_string(i));
				}
				if (j == 2)
				{
					possible.push_back("11" + to_string(i));
				}
				if (j == 3)
				{
					possible.push_back("10" + to_string(i));
				}
				n[i][j].seen = true;
			}
		}
	}

	return possible;
}




void showfunction(vector<string> possible)
{
	
	if (possible[0] != "True" && possible[0] != "False")
	{
		cout << "F = ";
	}
	
	for (int i = 0; i < possible.size(); i++)
	{
		
		if (possible[i][0] == '1' )
			{
				cout << 'A';
			}
		if (possible[i][1] == '1' )
			{
				 cout << 'B';
			}
		if (possible[i][2] == '1' )
			{
				cout << 'C';
			}
		if (possible[i][0] == '0' )
			{
				cout << "A`";
			}
		if (possible[i][1] == '0' )
			{
				cout << "B`";
			}
		if (possible[i][2] == '0' )
			{
				cout << "C`";
			}
		if (i != possible.size()-1)
			{
				cout << " + ";
			}
		
	}
	cout << endl;
}


int main()
{
	minterms ** n;
	n = new minterms*[2];
	for (int i = 0; i < 2; i++)
	{
		n[i] = new minterms[4];
	}

	vector<string> possible;
	
	get_input(n);
	cout << endl;
	show_kmap(n);
	cout << endl;
	possible = Generate_Boolean_Exp(n);
	cout << endl;

	
	showfunction(possible);
	


		
	

	system("pause");
	return 0;
}