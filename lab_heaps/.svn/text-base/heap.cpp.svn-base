/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    /// @todo Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the left child.
    return (2*currentIdx);
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the right child.
    return (2*currentIdx+1);
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    /// @todo Update to return the index of the parent.
    return (currentIdx/2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    /// @todo Update to return whether the given node has a child
    bool ret;
    if(leftChild(currentIdx)<=size)
        ret = true;
    else ret = false;
    return ret;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    size_t leftChildIdx = leftChild(currentIdx);
    size_t rightChildIdx = rightChild(currentIdx);
    if(rightChildIdx > size)
        return leftChildIdx;
    if(higherPriority(_elems[leftChildIdx],_elems[rightChildIdx]))
        return leftChildIdx;
    else return rightChildIdx;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    /// @todo Implement the heapifyDown algorithm.
    if(!hasAChild(currentIdx))
        return;
    size_t minChildInx = maxPriorityChild(currentIdx);
    if(higherPriority(_elems[minChildInx], _elems[currentIdx]))
    {
        std::swap(_elems[currentIdx], _elems[minChildInx]);
        heapifyDown(minChildInx); 
    }

}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
    size = 0;
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    /// @todo Construct a heap using the buildHeap algorithm
    if(elems.empty())
    {
        _elems.push_back(T());
        size = 0;
    }
    
    else
    {
        size = elems.size();

        _elems.push_back(T());
        for(size_t i=0;i<size;i++)
            _elems.push_back(elems[i]);

        for(size_t i = parent(size);i>0;i--)
            heapifyDown(i);
    }  

}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    /// @todo Remove, and return, the element with highest priority
    T ret = _elems[1];
    _elems[1] = _elems[size];
    _elems.pop_back();
    size--;
    heapifyDown(1);
    return ret;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    /// @todo Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    /// @todo Add elem to the heap
    size++;
    _elems.push_back(elem);
    heapifyUp(size);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
    if(size>0)
        return false;
    else return true;
}
