#include <iostream>
#include <vector>
#include "vector.h"
using namespace std;
class pwd
{
public:
	int id;
	static int ctor_count;
	static int copy_count;
	static int move_count;
	static int dtor_count;


	explicit pwd(int num)
	{
		ctor_count++;
		id = num;

		//cout << "[constructed]" << "[" << id << "]" << endl;
	}

	pwd()
	{
		ctor_count++;
		id = 0;
		//cout << "[constructed default]" << endl;
	}

	mutable bool is_copied = false;
	bool is_moved = false;
	pwd(pwd&& other)noexcept
	{
		move_count++;
		ctor_count++;
		other.is_moved = true;
		id = other.id;
		other.id = -1;
		//cout << "[moved]" << "[" << id << "]" << endl;
	}

	pwd(const pwd& other)
	{
		copy_count++;
		ctor_count++;
		other.is_copied = true;
		id = other.id;

		//cout << "[copied]" << "[" << id << "]" << endl;
	}

	pwd& operator=(const pwd& other)
	{
		copy_count++;
		other.is_copied = true;
		id = other.id;
		//cout << "[copied via =]" << "[" << id << "]" << endl;
		return *this;

	}

	pwd& operator=(pwd&& other)noexcept
	{
		move_count++;
		/*cout << "old id = " << this->id << endl;*/

		other.is_moved = true;
		id = other.id;
		other.id = -1;
		//cout << "[moved via =]" << "[" << id << "]" << endl;
		return *this;
	}

	~pwd()
	{
		dtor_count++;
		/*if (is_moved)
		{
			cout << "[moved destroyed]" << "[" << id << "]" << endl;

		}
		else if (is_copied)
		{
			cout << "[copied destroyed]" << "["<< id <<"]" << endl;
		}
		else
		{
			cout << "Destroyed! ["<< id <<"]" << endl;
		}*/


	}
};

int pwd::ctor_count = 0;
int pwd::dtor_count = 0;
int pwd::copy_count = 0;
int pwd::move_count = 0;

int main()
{
	my_vector::vector b = { pwd(1),pwd(2) };
	b.emplace_back(2);
	cout << "dtor: " << pwd::dtor_count << endl;
	cout << "ctor: " << pwd::ctor_count << endl;
	cout << "copy: " << pwd::copy_count << endl;
	cout << "move: " << pwd::move_count << endl;
}

//20
//20
//1
//13