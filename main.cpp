#include <iostream>
#include<queue>
#include<stack>
#include<vector>
#include<algorithm>
#include<math.h>
using namespace std;

class node
{
  public:
  int data;
  node*next;
  node(int data)
  {
    this->data=data;
    next=NULL;
  }
};
template<typename T>
class binarytreenode
{
  public:
  int data;
  binarytreenode *left;
  binarytreenode *right; 
  binarytreenode(T data)
  {
    this->data=data;
    left=NULL;
    right=NULL;
  }
  ~binarytreenode()
  {
    delete left;
    delete right;
  }
};
void printtree(binarytreenode<int> *root)
{
  if(root==NULL)
  {
    return;
  }
  cout<<root->data<<":";
  if(root->left!=NULL)
  {
    cout<<"L"<<root->left->data<<" ";
  }
  if(root->right!=NULL)
  {
    cout<<"R"<<root->right->data<<" ";
  }
  cout<<endl;
  printtree(root->left);
  printtree(root->right); 
}
binarytreenode<int> *takeinput()
{
  int rootdata;
  cout<<"enter rootdata"<<endl;
  cin>>rootdata;
  if(rootdata==-1)
  {
    return NULL;
  }
  binarytreenode<int> *root= new binarytreenode<int>(rootdata);
  queue<binarytreenode<int>*> pendingnodes;
  pendingnodes.push(root);
  while(pendingnodes.size()!=0)
  {
    binarytreenode<int> *front = pendingnodes.front();
    pendingnodes.pop();
    cout<<"enter left child of"<<front->data<<endl;
    int leftchilddata;
    cin>>leftchilddata;
    if(leftchilddata!=-1)
    {
      binarytreenode<int> *child = new binarytreenode<int>(leftchilddata);
      front->left=child;
      pendingnodes.push(child);
    }
    cout<<"enter right child of"<<front->data<<endl;
    int rightchilddata;
    cin>>rightchilddata;
    if(rightchilddata!=-1)
    {
      binarytreenode<int> *child= new binarytreenode<int>(rightchilddata);
      front->right=child;
      pendingnodes.push(child);
    }
  }
  return root; 
}
int numnodes(binarytreenode<int>*root)
{
  if(root==NULL)
  {
    return 0;
  }
  return 1+numnodes(root->left)+numnodes(root->right); 
}
void inorder(binarytreenode<int>*root)
{
  if(root ==NULL)
  {
    return;
  }
  inorder(root->left);
  cout<<root->data<<" ";
  inorder(root->right);
}
void preorder(binarytreenode<int>*root)
{
  if(root ==NULL)
  {
    return;
  }
  cout<<root->data<<" ";
  inorder(root->left);
  inorder(root->right);
}
void postorder(binarytreenode<int>*root)
{
  if(root ==NULL)
  {
    return;
  }
  inorder(root->left);
  inorder(root->right);
  cout<<root->data<<" ";
}
binarytreenode<int>*buildtreehelper(int *in,int *pre,int inS,int inE,int preS,int preE )
{
  if(inS>inE)
  {
    return NULL;
  }
  int rootdata=pre[preS];
  int rootindex=-1;
  for(int i=inS;i<=inE;i++)
  {
    if(in[i]==rootdata)
    {
      rootindex=i;
      break;
    }
  }
  int linS=inS;
  int linE=rootindex-1;
  int rinS=rootindex+1;
  int rinE=inE;
  int lpreS=preS+1;
  int lpreE=lpreS+linE-linS;
  int rpreS=lpreE+1;
  int rpreE=preE;
  binarytreenode<int>*root = new binarytreenode<int>(rootdata);
  root->left=buildtreehelper(in,pre,linS,linE,lpreS,lpreE);
  root->right=buildtreehelper(in, pre, rinS, rinE, rpreS, rpreE);
  return root;
}
binarytreenode<int>*buildtree(int *in,int *pre,int size)
{
  return buildtreehelper(in, pre, 0, size-1, 0, size-1);
}
int maximum(binarytreenode<int>*root)
{
  if(root==NULL)
  {
    return INT16_MIN;
  }
  return max(root->data,max(maximum(root->left),maximum(root->right)));
}
int minimum(binarytreenode<int>*root)
{
  if(root==NULL)
  {
    return INT16_MAX;
  }
  return min(root->data,min(minimum(root->left),minimum(root->right)));
}
bool isBST(binarytreenode<int>*(root))
{
  if(root==NULL)
  {
    return true;
  }
  int leftmax = maximum(root->left);
  int rightmin = minimum(root->right);
  bool output = (root->data>leftmax)&&(root->data<=rightmin)&& isBST(root->left) && isBST(root->right);
  return output;
}
vector<int> *roottonodepath(binarytreenode<int>*root,int data)
{
  if(root==NULL)
  {
    return NULL;
  }
  if(root->data==data)
  {
    vector<int>*output = new vector<int>();
    output->push_back(root->data);
    return output;
  }
  vector<int>*leftoutput = roottonodepath(root->left, data);
  if(leftoutput!=NULL)
  {
    leftoutput->push_back(root->data);
    return leftoutput;
  }
  vector<int>*rightoutput = roottonodepath(root->right, data);
  if(rightoutput!=NULL)
  {
    rightoutput->push_back(root->data);
    return rightoutput;
  }
  else
  {
    return NULL;
  }
}
int tree_height(binarytreenode<int>* root)
{
  if (root == NULL)
  {
    return 0;
  }
  int left_height = tree_height(root->left);
  int right_height = tree_height(root->right);
  return max(left_height, right_height) + 1;
}
bool is_balanced(binarytreenode<int>*root)
{
  if(root==NULL)
  {
    return true;
  }
  int leftheight = tree_height(root->left);
  int rightheight =tree_height(root->right);
  if(abs(leftheight-rightheight)<=1)
  {
    return true;
  }
  return false;
}
void printlevelwise(binarytreenode<int>*root)
{
  queue<binarytreenode<int>*> pendingnodes;
  pendingnodes.push(root);
  pendingnodes.push(NULL);
  while(!pendingnodes.empty())
  {
    binarytreenode<int>* front= pendingnodes.front();
    pendingnodes.pop();
    if(front ==NULL)
    {
      cout<<"\n";
      if(!pendingnodes.empty())
      {
        pendingnodes.push(NULL);
      }
    }
    else
    {
      cout<<front->data<<" ";
      if(front->left!=NULL)
      {
        pendingnodes.push(front->left);
      }
      if(front->right!=NULL)
      {
        pendingnodes.push(front->right);
      }
    }
  }
}
binarytreenode<int>*removeleafnodes(binarytreenode<int>*root)
{
  if(root==NULL)
  {
    return root;
  }
  if(root->left==NULL && root->right==NULL)
  {
    return NULL;
  }
  root->left=removeleafnodes(root->left);
  root->right=removeleafnodes(root->right);
  return root;
}
vector<node*>constructlinkedlistlevelwise(binarytreenode<int>*root)
{
  vector<node *> output;
  if(root==NULL)
  {
    return output;
  }
  queue<binarytreenode<int>*> pendingnodes;
  node* head=NULL;
  node* tail= NULL;
  int currentlevelremaining=1;
  int nextlevelcount=0;
  while(!pendingnodes.empty())
  {
     binarytreenode<int>* first = pendingnodes.front();
     pendingnodes.pop();
     node * newnode= new node(first->data);
     if(head==NULL)
     {
       head=newnode;
       tail=newnode;
     }
     else
     {
       tail->next=newnode;
       tail= newnode;
     }
     if(first->left!=NULL)
     {
       pendingnodes.push(first->left);
       nextlevelcount++;
     }
     if(first->right!=NULL)
     {
       pendingnodes.push(first->right);
       nextlevelcount++;
     }
     currentlevelremaining--;
     if(currentlevelremaining==0)
     {
       output.push_back(head);
       head=NULL;
       tail=NULL;
       currentlevelremaining=nextlevelcount;
       nextlevelcount=0;
     }
  }
  return output;
}
void nodewithoutsiblings(binarytreenode<int>*root)
{
  if(root==NULL)
  {
    return;
  }
  else if(root->left!=NULL && root->right==NULL)
  {
    cout<<root->left->data<<" ";
  }
  else if(root->left==NULL && root->right!=NULL)
  {
    cout<<root->right->data<<" ";
  }
  nodewithoutsiblings(root->left);
  nodewithoutsiblings(root->right);
}
void insertduplicatenode(binarytreenode<int>*root)
{
  if(root==NULL)
  {
    return;
  }
  binarytreenode<int>*duplicate=new binarytreenode<int>(root->data);
  binarytreenode<int>*rootleft=root->left;
  root->left=duplicate;
  duplicate->left=rootleft;
  insertduplicatenode(root->right);
  insertduplicatenode(rootleft);
}
void converttreetoarray(binarytreenode<int>*root,vector<int>&output)
{
  if(root==NULL)
  {
    return;
  }
  output.push_back(root->data);
  converttreetoarray(root->left,output);
  converttreetoarray(root->right, output);
}
void pairsum(binarytreenode<int>*root,int sum)
{
  vector<int> output;
  converttreetoarray(root,output);
  sort(output.begin(),output.end());
  int j=output.size()-1;
  for(int i=0;i<j;i++)
  {
    if(output[i]+output[j]==sum)
    {
      cout<<output[i]<<" "<<output[j]<<"\n";
    }
  }
}
int main()
{ 
  binarytreenode<int>*root = takeinput();
  printtree(root);
  cout<<endl; 
  cout<<"no. of nodes"<<numnodes(root);
  cout<<endl;
  inorder(root);
  cout<<endl;
  postorder(root);
  cout<<endl;
  preorder(root);
  cout<<endl;
  cout<<is_balanced(root);
  cout<<endl;
  printlevelwise(root);
  cout<<endl;
  pairsum(root, 8);
  cout<<endl;
  nodewithoutsiblings(root);
  cout<<endl;
  removeleafnodes(root);
  printtree(root);
  cout<<endl;
  insertduplicatenode(root);
  printtree(root);
  delete(root);
} 