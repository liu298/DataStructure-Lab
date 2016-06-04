/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */
#include "exercises.h"
namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */

template <typename T>
T sum(stack<T>& s)
{	
	T stack_sum ;
	T temp;
   if(s.empty())
     return T(); 
   else
	{
	temp = s.top();
	s.pop();
	stack_sum = sum(s) + temp;
	s.push(temp);
	return stack_sum; 
	} // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    T temp;
    size_t i=0;
    size_t sum_size=0;
    // optional: queue<T> q2;
    while(sum_size <= q.size())
      {
	i++;
       	sum_size += i;
       	if(sum_size >q.size())  //leftover
	  {
	    size_t leftover = q.size()-sum_size+i;
	    if(i%2)
	      {
		for(size_t j=0;j<leftover;j++) //leftover in odd block
	     {
	       temp = q.front();
	       q.pop();
	       q.push(temp);
	     }
	      }
	    else  //leftover in even block
	    {
	    for(size_t j=0;j<leftover;j++) //push the leftover into a stack
	       {
		 temp=q.front();
		 s.push(temp);
		 q.pop();
	        }
	    for(size_t j=0;j<leftover;j++) //pop the leftover from the stack REVERSED
	       {
		 temp=s.top();
		 q.push(temp);
		 s.pop();
	        }
	     }
	  }
	else if(i%2)//odd block placed on the queue in the original order
	  {
	    for(size_t j=0;j<i;j++)
	     {
	       temp = q.front();
	       q.pop();
	       q.push(temp);
	     }
	  }
	else //even block reverses
          {
	    for(size_t j=0;j<i;j++) //push the even block into a stack
	       {
		 temp=q.front();
		 s.push(temp);
		 q.pop();
	        }
	    for(size_t j=0;j<i;j++) //pop the even block from the stack REVERSED
	       {
		 temp=s.top();
		 q.push(temp);
		 s.pop();
	        }
	  }
      }
    return;
  
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
	T s_temp;
	T q_temp;
	bool retval;

   if(s.size()==0)
    return true;
   s_temp = s.top();
   s.pop();
   retval = verifySame(s,q);
   if(s.top() != q.front())
   	 retval = false;
   else
   {
   	retval = true;
   	q_temp = q.front();
   	q.pop();
  
    q.push(q_temp);
	}
	
	s.push(s_temp);
	return retval;
	 

}
}