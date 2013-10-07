#include <iostream>
#include <cassert>

using namespace std;

template <class T>

class myvector
{
private:
	T *array;
	int my_size;
	int my_capacity;

public:
	// Constructors
	myvector() // empty-constructor
	{
		my_size = 0;
		my_capacity = 10;
		array = new T [my_capacity]; 
	}

	myvector(int size) // constructor with initial length of the vector 
	{
		my_size = size;
		my_capacity = 2*size;
		array = new T [my_capacity];
	}

	myvector(T array1[], int size)  // an array of the same type and the integer array length -- copy contents of array into the vector
	{
		my_size = size;
		my_capacity = size;
		array = new T [my_capacity];

		for (int i = 0; i < size; i++)
		{
			array[i] = array1[i];
		}
	}

	myvector(const myvector<T> & arr) // constructor that takes another vector of the same type (as a const reference)
	{
		my_size = arr.my_size;
		my_capacity = arr.my_capacity;
		array = new T[my_capacity];

		for (int i = 0; i < my_size; i++)
		{
			array[i] = arr.array[i];
		}
	} //End of Constructors
	
	//Destructor
	~myvector()
	{
		delete[] array;
	}

	int size()
	{
		return my_size;
	}

	int capacity()
	{
		return my_capacity;
	}

	bool empty()
	{
		if (my_size == 0)
			return true;

		return false;
	}

	void reserve(int new_cap)
	{
		if (new_cap < my_size)
			cout << endl << "New Capacity smaller than size! No changes in the vector capacity." << endl;

		else
		{
			T *_array = new T[new_cap];
			assert(_array);
			for(int i = 0; i < my_size; i++)
				_array[i] = array[i];
			my_capacity = new_cap;
			delete[] array;
			array = _array;
		}
	}

	void resize(int new_size)
	{
		if(new_size >= my_capacity)
			reserve(2*new_size);
		
		my_size = new_size;
	}

	T & operator[](int index) 
	{
		assert(index > -1 && index < my_capacity);
		return array[index];
	}

	T at(int index)
	{
		assert(index > -1 && index < my_capacity);
		return array[index];
	}

	myvector & operator=(const myvector &arr2)
	{
		if(this != &arr2)
		{
			my_size = arr2.my_size;
			delete[] array;		//delete the array thats within the class on lhs
			array = new T[my_size];

			for(int i = 0; i < my_size; i++)
			{
				array[i] = arr2.my_array[i];
			}
		}
		return *this;
	}

	void assign(int position, T val)
	{
		if(position > my_capacity)
			cout << "Assigning the value " << val << " at a wrong position " << position << " which is outside the vector." << endl;

		else
			array[position] = val;
	}

	void push_back(T val)
	{
		if(my_size == my_capacity)
			reserve(2*my_capacity);

		array[my_size] = val;
		my_size++;
	}

	T pop_back()
	{
		if(my_size == 0)
		{
			cout << "No elements in the vector!" << endl;
			return NULL;
		}

		T temp = array[my_size-1];
		my_size--;
		return temp;
	}

	void insert(int pos, T val)
	{
		if (my_size == my_capacity)
			reserve(2*my_capacity);

		my_size++;
			
		for(int i = my_size-1; i >= pos; i--)
			array[i] = array[i-1];

		array[pos] = val;
	}

	void erase(int pos)
	{
		for(int i = pos; i < my_size; i++)
			array[i] = array[i+1];
		my_size--;
	}

	void erase(int start_pos, int end_pos)
	{
		for(int i = start_pos; i < end_pos; i++)
		{
			array[i] = NULL; 
			my_size--;
		}

		// need to push all the elements up
		for(int i = start_pos, j = end_pos-1; j < my_size, i < my_size; i++, j++)
		{
			array[i] = array[j+1];
			array[j+1] = NULL;
		}
	}

	void clear()
	{
		my_size = 0;
	}
};

int main() // In order to test
{
	cout << "My Vector Class Implementation!" << endl << endl;
	
	int arr[6] = {0, 1, 2, 3, 4, 5};

	myvector<int> myvec;

	myvec.reserve(20);
	cout << "Allocating capacity of 20. " << endl;
	cout << endl;
	cout << endl << "Size: " << myvec.size() << endl;
	cout << "Capacity: " << myvec.capacity() << endl << endl;
	bool empty;	
	empty = myvec.empty();

	if(empty)
		cout << "Vector is empty!" << endl;

	else
		cout << "Vector is not empty!" << endl;

	cout << endl << "Size: " << myvec.size() << endl;
	cout << "Capacity: " << myvec.capacity() << endl;
	
	for(int i = 0; i < myvec.capacity(); i++)
		myvec.push_back(i);
	cout << endl << "Size: " << myvec.size() << endl;
	cout << "Capacity: " << myvec.capacity() << endl;
	cout << endl;

	for(int i = 0; i < myvec.size(); i++)
		cout << i << "\t" << myvec[i] << endl;
		
	cout << endl;

	myvec.pop_back();
	myvec.pop_back();
	myvec.pop_back();
	
	for(int i = 0; i < myvec.size(); i++)
		cout << i << "\t" << myvec[i] << endl;

	empty = myvec.empty();
	cout << endl << "Size: " << myvec.size() << endl;
	cout << "Capacity: " << myvec.capacity() << endl;

	myvec.assign(15,1500);
	myvec.assign(16,1600);
	myvec.insert(17,1700);
	myvec.insert(18,1800);

	for(int i = 0; i < myvec.size(); i++)
		cout << i << "\t" << myvec[i] << endl;

	cout << endl << "Size: " << myvec.size() << endl;
	cout << "Capacity: " << myvec.capacity() << endl;

	myvec.erase(10);
	
	for(int i = 0; i < myvec.size(); i++)
		cout << i << "\t" << myvec[i] << endl;

	cout << endl << "Size: " << myvec.size() << endl;
	cout << "Capacity: " << myvec.capacity() << endl;
	
	myvec.erase(10,13);

	for(int i = 0; i < myvec.size(); i++)
		cout << i << "\t" << myvec[i] << endl;

	cout << endl << "Size: " << myvec.size() << endl;
	cout << "Capacity: " << myvec.capacity() << endl;

	myvec.reserve(100);
	myvec.resize(50);

	cout << endl << "Size: " << myvec.size() << endl;
	cout << "Capacity: " << myvec.capacity() << endl;

	myvec.clear();
	empty = myvec.empty();
	cout << endl << "Size: " << myvec.size() << endl;
	cout << "Capacity: " << myvec.capacity() << endl;

	myvec.push_back(1000);
	myvec.push_back(2000);
	myvec.push_back(3000);
	myvec.push_back(4000);
	myvec.push_back(5000);
	for(int i = 0; i < myvec.size(); i++)
		cout << i << "\t" << myvec[i] << endl;

	cout << endl << "Size: " << myvec.size() << endl;
	cout << "Capacity: " << myvec.capacity() << endl;

	myvector<int> myvec2(myvec);
	cout << endl << "Size2: " << myvec2.size() << endl;
	cout << "Capacity2: " << myvec2.capacity() << endl;
	for(int i = 0; i < myvec2.size(); i++)
		cout << i << "\t" << myvec2[i] << endl;

	myvector<int> myvec3(10);
	cout << endl << "Size3: " << myvec3.size() << endl;
	cout << "Capacity3: " << myvec3.capacity() << endl;
	for(int i = 0; i < myvec3.size(); i++)
		cout << i << "\t" << myvec3[i] << endl;

	myvector<int> myvec4(arr, 6); 
	cout << endl << "Size4: " << myvec4.size() << endl;
	cout << "Capacity4: " << myvec4.capacity() << endl;
	for(int i = 0; i < myvec4.size(); i++)
		cout << i << "\t" << myvec4[i] << endl;
}	