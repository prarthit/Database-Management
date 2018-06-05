#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
#define COUNT 10
//NOTE : I also have a print tree function if you would like to display how the tree looks remove all comments before
//       and after print functions and also switch statement
int maxi=-1,mini=-1,flags=0;

struct tree 
{
	struct tree *left;
	struct tree *right;
	int salary;
	int height;
	int frequency;
};

struct tree *createNode(int salary)
{
	struct tree *tempNode;

	tempNode=new tree;
	tempNode->height=1;
	tempNode->salary=salary;
	tempNode->left=NULL;
	tempNode->right=NULL;
	tempNode->frequency=1;
	
	return tempNode;
}

int height(struct tree *tempNode)
{
	if(tempNode==NULL)
	{
		return 0;
	}
	return (tempNode->height);
}

int max(int a, int b)
{
    return (a >= b)? a : b;
}

struct tree *leftRotate(struct tree *z)
{
	struct tree *y,*yleftchild;
	
	y=z->right;
	yleftchild=y->left;
	y->left=z;
	z->right=yleftchild;
	
	z->height = 1+max(height(z->left), height(z->right));
    y->height = 1+max(height(y->left), height(y->right));

	return y;
}

struct tree *rightRotate(struct tree *z)
{
	struct tree *y,*yrightchild;
	
	y=z->left;
	yrightchild=y->right;
	y->right=z;
	z->left=yrightchild;
	
	z->height = 1+max(height(z->left), height(z->right));
    y->height = 1+max(height(y->left), height(y->right));

	return y;
}

int getDiffer(struct tree *tempNode)
{
    if (tempNode == NULL)
    {
	   return 0;
	}
    return (height(tempNode->left) - height(tempNode->right));
}

struct tree *minValueNode(struct tree *tempNode)
{
	if(tempNode==NULL)
	return tempNode;
	else
	{
		if(tempNode->left==NULL)
		return tempNode;
		else
		{
			tempNode=minValueNode(tempNode->left);
		}
	}
}

struct tree *maxValueNode(struct tree *tempNode)
{
	if(tempNode==NULL)
	return tempNode;
	else
	{
		if(tempNode->right==NULL)
		return tempNode;
		else
		{
			tempNode=maxValueNode(tempNode->right);
		}	
	}
}

struct tree *insertTree(struct tree *root,int salary)
{
	if(root==NULL)
	{
		return createNode(salary);
	}
	
	else if(salary<root->salary)
	root->left=insertTree(root->left,salary);
	
	else if(salary>root->salary)	
	root->right=insertTree(root->right,salary);
	
	else
	{
		root->frequency++;
		return root;
	}
	
	root->height = 1 + max(height(root->left),height(root->right));
	
	int differ = getDiffer(root);
	
	//right left
	if(differ<-1 && salary<(root->right->salary))
	{
		root->right=rightRotate(root->right);
		return leftRotate(root);
	}
	
	//right right
	else if(differ<-1 && salary>(root->right->salary))
	{
		return leftRotate(root);
	}
	//left right
	else if(differ>1 && salary>root->left->salary)
	{
		root->left=leftRotate(root->left);
		return rightRotate(root);
	}
	
	//left left
	else if(differ>1 && salary<root->left->salary)
	{
		return rightRotate(root);
	}	
	//unchanged
	else
	{
		return root;
	}

}

struct tree *deleteTree(struct tree *root, int salary)
{
    if (root == NULL)
        return root;
        
    if((root->salary)<salary && root->salary>mini)
    {
    	mini=root->salary;
	}
	
	if((root->salary)>=salary && root->salary<=maxi)
    {
    	maxi=root->salary;
    	flags=1;
	}
	
    if ( salary < root->salary )
    {
    	if(root->left==NULL)
    	{
    		if(mini==-1 || flags==0)
    		{
    			int t = mini=-1 ? maxi : mini;
    			cout<<"\n\nSorry the given salary doesnot exist but closest salary is "<<t<<endl;
			}
			
			else
			{
				int a=salary-mini,b=maxi-salary;
				if(a<b)
				{
					cout<<"\n\nSorry the given salary doesnot exist but closest salary is "<<mini<<endl;
				}
				else if(b<a)
				{
					cout<<"\n\nSorry the given salary doesnot exist but closest salary is "<<maxi<<endl;
				}
				else
    			cout<<"\n\nSorry the given salary doesnot exist but closest salaries are "<<mini<<" and "<<maxi<<endl;
			}
		}
        root->left = deleteTree(root->left, salary);
    }
        
 
    else if( salary > root->salary )
    {
    	if(root->right==NULL)
    	{
    		if(mini==-1 || flags==0)
    		{
    			int t;
    			if(flags==0)
    			t=mini;
    			else
    			t=maxi;
    			cout<<"\n\nSorry the given salary doesnot exist but closest salary is "<<t<<endl;
    			cout<<flags;
			}
			else
    		{
    			int a=salary-mini,b=maxi-salary;
				if(a<b)
				{
					cout<<"\n\nSorry the given salary doesnot exist but closest salary is "<<mini<<endl;
				}
				else if(b<a)
				{
					cout<<"\n\nSorry the given salary doesnot exist but closest salary is "<<maxi<<endl;
				}
				else
    			cout<<"\n\nSorry the given salary doesnot exist but closest salaries are "<<mini<<" and "<<maxi<<endl;
    		}
		}
        root->right = deleteTree(root->right, salary);
    }

    else
    {
    	if(root->frequency<=1)
    	{
		
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct tree *temp = root->left ? root->left : root->right;
 
            if (temp == NULL)    //doesnot hv any child
            {
                temp = root;
                root = NULL;
            }
            
			else //has one child
			*root = *temp; 
			
            free(temp);
            temp=NULL;
        }
        else  //has two subtrees i.e. 2 children
        {
            
            struct tree *temp = minValueNode(root->right);
 
            root->salary = temp->salary;
            root->frequency = temp->frequency;
            temp->frequency=1;

            root->right=deleteTree(root->right,temp->salary);
        }
    }
    
    else
    root->frequency--;
    
	}
    
    if (root == NULL)
      return root;
 
    root->height = 1 + max(height(root->left),height(root->right));
 
    int differ = getDiffer(root);

    // Left Left
    if (differ > 1 && getDiffer(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right
    if (differ > 1 && getDiffer(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right
    if (differ < -1 && getDiffer(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left
    if (differ < -1 && getDiffer(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}

/*void print2DUtil(struct tree *root, int space)
{
    if (root == NULL)
        return;
 
    space += COUNT;
 
    print2DUtil(root->right, space);
 
    cout<<"\n";
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    printf("%d|%d\n", root->salary,root->frequency);
 
    print2DUtil(root->left, space);
}

void print2D(struct tree *root)
{
   print2DUtil(root, 0);
}*/

int range(struct tree *root,int num1,int num2)
{
	int cc=0;
	if(root==NULL)
	return 0;
	
	if((root->salary>=num1 && root->salary<=num2))
	{
		cc+=root->frequency;
		if(maxValueNode(root->left)!=NULL && maxValueNode(root->left)->salary>=num1)
		{
			cc=cc+range(root->left,num1,num2);
		}
	
		if(minValueNode(root->right)!=NULL && minValueNode(root->right)->salary<=num2)
		{
			cc+=range(root->right,num1,num2);
		}
	}
	else if(maxValueNode(root->left)!=NULL && maxValueNode(root->left)->salary>=num1)
		{
			cc=cc+range(root->left,num1,num2);
		}
	else if(minValueNode(root->right)!=NULL && minValueNode(root->right)->salary<=num2)
		{
			cc+=range(root->right,num1,num2);
		}
	
	return cc;
}


int main()
{
	struct tree *root=NULL;
	
	ifstream inn("abc.txt");
	int num,i=0;
	
	inn>>num;
	int arrnum[num],sizeofarr=num;
	
	while(inn>>num)
	{
	//	root=insertTree(root,num);
		arrnum[i]=num;
		i++;
	}

	for(i=0;i<sizeofarr;i++)
	{
		root=insertTree(root,arrnum[i]);
	}
	
	int choice=1;
	while (choice!=6)
    {
        cout<<"\n";
        cout<<"1 - Add a salary to the database."<<endl;
        cout<<"2 - Remove a salary from the database."<<endl;
        cout<<"3 - No of employees in a given range in the database."<<endl;
        cout<<"4 - Maximum salary in the database."<<endl;
        cout<<"5 - Minimum salary in the database."<<endl;
        cout<<"6 - Exit"<<endl;
    //    cout<<"7 - Display tree"<<endl;
        
        cout<<"Enter your Choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter salary to be inserted: ";
            int salary;
            cin>>salary;
            root = insertTree(root,salary);
            break;
            
        case 2:
        	if (root == NULL)
            {
                cout<<"Sorry the database has no entries"<< endl;
            }
            else
            {
        		int salary;
        		cout<<"Enter salary to be deleted: ";
        		cin>>salary;
        		maxi=root->salary;
        		flags=0;
            	root = deleteTree(root,salary);
            	mini=-1;
            }
			break;
			
        case 3:
            if (root == NULL)
            {
                cout<<"Sorry the database has no entries"<< endl;
            }
			else
			{
				int n1,n2;
				cout<<"Enter lowerbound : ";
				cin>>n1;
				
				cout<<"Enter upperbound : ";
				cin>>n2;
                int cnt=range(root,n1,n2);
				cout<<"\nNo of employees with salaries in this range are "<<cnt<<endl;
            }
            break;
            
        case 4:
            if (root == NULL)
            {
                cout<<"Sorry the database has no entries"<< endl;
            }
			else
			{
				struct tree *temp;
				temp=maxValueNode(root);	
                cout<<"The maximum salary in the database is  "<<temp->salary<<endl; 
            }
             break;
            
        case 5:
            if (root == NULL)
            {
                cout<<"Sorry the database has no entries"<< endl;
            }
			else
			{
				struct tree *temp;
				temp=minValueNode(root);	
                cout<<"The minimum salary in the database is  "<<temp->salary<<endl; 
            }
             break;
             
        case 6:
        	cout<<"THANK YOU"<<endl;
        	break;
             
     /*   case 7:
        	cout<<"Your database looks like : \n"<<endl;
        	print2D(root);
        	break;*/
             
    	default:
    		cout<<"Sorry wrong choice"<<endl;
            
        }
    }
	
	return 0;
}

