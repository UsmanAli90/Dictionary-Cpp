#include<iostream>
#include<fstream>
#include"huffman.h"
#include<string>
using namespace std;
/////////////////////////////////////////////////////////////////editor///
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
int j = 0;
///////////////////
//////////////////////////
///////////////////////////////////////////////////////////
class n1 {
	//creating an node sutructure here we will have simple ll nodes which we are using to store our 10auggestion
public:
	n1* n;
	string data;

};
void insert1(string w, n1*& head)//simple ll insertion a we decided to store 10 suggestion in the ll to get them in the main
{
	if (head == nullptr)
	{
		head = new n1;
		head->n = head;
		head->data = w;
	}
	else
	{
		n1* curr = head;
		while (curr->n != head)
		{
			curr = curr->n;
		}
		n1* temp = new n1;
		curr->n = temp;
		temp->n = head;
		temp->data = w;

	}
}/////
////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////////////////////////////////

class n2 {//creating a node sutructure so we 
public:
	n2* next[26];
	bool WE;

};



n2* getnode()
{
	n2* temp = new n2;
	temp->WE = false;
	for (int i = 0;i < 26;i++)
	{
		temp->next[i] = nullptr;
	}
	return temp;
}

void insert(n2* root, string word)//insertion in the tri treee
{
	n2* curr = root;
	for (int i = 0;i < word.length();i++)//here we are inserting the word in the tri tree
	{
		int idx = word[i] - 'a';//getting the index to create a node on that index
		if (!curr->next[idx])
		{
			curr->next[idx] = getnode();
		}
		curr = curr->next[idx];
	}
	curr->WE = true;//after storing a whole word the word end var will be set true 
	//which will indicate us that the word is completed here
}

////////////////////////////////////////////////
///////////////////////////////////////////////


bool Mylastnode(n2* root)
{
	for (int i = 0;i < 26;i++)
	{
		if (root->next[i])
		{
			return 0;
		}
	}
	return 1;
}

void CreatingSuggestion(n2* root, string word, n1*& head)
{

	if (j == 10)//case to stop our recur..
	{
		return;
	}
	if (root->WE)//if the word end var equal to true putt that word into the linklist which we are suing in the main
	{
		cout <<j<<")"<< word << endl;
		insert1(word, head);
		j++;
	}
	for (int i = 0;i < 26;i++)//here we will create a suggestion 
	{
		if (root->next[i])
		{
			char c = 'a' + i;//going to that size where the node is present and converting the index to char
			// by adding the 'a' in the index and add to out half written word ie concatination them
			CreatingSuggestion(root->next[i], word + c, head);

		}
	}
}
int suggestTheword(n2* root, string word, n1*& head)
{
	n2* curr = root;
	for (int i = 0;i < word.length();i++)//as we have the half word so first we will check weather 
	{ 	//the related word is present in our tri tree if yes then 

		int idx = word[i] - 'a';
		if (!curr->next[idx])
		{
			return 0;
		}
		curr = curr->next[idx];
	}
	//then we will call the creating suggestion
	if (Mylastnode(curr))
	{
		cout << word;
		return -1;
	}
	CreatingSuggestion(curr, word, head);

}
///////////////////////////////////editor end/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////
/////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
string arr[27];
struct n3
{
	char c;
	int freq;
	n3* next, * left, * right;
};
n3* createNode(char c, int freq)
{
	n3* temp = new n3;
	temp->c = c;
	temp->freq = freq;
	temp->next = NULL;
	temp->right = NULL;
	temp->left = NULL;
	return temp;
}


void insert(char c, int* freq, n3*& hf)
{
	if (hf == NULL)
	{
		n3* temp = createNode(c, *freq);
		temp->next = hf;
		hf = temp;

	}
	else
	{
		n3* curr = hf;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}
		n3* temp = createNode(c, *freq);
		curr->next = temp;
		temp->next = NULL;

	}
}

//first we are 

void assigning(string str, int* freq, int length, n3*& head)
{
	for (int i = 0; i < length; i++)
	{
		if (str[i] != '0')
		{
			insert(str[i], &freq[i], head);
		}
	}
}



//simple sorting function
void sort(n3*& head)
{
	n3* curr = head;
	n3* curr1 = head;
	int count = 0;
	while (curr1 != NULL)
	{
		count++;
		curr1 = curr1->next;
	}
	for (int i = 0; i < count; i++)
	{
		n3* curr = head;
		while (curr->next != nullptr)
		{
			if (curr->freq > curr->next->freq)
			{
				swap(curr->freq, curr->next->freq);
				swap(curr->c, curr->next->c);

			}
			curr = curr->next;
		}

	}



}
void huffmaninsertion(n3* temp, n3*& head)
{
	n3* curr = head;
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	curr->next = temp;
}

void huffman(n3*& head)//creating the huffman tree by collecint the first two node and attaching them to the 
//last new node left and right poinetr and doing it until the head next not equal to null
//isk doran head k 2 stepaaagy b bhejry taa k jo attch ho chuky wo htm hjen
{
	while (head->next != NULL)
	{
		n3* curr = head;
		int xfreq = curr->freq + curr->next->freq;
		n3* temp = createNode('*', xfreq);
		temp->left = curr;
		temp->right = curr->next;
		huffmaninsertion(temp, head);
		if (curr->next != NULL)
		{
			head = curr->next->next;
		}
		sort(*&head);
	}
}
//codding in the file
void movtoarr(string a, char c)
{
	if (c != ' ')
	{
		int ind = c - 'a';
		arr[ind] = a;
	}
	else
	{
		arr[26] = a;
	}
}

//making code of char using huffman tree and stroing them into the array and each index of array will have
//  the special code of that perticular char
//
void creatingCodeOfChThroughHuffmanTree(n3* head, string str)
{
	if (head == NULL)
		return;

	if (head->c == '*')
	{
		creatingCodeOfChThroughHuffmanTree(head->left, str + "0");
		creatingCodeOfChThroughHuffmanTree(head->right, str + "1");
	}

	if (head->c != '*')
	{
		movtoarr(str, head->c);
		
		creatingCodeOfChThroughHuffmanTree(head->left, str + "0");
		creatingCodeOfChThroughHuffmanTree(head->right, str + "1");
	}
}
/////// givng the code of perticular char which is stored in the array
 string getc(char c)
{
	if (c != ' ')
	{
		int ind = c - 'a';
		return arr[ind];
	}
	else
	{
		return arr[26];
	}
}
// stroing codeed data into the file using the array whci we created 
void storetofile(n3* head, string st)
{
	ofstream out;
	out.open("encode.txt");
	for (int i = 0;i < st.length();i++)
	{
		out << getc(st[i]) << " ";
	}
}

//decoding the encoded data in teh file
void DecodingOfHufman(n3* head) //collecting data from file and decoding them and then storing them into the file ie decoded data file
{
	ofstream o;
	o.open("decoded.txt");
	o << " ";
	
	ifstream n;
	n3* h = head;
	n.open("encode.txt");
	string k;
	while (!(n.eof()))
	{
		h = head;
		n >> k;//taking input of the code of a ch which is a string and 
		for (int i = 0;i < k.length();i++)//then comparing index by index if the index val is 0 go to left in huffman elsr
			//go to right in the huffman
		{
			char a = k[i];
			if (a == '0')
			{
				h = h->left;
			}
			else if (a == '1')
			{
				h = h->right;
			}
		}
		cout << h->c;
		o << h->c;
	}
}


/////////////////////////////////////////
/////////////////////
//////////////////////////////
//////////////////////////
/////////////////////////////////////////////////
//.making the frequency..making the hufman tree and storing codded data in the file ...
void fun(n3* &hf,string st)
{


	string copy;
	copy = st;

	int i, j, length = st.length();
	int* freq = new int[length];

	for (i = 0; i < length; i++)
	{
		freq[i] = 1;
		for (j = i + 1; j < length; j++)
		{
			if (st[i] == st[j])
			{
				freq[i]++;
				//Set string[j] to 0 to avoid printing visited character  
				st[j] = '0';
			}
		}
	}
	//Displays the each character and their corresponding frequency  
	assigning(st, freq, length, hf);
	sort(hf);
	huffman(hf);
	creatingCodeOfChThroughHuffmanTree(hf, "");
	storetofile(hf, copy);
	
	
}

int main()
{
	n3* hf = NULL;
	
	ifstream in;
	in.open("outfile.txt");
	string a;
	n2* root = getnode();
	while (!(in.eof()))
	{
		getline(in, a);
		insert(root, a);
	}
	n1* head = nullptr;
	int op;
	cout << "1)To Start from last eidted notepad\n2)To start from new notepad"<<endl;
	cin >> op;
	if (op == 1){
		ifstream input;
		string get;
		input.open("Notepad.txt");
		while (!(input.eof()))
		{
			getline(input, get);
			cout << get;
		}
		input.close();

	}
	else if (op == 2)
	{
		ofstream o;
		o.open("Notepad.txt");
		o << " ";
		o.close();
	}
	system("pause");
	string msg1, ch, msg2;
	bool m = true;
	while (1) {
		system("cls");
		ifstream inp;
		hf = nullptr;
		inp.open("Notepad.txt");
		string get;
		while (!(inp.eof()))
		{
			getline(inp, get);
			cout << get;
		}
		inp.close();
		cin >> msg1;
		int id = 'a'-msg1[0]-46;
		if(id < 9&&id>0)
		{
			cout << "invalid input enter again:";
			cin >> msg1;
		}
		suggestTheword(root, msg1, head);
		j = 0;
		if (head == nullptr)
		{
			cout << "NO suggestion:";

			ofstream out;
			out.open("Notepad.txt", ios::app);
			out << " " << msg1;
			out.close();


			ifstream ino;
			ino.open("Notepad.txt");
			string g;
			while (!(ino.eof()))
			{
				getline(ino, g);
			}

			fun(hf, g);

			
		}
		else
		{
			msg2 = head->data;



			cout << "By default you have selected suggestion 0 Press / to move to next suggestion" << endl << " else press ; to select a suggestion" << endl << "To skip suggestion press 1" << endl;
			int count = 0;
			m = true;
			while (m)
			{
				cin >> ch;
				if (ch == "/") {
					count++;
					ofstream out;
					out.open("Notepad.txt", ios::app);
					head = head->n;
					cout << "your on suggestion :" << count << endl;
				}
				else if (ch == ";")
				{
					ofstream out;
					out.open("Notepad.txt", ios::app);
					msg2 = head->data;
					out << " " << msg2;
					out.close();
					ifstream ino;
					ino.open("Notepad.txt");
					string g;
					while (!(ino.eof()))
					{
						getline(ino, g);
					}
					fun(hf, g);


					m = false;
				}
				else if (ch == "1")
				{
					ofstream out;
					out.open("Notepad.txt", ios::app);
					out << " " << msg1;
					out.close();


					ifstream ino;
					ino.open("Notepad.txt");
					string g;
					while (!(ino.eof()))
					{
						getline(ino, g);
					}

					fun(hf, g);

					m = false;
				}
				if (count == 9)
				{
					count = 0;
				}
			}
		}
		head = nullptr;
		cout << "\n 1)Stop editing else any key :";
		string a;
		cin >> a;
		if (a == "1")
		{
			break;
		}
		system("cls");
		DecodingOfHufman(hf);
		ofstream ot;
		ot.open("hufftree.txt");
		for (int i = 0;i < 27;i++)
		{
			ot << arr[i] << " ";
		}

	}




	
	//system("pause");
}
