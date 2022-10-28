#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
	unsigned long *result = new unsigned long int[1]{ 1 };

	int n;
	cin >> n;
	for (int i = 2; i <= n; i++)
	{
		unsigned long int *temp = result;
		result = new unsigned long int[i];
		result[0] = result[i - 1] = 1;
		for (int j = 1; j < i-1; j++)
		{
			result[j] = temp[j - 1] + temp[j];

		}

	}
	cout << endl << "Row " << n << ": " << endl;
	for (int i = 0; i < n; i++)
		cout << result[i] << "\t";
}