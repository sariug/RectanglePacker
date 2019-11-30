#include "PackNode.h"

PackNode::PackNode()
{
	x = y = w = h = 0;
	is_full = false;
}
PackNode::PackNode(int X, int Y, int W, int H) : x(X), y(Y), h(H), w(W), is_full(false){}

void PackNode::extend(int e)
{
	if (this->x + this->w == e)
		this->w++;

	if (this->y + this->h == e)
		this->h++;

	if (!this->children.empty())
	{
		this->children[0].extend(e);
		this->children[1].extend(e);
	}
}

PackNode *PackNode::insert(Rect &R)
{
	if (!this->children.empty())
	{
		PackNode *newnode = this->children[0].insert(R);
		if (newnode != NULL)
			return newnode;
		return this->children[1].insert(R);
	}
	else
	{
		if (this->is_full)
			return nullptr;
		if (w < R.get_width() || h < R.get_height())
			return nullptr;

		if (this->w == R.get_width() && h == R.get_height())

		{
			R.setloc(this->x, this->y);
			is_full = true;
			return this;
		}

		int dw = this->w - R.get_width();
		int dh = this->h - R.get_height();

		if (dw > dh)
		{
			// split vertical
			this->children.push_back(PackNode(this->x, this->y, R.get_width(), this->h));
			this->children.push_back(PackNode(this->x + R.get_width(), this->y, this->w - R.get_width(), this->h));
		}
		else
		{
			// split horizontal
			this->children.push_back(PackNode(this->x, this->y, this->w, R.get_height()));
			this->children.push_back(PackNode(this->x, this->y + R.get_height(), this->w, this->h - R.get_height()));
		}
		return this->children[0].insert(R);
	}
}
