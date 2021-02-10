#include "..\..\Include\DarkGDK\DarkGDK.h"
#include <vector>

//Scene-Graph

// Abstract node
class Node
{
public:
	int X, Y, W, H;
	std::vector<Node*> Child;

	Node(void) : X(0), Y(0), W(0), H(0)
	{
	}

	Node(int x, int y, int w, int h) : X(x), Y(y), W(w), H(h)
	{
	}

	void AddChild(Node* child)
	{
		Child.push_back(child);
	}

	virtual void Render(int x, int y, float dist)
	{
		for (size_t c = 0; c < Child.size(); c++)
		{
			float distToChild = (x - Child[c]->X) * (x - Child[c]->X) + (y - Child[c]->Y) * (y - Child[c]->Y);

			if (distToChild <= (dist * dist))
				Child[c]->Render(x, y, dist / 2);
		}
	}

	void Drop(void)
	{
		while (!Child.empty())
		{
			if (Child.back())
			{
				Child.back()->Drop();
				delete Child.back();
			}

			Child.pop_back();
		}
	}
	
};


// Square node
class Square : public Node
{
public:
	Square(void) : Node()
	{
	}
	Square(int x, int y, int w, int h) : Node(x, y, w, h)
	{
	}

	void Render(int x, int y, float dist)
	{
		Node::Render(x, y, dist);
		//if (Child.empty())
		{
			dbLine(X - W / 2, Y - H / 2, X + W / 2, Y - H / 2);
			dbLine(X - W / 2, Y + H / 2, X + W / 2, Y + H / 2);
			dbLine(X - W / 2, Y - H / 2, X - W / 2, Y + H / 2);
			dbLine(X + W / 2, Y - H / 2, X + W / 2, Y + H / 2);
		}
	}
};


void Generate(Node* node, int depth)
{
	if (depth == 0) return;

	int count = 4;
	float ang = 360.0f / count;

	for (int c = 0; c < count; c++)
	{
		int mx = (dbSin(c * 90.0f + 45.0f) >= 0.0f) ? 1 : -1;
		int my = (dbCos(c * 90.0f + 45.0f) >= 0.0f) ? 1 : -1;
		Node* child = new Square(node->X + (node->W / 4) * mx, node->Y + (node->H / 4) * my, node->W / 2.1f, node->H / 2.1f);
		node->AddChild(child);
		Generate(child, depth - 1);
	}
}


void DarkGDK(void)
{
	dbSyncOn();
	dbSyncRate(60);
	dbSetDisplayMode(1024, 768, 32);
	dbRandomize(dbTimer());

	Node * test = new Square(512, 394, 750, 750);
	Generate(test, 6);

	float dist = 1000.0f;

	while (LoopGDK())
	{
		test->Render(dbMouseX(), dbMouseY(), dist);

		if (dbUpKey()) dist *= 1.2f;
		if (dbDownKey()) dist /= 1.2f;

		dbText(10, 10, dbStr(dist));
		dbText(10, 50, dbStr(dbScreenFPS()));

		dbSync();
		dbCLS();
	}

	test->Drop();
	delete test;

	return;
}
