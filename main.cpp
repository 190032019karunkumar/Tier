// An advanced data structure useful for storage of large collection of words and their faster retrieval.

#include <bits/stdc++.h>
using namespace std;

struct Node
{
	bool isEOW;  // end of the word
	Node* next[26];  // array of node pointers
	Node()
	{
		isEOW = false;
		for(int i=0;i<26;i++)
		{
			next[i] = NULL;
		}
	}
};

// Insert Function

void insertWord(Node* root,string word)
{
	Node* temp = root;
	for(auto ch:word)
	{
		int idx = ch - 'a';   // getting the index
		if(temp->next[idx] == NULL)
		{
			temp->next[idx] = new Node();    // if the index pointer is null then assign the index value to the pointer.
		}
		temp = temp->next[idx];
	}
	temp->isEOW = true;   // after all the indexs are assign the end of word becomes true
}


// Check Function

bool checkWord(Node* root, string word)
{
	Node* temp = root;

	for(auto ch:word)
	{
		int idx = ch - 'a';
		if(temp->next[idx]==NULL)
		{
			return false;
		}
		temp = temp->next[idx];
	}
	return temp->isEOW;
}


// Print Function

char path[100]; // path array to store the letters of the word
void printAllWords(Node* root,int pi)
{
	if(root->isEOW)
	{
		string word="";
		for(int i=0;i<pi;i++)
		{
			word += path[i];
		}
		cout<<word<<" "<<"\n";
	}
	for(int i=0;i<26;i++)
	{
		if(root->next[i] != NULL)
		{
			char ch = i + 'a';
			path[pi] = ch;
			printAllWords(root->next[i],pi+1);
		}
	}
}


// AutoSuggest Function

char suggest[100];
void autoSuggest(Node* root,int pi,string pattern)
{
	int k=1;
	int n = pattern.size();
	if(root->isEOW)
	{
		string word="";
		for(int i=0;i<pi;i++)
		{
			word += suggest[i];
		}
		for(int i=0;i<n;i++)
		{
			if(word[i]!=pattern[i])
			{
				k=0;
			}
		}
		if(k==1)
			cout<<word<<" "<<"\n";
	}
	for(int i=0;i<26;i++)
	{
		if(root->next[i] != NULL)
		{
			char ch = i + 'a';
			suggest[pi] = ch;
			autoSuggest(root->next[i],pi+1,pattern);
		}
	}
}


int main()
{
	Node* root = new Node();
	FILE* fp = fopen("C:\\Users\\Acer\\OneDrive\\Desktop\\dict.txt","r");
	char words[1000];
	while(!feof(fp))
	{
		fscanf(fp,"%s",words);
		string str(words);
		insertWord(root,str);
	}
	cout<<"=======================Menu============================\n";
	cout<<"Enter 1 for Insert the Word\n";
	cout<<"Enter 2 for Check the Word is Present or Not\n";
	cout<<"Enter 3 for Print All the Word\n";
	cout<<"Enter 4 for Auto Suggest of the Given Pattern\n";

	int choice;cin>>choice;

	switch (choice) {
    case 1: {
        cout << "Enter the word you want to insert\n";
        string str;cin>>str;
        insertWord(root,str);
        break;
    }
    case 2: {
        cout << "Enter the word you want to Check\n";
        string str;cin>>str;
        cout<<checkWord(root,str);
        break;
    }
    case 3: {
        cout << "All the words in the Tire\n";
        printAllWords(root,0);
        break;
    }
    case 4: {
        cout << "Enter the pattern for pattern\n";
        string pattern;cin>>pattern;
        autoSuggest(root,0,pattern);
        break;
    }
    default:
        printf("Wrong Input\n");
    }
	return 0;
}
