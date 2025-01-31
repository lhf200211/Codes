//https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/

/*
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
*/


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
 
  class Solution1 {
  public:

      bool IsInSubTree(TreeNode* root, TreeNode* x)
      {
          if(root==nullptr)
              return false;
          if(root == x)
              return true;

          return IsInSubTree(root->left, x) || IsInSubTree(root->right, x);
      }

      TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
          if(root==nullptr)
              return root;
          if(p == root || q == root)
              return root;

          bool pInLeft = IsInSubTree(root->left, p);
          bool pInRight = !pInLeft;

          bool qInLeft = IsInSubTree(root->left, q);
          bool qInRight = !qInLeft;

          if((pInLeft && qInRight) || (qInLeft && pInRight))
          {
              return root;
          }
          else if(pInLeft && qInLeft)
          {
              return lowestCommonAncestor(root->left, p, q);
          }
          else if(pInRight && qInRight)
          {
              return lowestCommonAncestor(root->right, p, q);
          }
          else
          {
              return nullptr;
          }
      }
  };


class Solution2 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if (root == nullptr)
            return nullptr;

        if (root == p || root == q)
        {
            return root;
        }

        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        if (left && right)
        {
            return root;
        }
        else if (left)
        {
            return left;
        }
        else if (right)
        {
            return right;
        }
        else
        {
            return nullptr;
        }

    }
};

#include<vector>
#include<stack>
using std::stack;
using std::vector;

class Solution3 {
public:
    bool findPath(TreeNode* root, TreeNode* x, stack<TreeNode*, vector<TreeNode*>>& path)
    {
        if (root == nullptr)
            return false;

        path.push(root);

        if (root == x)
            return true;

        if (findPath(root->left, x, path))
            return true;

        if (findPath(root->right, x, path))
            return true;

        path.pop();
        return false;

    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        stack<TreeNode*, vector<TreeNode*>> pPath, qPath;

        findPath(root, p, pPath);
        findPath(root, q, qPath);

        while (pPath.size() > qPath.size())
        {
            pPath.pop();
        }

        while (pPath.size() < qPath.size())
        {
            qPath.pop();
        }

        while (pPath.top() != qPath.top())
        {
            pPath.pop();
            qPath.pop();
        }

        return pPath.top();

    }

};