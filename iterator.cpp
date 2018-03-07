#include "iterator.h"

OperatorIterator::OperatorIterator(Base * ptr) : Iterator(ptr) { };
UnaryIterator::UnaryIterator(Base * ptr) : Iterator(ptr) { };
NullIterator::NullIterator(Base * ptr) : Iterator(ptr) { };
PreOrderIterator::PreOrderIterator(Base * ptr) : Iterator(ptr) { };

void OperatorIterator::first() {
    current_ptr = self_ptr->get_left();
}

void OperatorIterator::next() {
    if (current_ptr == self_ptr->get_left()) {
        current_ptr = self_ptr->get_right();
    } else {
        current_ptr = NULL;
    }
    
}

bool OperatorIterator::is_done() {
    if (current_ptr == NULL) {
        return true;
    }
    
    return false;
}

Base * OperatorIterator::current() {
    return current_ptr;
}

void UnaryIterator::first() {
    current_ptr = self_ptr->get_left();
}

void UnaryIterator::next() {
    current_ptr = NULL;
}

bool UnaryIterator::is_done() {
    if(current_ptr == NULL) {
        return true;
    }
    return false;
}

Base* UnaryIterator::current() {
    return current_ptr;
}

void NullIterator::first(){
    current_ptr = NULL;
}

void NullIterator:: next(){
    current_ptr = NULL;
}

bool NullIterator::is_done(){
    return true;
}

Base* NullIterator::current(){
    return current_ptr;
}

void PreOrderIterator::first() {
    while (!iterators.empty()) {
        iterators.pop();
    }
    
    Iterator * firstIt = self_ptr->create_iterator();
    firstIt->first();
    iterators.push(firstIt);
    current_ptr = firstIt->current();
    firstIt = 0;
    
    
    // Empty the stack (just in case we had something leftover from another run)
    // Create an iterator for the Base* that we built the iterator for
    // Initialize that iterator and push it onto the stack
}

void PreOrderIterator::next() {

    while (iterators.top()->is_done()) {
        iterators.pop();
    }
    
    Iterator * nextIt = iterators.top()->current()->create_iterator();
    nextIt->first();
    iterators.push(nextIt);
    current_ptr = nextIt->current();
    nextIt = 0;
    
    while (iterators.top()->is_done()){
        iterators.pop();
        if (!iterators.empty()) {
            iterators.top()->next();
            current_ptr = iterators.top()->current();
        } else { break; }
    }

    // Create an iterator for the item on the top of the stack
    // Initialize the iterator and push it onto the stack
    // As long as the top iterator on the stack is_done(), pop it off the stack and then advance whatever iterator is now on top of the stack
}

bool PreOrderIterator::is_done() {
    if(iterators.empty()){
        return true;
    }
    return false;
    // Return true if there are no more elements on the stack to iterate
}

Base* PreOrderIterator::current() {
    // Return the current for the top iterator in the stack
    if (!iterators.empty()) {
        return iterators.top()->current();
    }
    
    return NULL;
}




