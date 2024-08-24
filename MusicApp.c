#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#define MAX 50
#define SIZE 50
typedef struct tree
{
    int duration;
    int data;
    int height;
    int serial_number, flag;
	char name[20],singer[20],lyricist[20],album[20],composer[20],genre[20];
	struct tree *left;
    struct tree *right;
}tree;
struct strings 
{
    char s[MAX];
};
void appendinfile(tree *root)
{
    tree *temp=root;
    FILE *p;
    p=fopen("playlist.txt","a");
    fprintf(p,"%s\t%s\t%s\t%s\t%s\t%s\t%d\n",temp->name,temp->singer,temp->lyricist,temp->composer,temp->album,temp->genre,temp->duration);
    fclose(p);
    printf("appended\n");
}
//MAX VALUE
int max(int a,int b)
{
    return (a>b)?a:b;
}
//HEIGHT OF TREE
int height(tree *root)
{
    if(root==NULL)
    {
    	return 0;
	}
    else
    {
    	return 1+max(height(root->left),height(root->right));
	}
}
//RIGHT ROTATION
tree *rightRotate(tree *root)
{
    tree *x=root->left;
    tree *T2=x->right;
    x->right = root;
    root->left = T2;
    return x;
}
//LEFT ROTATION
tree *leftRotate(tree *root)
{
    tree *y = root->right;
    tree *T2 = y->left;
    y->left = root;
    root->right = T2;
    return y;
}
//BALANCE FACTOR
int getBalance(tree *root)
{
    if(root==NULL)
    {
    	return 0;
	}
	else
	{
		return height(root->left)-height(root->right);
	}
}
//QUE 1 TO INSERT NODE IN PLAYLIST
tree *insert(tree *root,tree *temp)
{
	if(root==NULL)
    {
    	root=temp;
		return root;
	}
    if(strcmp(temp->name,root->name)<0)
    {
    	root->left=insert(root->left,temp);
	}
    else if(strcmp(temp->name,root->name)>0)
    {
    	root->right=insert(root->right,temp);
	}
    else		//don't accept duplicates
    {
    	return root;
	}
    int balance=getBalance(root);
    if(balance>1 && strcmp(temp->name,root->left->name)<0)
    {
    	root=rightRotate(root);
	}
    if(balance<-1 && strcmp(temp->name,root->right->name)>0)
    {
    	root=leftRotate(root);
	}
    if(balance>1 && strcmp(temp->name,root->left->name)>0)
    {
        root->left=leftRotate(root->left);
        root=rightRotate(root);
    }
    if(balance<-1 && strcmp(temp->name,root->right->name)<0)
    {
        root->right=rightRotate(root->right);
        root=leftRotate(root);
    }
    appendinfile(root);
    return root;
}
//NODE WITH MINIMUM VALUE
tree *minValueNode(tree *root)
{
    tree *nptr=root;
    while (nptr->left!=NULL)
    {
    	nptr=nptr->left;
	}
    return nptr;
}
//QUE 3 DISPLAYING DATA IN ASCENDING AND DESCENDING ORDER
void inorder(tree *root)
{
    if(root!=NULL)
    {
		inorder(root->left);
		printf("%s %s %s %s %s %s %d\n",root->name,root->singer,root->lyricist,root->composer,root->album,root->genre,root->duration);
		inorder(root->right);
    }
}
void reverse(tree *root)
{
    if (root != NULL)
    {
        reverse(root->right);
        printf("%s %s %s %s %s %s %d\n", root->name, root->singer, root->lyricist, root->album, root->composer, root->genre, root->duration);
        reverse(root->left);
    }
}
//QUE 4 DELETE NODE FROM PLAYLIST
tree *deletenode(tree *root,char n[20])
{
    if(root==NULL)
    {
    	return root;
	}
    if(strcmp(n,root->name)<0)
    {
    	root->left=deletenode(root->left,n);
	}
    else if(strcmp(n,root->name)>0)
    {
    	root->right=deletenode(root->right,n);
	}
    else  //node match
    {
    	if((root->left==NULL) || (root->right==NULL))
        {
        	tree *temp;
			if(root->left!=NULL)
			{
				temp=root->left;
			}
			else
			{
				temp=root->right;
			}
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            {
            	*root = *temp;
			}
            free(temp);
        }
        else
        {
            tree *temp = minValueNode(root->right);
            strcpy(root->name,temp->name);
            root->right = deletenode(root->right,temp->name);
        }
    }
    int balance = getBalance(root);
    if(balance>1 && getBalance(root->left)>=0)
    {
		return rightRotate(root);
	}
    if(balance>1 && getBalance(root->left)<0) 
	{
		root->left=leftRotate(root->left);
		return rightRotate(root);
    }
    if(balance<-1 && getBalance(root->right)<=0)
    {
		return leftRotate(root);
	}
    if(balance<-1 && getBalance(root->right)>0)
    {
		root->right = rightRotate(root->right);
		return leftRotate(root);
    }
    return root;
}
//QUE 5 CREATE PLAYLIST BASED ON ATTRIBUTE AND THEIR VALUES
int countMatches(tree *curr_song, int num_attributes, char* attributes[], char* values[])
{
    int matches = 0, i;
    for (i = 0; i < num_attributes; i++) 
    {
        if (strcmp(attributes[i], "singer") == 0 && strcmp(curr_song->singer, values[i]) == 0) 
        {
            matches++;
        }
        else if (strcmp(attributes[i], "lyricist") == 0 && strcmp(curr_song->lyricist, values[i]) == 0) 
        {
            matches++;
        }
        else if (strcmp(attributes[i], "film") == 0 && strcmp(curr_song->album, values[i]) == 0) 
        {
            matches++;
        }
        else if (strcmp(attributes[i], "composer") == 0 && strcmp(curr_song->composer, values[i]) == 0) 
        {
            matches++;
        }
        else if (strcmp(attributes[i], "genre") == 0 && strcmp(curr_song->genre, values[i]) == 0) 
        {
            matches++;
        }
        else if (strcmp(attributes[i], "songName") == 0 && strcmp(curr_song->name, values[i]) == 0) 
        {
            matches++;
        }
        else if (strcmp(attributes[i], "duration") == 0 && curr_song->duration == atoi(values[i])) 
        {
            matches++;
        }
    }
    return matches;
}

void CreatePlaylistHelper(tree *root, char* attributes[], char* values[], int num_attributes, tree** playlist) 
{
	int i=1;
    if (root == NULL) 
	{
        return;
    }
    int matches = countMatches(root, num_attributes, attributes, values);
    if (matches == num_attributes) 
	{
        tree *new_song = (tree*)malloc(sizeof(tree));
        new_song->serial_number=i;
        strcpy(new_song->singer, root->singer);
        strcpy(new_song->lyricist, root->lyricist);
        strcpy(new_song->album, root->album);
        strcpy(new_song->composer, root->composer);
        strcpy(new_song->genre, root->genre);
        strcpy(new_song->name, root->name);
        new_song->duration = root->duration;
        new_song->left = NULL;
        new_song->right = NULL;
        *playlist=insert(*playlist, new_song);
        i++;
    }
    CreatePlaylistHelper(root->left, attributes, values, num_attributes, playlist);
    CreatePlaylistHelper(root->right, attributes, values, num_attributes, playlist);
}
tree *CreatePlaylist(tree *root, char* attributes[], char* values[], int num_attributes) 
{
    tree *playlist = NULL;
    CreatePlaylistHelper(root, attributes, values, num_attributes, &playlist);
    return playlist;
}
void playSong(tree *root)
{
    printf("Title: %s\n", root->name);
    printf("Artist: %s\n", root->singer);
    printf("Lyrics: %s\n", root->lyricist);
    printf("Composer: %s\n", root->composer);
    printf("Genre: %s\n", root->genre);
}

//QUE 6 AND 7  DISPLAYING SONG IN PLAYLIST WITH SERIAL NUMBER AND PRINTING PREVIOUS OR NEXT SONG ACCORDING TO THE PLAYLIST INCLUDING TO DISPLAY KTH PREVIOUS AND NEXT SONG
void displaylisttree(tree *root, int* count) 
{
    if (root == NULL) 
	{
        return;
    }
    displaylisttree(root->left, count);
    printf("%d. %s - %s\n", *count, root->name, root->singer);
    (*count)++;
    displaylisttree(root->right, count);
}
void displayother(tree* root, int* count, int s) 
{
    if (root == NULL) 
	{
        return;
    }
    displayother(root->left, count, s);
    
    if (*count == s+1) 
	{
        printf("\n%d. %s %s %s %s %s %s %d", *count, root->name, root->singer, root->lyricist, root->composer, root->album, root->genre, root->duration);
        return;
    }
    (*count)++;
    displayother(root->right, count, s);
}
void display_song(tree *root, int s) 
{
    if (root == NULL) 
	{
        printf("No songs found.\n");
        return;
    }
    if (s < 0) 
	{
        printf("Invalid serial number.\n");
        return;
    }
    int count = 1;
    displayother(root, &count, s);
}
void display_songs(tree* root) 
{
    int s;
    if (root == NULL) 
	{
        printf("No songs found.\n");
        return;
    }
    int count = 1;
    displaylisttree(root, &count);
    printf("enter serial number of song you want to play.");
    scanf("%d",&s);
    printf("\n%d. %s %s", s-1, root->left->name, root->left->singer);
    display_song(root, s-1);
    printf("\n%d. %s %s", s+1, root->right->name, root->right->singer);
     // Prompt the user to select the next or previous song
    char choice;
    printf("\nEnter 'N' for next song or 'P' for previous song: ");
    scanf(" %c", &choice);
    if(choice=='N')
       display_song(root, s);  
    else if(choice=='P')
        display_song(root, s-2);   
    int k;
    char direction;
    printf("\nEnter the offset 'k': ");
    scanf("%d", &k);
    printf("\nEnter 'U' for up or 'D' for down: ");
    scanf(" %c", &direction);
     if (direction == 'U')
        display_song(root, s-1-k);
    else if (direction == 'D')
          display_song(root, s-1+k);
}

//Q8. DISPLAY DETAILS OF SONG AND CREATE PLAYLIST BASED UPON THE CURRENT SONG ATTRIBUTES
void find_match(tree *root, tree** playlist, int num_attributes, char attributes[][100], char values[][100]) 
{
    if (root == NULL) 
	{
        return;
    }
    int match = 1, i;
    for (i = 0; i < num_attributes; i++) 
	{
        char* attribute_value;
        if (strcmp(attributes[i], "song_name") == 0) 
		{
            attribute_value = root->name;
        } 
		else if (strcmp(attributes[i], "singer") == 0) 
		{
            attribute_value = root->singer;
        } 
		else if (strcmp(attributes[i], "lyricist") == 0) 
		{
            attribute_value = root->lyricist;
        } 
		else if (strcmp(attributes[i], "album") == 0) 
		{
            attribute_value = root->album;
        } 
		else if (strcmp(attributes[i], "composer") == 0) 
		{
            attribute_value = root->composer;
        } 
		else if (strcmp(attributes[i], "genre") == 0) 
		{
            attribute_value = root->genre;
        } 
		else if (strcmp(attributes[i], "duration") == 0) 
		{
            char duration_str[10];
            sprintf(duration_str, "%d", root->duration);
            attribute_value = duration_str;
        } 
		else 
		{
            printf("Invalid attribute: %s\n", attributes[i]);
            return;
        }
        if (strcmp(attribute_value, values[i]) != 0) 
		{
            match = 0;
            break;
        }
    }
    if (match) 
	{
        *playlist = insert(*playlist, root);
    }
    find_match(root->left, playlist, num_attributes, attributes, values);
    find_match(root->right, playlist, num_attributes, attributes, values);
}
tree *create_playlist(tree* root) 
{
    int num_attributes, i;
    printf("Enter number of attributes to match: ");
    scanf("%d", &num_attributes);
    char attributes[num_attributes][100];
    char values[num_attributes][100];
    for (i = 0; i < num_attributes; i++) 
	{
        printf("Enter attribute %d: ", i+1);
        scanf("%s", attributes[i]);
        printf("Enter value for attribute %s: ", attributes[i]);
        scanf("%s", values[i]);
    }
    tree* playlist = NULL;
    find_match(root, &playlist, num_attributes, attributes, values);
    return playlist;
}
tree *search_song(tree* root, char* name) 
{
    if (root == NULL)
        return NULL;
    // Compare the song name with the current node
    int cmp = strcmp(name, root->name);
    if (cmp == 0) // Found the song
        return root;
    else if (cmp < 0) // Search in the left subtree
        return search_song(root->left, name);
    else // Search in the right subtree
        return search_song(root->right, name);
}
void create_playlist_by_attributes(tree* root)
{
	inorder(root);
	  // Prompt the user to select a song
    char selection[20];
    printf("Enter the song name: ");
    scanf("%s", &selection);
    tree *current=search_song(root, selection);
    if (current == NULL) 
	{
        printf("Song not found");
        return;
    }
    //printf("\nSong details: %s %s %s %s %s %s %d\n", current->name, current->singer, current->lyricist, current->composer, current->album, current->duration);
     // Allow the user to select one or more attributes of the current song
    inorder(current);
    printf("Select one or more attributes of the current song to create a playlist for:\n");
    printf("1. Singer  ");
    printf("2. Lyricist  ");
    printf("3. Album  ");
    printf("4. Composer  ");
    printf("5. Genre  \n");
	tree* playlist2 = create_playlist(root);
   printf("Playlist:\n");
   playSong(playlist2);
}

//QUE 9 FILTERING THE PLAYLIST ACCORDING TO ATTRIBUTE
tree *filter(tree *root,char attributes[20],char values[20])
{
	tree *lptr;
	lptr=NULL;
	char val[20];
	if(root=NULL)
	{
		return root;
	}
	if (strcmp(attributes,"singer") == 0) 
	{
        strcpy(val,root->singer);
    } 
	else if (strcmp(attributes,"lyricist") == 0) 
	{
        strcpy(val,root->lyricist);
    } 
	else if (strcmp(attributes,"album") == 0) 
	{
        strcpy(val,root->album);
    } 
	else if (strcmp(attributes,"composer") == 0) 
	{
        strcpy(val,root->composer);
    } 
	else if (strcmp(attributes,"genre") == 0) 
	{
        strcpy(val,root->genre);
    }
	else 
	{
        return NULL;  // Invalid attribute name
    }
    if(strcmp(val,values)!=0)
    {
    	root->left=filter(root->left,attributes,values);
	}
	else
	{
		lptr=insert(lptr,root);
	}
	root->right=filter(root->right,attributes,values);
	inorder(lptr);
	return lptr;
}
//QUE 11 RANGE SEARCH OPERATION
void range(tree *root,char x[20],char y[20])
{
	if(root==NULL)
	{
   		return;
	}   
	if(strcmp(x,root->name)<0)
	{
		range(root->left,x,y);
	}
	if (strcmp(x,root->name)<=0 && strcmp(y,root->name)>=0 )
	{
		printf("%s %s %s %s %s %s %d\n",root->name,root->singer,root->lyricist,root->composer,root->album,root->genre,root->duration);
	}    
	range(root->right,x,y);
}
//QUE 10 SHUFFLE TO SOMETHING ELSE
int getsongindex(int count) 
{
    int song_index;
    int played[song_index];
    do 
	{
        song_index = rand() % count;
    } while (played[song_index] == 1);
    return song_index;
}

void getsongs(tree* root, tree** songs, int* count) 
{
    if (root == NULL) 
	{
        return;
    }
    getsongs(root->left, songs, count);
    songs[*count] = root;
    (*count)++;
    getsongs(root->right, songs, count);
}
void shuffle_playlist(tree *root) 
{
    int count = 0, i, song_index;
    tree* songs[MAX];
    int played[song_index];
    getsongs(root, songs, &count);
    srand(time(NULL));
    // Shuffle the songs
    for (i = 0; i < count; i++) 
	{
        int j = rand() % count;
        tree* temp = songs[i];
        songs[i] = songs[j];
        songs[j] = temp;
    }
    // Play the shuffled playlist
    for (i = 0; i < count; i++) 
	{
        int song_index = getsongindex(count);
        printf("Playing %s by %s\n", songs[song_index]->name, songs[song_index]->singer);
        played[song_index] = 1;
    }
    // Reset the played flags for the next shuffle
    for (i = 0; i < count; i++) 
	{
        played[i] = 0;
    }
}

int main()
{
	struct tree *root = NULL;
	int ch, i, index, listCount = -1, sno, numOfAtt, dataBaseCount = 0;
	char attributes[20], values[20], song1[20], song2[20], singer[20], album[20], genre[20];
	tree *new_playlist[MAX];
	while(ch!=11)
	{
		printf("1.Insert()\n2.Display()\n3.Print in Ascending and Descending order\n4.Delete()\n5.Create playlist by attribute and Values\n6.Details of Songs according to serial number as well as showing the kth previous or next song\n7.Creating playlist based upon attributes of current song\n8.Filter Playlist based on Attributes\n9.Shuffle to something else\n10.Range Search based on two values\n11.exit\n");
		printf("enter your choice:");
		scanf("%d",&ch);
		if(ch==1)			//Q1.insert
		{
			tree *temp=(tree*)malloc(sizeof(tree));
		    printf("enter song name:");
			gets(temp->name);
			gets(temp->name);
			printf("enter singer name:");
			gets(temp->singer);
			printf("enter lyricist name:");
			gets(temp->lyricist);
			printf("enter composer name:");
			gets(temp->composer);
			printf("enter film/album name:");
			gets(temp->album);
			printf("enter genre name:");
			gets(temp->genre);
			printf("enter song duration:");
			scanf("%d", &temp->duration);
			temp->left=NULL;
    		temp->right=NULL;
			root=insert(root,temp);
		}
		else if(ch==2)			//Q.2 display
		{
			printf("Displaying the data stored as inorder in AVL tree. \n");
			inorder(root);
			printf("\n");
		}
		else if(ch==3)			//Q3. Ascending and descending
		{
			inorder(root);
			printf("\n");
			reverse(root);
			printf("\n");
		}
		else if(ch==4)			//Q4.Delete
		{
			char n[20],a[20];
			printf("enter name of song:");
			gets(n);
			gets(n);
			root=deletenode(root,n);
			printf("enter name of artist:");
			gets(a);
			root=deletenode(root,a);
		}
		else if(ch==5)			//Q5. CREATE PLAYLIST BASED ON ATTRIBUTE
		{
			printf("\nCreating a playlist based on attribute and Values : ");
			create_playlist(root);
		}
		else if(ch==6)			//Q6 AND Q7
		{
			printf("\nDisplaying details of the song according to serial number\n");
			display_songs(root);
		}
		else if(ch==7)          //Q8
		{
			create_playlist_by_attributes(root);
		}
		else if(ch==8)			//Q9
		{
			char attri[20],val[20];
			printf("Enter the attribute:");
			scanf("%s", &attributes[i]);
			printf("Enter the value:");
			scanf("%s", &values[i]);
			filter(root,attributes,values); 
		}
		else if(ch==9)			//Q10
		{
			shuffle_playlist(root);
		}
		else if(ch==10)			//Q11
		{
			printf("enter 2 songs:");
			gets(song1);
			gets(song2);
			gets(song2);
			range(root,song1,song2);
		}
		else if(ch==11)
		{
			break;
		}
	}
	return 0;
}
