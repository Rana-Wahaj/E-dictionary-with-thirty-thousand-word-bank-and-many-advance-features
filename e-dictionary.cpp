#include<iostream>
#include<fstream>
#include<string.h>
#include<conio.h>
#include<time.h>
#include<cstdlib>
#include<stdlib.h>
#include<windows.h>
#include<dos.h>
#include <unistd.h>

#define N  30
using namespace std;
int flag = 1;
int str_len(char[]);
void GameRule();
//-----------------------------------------------------

void DisplayDelayed(char arr[]){
	for(int i=0 ; arr[i] != '\0' ; i++){
		usleep(50000);
		cout<<arr[i];
	}
}
//-----------------------------------------------------

void DisplayDelayed2(char arr[]){
	for(int i=0 ; arr[i] != '\0' ; i++){
		usleep(1000);
		cout<<arr[i];
	}
}

//------------------------------------------------------

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
		node(node* n){
			strcpy(this->word , n->word);
			strcpy(this->meaning , n->meaning);
			strcpy(this->example , n->example);
		}
		node(char w[] , char m[] , char e[]){
			left = NULL;
			right = NULL;
			strcpy(word , w);
			strcpy(meaning , m);
			strcpy(example , e);
		}
	

};

class node_for_linklist{
	public:
	node* predictive_word;
	int key;
	node_for_linklist* next;
	
	node_for_linklist(){
		next = NULL;
		key = 0;
		predictive_word = new node();
	}
	node_for_linklist(char w[] , char m[] , char e[]  , int k){
		key = k;
		predictive_word = new node(w , m , e);
		next = NULL;
	}
};

class singlyLinkedlist{
	public:
		node_for_linklist * head ;
		static int k;
		singlyLinkedlist(){
			head = NULL;
		}
		

//-------------------------------------------------------------------------------------------------------

	void Add_Node_in_last(char w[] , char  m[] , char  e[] ){
		
		node_for_linklist* n = new node_for_linklist(w , m , e , k);
		k++;
		if(head == NULL){
			head = n;
		}
		else{
			node_for_linklist * temp ;
			for(temp = head ; temp->next!= NULL ; temp = temp->next){
				continue;
			}
			temp->next = n;
		}
	}

//-------------------------------------------------------------------------------------------------------
	
	void Search_and_display(int k){
			if(head == NULL){
				cout<<"\n\n\t\t\tTheres No Word Matching .";
			}
			else{
				node_for_linklist* temp ;
				
				for(temp = head ; temp != NULL ; temp = temp->next){
					if(k == temp->key){
						system("cls");
						cout << "\n\n\n\n\t\t\t\t\t "<<temp->predictive_word->word;
						cout << "\n\t\t\t\t\t------------------\n";
						cout << "\n\t\t MEANING : ";DisplayDelayed(temp->predictive_word->word);
						cout << "\n\n\t\t EXAMPLE : ";DisplayDelayed(temp->predictive_word->example);
						break;
					}
				}
			}
	}

//-------------------------------------------------------------------------------------------------------
	
	void  displayLinkList(bool* found){
			if(head == NULL){
				cout<<"Theres no Word Matching .";
				*(found) = false;
				getch();
			}
			else{
				node_for_linklist* temp ;
				int i;
				
				for(temp = head  ; temp != NULL ; temp = temp->next){
					cout<<" "<<temp->key<<"-"<<temp->predictive_word->word ;
				
				}
				*(found) = true;
			}
		}
		
//-------------------------------------------------------------------------------------------------------		
};
int singlyLinkedlist::k = 1;
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

//-------------------------------------------------------------------------------------------------------
	
	int balancefactor(node* r){
		if(r == NULL){
			return -1;
		}
		else{
			return (height(r->left) - height(r->right));
		}
	}
	
//-------------------------------------------------------------------------------------------------------
	
	node* rightRotate(node* r){
		node* a = r->left;
		node* T = a->right;
		
		a->right = r;
		r->left = T;
		
		return a;
	}
	
//-------------------------------------------------------------------------------------------------------
	
	node* leftRotate(node* r){
		node* a = r->right;
		node* T = a->left;
		
		a->left = r;
		r->right = T;
		
		return a;
	}
	
//-------------------------------------------------------------------------------------------------------
	
	node* insert(node* r ,char w[] , char m[] , char e[] ){
		node* data = new node( w ,  m ,  e);
		
		if(r == NULL){
			r = data;
			return  r;
		}
		else if(strcmp(data->word  , r->word ) < 0){
			r->left = insert(r->left , w ,  m ,  e);
	 	}
	 	
		else if(strcmp(data->word  , r->word ) > 0){
			r->right = insert(r->right , w ,  m ,  e);
		}
		else {
		
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
	
//-------------------------------------------------------------------------------------------------------
	
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
			cout <<"\n\n\t\t\t\t\tWORD DELETED SUCCESSFULLY!!\n";
			getch();
			node * temp = r -> right;
        	delete r;
        	return temp;
		} 
		else if (r -> right == NULL) {
			cout <<"\n\n\t\t\t\t\tWORD DELETED SUCCESSFULLY!!\n";
			getch();
    	    node * temp = r -> left;
    	    delete r;
    	    return temp;
		}
	    else {
			node * temp = r->right;
			while(temp->left != NULL){
				temp = temp->left;
			} 
			cout <<"\n\n\t\t\t\t\tWORD DELETED SUCCESSFULLY!!\n";
			getch();
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
	
//-------------------------------------------------------------------------------------------------------
		  
		  void printInorder (node* r,char predictor[],char *chk , singlyLinkedlist* list ){
			chk=NULL;
			if (r==NULL){
				return;
			}
			else {
				printInorder(r->right,predictor,chk,list);
				chk = strstr(r->word,predictor);
				if (chk!=NULL){
				list->Add_Node_in_last(r->word , r->meaning , r->example );
				
				}
				printInorder(r->left,predictor,chk,list);  
			}
		}
		
//-------------------------------------------------------------------------------------------------------		
		
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
	
//-------------------------------------------------------------------------------------------------------	
	
	  void printGivenLevel(node * r, int level) {
		    if (r == NULL){
		       return;	
			}
		    else if (level == 0 && flag == 1){
		    	
		       char arr[200];
		       cout<<"\n\n\n\t\t\t\t\t";
			   strcpy(arr , "-----------------------");
				DisplayDelayed2( arr );
		   	   cout << "\n\t\t\t\t\t";
		   	   strcpy(arr , "    WORD OF THE DAY");
				DisplayDelayed2( arr );
		   	   cout << "\n\t\t\t\t\t";
		   	  strcpy(arr , "-----------------------");
				DisplayDelayed2( arr );
				cout<<endl;
		   	   
		       cout <<"WORD    : ";DisplayDelayed2( r->word );
			   cout << endl;
				strcpy(arr ,  "----------------------------------------------------------------------------------------------------------------------");
			   DisplayDelayed2( arr );
			   cout << endl;
		       cout <<"MEANING : ";DisplayDelayed2( r->meaning );
		       cout << endl;
		       DisplayDelayed2( arr );
		       cout << endl;
		       cout <<"EXAMPLE : ";DisplayDelayed2( r->example );
		       cout << endl;
		        DisplayDelayed2( arr );
		        cout << "\n\n\t\t\t\t\t";
		        
		        strcpy(arr , "We Hope This Has Increased Your Vacabulary, See You Tommorrow");
		        DisplayDelayed2( arr );
		        char c = 1;
		        cout<<c;
		        getch();
		       flag = 0;
    }
    else {
      printGivenLevel(r -> left, level - 1);
      printGivenLevel(r -> right, level - 1);
    }
  } 
  
  //-------------------------------------------------------------------------------------------------------
};

class HashTable{
	public:
		AVL* table ;
		
		HashTable(){
			table = new AVL[26];
		}
		
//-------------------------------------------------------------------------------------------------------
				
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

//-------------------------------------------------------------------------------------------------------
		
		void wordoftheday(){
			system("cls");
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
		
//-------------------------------------------------------------------------------------------------------
		
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

//-------------------------------------------------------------------------------------------------------

		void Insert_New_word_in_Dictionary(){
		char w[100];
		char m[500];
		char e[1000];
		system("cls");
		cout << "\n\n\n\n\t\t\t\t\t---------------------------------";
		cout << "\n\t\t\t\t\t       INSERTION  SECTION";
		cout << "\n\t\t\t\t\t---------------------------------";
		cout << "\n\t\t\t\t\t Hey Developer, You Got Some New ";
		cout << "\n\t\t\t\t\t    Words To Insert Into Your ";
		cout << "\n\t\t\t\t\t      Dictionary? Go Ahead ";
		cout << "\n\t\t\t\t\t        Press Any Key To ";
		cout << "\n\t\t\t\t\t             Continue";
		cout << "\n\t\t\t\t\t---------------------------------";
		getch();
		system("cls");
		cout << "\n\n\n\n\t\t\t\t\tNOTE : Please Make Sure First Letter";
		cout << "\n\t\t\t\t\t       Must Be Capital.";
		cout << "\n\n\t\t\t\t\t---------------------------------";
		cout << "\n\t\t\t\t\t Enter Word : ";
		fflush(stdin);
		cin.getline(w , 100);
		cout<<"\n\t\t\t\t\t Enter Meaning : ";
		fflush(stdin);
		cin.getline(m , 500);
		cout<<"\n\t\t\t\t\t Enter Supporting Example : ";
		fflush(stdin);
		cin.getline(e , 1000);
		w[0] = toupper(w[0]);
		for (int i = 1; i < w[i] != '\0'; i++) {
		w[i] = tolower(w[i]);
		}	
		
		int Alphabet = HashFunc(w);				
				
		if((Alphabet >= 0) && (Alphabet < 26)){
			table[ Alphabet ].root = table[Alphabet].insert(table[ Alphabet ].root , w , m , e);	
			system("cls");
			cout << "\n\n\n\n\t\t\t\t\t\' ";
			DisplayDelayed(w);	
			cout << " \'";
			cout << "\n\n\t\t\t\t\tAdded Successfully.";
			cout << "\n\t\t\t\t\t---------------------------------";
			getch();
		}
		fstream f;
		f.open("myfileFinal.txt", ios::app);
		node *temp = new node(w,m,e);
		f<< temp->word<<"\t"<<temp->meaning<<"\t"<<temp->example<<endl;
	}

//-------------------------------------------------------------------------------------------------------
	
	void Delete_word_from_Dictionary(){
		system("cls");
		char w[100];
		cout << "\n\n\n\n\t\t\t\t\t---------------------------------";
		cout << "\n\t\t\t\t\t       DELETE WORD SECTION";
		cout << "\n\t\t\t\t\t---------------------------------";
		cout << "\n\t\t\t\t\t Enter Word To be Deleted : ";
		fflush(stdin);
		cin.getline(w , 100);
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
	
//-------------------------------------------------------------------------------------------------------
	
		node* search_word(){
		char w[100];
		char c = 1;
		system("cls");
		cout << "\n\n\n\n\t\t\t\t\t---------------------------------";
		cout << "\n\t\t\t\t\t       SEARCH WORD SECTION";
		cout << "\n\t\t\t\t\t---------------------------------";
		cout << "\n\t\t\t\t\t Have Trouble Finding Your Life";
		cout << "\n\t\t\t\t\t Meaning? No Worries We Got You";
		cout << "\n\t\t\t\t\t   We can Help You Lookup For ";
		cout << "\n\t\t\t\t\t     Meaning Within Seconds ";
		cout << "\n\t\t\t\t\t        HAPPY SEARCHING"<< c ;
		cout << "\n\t\t\t\t\t---------------------------------";
		getch();
		
		system("cls");
		cout << "\n\n\n\n\t\t\t\t\t-------------------------------------";
		cout << "\n\t\t\t\t\tEnter Word To be Searched : ";
		fflush(stdin);
		cin.getline(w , 100);
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
					system("cls");
					cout << "\n\n\n\n\t\t\t\t\t "<<srch->word;
					cout << "\n\t\t\t\t\t------------------\n";
					cout << "\n\t\t MEANING : ";DisplayDelayed(srch->meaning);
					cout << "\n\n\t\t EXAMPLE : ";DisplayDelayed(srch->example); 
				
					getch(); 
				return srch;
				}
				else if(strcmp(w,srch->word)<0){
				srch = srch->left;
				}
				else if(strcmp(w,srch->word)>0){
				srch = srch->right;
				}
			}	 
			cout<<"\n\t\t\t\t\tWord Not Found!!\n";
			singlyLinkedlist::k = 1;
			predictionstep1(w);
			getch();
			
		}	
	}

//-------------------------------------------------------------------------------------------------------
	
			void predictionstep2(char predictor[],node *search,int alpha){
			HashTable t;
			singlyLinkedlist list;
			char n;
			char *chk;
			char tempsearch[4];
			while (search!=NULL){
				tempsearch[0]=search->word[0];
				tempsearch[1]=search->word[1];
				tempsearch[2]=search->word[2];
				tempsearch[3]=search->word[3];
				if (strcmp(predictor,tempsearch)==0){
					cout <<"\n\n\t\tDO YOU MEAN : ";
					t.table[alpha].printInorder(search,predictor,chk, &list );
					bool found;
					list.displayLinkList(&found);
					 
					if(found == true){
						cout<<"\n\n\t\t-----------------------------------------\n\t\tEnter Your Choice (Press 'E' To Exit) : ";
						cin >> n; 
						if(n == 'e' || n == 'E'){
							return;
						}
						list.Search_and_display( (int(n) - 48) ); // convert char to int
						return;
					}
					return;

					
					
					
				}
				else if (strcmp(predictor,tempsearch)>0){
					search = search->right;
				}
				else if (strcmp(predictor,tempsearch)<0){
					search = search->left;
				}
			}
		}
		
//-------------------------------------------------------------------------------------------------------		
		
		void predictionstep1 (char word[]){
			char predictor[4];
			for (int i=0;i<4;i++){
				predictor[i] = word[i];
				predictor[i] = tolower(predictor[i]);
			}
			predictor[0] =  toupper(predictor[0]);
		//	puts(predictor);
			int alphabet;
			alphabet = HashFunc(word);
			node *object = new node();
			object = table[alphabet].root;
			predictionstep2(predictor,object,alphabet);
		}
		
//-------------------------------------------------------------------------------------------------------
		
};

class stack_node{
	public:
		node Node;
		stack_node* next;
		
		stack_node(){
			next = NULL;
		}
		
		stack_node(node* n){
			Node = new node(n);
			next = NULL;
		}
};

class simple_stack{
	public:
		int s_stack[N];
		int s_top ;
		
		simple_stack(){
			s_top = -1;
		}
//-------------------------------------------------------------------------------------------------------
		
		void push(int x){
			if(s_top == N-1){
				cout<<"\nStack Overflow...";
			}
			else{
			
				s_top++;
				s_stack[s_top] = x;
			}
		}
		
//-------------------------------------------------------------------------------------------------------
		
		int top_s(){
			if(s_top == -1){
			}	
			else{
				int item = s_stack[s_top];
				return item;
			}
		}

//-------------------------------------------------------------------------------------------------------
		
		int pop(){
			int item;
			if(s_top == -1){
			}	
			else{
				item = s_stack[s_top];
				s_top--;
				return item;
			}
			
		}
	
//-------------------------------------------------------------------------------------------------------
		
		void peek(){
			if(s_top == -1){
			}
			else{
				cout<<"\nTop value in stack is: "<<s_stack[s_top];
				
			}
		}
		
//-------------------------------------------------------------------------------------------------------
		
		void display(){
			if(s_top == -1){
				cout<<"\nStack UnderFlow.";
			}
			else{
				cout<<endl;
				for(int i=s_top ; i>=0 ; i--){
					cout<<s_stack[i]<<" -> \n";
				}
			}
		}
		
//-------------------------------------------------------------------------------------------------------
		
};

class stack{
	public:
	stack_node* top;
	
	stack(){
		top = NULL;
	}

//-------------------------------------------------------------------------------------------------------
	
	bool isEmpty(){
		if(top == NULL){
			return true;
		}
		return false;
	}
	
//-------------------------------------------------------------------------------------------------------
	
	void push(stack_node* n){
		
		if(top == NULL){
			top = n;
			
		}
		else{
			n->next = top;
			top = n;
			
		}
		
	}
	
//-------------------------------------------------------------------------------------------------------
	
	void pop(){
		if(isEmpty()){
			cout<<"\nStack Underflow...\n";
		}
		else{
			top = top->next;
		}
	}
	
//-------------------------------------------------------------------------------------------------------
	
	stack_node* top_val(){
		if(isEmpty()){
			cout<<"\nStack Underflow...\n";
		}
		else{
			return top;
		}
	}

//-------------------------------------------------------------------------------------------------------

};
class Game : HashTable{
	protected: 
		char id[10];
		char password[10];
		int score;
		int lifelines;
		int level;
		int total_correct_words;
		int total_wrong_words;
		int total_words_guessed;
		public:
		static int noOfPlayer;
		Game(){
			
			strcpy(id , "ABCD123");
			strcpy(password , "admin123");
			score = 0;
			lifelines = 10;
			level = 1;
			total_correct_words = 0;
			total_wrong_words = 0;
			total_words_guessed = 0;
			
		}
		
//-------------------------------------------------------------------------------------------------------
		
		void PlayGame(HashTable t){
			
			simple_stack s;
			char ch; 
			fstream f;
			fstream tt;
			Game game;
			again:
				system("cls");
			cout << "\n\n\n\n\t\t\t\t\t----------------------------------\n\t\t\t\t\tWELCOME TO WORD GUESSING GAME\n\t\t\t\t\t----------------------------------";
			cout << "\n\t\t\t\t\t 1 : Login To Existent Account.";
			cout << "\n\t\t\t\t\t 2 : Sign-up For New Account.";
			cout << "\n\t\t\t\t\t 3 : Exit\n";
			fflush(stdin);
			cin >> ch;
			if(ch == '1')
			{
				login:
					int flag = 0;
					int is_pass = 0;
					system("cls");
					game.input();
					f.open("gamedata.txt" , ios::in );
					Game g;
					char pass[20];
					while((f.read((char*)&g , sizeof(g))) != NULL){
						if(strcmp( g.id , game.id) == 0){
						
							flag = 1;
							if(strcmp(g.password , game.password) == 0){
								is_pass = 1;
							}
							else{
								strcpy(pass , g.password);
							}
							break;
						}
						
					}
					f.close();
					if(flag == 0)
					{
						cout << "\n\n\t\t\t\t\tSorry, You Are Not Registered, We Are Re-directing You To Sign-up Page.";
						getch();
						goto signup;
						
					}
					if(flag == 1)
					{
						if(is_pass == 1)
						{
							char ch3;
								do{
									system("cls");
									cout << "\n\n\n\n\t\t\t\t\t-----------------------------------------------";
									cout << "\n\t\t\t\t\tWELCOME TO WORD-GUESSING GAME DESIGNED BY 'WHA'";
									cout << "\n\t\t\t\t\t-----------------------------------------------";
									cout << "\n\t\t\t\t\tEnter: ";
									cout << "\n\t\t\t\t\t\t1 : Play";
									cout << "\n\t\t\t\t\t\t2 : Scoreboard";
									cout << "\n\t\t\t\t\t\t3 : Rules";
									cout << "\n\t\t\t\t\t\t4 : Log-out";
									cout << "\n\t\t\t\t\t-----------------------------------------------";
									cout << "\n\t\t\t\t\tEnter Your Choice : ";
									fflush(stdin);
									cin >> ch;
									
									switch(ch){
										case '1':
											system("cls");
											readDataFromFile(game.id);
											playgamewindow(t , s);
											saveDataToFile(game.id);
											break;
											
										case '2':
											system("cls");
											display_scoreboard(game.id);
											break;
										case '3':
											
											system("cls");
											GameRule();
											break;
										case '4':
												goto again;
											break;	
										default:
											cout << "\n\t\t\t\t\tError : Invalid Choice.";		
											getch();	
									}
								}while(ch != '4');
						}
						//if incorrect password
						else if(is_pass == 0)
						{
							incorrect_password:
								
								
							again1:
								system("cls");
								Beep(1000 , 100);
							cout << "\n\n\n\n\t\t\t\t\tIncorrect Password";
							cout << "\n\t\t\t\t\t------------------";
							cout << "\n\t\t\t\t\t 1 : Enter Password Again.";
							cout << "\n\t\t\t\t\t 2 : Forget Password?";
							cout << "\n\t\t\t\t\t 3 : Exit\n";
							
							fflush(stdin);
							char ch1; cin >> ch1;
							
							if(ch1 == '1')
							{
								char p[20];
								system("cls");
								cout << "\n\n\n\n\t\t\t\t\t------------------";
								cout << "\n\t\t\t\t\tEnter Password : ";
									fflush(stdin);
									gets(p);
									
								if(strcmp(p , pass) == 0)
								{
									do{
									system("cls");
									cout << "\n\n\n\n\t\t\t\t\t-----------------------------------------------";
									cout << "\n\t\t\t\t\tWELCOME TO WORD-GUESSING GAME DESIGNED BY 'WHA'";
									cout << "\n\t\t\t\t\t-----------------------------------------------";
									cout << "\n\t\t\t\t\tEnter: ";
									cout << "\n\t\t\t\t\t\t1 : Play";
									cout << "\n\t\t\t\t\t\t2 : Scoreboard";
									cout << "\n\t\t\t\t\t\t3 : Rules";
									cout << "\n\t\t\t\t\t\t4 : Log-out";
									cout << "\n\t\t\t\t\t-----------------------------------------------";
									cout << "\n\t\t\t\t\tEnter Your Choice : ";
									fflush(stdin);
									cin >> ch;
									
									switch(ch){
										case '1':
											system("cls");
											readDataFromFile(game.id);
											playgamewindow(t , s);
											saveDataToFile(game.id);
											break;
										case '2':
											system("cls");
											display_scoreboard(game.id);
											break;
										case '3':
											system("cls");
											GameRule();
											break;
										case '4':
												goto again;
											break;	
										default:
											cout << "\n\t\t\t\t\tError : Invalid Choice.";		
											getch();	
									}
									}while(ch != '4');
								}	
								else
								{
									goto incorrect_password;
								}
							}
							else if(ch1 == '2'){
								char p[20];
								system("cls");
								cout << "\n\n\n\n\t\t\t\t\tPlease Select New Password\n\t\t\t\t\t--------------------------";
								cout << "\n\t\t\t\t\tNOTE: Your ID should'nt exceed 10 letters, you can use characters and Numbers both.";
								cout << "\n\t\t\t\t\tEnter Password : ";
									fflush(stdin);
									gets(p);
									f.open("gamedata.txt" , ios::in );
									tt.open("temp.txt" , ios::out);
									Game g;
									while((f.read((char*)&g , sizeof(g))) != NULL){
										if(strcmp(g.id , game.id) == 0){
											strcpy(g.password , p);
											tt.write((char*)&g , sizeof(g));
										}
										else{
											tt.write((char*)&g , sizeof(g));
										}
									}
									f.close();
									tt.close();
									
									f.open("gamedata.txt" , ios::out );
									tt.open("temp.txt" , ios::in);
									
										while((tt.read((char*)&g , sizeof(g))) != NULL){
											f.write((char*)&g , sizeof(g));
										}
										Beep(1000 , 100);
										cout<<"\n\t\t\t\t\tPassword changed successfully.";
										getch();
										goto again;
										getch();
									f.close();
									tt.close();
									
							}
							else if(ch1 == '3'){
								goto again;
							}
							else
							{
								cout << "\n\n\t\t\t\t\tError: Invalid Choice.";
								getch();
								goto again1;
								
							}
						}
					}
			}
			else if (ch == '2')
			{
				signup:
				int flag = 0;
				system("cls");
				char ch2;
				cout << "\n\n\n\n\t\t\t\t\t-----------------------------";
				cout << "\n\t\t\t\t\t|                           |";
				cout << "\n\t\t\t\t\t|  SIGN-UP FOR NEW ACCOUNT  |";
				cout << "\n\t\t\t\t\t|                           |";
				cout << "\n\t\t\t\t\t-----------------------------";
				cout << "\n\t\t\t\t\t|                           |";
				cout << "\n\t\t\t\t\t|   NOTE: Use Char & Nums   |";
				cout << "\n\t\t\t\t\t|   ---------------------   |";
				cout << "\n\t\t\t\t\t|   Select ID & Password    |";
				cout << "\n\t\t\t\t\t|                           |";
				cout << "\n\t\t\t\t\t-----------------------------";
				cout << "\n\t\t\t\t\t Press any Key to continue.";
				cout << "\n\t\t\t\t\t Press 'E' to Exit.";
				fflush(stdin);
				cin >> ch2;
				if(ch2 == 'E' || ch2 == 'e'){
					goto again;
				}
				else{
				
				system("cls");
				game.input();
				Game g;
				f.open("gamedata.txt" , ios::in);
				while( (f.read((char*)&g , sizeof(g))) != NULL ){
								
					if(strcmp( g.id , game.id ) == 0){
					
						flag = 1;
						break;
					}
				}
				f.close();
				if(flag == 1){
					cout << "\n\n\t\t\t\t\tThis Player Is Already Registered, We Are Re-directing You To Login Page.";
					getch();
					goto login;
				}
				
				if(flag == 0){
					f.open("gamedata.txt" , ios::app);
					f.write((char*)&game , sizeof(g));
					f.close();
					noOfPlayer++;
					cout << "\n\n\t\t\t\t\tCongratulations! You Are Registered Successfully.";
					getch();
								do{
									system("cls");
									cout << "\n\n\n\n\t\t\t\t\t-----------------------------------------------";
									cout << "\n\t\t\t\t\tWELCOME TO WORD-GUESSING GAME DESIGNED BY 'WHA'";
									cout << "\n\t\t\t\t\t-----------------------------------------------";
									cout << "\n\t\t\t\t\tEnter: ";
									cout << "\n\t\t\t\t\t\t1 : Play";
									cout << "\n\t\t\t\t\t\t2 : Scoreboard";
									cout << "\n\t\t\t\t\t\t3 : Rules";
									cout << "\n\t\t\t\t\t\t4 : Log-out";
									cout << "\n\t\t\t\t\t-----------------------------------------------";
									cout << "\n\t\t\t\t\tEnter Your Choice : ";
									fflush(stdin);
									cin >> ch;
									
									switch(ch){
										case '1':
											system("cls");
											readDataFromFile(game.id);
											playgamewindow(t , s);
											saveDataToFile(game.id);
											break;
										case '2':
											system("cls");
											display_scoreboard(game.id);
											break;
										case '3':
											system("cls");
											GameRule();
											
											break;
										case '4':
												goto again;
											break;	
										default:
											cout << "\n\t\t\t\t\tError : Invalid Choice.";		
											getch();	
									}
									}while(ch != '4');
				}
			}
			} 
			else if(ch == '3'){
					return;
			} 
			else{
				cout << "\n\n\t\t\t\t\tError : Invalid Choice.";
				getch();
				goto again;
			}
		}

//-------------------------------------------------------------------------------------------------------
		
		void input(){
			cout << "\n\n\n\n\t\t\t\t\t-------------------";
			cout << "\n\t\t\t\t\tEnter ID : ";
				fflush(stdin);
				gets(id);
				
			cout << "\n\t\t\t\t\t-------------------";
			cout << "\n\t\t\t\t\tEnter Password : ";
				fflush(stdin);
				int i=0;
			for(int i=0 ; i<10 ; i++){
				password[i] =  '\0';
			}
				char ch = _getch();
		   while(ch != 13){//character 13 is enter
		      password[i] = ch;
		      cout << '*';
		      ch = _getch();
		      i++;
		   }
				}
		

//-------------------------------------------------------------------------------------------------------
	
	void saveDataToFile(char idd[]){
		fstream f;
		fstream tt;
		f.open("gamedata.txt" , ios::in);
		tt.open("temp.txt" , ios::out);
		Game g;
		while((f.read((char*)&g , sizeof(g))) != NULL){
			if(strcmp(idd , g.id) == 0){
				g.level = this->level;
				g.score = this->score;
				g.lifelines = this->lifelines;
				g.total_correct_words = this->total_correct_words;
				g.total_words_guessed = this->total_words_guessed;
				g.total_wrong_words = this->total_wrong_words;
													
				tt.write((char*)&g , sizeof(g));
		}
				tt.write((char*)&g , sizeof(g));
	}
		f.close();
		tt.close();							
																		
		f.open("gamedata.txt" , ios::out );
		tt.open("temp.txt" , ios::in);
													
		while((tt.read((char*)&g , sizeof(g))) != NULL){
			f.write((char*)&g , sizeof(g));
			}
		f.close();
	    tt.close();
	}
	
//-------------------------------------------------------------------------------------------------------
	
	void readDataFromFile(char idd[]){
		fstream f;
		int flag = 0;
		f.open("gamedata.txt" , ios::in);
		Game g;
		while((f.read((char*)&g , sizeof(g))) != NULL){
			if(strcmp(g.id , idd ) == 0){
				flag = 1;
				this->level = g.level;
				this->score = g.score;
				this->lifelines = g.lifelines;
				this->total_correct_words = g.total_correct_words;
				this->total_words_guessed = g.total_words_guessed;
				this->total_wrong_words = g.total_wrong_words;
				break;
			}
	}
	if(flag == 0){
				this->level = 1;
				this->score = 0;
				this->lifelines = 10;
				this->total_correct_words  = 0;
				this->total_words_guessed =  0;
				this->total_wrong_words  = 0;
	}
		
	}
	
//-------------------------------------------------------------------------------------------------------
	
	void display_scoreboard(char idd[]){
		fstream f;
		f.open("gamedata.txt" , ios::in);
		Game g;
		while((f.read((char*)&g , sizeof(g))) != NULL){
			if(strcmp(g.id , idd) == 0){
				break;
			}
		}
		
		cout << "\n\n\n\n\t\t\t\t\t-------------------------------------";
		cout << "\n\t\t\t\t\t\t     SCORE-BOARD";
		cout << "\n\t\t\t\t\t-------------------------------------";
		cout << "\n\t\t\t\t\t Level              : " << g.level;
		cout << "\n\t\t\t\t\t Socre              : " << g.score;
		cout << "\n\t\t\t\t\t Lifelines Left     : " << g.lifelines;
		cout << "\n\t\t\t\t\t Total Words Played : " << g.total_words_guessed;
		cout << "\n\t\t\t\t\t Total Win Words    : " << g.total_correct_words;
		cout << "\n\t\t\t\t\t Total Lost Words   : " << g.total_wrong_words;
		cout << "\n\t\t\t\t\t-------------------------------------";
		getch();
		f.close();
	}

//-------------------------------------------------------------------------------------------------------
	
	stack_node* iinterface(HashTable t , simple_stack ss , char w1[]){
		system("cls");
		srand(time(0));
		int n;
		int m;
		int index = 0;
		int o;
		int height;
		int i = 0;
		int length = 0;
		char w2[100];
		int level_update = 0;
		
		if( ss.top_s() != level && total_correct_words % 5 == 0  && total_correct_words > 0){
			level++;
			level_update = 1;	
		}
		total_words_guessed += 1;
		
		cout << "-------------------------------------------------------------------------------------------------------------------------------------";
		cout << "\n\nLifeLines : " << lifelines;
		cout << "\t\t\t\t\t     Level : " << level;
		
		time_t ct = time(0);
		string currenttime = ctime(&ct);
		cout << "\t\t\t\t      Current-Time : " << currenttime ;
		cout << "\n-------------------------------------------------------------------------------------------------------------------------------------\n";
		index = rand() % 26;
		height = t.table[index].height(t.table[index].root); 
		
		if(level_update == 1){
			cout<<"\n\n\t\t\t\t\t\t------------------------------------";
			cout<<"\n\t\t\t\t\t\t   Congratulations! Your Level up   ";
			cout<<"\n\t\t\t\t\t\t------------------------------------\n";
		}
		
		stack s;
		node* r = t.table[index].root;
		
		do{
			
			n = (rand() % height) + 1;
			o = (rand() % height) + 1;
			m = rand() % 100;
	
		if( m % height == n ){
			r = r->right;
		}
		else if(m % height == o){
			r = r->left;
		}
			
			stack_node* n = new stack_node(r);
			s.push(n);
			i++;	
		}while(i != height );
		
		stack_node* nn = s.top_val();
		cout << nn->Node.word<<endl;
		strcpy(w2 , nn->Node.word);
		length = str_len(w2);
		i = 0;
		cout<<"\n\t\t\t\t\t\t\t";
		
		strcpy(w1 , w2);
		
		while(i != length){
			n = rand() % 11;
			if( n % 2 == 0){
				cout<<" _";
				w1[i] = '_';
			}
			else{
				cout<<" "<<w2[i];
			}
			i++;
		}
		return nn;
	}
	
//-------------------------------------------------------------------------------------------------------
	
	void interface2(HashTable t , simple_stack ss , char w1[] ){
		system("cls");
		int level_update = 0;
		int n;
		int m;
		int o;
		int length;
		int index;
		int height;
		if( ss.top_s() != level && total_correct_words % 5 == 0  && total_correct_words > 0){
			level++;
			level_update = 1;	
		}
		total_words_guessed += 1;
		
		cout << "-------------------------------------------------------------------------------------------------------------------------------------";
		cout << "\n\nLifeLines : " << lifelines;
		cout << "\t\t\t\t\t      Level : " << level;
		
		time_t ct = time(0);
		string currenttime = ctime(&ct);
		cout << "\t\t\t\t      Current-Time : " << currenttime ;
		cout << "\n-------------------------------------------------------------------------------------------------------------------------------------";
		index = rand() % 26;
		height = t.table[index].height(t.table[index].root); 
		
		if(level_update == 1){
			cout<<"\n\n\t\t\t\t\t\t------------------------------------";
			cout<<"\n\t\t\t\t\t\t   Congratulations! Your Level up   ";
			cout<<"\n\t\t\t\t\t\t------------------------------------\n";
		}
		
		cout<<"\n\t\t\t\t\t\t\t";
		
		for(int i=0 ; w1[i] != '\0' ; i++){
			cout<<" "<<w1[i];
		}
	}

//-------------------------------------------------------------------------------------------------------

	void playgamewindow(HashTable t , simple_stack ss){
		
		int is_life = 0;
		char h;
		char ch;
		char w[100];
		char w1[100];
		char w2[100];
		stack_node* nn = this->iinterface(t , ss , w);
		strcpy(w2 , nn->Node.word);
		here:
		cout << "\n\n\t\t\t\t\t____________________________________________";
		cout << "\n\t\t\t\t\t|                                          |";
		cout << "\n\t\t\t\t\t|                 Enter                    |";
		cout << "\n\t\t\t\t\t|__________________________________________|";
		cout << "\n\t\t\t\t\t|                                          |";	
		cout << "\n\t\t\t\t\t|   H : If You Want Hint                   |";
		cout << "\n\t\t\t\t\t|   A : To Enter Word                      |";
		cout << "\n\t\t\t\t\t|   L : To Use LIFELINE (i.e Skip Word)    |" ;
		cout << "\n\t\t\t\t\t|   E : To Exit                            |";
		cout << "\n\t\t\t\t\t|__________________________________________|";
		cout << "\n\t\t\t\t\t Enter Your Choice : ";
		fflush(stdin);
		cin >> h;
		
		if( h == 'h' || h == 'H'){
			this->interface2(t , ss , w);
			
			cout<<endl<<"\n\t\t\t\t\tHINT : "<<nn->Node.meaning;
			here2:
				cout << "\n\n\t\t\t\t\t____________________________________________";
				cout << "\n\t\t\t\t\t|                                          |";
				cout << "\n\t\t\t\t\t|                 Enter                    |";
				cout << "\n\t\t\t\t\t|__________________________________________|";
				cout << "\n\t\t\t\t\t|                                          |";
				cout << "\n\t\t\t\t\t|   A : To Enter Word                      |";
				cout << "\n\t\t\t\t\t|   L : To Use LIFELINE (i.e Skip Word)    |" ;
				cout << "\n\t\t\t\t\t|   E : To Exit                            |";
				cout << "\n\t\t\t\t\t|__________________________________________|";
				cout << "\n\t\t\t\t\t Enter Your Choice : ";
				fflush(stdin);
				cin >> ch;
				
				if(ch == 'A' || ch == 'a'){
					goto Enter_word;
				}
				else if(ch == 'L' || ch == 'l'){
					goto Use_lifeline;
				}
				else if(ch == 'E' || ch == 'e'){
					total_wrong_words++;
					return;
				}
				else{
					
					cout<<"\n\t\t\t\t\t Error: Inavlid input.";
					getch();
					this->interface2(t , ss , w);
					goto here2;
				}
		}
		else if(h == 'A' || h == 'a'){
			Enter_word:
				cout<<"\n\t\t\t\t\t Enter Word : ";
				fflush(stdin);
				cin.getline(w1 , 100);
				
				if(Compare(w1, w2 )){
					cout<<"\n\t\t\t\t\t Great You Vocabulist";
					total_correct_words++;
					score++;
					getch();
					playgamewindow(t , ss);
				}
				else{
					cout<<"\n\t\t\t\t\t Wrong Word";
					score--;
					total_wrong_words++;
					cout << "\n\n\t\t\t\t\t Correct Word : "<<w2;
					getch();
					ss.push(level);
					playgamewindow(t , ss);
				}
		}
		else if(h == 'L' || h == 'l')
		{
			Use_lifeline:
			if(lifelines > 0)
			{
				
				lifelines -= 1;
				cout<<"\n\t\t\t\t\t You Have Used LifeLine.";
				getch();
				ss.push(level);
				playgamewindow(t , ss);
				
			}
			else
			{
				
				cout<<"\n\t\t\t\t\t Your LifeLines ended, For More Lifelines Subscribe.";
				getch();
				this->interface2(t , ss , w);
				is_life = 1;
				goto here;
			}
				
		}
		else if(h == 'e' || h == 'E'){
			if(is_life){
				 score--;
			}
			total_wrong_words++;
			return ;
		}
		
		else
		{
			cout<<"\n\t\t\t\t\t Error: Inavlid input.";
			getch();
			this->interface2(t , ss , w);
			goto here;
		}
	
	}
	
//-------------------------------------------------------------------------------------------------------
	
	bool Compare(char w1[] , char w2[])
	{	
		if(w1[0] >=97 && w1[0] <=122){
			w1[0] -= 32;
		}
		
		for(int i=1 ; w1[i] != '\0' ; i++){
			if(w1[i] >=65 && w1[i] <=90 ){
				w1[i] += 32;
			}
		}
		
		if(strcmp(w1 , w2) == 0){
			return true;
		}
		else{
			return false;
		}
	}
	
//-------------------------------------------------------------------------------------------------------
	
};
int Game::noOfPlayer = 0;

//-------------------------------------------------------------------------------------------------------

int str_len(char arr[]){
	int i=0;
	while( arr[i] != '\0'){
		i++;
	}
	return i;
}

//-------------------------------------------------------------------------------------------------------

void intro(){
	char arr[100];
		
		cout << "\n\n\n\n\t\t\t\t\t";
		strcpy(arr ," ------------------------------" );
		DisplayDelayed2(arr);
		cout << "\n\t\t\t\t\t";
		strcpy(arr ,"           WELCOME            " );
		DisplayDelayed2(arr);
		cout << "\n\t\t\t\t\t";
		strcpy(arr ,"------------------------------" );
		DisplayDelayed2(arr);

		cout << "\n\t\t\t\t\t";
		strcpy(arr ,"         Team Members         " );
		DisplayDelayed2(arr);
		cout << "\n\t\t\t\t\t";
		strcpy(arr ,"------------------------------" );
		DisplayDelayed2(arr);
		cout << "\n\t\t\t\t\t                              "; 
		cout << "\n\t\t\t\t\t";
		strcpy(arr ,"          ~Rana Wahaj         " );
		DisplayDelayed2(arr);
		cout << "\n\t\t\t\t\t";
		strcpy(arr ,"            21k-3281          " );
		DisplayDelayed2(arr);
		cout << "\n\t\t\t\t\t                              "; 
		cout << "\n\t\t\t\t\t";
		strcpy(arr ,"          ~Hassan Khan        " );
		DisplayDelayed2(arr);
		cout << "\n\t\t\t\t\t";
		strcpy(arr ,"            21k-4577          " );
		DisplayDelayed2(arr);
		cout << "\n\t\t\t\t\t                              "; 
		cout << "\n\t\t\t\t\t";
		strcpy(arr ,"          ~Ibad Rehman        " );
		DisplayDelayed2(arr);
		cout << "\n\t\t\t\t\t";
		strcpy(arr ,"            21k-4652          " );
		DisplayDelayed2(arr);
		cout << "\n\t\t\t\t\t";
		strcpy(arr ,"------------------------------" );
		DisplayDelayed2(arr);
		getch();
}

//-------------------------------------------------------------------------------------------------------

void dictionary_guide(){
	char arr[1000];
	cout<<"\n\n\n\n\t\t\t\t\t--------------------------------";
	cout<<"\n\t\t\t\t\t      e-Dictionary Guide";
	cout<<"\n\t\t\t\t\t--------------------------------";

	strcpy(arr , "Basic Word Searching: The dictionary includes a wide array of words from the whole English language and can be used to find the meaning of any words you are having trouble with! The dictionary will also offer suggestions in case you want to find the meaning of words you can't spell right!");
	cout<<"\n\n\t"<<"1"<<" : ";DisplayDelayed2(arr);

	strcpy(arr , "The smart dictionary also helps to improve your comprehension skills by making you familiar with a new \"Word Of The Day\" every 24 hours to help you become a better writer! We realize that learning new words can be dull and unexciting, so to solve that problem, we have developed a game that makes you improve your English skills while having fun! The new word guessing game allows you to make your own personalized account that saves your progress. The game is multiplayer as many accounts, all of which are protected by passwords, can be created. But don't worry, if you forget your password, you can always reset your password in the \"Forgot Password\" feature. To find out more about the game, goto user mode->word guessing game->rules.");
	cout<<"\n\n\t"<<"2"<<" : ";DisplayDelayed2(arr);

	strcpy(arr , "To personalize the dictionary, you can always add your own words through the Developer Mode");
	cout<<"\n\n\t"<<"3"<<" : ";DisplayDelayed2(arr);
	
	strcpy(arr , "Any disliked or impractical words can be deleted from your dictionary based on your preferences.");
	cout<<"\n\n\t"<<"4"<<" : ";DisplayDelayed2(arr);
	getch();
}

//-------------------------------------------------------------------------------------------------------

void GameRule(){
	char arr[500];
	cout << "\n\n\n\n\n\t\t\t\t\t-----------------------";
	cout << "\n\t\t\t\t\t   RULES OF THE GAME";
	cout << "\n\t\t\t\t\t-----------------------\n";

	strcpy(arr , "The game consists of a point and level system. The player will be promoted to the next level when they manage to score 5 points on the current level.  A point is awarded upon guessing a word correctly. However, if the guess was incorrect, the player pays the penalty of a point deduction.");
	cout<<"\n";DisplayDelayed2(arr);

	strcpy(arr , "Press 'a' when you have finished guessing without using any hints");
	cout<<"\n\n\t"<<"1"<<" : ";DisplayDelayed2(arr);

	strcpy(arr , "To make a calculated guess, you may use a hint by pressing 'h'. This will show the meaning of the word.");
	cout<<"\n\n\t"<<"2"<<" : ";DisplayDelayed2(arr);
	
	strcpy(arr , "Word too difficult for you? You can always use a lifeline by pressing 'l' to skip the word without a point penalty. ");
	cout<<"\n\n\t"<<"3"<<" : ";DisplayDelayed2(arr);
	
	strcpy(arr , "We believe deserters are losers, so if you close the game after seeing a word, a point penalty will be applied. ");
	cout<<"\n\n\t"<<"4"<<" : ";DisplayDelayed2(arr);
	getch();
}
int main()
{
	
	HashTable t;
	t.upload_data_from_file_to_AVL();
	char ch;
	char ch1;
	char ch2;
	Game g;
	intro();
	do{
		here:
			system("cls");
		cout << "\n\n\n\n\t\t\t\t-------------------------------------";
		cout << "\n\t\t\t\t     WELCOME TO SMART DICTIONARY";
		cout << "\n\t\t\t\t-------------------------------------";
		cout << "\n\t\t\t\tEnter:";
		cout << "\n\t\t\t\t      1 : USER MODE";
		cout << "\n\t\t\t\t      2 : DEVELOPER MODE";
		cout << "\n\t\t\t\t      3 : DICTIONARY GUIDE";
		cout << "\n\t\t\t\t      4 : EXIT";	
		cout << "\n\t\t\t\t-------------------------------------";
		cout << "\n\t\t\t\tEnter Your Choice : "; 
		fflush(stdin);
		cin>>ch;
		
//-------------------------------------------------------------------------------------------------------
		
		if(ch == '1'){
			do{
				here1:
				system("cls");
				cout << "\n\n\n\n\t\t\t\t-------------------------------------";
				cout << "\n\t\t\t\t     WELCOME TO USER SECTION";
				cout << "\n\t\t\t\t-------------------------------------";
				cout << "\n\t\t\t\tEnter:";
				cout << "\n\t\t\t\t      1 : Search Word";
				cout << "\n\t\t\t\t      2 : Word Of The Day";
				cout << "\n\t\t\t\t      3 : Word Guessing Game";	
				cout << "\n\t\t\t\t      4 : Exit";	
				cout << "\n\t\t\t\t-------------------------------------";
				cout << "\n\t\t\t\tEnter Your Choice : "; 
				fflush(stdin);
				cin>>ch1;
				
				switch(ch1){
					case '1':
						t.search_word();
						break;
					case '2':
						flag=1;
						t.wordoftheday();
						break;
					case '3':
						g.PlayGame(t);
						break;	
					case '4':
							continue;
						break;
					default:
							cout << "\n\t\t\t\t\tInvlid Input";
							getch();
							goto here1;		
				}
			}while(ch1 != '4');
		}
		
//-------------------------------------------------------------------------------------------------------
		
		else if(ch == '2'){
			do{
				here2:
				system("cls");
				cout << "\n\n\n\n\t\t\t\t-------------------------------------";
				cout << "\n\t\t\t\t     WELCOME TO DEVELOPER SECTION";
				cout << "\n\t\t\t\t-------------------------------------";
				cout << "\n\t\t\t\tEnter:";
				cout << "\n\t\t\t\t      1 : Insert New Word";
				cout << "\n\t\t\t\t      2 : Delete Word";
				cout << "\n\t\t\t\t      3 : Exit";	
				cout << "\n\t\t\t\t-------------------------------------";
				cout << "\n\t\t\t\tEnter Your Choice : "; 
				fflush(stdin);
				cin>>ch2;
				
				switch(ch2){
					case '1':
						t.Insert_New_word_in_Dictionary();
						break;
					case '2':
						t.Delete_word_from_Dictionary();
						break;
					case '3':
							continue;
						break;
					default:
							cout << "\n\t\t\t\t\tInvlid Input";
							getch();
							goto here2;		
				}
			}while(ch2 != '3');
		}

//-------------------------------------------------------------------------------------------------------
		
		else if (ch == '3'){
			system("cls");
			dictionary_guide();
			continue;
		}

//-------------------------------------------------------------------------------------------------------
		
		else if (ch == '4'){
			continue;
		}
		
//-------------------------------------------------------------------------------------------------------
		
		else{
			cout << "\n\t\t\t\t\tInvlid Input";
			getch();
			goto here;
		}

//-------------------------------------------------------------------------------------------------------				
	}while(ch != '4');

	return 0;

}


