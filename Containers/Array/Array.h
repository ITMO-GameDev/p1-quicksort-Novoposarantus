#pragma once

namespace containers {
	const int emptyConstructArraySize = 8;

	template <typename T>
	class DynamicArray
	{
	public:

		class Iterator
		{
			friend class DynamicArray<T>;
		public:
			Iterator(DynamicArray<T>& arrRef);
			const T& get() const;
			void set(const T& value);
			void insert(const T& value);
			void remove();
			void next();
			void prev();
			void toIndex(int index);
			bool hasNext() const;
			bool hasPrev() const;
		private:
			int index;
			DynamicArray<T>& arrRef;
		};

		DynamicArray();
		DynamicArray(int capacity);
		~DynamicArray();
		int size(); 
		void insert(const T& value);
		void insert(int index, const T& value);
		void remove(int index);
		const T& DynamicArray<T>::operator[](int index) const;
		T& operator[](int index);
		Iterator iterator() {
			Iterator iterator(*this);
			return iterator;
		}
		const Iterator iterator() const {
			Iterator iterator(*this);
			return iterator;
		}

	private:
		int realSize;
		int publicSize;
		T* arr;
		void increaseSize();
		void increaseSize(int index, const T& value);
	};

	//DynamicArray
	//public

	template <typename T>
	DynamicArray<T>::DynamicArray() {
		arr = new T[emptyConstructArraySize];
		realSize = emptyConstructArraySize;
		publicSize = 0;
	}

	template <typename T>
	DynamicArray<T>::DynamicArray(int capacity) {
		arr = new T[capacity];
		realSize = capacity;
		publicSize = capacity;
	}

	template <typename T>
	DynamicArray<T>::~DynamicArray() {
		delete[] arr;
	}

	template <typename T>
	const T& DynamicArray<T>::operator[](int index) const {
		if (index < 0 || index >= publicSize) {
			throw std::out_of_range("index out of range");
		}
		return arr[index];
	}

	template <typename T>
	T& DynamicArray<T>::operator[](int index) {
		if (index < 0 || index >= publicSize) {
			throw std::out_of_range("index out of range");
		}
		return arr[index];
	}

	template <typename T>
	int DynamicArray<T>::size() {
		return publicSize;
	}

	template <typename T>
	void DynamicArray<T>::insert(const T& value) {
		if (publicSize == realSize) {
			increaseSize();
		}

		arr[publicSize] = value;
		publicSize++;
	}

	template <typename T>
	void DynamicArray<T>::insert(int index, const T& value) {
		if (realSize == index) {
			increaseSize();
			arr[index] = value;
			publicSize++;
		}

		if (publicSize == realSize) {
			increaseSize(index, value);
			return;
		}

		for (int i = realSize - 2; i >= index; --i) {
			arr[i + 1] = arr[i];
		}
		arr[index] = value;
		publicSize++;
	}

	template <typename T>
	void DynamicArray<T>::remove(int index) {
		for (int i = index; i < realSize - 1; ++i) {
			arr[i] = arr[i + 1];
		}
		publicSize--;
	}
	//end public

	//private

	template <typename T>
	void DynamicArray<T>::increaseSize() {
		realSize = (int)(realSize * 1.6);
		T* newArray = new T[realSize];
		for (int i = 0; i < publicSize; ++i) {
			newArray[i] = arr[i];
		}
		arr = newArray;
	}

	template <typename T>
	void DynamicArray<T>::increaseSize(int index, const T& value) {
		publicSize++;
		realSize = (int)(realSize * 1.6);
		T* newArray = new T[realSize];
		int supIndex = 0;
		for (int i = 0; i < publicSize; ++i) {
			if (i == index) {
				newArray[i + supIndex] = value;
				++supIndex;
			}
			newArray[i + supIndex] = arr[i];
		}
		arr = newArray;
	}

	//end private
	//end DynamicArray

	//Iterator
	//public

	template <typename T>
	DynamicArray<T>::Iterator::Iterator(DynamicArray<T>& arrRef) : arrRef(arrRef)
	{
		index = 0;
	}

	template <typename T>
	const T& DynamicArray<T>::Iterator::get() const {
		return arrRef.arr[index];
	}

	template <typename T>
	void DynamicArray<T>::Iterator::set(const T& value) {
		arrRef.arr[index] = value;
	}

	template <typename T>
	void DynamicArray<T>::Iterator::insert(const T& value) {
		arrRef.insert(index, value);
	}

	template <typename T>
	void DynamicArray<T>::Iterator::remove() {
		arrRef.remove(index);
	}
	template <typename T>
	void DynamicArray<T>::Iterator::next() {
		index++;
	}

	template <typename T>
	void DynamicArray<T>::Iterator::prev() {
		index--;
	}

	template <typename T>
	void DynamicArray<T>::Iterator::toIndex(int index) {
		this->index = index;
	}

	template <typename T>
	bool DynamicArray<T>::Iterator::hasNext() const {
		return index < arrRef.publicSize - 1;
	}

	template <typename T>
	bool DynamicArray<T>::Iterator::hasPrev() const {
		return index > 1;
	}
	//end public
}
