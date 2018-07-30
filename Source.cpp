#include<iostream>
#include<vector>
#include<string>
#include<math.h>

using namespace std;

// Function to get the parity from positions which are defined
int getParity(int pos, vector<int> data) {
	// pos is pos-1 since computer indexing starts at 0
	pos++;
	int par = 0;

	for (int i = pos; i < data.size()+1;) {
		for (int j = i; j < i + pos; j++) {
			if (j > data.size())
				break;
			if (data[j - 1] == -1)
				continue;
			par = par ^ data[j - 1];
		}
		i += (2*pos);
	}
	return par;
}

int main() {
	// ============
	// Senders Code
	// =============
	string input;
	cout << "\n======\nSender\n======\n";
	cout << "\nEnter the data: ";
	cin >> input;

	// Calculate uptil which power to get parity i.e 1, 2, 4, 8, 16 ...
	cout << "Power of 2 to be used: 2^" << floor(log2(input.length())) <<endl;

	// Make space for hammingCode vector
	vector<int>hammingCode(floor(log2(input.length()))+1 + input.length(), 0);

	// Fill all the power of 2 positions as -1
	for (int i = 0; i <= floor(log2(input.length())); i++)
		hammingCode[pow(2, i) - 1] = -1;

	// Fill all the rest with the data
	for (int i = 0, j=0; i < floor(log2(input.length())), j<input.size(); i++) {
		if (hammingCode[i] != -1) {
			if (input[j] == '0')
				hammingCode[i] = 0;
			else
				hammingCode[i]=1;
			j++;
		}
	}


	// ===========================================
	// Partial Output to display hamming positions
	// ===========================================
	cout << "\nPartial Output: ";
	// Display the code
	for (auto i : hammingCode)
		i != -1 ? cout << i : cout << '_';


	// Fill the hamming code with parities
	for (int i = 0; i <= floor(log2(input.length())); i++) {
		int par = getParity((pow(2, i) - 1), hammingCode);
		cout << "\nParity: " << par;
		hammingCode[pow(2, i) - 1] = par;
	}

	// Display the code
	cout << "\nHamming Code: ";
	for (auto i : hammingCode)
		cout << i;


	// Ask user if they want to use the same data to check
	char ans;
	cout << "\nUse same data to check? (y/n): ";
	cin >> ans;
	if (ans == 'n' || ans == 'N') {
		cout << "Enter hamming Code: ";
		cin >> input;
		hammingCode.resize(input.length());
		for (int i = 0; i < input.length(); i++)
			if (input[i] == '0')
				hammingCode[i] == 0;
			else
				hammingCode[i] == 1;
	}

	// ===============
	// Reciever's Code
	// ===============
	cout << "\n========\nReciever\n===========\n";
	cout << "\nData is: ";
	for (auto i : hammingCode)
		cout << i;

	// Get parity which is present in code
	cout << "\nParity from hamming code: ";
	int pow2 = log2(hammingCode.size());
	for (int i = 0; i <= pow2; i++)
		cout << hammingCode[pow(2,i) - 1] << " ";

	// Calculate the parity from the new positions
	cout << "\nCalculated Parity: ";
	int pos = 0;
	for (int i = 0; i <= pow2; i++) {
		int par = getParity((pow(2, i) - 1), hammingCode);
		cout << "\nParity: " << par;
		if (par == 1)
			pos += pow(2,i);
	}

	// If there is error in parity then position wont be == 0
	if (pos) {
		cout << "\nThere is an error in code!\nPosition: " << pos;
	}
	else {
		cout << "\nData is Correct!";
	}

	cout << endl;
	system("PAUSE");
	return 0;
}