#include<iostream>
#include<fstream>
#include<string.h>
#include<conio.h>
#include <ctime>
using namespace std;

    int flag = 1;
class node{
	public:
		char word[100];
		char meaning[500];
		char example[1000];
		
		node* left;
		node* right;
		
		node(){
			left = NULL;
			right = NULL;
		}
		node(char w[] , char m[] , char e[]){
			left = NULL;
			right = NULL;
			strcpy(word , w);
			strcpy(meaning , m);
			strcpy(example , e);
		}
	
};

class AVL{
	public:
		node* root;
		
	AVL(){
		root =  NULL;
	}
	int height(node* r){
		if( r==NULL){
			return -1;
		}
		else{
			int L = height(r->left);
			int R = height(r->right);
			
			if(L > R){
				return L+1;
			}
			else{
				return R+1;
			}
		}
	}
	int balancefactor(node* r){
		if(r == NULL){
			return -1;
		}
		else{
			return (height(r->left) - height(r->right));
		}
	}
	
	node* rightRotate(node* r){
		node* a = r->left;
		node* T = a->right;
		
		a->right = r;
		r->left = T;
		
		return a;
	}
	node* leftRotate(node* r){
		node* a = r->right;
		node* T = a->left;
		
		a->left = r;
		r->right = T;
		
		return a;
	}
	
	node* insert(node* r ,char w[] , char m[] , char e[] ){
		node* data = new node( w ,  m ,  e);
		
		if(r == NULL){
			r = data;
			cout<<"\t\t\t**Node inserted**\n";
			return  r;
		}
		else if(strcmp(data->word  , r->word ) < 0){
			r->left = insert(r->left , w ,  m ,  e);
	 	}
	 	
		else if(strcmp(data->word  , r->word ) > 0){
			r->right = insert(r->right , w ,  m ,  e);
		}
		else {
			cout<<"\t\t\t**Data Duplication Error.**\n";
			return r;
		}
		
		int bf = balancefactor(r);
		if(bf>1 && strcmp(data->word  , r->left->word ) < 0 ){
			return (rightRotate(r));
		}
		if(bf>1 && strcmp(data->word  , r->left->word ) > 0){
			r->left = leftRotate(r->left);
			return (rightRotate(r));
		}
		if(bf<-1 && strcmp(data->word  , r->right->word ) > 0){
			return (leftRotate(r));
		}
		if(bf <-1 && strcmp(data->word  , r->right->word ) < 0){
			r->right = rightRotate(r->right);
			return (leftRotate(r));
		}
		return r;
	}
	
	
	node * delete_word(node* r, char w[]) {
    if (r == NULL) {
      return NULL;
    }
	else if(strcmp(w,r->word)<0){
		r->left = delete_word(r->left,w);
	}
	else if(strcmp(w,r->word)>0){
		r->right = delete_word(r->right,w);
	}
    else {
		if (r -> left == NULL) {
			cout <<"WORD DELETED !!\n";
			node * temp = r -> right;
        	delete r;
        	return temp;
		} 
		else if (r -> right == NULL) {
			cout <<"WORD DELETED !!\n";
    	    node * temp = r -> left;
    	    delete r;
    	    return temp;
		}
	    else {
			node * temp = r->right;
			while(temp->left != NULL){
				temp = temp->left;
			} 
			cout <<"WORD DELETED !!\n";
			strcpy(r->word,temp->word);
			strcpy(r->meaning,temp->meaning);
			strcpy(r->example,temp->example);
						
			r->right = delete_word(r->right,temp->word);      
			}
    }

    int bf = balancefactor(r);
    if (bf == 2 && balancefactor(r -> left) >= 0)
      return rightRotate(r);
    else if (bf == 2 && balancefactor(r -> left) == -1) {
      r -> left = leftRotate(r -> left);
      return rightRotate(r);
    }
    else if (bf == -2 && balancefactor(r -> right) <= -0)
      return leftRotate(r);
    else if (bf == -2 && balancefactor(r -> right) == 1) {
      r -> right = rightRotate(r -> right);
      return leftRotate(r);
    }

    return r;
	}
	
			
	void BF_As_Inorder(node* r){
			if(r == NULL){
				return ;
			}
			else{
				BF_As_Inorder(r->left);
				cout<<"\n\nNode\n-------\n"<<r->word<<endl<<r->meaning<<endl<<r->example<<endl;
				BF_As_Inorder(r->right);
			}
		}
		void printPreorder(node * r) 
		  {
		    if (r == NULL)
		      return;
		    cout << r -> word << " ";
		    printPreorder(r -> left);
		    printPreorder(r -> right);
		  }
	void print2DUtil(node* root, int space)
		{
	    if (root == NULL)
	        return;
	    space += 10;
	    print2DUtil(root->right, space);
	    cout << endl;
	    for (int i = 10; i < space; i++)
	        cout << " ";
	    cout << root->word << "\n";
	    print2DUtil(root->left, space);
	}
	void print2D(node* root)
	{
	    print2DUtil(root, 0);
	}
    void printGivenLevel(node * r, int level) {
    if (r == NULL){
       return;	
	}
    else if (level == 0 && flag == 1){
    	cout <<"Word Of The Day "<<endl;
       cout <<"Word : "<< r->word <<endl;
       cout <<"Meaning : "<<r->meaning<<endl;
       cout <<"Example : "<<r->example<<endl;
       flag = 0;
    }
    else {
      printGivenLevel(r -> left, level - 1);
      printGivenLevel(r -> right, level - 1);
    }
  } 
  
};

class HashTable{
	public:
		AVL* table ;
		
		HashTable(){
			table = new AVL[26];
		}
		
		
		int HashFunc(char word[]){
			int Alphabet;
			if(word[0] >= 65 && word[0] <= 90){
			 Alphabet = word[0] - 65;
			}
			else if(word[0] >= 97 && word[0] <= 122){
				 Alphabet = word[0] - 97;
			}
			return Alphabet;
		}
		
		void wordoftheday(){
	    	time_t now = time(0);
			tm *ltm = localtime(&now);
			int month = ltm->tm_mon;
			month = month %8;
			int day =  ltm->tm_mday;	
			int random = day%26;
			int height =  table[random].height(table[random].root);
			height = height%month;
			table[random].printGivenLevel(table[random].root,height);
		}
		
		void upload_data_from_file_to_AVL(){
			node* obj = new node();
			fstream f;
		
			f.open("myfileFinal.txt" , ios::in);
			int i = 1;
			if(f.is_open()){
	
				while(! f.eof()){
			
		
				f.getline(obj->word , 100 , '	');
				f.getline(obj->meaning , 500 , '	');
				f.getline(obj->example , 1000 , '\n');
				
				
				int Alphabet = HashFunc(obj->word);
				if((Alphabet >= 0) && (Alphabet < 26)){


						table[ Alphabet ].root = table[Alphabet].insert(table[ Alphabet ].root , obj->word , obj->meaning , obj->example);		
				}
			
		
		
			}
		f.close();
	}
	

}
	void Insert_New_word_in_Dictionary(){
		char w[100];
		char m[500];
		char e[1000];
		cout<<"\nINSERTION\n-------------\n";
		cout<<"Enter Word : ";
		gets(w);
		cout<<"Enter Meaning : ";
		gets(m);
		cout<<"Enter Supporting Example : ";
		gets(e);
		w[0] = toupper(w[0]);
		for (int i = 1; i < w[i] != '\0'; i++) {
		w[i] = tolower(w[i]);
		}	
		
		int Alphabet = HashFunc(w);				
				
		if((Alphabet >= 0) && (Alphabet < 26)){
			table[ Alphabet ].root = table[Alphabet].insert(table[ Alphabet ].root , w , m , e);		
			cout<<"\nNew word Added Successfully.";
		}
		fstream f;
		f.open("myfileFinal.txt", ios::app);
		node *temp = new node(w,m,e);
		f<< temp->word<<"\t"<<temp->meaning<<"\t"<<temp->example<<endl;
	}
	
	void Delete_word_from_Dictionary(char w[]){
		w[0] = toupper(w[0]);
		for (int i = 1; i < w[i] != '\0'; i++) {
		w[i] = tolower(w[i]);
		}	
		
		
		int alphabet = HashFunc(w);
		node *temp;
		if(alphabet<26 &&  alphabet > -1){
			temp = table[alphabet].root;
			table[alphabet].root = table[alphabet].delete_word(temp,w);
		}		
	}
	
	node* search_word(char w[]){
		w[0] = toupper(w[0]);
		for (int i = 1; i < w[i] != '\0'; i++) {
		w[i] = tolower(w[i]);
		}		
		
		
		int alphabet;
		node *srch = new node(); 
		alphabet = HashFunc(w);
		if(alphabet<26 &&  alphabet > -1){
			srch = table[alphabet].root;
			while (srch!=NULL){
				if(strcmp(w,srch->word)==0){
				cout<<"Meaning: "<<srch->meaning<<endl;
				cout<<"Example: "<<srch->example<<endl;  
				return srch;
				}
				else if(strcmp(w,srch->word)<0){
				srch = srch->left;
				}
				else if(strcmp(w,srch->word)>0){
				srch = srch->right;
				}
			}	 
			cout<<"Word not found!!\n";
		}	
	}

		
	
};
int main()
{
	HashTable t;
	t.upload_data_from_file_to_AVL();
//	t.Insert_New_word_in_Dictionary();
//	for(int i=0 ; i<26 ; i++){
//		cout<<"\n\n"<<i<<"\n------";
//		//t.table[i].printPreorder(t.table[i].root );
//		t.table[i].BF_As_Inorder(t.table[i].root );
//	}
	
	char wrd[100];
	
//	cout <<"Enter Word to be deleted : ";
//	gets(wrd2);
//	t.Delete_word_from_Dictionary(wrd2);
	t.wordoftheday();
	cout<<"Enter word to be searched: ";
	gets(wrd);
	t.search_word(wrd);

	
	
	return 0;

}


