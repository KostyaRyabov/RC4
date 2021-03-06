#include <iostream>

using namespace std;

struct temp {
	char symb;
	temp* next;
};

unsigned char* PLSTR(int &len) {
	int i = 0;
	temp *pNEW, *pSTART, *pKEPT;

	pNEW = NULL;
	pSTART = NULL;
	pKEPT = NULL;

	char c = getchar();

	while (c != 10) {
		pNEW = new temp;
		pNEW->symb = c;

		if (pSTART == NULL) {
			pSTART = pNEW;
		}
		else {
			pKEPT->next = pNEW;
		}
		pKEPT = pNEW;

		i++;
		c = getchar();
	}

	if (i == 0) {
		pNEW = new temp;
		pNEW->symb = 48;
		pSTART = pNEW;
		i++;
	}

	pNEW->next = NULL;

	unsigned char *str = new unsigned char[i + 1];

	i = 0;
	pNEW = pSTART;

	while (pNEW != NULL) {
		*(str + i) = pNEW->symb;

		pKEPT = pNEW;
		pNEW = pNEW->next;
		delete(pKEPT);
		i++;
	}

	*(str + i) = '\0';

	len = i;

	cout << "  [(" << len << ")]" << endl << endl;

	return str;
}

class RC4 {
private:
	int message_len, key_len, i, j, x, y;

	unsigned char *key, *message, *S;
public:
	void SetKey() {
		cout << endl << "Enter key: ";
		key = PLSTR(key_len);
	}
	void SetMessage() {
		cout << endl << "Enter message: ";
		message = PLSTR(message_len);
	}
	void KeyInit() {
		S = new unsigned char[256];

		x = 0;
		y = 0;

		for (int i = 0; i < 255; i++) {
			*(S + i) = i;
		}

		unsigned char tempC;

		for (j = i = 0; i < 255; i++) {
			j = (j + key[i % key_len] + S[i]) % 256;
			tempC = S[i];
			S[i] = S[j];
			S[j] = tempC;
		}
	}
	unsigned char keyItem()
	{
		x = (x + 1) % 256;
		y = (y + S[x]) % 256;

		unsigned char tempC;

		tempC = S[x];
		S[x] = S[y];
		S[y] = tempC;

		return S[(tempC + S[y]) % 256];
	}
	void Encode() {
		for (int m = 0; m < message_len; m++) {
			*(message + m) = (unsigned char)(keyItem() ^ *(message + m)) % 256;
		}
	}
	void ShowRes() {
		cout << "Result: ";
		for (int m = 0; m < message_len; m++) {
			cout << *(message + m);
		}
	}
	void ShowResID() {
		cout << endl << "Result (id): ";
		for (int m = 0; m < message_len; m++) {
			cout << "#" << m+1 << " - [ " << (int)(*(message + m)) << "] ";
		}
	}
	void ShowResOnArray() {
		cout << endl << "Result on Array: [";
		for (int m = 0; m < message_len; m++) {
			cout << (*(message + m)) << ",";
		}
		cout << "]";
	}
	void ShowResIDOnArray() {
		cout << endl << "Result on Array: [";
		for (int m = 0; m < message_len; m++) {
			cout << (int)(*(message + m)) << ",";
		}
		cout << "]";
	}
};

int main()
{
	cout << endl << "////Input line ends with 'Enter'////" << endl;

	char c = 10;

	while (c == 10) {
		cout << "---------------------------------------" << endl << endl;
		
		RC4 *obj = new RC4();

		obj->SetKey();
		obj->SetMessage();

		obj->KeyInit();

		cout << endl << "Encode->";

		obj->Encode();
		obj->ShowRes();
		//obj->ShowResID();

		cout << endl << endl << "Decode->";

		obj->KeyInit();

		obj->Encode();
		obj->ShowRes();
		//obj->ShowResID();

		cout << endl << endl << "press 'enter' to enter a new message: ";

		c = getchar();

		delete obj;
	}
}