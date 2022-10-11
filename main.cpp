#pragma once
#include<iostream>
//#include<string>
#include<queue>
#include<vector>
#include<math.h>

using namespace std;

//二叉树的节点
class Linknode
{
public:
    Linknode();
    int data;
    Linknode* left;//左子节点
    Linknode* right;//右子节点
};
Linknode::Linknode()
{

    left = NULL;
    right = NULL;
}


//二叉树
class Tree
{
public:

    Tree();
    Linknode* root;//记录二叉树的根
    int nodenum;//记录二叉树节点的数量

    //创建一个二叉树
    void Gettree(Linknode* root);
    //二叉树的前序遍历打印
    void pre_order(Linknode* root);
    //二叉树的中序遍历打印
    void in_order(Linknode* root);
    //二叉树的后序遍历打印
    void post_order(Linknode* root);
    //二叉树的层序遍历打印
    void level_order(Linknode* root);
    //返回二叉树节点的数量
    int LNnum(Linknode* root);
    //返回二叉树第k层节点的个数(这里采用函数的重载)
    int Lnnum(Linknode* root,int k);
    //返回二叉树的深度
    int depth(Linknode* root);
    //返回节点存储值为val的第一个节点
    Linknode* Find(Linknode* root, int val);
    //判断二叉树是否为完全二叉树
    bool Iscomplete(Linknode* root);
    //销毁二叉树
    void clear(Linknode* root);
};


Tree::Tree()
{
    root = NULL;
    nodenum = 1;
}

//创建一个二叉树
//根据层序遍历的原理创建一个二叉树，一层一层创建节点
//当没有左子节点，或者右子节点时，输入-1即可
//输入的时候记得小心！！！
void Tree::Gettree(Linknode* root)
{
    queue<Linknode*> q;
    if (root == NULL)
        return;
    q.push(root);
    while (!q.empty())
    {
        cout << "请输入此节点的左字节点的值" << endl;
        q.front()->left = new Linknode;
        cin >> q.front()->left->data;
        if (q.front()->left->data == -1)
        {
            delete q.front()->left;
            q.front()->left = NULL;
        }
        else
        {
            q.push(q.front()->left);
            this->nodenum++;
        }
        cout << "请输入此节点的右字节点的值" << endl;
        q.front()->right = new Linknode;
        cin >> q.front()->right->data;
        if (q.front()->right->data == -1)
        {
            delete q.front()->right;
            q.front()->right = NULL;
        }
        else
        {
            q.push(q.front()->right);
            this->nodenum++;
        }
        q.pop();
    }
}

//二叉树的前序遍历打印(方法一：采用递归方式)
//访问根节点，按前序遍历左子树，按前序遍历右子树
void Tree::pre_order(Linknode* root)
{
    if (root == NULL)//空节点，不打印（也可以打印空）
        return;//递归返回
    cout << root->data;//打印本节点

    pre_order(root->left);//遍历左子树，左节点作为左子树的根
    pre_order(root->right);//遍历右子树，右节点作为右子树的根
}

//二叉树的中序遍历打印
//按中序遍历左子树，访问根节点，按中序遍历右子树。特别的 ，对于二叉树搜索树，中序遍历可以获得一个由大到小或由小到大的有序序列
void Tree::in_order(Linknode* root)
{
    if (root != NULL)
        in_order(root->left);
    else
        return;
    cout << root->data;//打印本节点
    in_order(root->right);
}

//二叉树的后序遍历打印
//按后序遍历左子树，按后序遍历右子树，访问根节点
void Tree::post_order(Linknode* root)
{
    if (root != NULL)
        post_order(root->left);
    else
        return;
    post_order(root->right);
    cout << root->data;
}

//二叉树的层序遍历打印
void Tree::level_order(Linknode* root)
{
    //先将根结点入队，根据队列先进先出的性质。当上一层的结点出队的时候，把下一层的结点入队......
    queue<Linknode*> q;//创建队列
    if (root == NULL)//空树不打印
        return;
    q.push(root);//将根入队
    cout << root->data;//打印本节点
    while (!q.empty())
    {
        if (q.front()->left)//左子节点是否为空
        {
            q.push(q.front()->left);//不为空入队
            cout << q.front()->left->data;//打印节点

        }
        if (q.front()->right)//右子节点是否为空
        {
            q.push(q.front()->right);//不为空入队
            cout << q.front()->right->data;//打印节点
        }
        q.pop();//将父节点删除
    }//循环直到没有节点
}

//返回二叉树节点的数量
int Tree::LNnum(Linknode* root)
{
    return this->nodenum;
}

//返回二叉树第k层节点的个数(这里采用函数的重载)
int Tree::Lnnum(Linknode* root, int k)
{
    queue<Linknode*> q;//同层序遍历相似
    if (root == NULL)
        return 0;
    if (k == 0)
        return 1;
    q.push(root);
    int floor = 1;//层数
    int fnum = 1;//上一层的节点数
    int arr[100] = { 0 };//创建一个数组，存储k层的节点数
    while (!q.empty()&&floor<=k)
    {
        if (q.front()->left != NULL)
        {
            q.push(q.front()->left);
            arr[floor]++;//+1
        }
        if (q.front()->right != NULL)
        {
            q.push(q.front()->right);
            arr[floor]++;
        }
        q.pop();
        fnum--;
        if (fnum == 0)
        {
            floor++;
            fnum = arr[floor - 1];
        }
    }
    return arr[floor-1];
}

//返回二叉树的深度
int Tree::depth(Linknode* root)
{
    int dep = 1;//深度
    int fnum = 1;//上一层的节点数
    int arr[100] = { 0 };//创建一个数组，存储k层的节点数
    queue<Linknode*> q;//同层序遍历相似
    if (root == NULL)
        return 0;
    q.push(root);
    while (!q.empty())
    {
        if (q.front()->left != NULL)
        {
            q.push(q.front()->left);
            arr[dep]++;//+1
        }
        if (q.front()->right != NULL)
        {
            q.push(q.front()->right);
            arr[dep]++;
        }
        q.pop();
        fnum--;
        if (fnum == 0)
        {
            if (arr[dep] == 0)
                return dep;
            dep++;
            fnum = arr[dep - 1];
        }
    }
    return dep;
}

//返回节点存储值为val的第一个节点
//这里有四种方式返回（即四种遍历的方式返回四种情况）
//这里以前序遍历为例
Linknode* Tree::Find(Linknode* root,int val)
{
    if (root == NULL)
        return NULL;
    if (root->data == val)
        return root;//首次找到节点，返回地址
    Linknode* ret1=Find(root->left,val);//左子节点的由ret1接受，没有找到ret1为空
    if (ret1)//如果ret1不为空返回，直到根节点，然后递归结束
        return ret1;
    Linknode* ret2=Find(root->right,val);//右子节点的由ret2接受，没有找到ret2为空
    if (ret2)//同ret1
        return ret2;
}

//判断二叉树是否为完全二叉树
bool Tree::Iscomplete(Linknode* root)
{
    queue<Linknode*> q;
    //借助层序遍历
    //将地址为空的也进入队列
    //当队列的第一个元素为NULL时，看队列元素是否全为空，当全为空时，为完全二叉树，反之则不是
    if (root == NULL)
        return false;
    q.push(root);
    while (!q.empty())
    {
        if (q.front() == NULL)
            break;
        q.push(q.front()->left);
        q.push(q.front()->right);
        q.pop();
    }
    while (!q.empty())
    {
        q.pop();
        if (q.front())//碰见元素不为NULL
            return false;
    }
    return true;
}

//销毁二叉树,防止内存泄漏
void Tree::clear(Linknode* root)
{
    if (root == NULL)
        return;
    clear(root->left);
    clear(root->right);
    delete root;
}

int main()
{
    Tree t;
    t.root = new Linknode;

    t.root->data = 1;
    t.root->left = new Linknode;
    t.root->left->data = 2;
    t.root->left->left = new Linknode;
    t.root->left->left->data = 3;
    t.root->right = new Linknode;
    t.root->right->data = 4;
    t.root->right->left = new Linknode;
    t.root->right->left->data = 5;
    t.root->right->right = new Linknode;
    t.root->right->right->data = 6;
    //t.Gettree(t.root);//使用函数创建树
    cout << "前序遍历打印:";
    t.pre_order(t.root);
    cout << endl;
    cout << "中序遍历打印:";
    t.in_order(t.root);
    cout << endl;
    cout << "后序遍历打印:";
    t.post_order(t.root);
    cout << endl;
    cout << "层序遍历打印:";
    t.level_order(t.root);
    cout << "这个树的节点有：" << t.LNnum(t.root) << "个" << endl;
    cout << "这个树第2层的节点有：" << t.Lnnum(t.root,2) << "个" << endl;
    cout << "深度为：" << t.depth(t.root) << endl;
    cout << t.Find(t.root, 3) << endl;
    cout << t.Iscomplete(t.root) << endl;
    return 0;
}

