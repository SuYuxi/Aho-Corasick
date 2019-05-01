#ifndef AhoCorasick_H
#define AhoCorasick_H

#include <vector>
#include <queue>
#include <string>
#include <memory>
#include <iostream>
const int SIGMA = 26;

//Aho–Corasick algorithm
namespace Aho_Corasick {
	using namespace std;
	struct Node {
		vector<shared_ptr<Node>> children;	
		shared_ptr<Node> parent;
		shared_ptr<Node> fail; //match fail node
		string word;
		vector<string> suffixWords;
		bool isWord;

		Node(shared_ptr<Node> _parent = nullptr) : parent(_parent), children(SIGMA, nullptr), fail(nullptr), isWord(false) {}; 
	};

	class AhoCorasick {
	public:
		AhoCorasick() : root(nullptr) {};
		void build(vector<string> _patterns)
		{
			patterns = _patterns;
			root = make_shared<Node>();
			for(int inx = 0; inx < patterns.size(); inx++)
			{
				addPattern(patterns[inx]);
			}
			buildFailureLink();
		}

		void query(string str)
		{
			shared_ptr<Node> curNode = root;
			for(int i = 0; i < str.size(); i++)
			{
				int inx = str[i] - 'a';	
				while(curNode != nullptr && curNode->children[inx] == nullptr)
				{
					curNode = curNode->fail;
				}
				if(curNode == nullptr)
				{
					curNode = root;
				}
				else
				{
					curNode = curNode->children[inx];
				}
				for(string& s :curNode->suffixWords)
				{
					cout << s << endl;
					cout << "(" << i - s.size() + 1 << "," << i << ")" << endl; 
				}
				if(curNode->isWord)
				{
					cout << curNode->word << endl;
					cout << "(" << i - curNode->word.size() + 1 << "," << i << ")" << endl; 
				}
			}
		};

		void addPattern(string pattern)
		{
			if(pattern.empty()) return;
			shared_ptr<Node> node = root;
			for(char& c : pattern)
			{
				int i = c - 'a';
				if(node->children[i] == nullptr)
				{
					node->children[i] = make_shared<Node>(node);
				}
				node = node->children[i];
			}
			node->word = pattern;
			node->isWord = true;
		}

		void buildFailureLink()
		{
			queue<shared_ptr<Node>> q;
			for(shared_ptr<Node>& child : root->children)
			{
				if(child != nullptr)
				{
					q.emplace(child);
					child->fail = root;
				}
			}
			while(!q.empty())
			{
				shared_ptr<Node> node = q.front();
				q.pop();
				for(int i = 0; i < SIGMA; i++)
				{
					if(node->children[i] != nullptr)
					{
						q.emplace(node->children[i]);
						shared_ptr<Node> cur = node->fail;
						while(cur != nullptr && cur->children[i] == nullptr)
						{
							cur = cur->fail;
						}
						if(cur == nullptr)
						{
							node->children[i]->fail = root;
						}
						else
						{
							node->children[i]->fail = cur->children[i];
							node->children[i]->suffixWords.clear();
							for(string& word : cur->children[i]->suffixWords)
							{
								node->children[i]->suffixWords.emplace_back(word);
							}
							if(cur->children[i]->isWord)
							{
								node->children[i]->suffixWords.emplace_back(cur->children[i]->word);
							}
						}
					}
				}
			}
		}
		
	private:
		shared_ptr<Node> root;
		vector<string> patterns;
	};
}
#endif
