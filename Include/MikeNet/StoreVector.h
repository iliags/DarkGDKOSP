#pragma once
#include "Store.h"

/**
 * @brief	Manages a vector of objects efficiently and safely.
 * @remarks	Michael Pryor, 6/28/2010.
 *
 * The vector manages the objects using pointers, making it very efficient.\n\n
 *
 * Only the vector itself is thread safe, not the use of the objects in the vector.\n\n
 */
template<class T>
class StoreVector: public Store<T>
{
	/** @brief Vector, storing pointers to elements. */
	vector<T*> data;

public:
	/** @brief Constructor. */
	StoreVector() : Store()
	{

	}

	/**
	 * @brief Deep copy constructor.
	 *
	 * @param	copyMe	Object to copy.
	 */
	StoreVector(const StoreVector & copyMe) : Store(copyMe)
	{
		copyMe.Enter();
		this->Enter();

		try
		{
			this->data.resize(copyMe.data.size());
			for(size_t n = 0;n<copyMe.data.size();n++)
			{
				if(copyMe.IsAllocated(n) == true)
				{
					this->data[n] = new (nothrow) T(*copyMe.data[n]);
					Utility::DynamicAllocCheck(this->data[n],__LINE__,__FILE__);
				}
				else
				{
					this->data[n] = NULL;
				}
			}
		}
		// Release control of all objects before throwing final exception
		catch(ErrorReport & Error){ copyMe.Leave(); this->Leave(); throw(Error); }
		catch(...){	copyMe.Leave(); this->Leave(); throw(-1); }

		this->Leave();
		copyMe.Leave();
	}

	/**
	 * Deep assignment operator.
	 *
	 * @param	copyMe	Object to copy. 
	 *
	 * @return	reference to this object.
	 */
	StoreVector & operator= (const StoreVector & copyMe)
	{
		this->Enter();
		copyMe.Enter();

		try
		{
			// Resize vector
			this->Resize(copyMe.Size());

			// Copy data
			for(size_t n = 0;n<this->Size();n++)
			{
				if(copyMe.IsAllocated(n) == true)
				{
					Allocate(n,copyMe[n]);
				}
				else
				{
					Deallocate(n);
				}
			}
		}
		// Release control of all objects before throwing final exception
		catch(ErrorReport & Error){ copyMe.Leave(); this->Leave(); throw(Error); }
		catch(...){	copyMe.Leave(); this->Leave(); throw(-1); }

		copyMe.Leave();
		this->Leave();

		return *this;
	}


	/** @brief Destructor. */
	virtual ~StoreVector()
	{
		const char * cCommand = "an internal function (~StoreVector)";
		try
		{
			Clear();
		}
		MSG_CATCH
	}

	/**
	 * @brief	Retrieves a pointer to an internal pointer to an element of data.
	 *
	 * This is used where the pointer itself needs to be directly modified. Use with caution
	 * as the retrieved pointer may become invalid if the vector changes in size.
	 *
	 * @param	element	The element.
	 *
	 * @return	a pointer to an internal pointer to an element of data. 
	 */
	T ** GetPtr(size_t element)
	{
		T ** returnMe = NULL;
		Enter();
		try
		{
			_ErrorException((element >= this->Size()),"retrieving a vector element's pointer, element specified is out of bounds",0,__LINE__,__FILE__);
			returnMe = &data[element];
		}
		// Release control of all objects before throwing final exception
		catch(ErrorReport & error){Leave(); throw(error);}
		catch(...){Leave(); throw(-1);}
		Leave();
		return returnMe;
	}

	/**
	 * @brief [] Operator, returns constant pointer to element in vector.
	 *
	 * @note MUST return reference for multidimensional elements so that
	 * subsequent dimensions can be accessed in this fashion: Vec[][].
	 *
	 * @param element Element to access.
	 * @return object at @a element.
	 *
	 * @exception ErrorReport If element is out of bounds.
	 */
	const T & operator[](size_t element) const
	{
		T * returnMe = NULL;

		Enter();
		try
		{
			_ErrorException((element >= this->Size()),"accessing element of vector, element specified is out of bounds",0,__LINE__,__FILE__);
			_ErrorException((IsAllocated(element) == false),"accessing element of vector, element is not allocated",0,__LINE__,__FILE__);
			returnMe = data[element];
		}
		// Release control of all objects before throwing final exception
		catch(ErrorReport & error){Leave(); throw(error);}
		catch(...){Leave(); throw(-1);}

		Leave();
		return(*returnMe);
	}

	/**
	 * @brief [] Operator, returns mutable pointer to element in vector.
	 *
	 * @note MUST return reference for multidimensional elements so that
	 * subsequent dimensions can be accessed in this fashion: Vec[][].
	 *
	 * @param element Element to access.
	 * @return object at @a element.
	 *
	 * @exception ErrorReport If element is out of bounds.
	 */
	T & operator[](size_t element)
	{
		T * returnMe = NULL;

		Enter();
		try
		{
			_ErrorException((element >= this->Size()),"accessing element of vector, element specified is out of bounds",0,__LINE__,__FILE__);
			_ErrorException((IsAllocated(element) == false),"accessing element of vector, element is not allocated",0,__LINE__,__FILE__);
			returnMe = data[element];
		}
		// Release control of all objects before throwing final exception
		catch(ErrorReport & error){Leave(); throw(error);}
		catch(...){Leave(); throw(-1);}

		Leave();
		return(*returnMe);
	}
	
	/**
	 * @brief Remove element from vector, decreasing vector size by 1.
	 *
	 * Use Deallocate() to erase the contents of the element but not remove it from the vector.
	 *
	 * @param element Element to remove.
	 *
	 * @throws ErrorReport If @a element is out of bounds.
	 */
	void Erase(size_t element)
	{
		Enter();
		try
		{
			_ErrorException((element >= this->Size()),"erasing element of vector, element specified is out of bounds",0,__LINE__,__FILE__);

			Deallocate(element);
			data.erase(data.begin()+element);
		}
		// Release control of all objects before throwing final exception
		catch(ErrorReport & error){Leave(); throw(error);}
		catch(...){Leave(); throw(-1);}

		Leave();
	}

	/**
	 * @brief Allocate memory to specified element, overwriting anything currently stored.
	 *
	 * New memory is allocated using default constructor.
	 *
	 * @param element Element to allocate to.
	 */
	void Allocate(size_t element)
	{
		Enter();
		try
		{
			_ErrorException((element >= this->Size()),"allocating element of vector with default constructor, element specified is out of bounds",0,__LINE__,__FILE__);
			Deallocate(element);

			data[element] = new (nothrow) T();
			Utility::DynamicAllocCheck(data[element],__LINE__,__FILE__);
		}
		// Release control of all objects before throwing final exception
		catch(ErrorReport & error){Leave(); throw(error);}
		catch(...){Leave(); throw(-1);}

		Leave();
	}

	/**
	 * @brief Allocate memory to specified element, overwriting anything currently stored.
	 *
	 * @param element Element to overwrite.
	 * @param [in] newElement Reference to object to copy from.
	 */
	void Allocate(size_t element, const T & newElement)
	{
		Enter();
		
		try
		{
			_ErrorException((element >= this->Size()),"allocating memory to element of vector, element specified is out of bounds",0,__LINE__,__FILE__);
			
			Deallocate(element);

			data[element] = new (nothrow) T(newElement);
			Utility::DynamicAllocCheck(data[element],__LINE__,__FILE__);
		}
		// Release control of all objects before throwing final exception
		catch(ErrorReport & error){Leave(); throw(error);}
		catch(...){Leave(); throw(-1);}

		Leave();
	}

	/**
	 * @brief Allocate memory to specified element, overwriting anything currently stored.
	 *
	 * @param element Element to overwrite.
	 * @param [in] newElement Pointer that is now owned by this object and should not be referenced elsewhere.
	 */
	void Allocate(size_t element, T * newElement)
	{
		Enter();
		
		try
		{
			_ErrorException((element >= this->Size()),"allocating memory to element of vector with pointer, element specified is out of bounds",0,__LINE__,__FILE__);

			Deallocate(element);

			data[element] = newElement;
		}
		// Release control of all objects before throwing final exception
		catch(ErrorReport & error){Leave(); throw(error);}
		catch(...){Leave(); throw(-1);}

		Leave();
	}

	/**
	 * @brief Deallocate element from vector setting it to NULL, without decreasing size of vector.
	 *
	 * Use Erase() to completely remove an element from the vector, decreasing the size of the vector.
	 *
	 * @param element To deallocate.
	 */
	void Deallocate(size_t element)
	{
		Enter();
		
		try
		{
			_ErrorException((element >= data.size()),"deallocating element of vector, element specified is out of bounds",0,__LINE__,__FILE__);
	
			delete data[element];
			data[element] = NULL;
		}
		// Release control of all objects before throwing final exception
		catch(ErrorReport & error){Leave(); throw(error);}
		catch(...){Leave(); throw(-1);}

		Leave();
			
	}

	/**
	 * @brief Empty the contents of the vector.
	 */
	void Clear()
	{
		Enter();

		while(data.size() > 0)
		{
			Erase(0);
		}

		Leave();		
	}


	/**
	 * @brief Get object from front of queue and remove it from vector.
	 *
	 * @param [out] destination Location to copy retrieved object.
	 *
	 * @return number of objects in collection before this method was called.
	 */
	size_t Get(T * destination)
	{
		size_t returnMe;

		Enter();
		try
		{
			returnMe = data.size();

			if(data.size() > 0)
			{
				*destination = *data.front();
				delete data.front();
				data.erase(data.begin());
			}
		}
		// Release control of all objects before throwing final exception
		catch(ErrorReport & error){Leave(); throw(error);}
		catch(...){Leave(); throw(-1);}
		Leave();

		return(returnMe);
	}

	/**
	 * @brief Add object to back of vector.
	 *
	 * @param [in] object Object to add to collection. @a object is now owned by this object
	 * and should not be referenced elsewhere.
	 */
	void Add(T * object)
	{
		_ErrorException((object == NULL),"adding a packet to a packet store vector, NULL pointer received",0,__LINE__,__FILE__);
		Enter();
			data.push_back(object);
		Leave();
	}

	/**
	 * @brief Retrieve the number of objects in the vector.
	 * 
	 * @return number of objects in vector.
	 */
	size_t Size() const
	{
		size_t returnMe = 0;

		Enter();
			returnMe = data.size();
		Leave();

		return(returnMe);
	}
	
	/**
	 * @brief Retrieve the object at the front of the vector (without removing it).
	 *
	 * @return element at front.
	 */
	T * Front() const
	{
		T * returnMe;

		Enter();
		try
		{
			_ErrorException((data.size() == 0),"retrieving an element from the front of a vector, vector is empty",0,__LINE__,__FILE__);
			returnMe = data.front();
		}
		// Release control of all objects before throwing final exception
		catch(ErrorReport & error){Leave(); throw(error);}
		catch(...){Leave(); throw(-1);}
		Leave();

		return(returnMe);
	}

	/**
	 * @brief Retrieve the object at the back of the vector (without removing it).
	 *
	 * @return element at back.
	 */
	T * Back() const
	{
		T * returnMe;

		Enter();
		try
		{
			_ErrorException((data.size() == 0),"retrieving an element from the back of a vector, vector is empty",0,__LINE__,__FILE__);
			returnMe = data.back();
		}
		// Release control of all objects before throwing final exception
		catch(ErrorReport & error){Leave(); throw(error);}
		catch(...){Leave(); throw(-1);}
		Leave();

		return(returnMe);
	}

	/**
	 * @brief Resizes vector, allocating memory to new elements.
	 *
	 * Memory is allocated using default constructor.
	 *
	 * @param newSize New size of vector.
	 */
	void ResizeAllocate(size_t newSize)
	{
		Enter();
		try
		{
			size_t originalSize = data.size();
			data.resize(newSize);
			for(size_t n = originalSize;n<newSize;n++)
			{
				Allocate(n);
			}
		}
		// Release control of all objects before throwing final exception
		catch(ErrorReport & error){Leave(); throw(error);}
		catch(...){Leave(); throw(-1);}

		Leave();
	}

	/**
	 * @brief Resizes vector, allocating memory to new elements.
	 *
	 * Memory is allocated using the copy constructor.
	 *
	 * @param newSize New size of vector.
	 * @param copyMe Object to pass to copy constructor of T when allocating new objects.
	 */
	void ResizeAllocate(size_t newSize, const T & copyMe)
	{
		Enter();
		try
		{
			size_t originalSize = data.size();
			data.resize(newSize);
			for(size_t n = originalSize;n<newSize;n++)
			{
				Allocate(n,copyMe);
			}
		}
		// Release control of all objects before throwing final exception
		catch(ErrorReport & error){Leave(); throw(error);}
		catch(...){Leave(); throw(-1);}

		Leave();
	}

	/**
	 * @brief Determines whether the specified element has memory allocated to it.
	 * 
	 * @return true if specified element has memory allocated to it (is not NULL).
	 * @param element Element to check.
	 */
	bool IsAllocated(size_t element) const
	{
		bool returnMe;

		Enter();
		try
		{
			_ErrorException((element >= data.size()),"determining whether an element is allocated, element specified is out of bounds",0,__LINE__,__FILE__);
			returnMe = (data[element] != NULL);
		}
		// Release control of all objects before throwing final exception
		catch(ErrorReport & error){Leave(); throw(error);}
		catch(...){Leave(); throw(-1);}
		Leave();
		return returnMe;
	}

	/**
	 * @brief Resizes array without allocating memory (setting new elements to NULL).
	 *
	 * @param newSize New size of vector.
	 */
	void Resize(size_t newSize)
	{
		Enter();
			size_t originalSize = data.size();

			// Resize array and set new elements to NULL
			data.resize(newSize);
			for(size_t n = originalSize;n<newSize;n++)
			{
				data[n] = NULL;
			}
		Leave();
	}

	/**
	 * @brief Finds an identical object in the vector.
	 *
	 * This has a worst and average case complexity of O(n) and should be replaced
	 * with a merge sort equivalent when time allows. 
	 *
	 * @param findMe Object to find.
	 * @param [out] position Pointer to location to store element that object was found at.
	 *
	 * @return true if an identical object was found.
	 * @return false if not.
	 */
	bool Find(const T & findMe, size_t * position)
	{
		bool found = false;
		for(size_t n = 0;n<Size();n++)
		{
			if(*data[n] == findMe)
			{
				found = true;
				if(position != NULL)
				{
					*position = n;
				}
				break;
			}
		}
		return found;
	}

	/**
	 * @brief Tests class.
	 *
	 * @return true if no problems while testing were found, false if not.
	 * Note that not all tests automatically check for problems so some tests
	 * require manual verification.
	 */
	static bool TestClass()
	{
		cout << "Testing StoreVector class...\n";
		bool problem = false;

		size_t size = 5;

		StoreVector<size_t> vec;
		vec.Resize(size);

		if(vec.Size() != size)
		{
			cout << "Resize or Size is bad\n";
			problem = true;
		}
		else
		{
			cout << "Resize and Size are good\n";
		}

		bool allocated = false;
		for(size_t n = 0;n<vec.Size();n++)
		{
			if(vec.IsAllocated(n) == true)
			{
				allocated = true;
				break;
			}
		}

		if(allocated == true)
		{
			cout << "Resize or IsAllocated is bad\n";
			problem = true;
		}
		else
		{
			cout << "Resize and IsAllocated are good\n";
		}
		
		vec.Allocate(0);
		if(vec.IsAllocated(0) == false)
		{
			cout << "Allocate or IsAllocated is bad\n";
			problem = true;
		}
		else
		{
			cout << "Allocate and IsAllocated are good\n";
		}

		size_t newElement = 1;
		size_t newElementValue = 4000;
		vec.Allocate(newElement,newElementValue);
		if(vec[newElement] != newElementValue)
		{
			cout << "Allocate or [] is bad\n";
			problem = true;
		}
		else
		{
			cout << "Allocate and [] are good\n";
		}

		newElement = 2;
		vec.Allocate(newElement,new size_t(newElementValue));
		if(vec[newElement] != newElementValue)
		{
			cout << "Allocate or [] is bad\n";
			problem = true;
		}
		else
		{
			cout << "Allocate and [] are good\n";
		}

		vec.Deallocate(newElement);
		if(vec.IsAllocated(newElement) == true)
		{
			cout << "Deallocate or IsAllocated is bad\n";
			problem = true;
		}
		else
		{
			cout << "Deallocate and IsAllocated are good\n";
		}

		vec.Clear();
		if(vec.Size() > 0)
		{
			cout << "Clear or Size is bad\n";
			problem = true;
		}
		else
		{
			cout << "Clear and Size are good\n";
		}

		vec.Add(new size_t(10));
		vec.Add(new size_t(20));

		if(vec.Size() != 2 || vec[0] != 10 || vec[1] != 20)
		{
			cout << "Add is bad\n";
			problem = true;
		}
		else
		{
			cout << "Add is good\n";
		}

		if(*vec.Front() != vec[0] || *vec.Back() != vec[1])
		{
			cout << "Front or Back is bad\n";
			problem = true;
		}
		else
		{
			cout << "Front and Back are good\n";
		}

		size_t destination;
		vec.Get(&destination);
		if(vec.Size() != 1 || vec[0] != 20)
		{
			cout << "Get is bad\n";
			problem = true;
		}
		else
		{
			cout << "Get is good\n";
		}

		vec.Clear();
		
		vec.Resize(5);
		vec.ResizeAllocate(10,100);

		allocated = false;
		for(size_t n = 0;n<5;n++)
		{
			if(vec.IsAllocated(n) == true)
			{
				allocated = true;
				break;
			}
		}

		if(allocated == true)
		{
			cout << "Resize or ResizeAllocate is bad\n";
			problem = true;
		}
		else
		{
			cout << "Resize and ResizeAllocate are good\n";
		}

		allocated = true;
		for(size_t n = 5;n<vec.Size();n++)
		{
			if(vec.IsAllocated(n) == false)
			{
				allocated = true;
				break;
			}
		}

		if(allocated == false)
		{
			cout << "ResizeAllocate is bad\n";
			problem = true;
		}
		else
		{
			cout << "ResizeAllocate is good\n";
		}

		StoreVector<size_t> copyOperator(vec);
		bool same = (copyOperator.Size() == vec.Size());
		if(same == true)
		{
			for(size_t n = 0;n<copyOperator.Size();n++)
			{
				if(copyOperator.IsAllocated(n) == true && vec.IsAllocated(n) == true)
				{
					if(copyOperator[n] != vec[n])
					{
						same = false;
						break;
					}
				}
				else
				{
					if(copyOperator.IsAllocated(n) == true || vec.IsAllocated(n) == true)
					{
						same = false;
						break;
					}
				}
			}
		}

		if(same == false)
		{
			cout << "Copy constructor is bad\n";
			problem = true;
		}
		else
		{
			cout << "Copy constructor is good\n";
		}

		StoreVector<size_t> assignmentOperator;
		assignmentOperator = vec;
		same = (assignmentOperator.Size() == vec.Size());
		if(same == true)
		{
			for(size_t n = 0;n<assignmentOperator.Size();n++)
			{
				if(assignmentOperator.IsAllocated(n) == true && vec.IsAllocated(n) == true)
				{
					if(assignmentOperator[n] != vec[n])
					{
						same = false;
						break;
					}
				}
				else
				{
					if(assignmentOperator.IsAllocated(n) == true || vec.IsAllocated(n) == true)
					{
						same = false;
						break;
					}
				}
			}
		}

		if(same == false)
		{
			cout << "Assignment operator is bad\n";
			problem = true;
		}
		else
		{
			cout << "Assignment operator is good\n";
		}


		cout << "\n\n";
		return !problem;
	}

};