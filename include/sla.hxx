#ifndef __SLA_HXX__
#define __SLA_HXX__

#include <cstddef>
#include <vector>
#include <limits>
#include <type_traits>
#include <stdexcept>

template <typename T> class SlabAllocator {
	private:
	std::vector<T*> blocks;
	T *head;
	std::size_t tail_block_size;
	std::size_t total_size;
	
	public:
	typedef T value_type;
	
	std::size_t max_size() const {
		return 1;
	}
	
	SlabAllocator(std::size_t reserve = (4095u + sizeof(T))/sizeof(T)){
		this->head = static_cast<T*>(::operator new(reserve*sizeof(T)));
		this->blocks = {this->head};
		this->tail_block_size = reserve;
		this->total_size = reserve;
		for(std::size_t i = 0; i + 1 < reserve; ++i){
			*reinterpret_cast<T**>(this->head + i) = this->head + i + 1;
		}
	}
	
	SlabAllocator(const SlabAllocator &other){
		this->head = ::operator new(other.total_size*sizeof(T));
		this->blocks = {this->head};
		this->tail_block_size = other.tail_block_size;
		this->total_size = other.total_size;
		for(std::size_t i = 0; i + 1 < this->total_size; ++i){
			*reinterpret_cast<T**>(this->head + i) = this->head + i + 1;
		}
	}
	
	template <typename U> SlabAllocator(const std::enable_if_t<sizeof(U) == sizeof(T), const SlabAllocator<U>&> other){
		this->head = ::operator new(other.total_size*sizeof(T));
		this->blocks = {this->head};
		this->tail_block_size = other.tail_block_size;
		this->total_size = other.total_size;
		for(std::size_t i = 0; i + 1 < this->total_size; ++i){
			*reinterpret_cast<T**>(this->head + i) = this->head + i + 1;
		}
	}
	
	~SlabAllocator(){//todo: clean up un-freed objects
		for(T *block : this->blocks){
			::operator delete(block);
		}
	}
	
	T *allocate(const std::size_t n){
		if(!n){
			return nullptr;
		}else if(n != 1){
			throw std::length_error("SlabAllocator::allocate(): request too big");
		}else if(!this->head){
			this->head = static_cast<T*>(::operator new(this->tail_block_size*2*sizeof(T)));
			this->blocks.push_back(this->head);
			this->tail_block_size *= 2;
			this->total_size += this->tail_block_size;
			for(std::size_t i = 0; i + 1 < this->tail_block_size; ++i){
				*reinterpret_cast<T**>(this->head + i) = this->head + i + 1;
			}
		}
		T *ret = this->head;
		this->head = *reinterpret_cast<T**>(ret);
		return ret;
	}
	
	void deallocate(T *p, std::size_t n){
		*reinterpret_cast<T**>(p) = this->head;
		this->head = p;
	}
	
	template <typename U> T *allocate(size_t n, const U *hint) const {
		return this->allocate(n);
	}
	
	SlabAllocator &operator = (const SlabAllocator&) = delete;
};

template <typename T, typename U>
bool operator != (const SlabAllocator<T> &a, const SlabAllocator<U> &b){
	return !operator == (a, b);
}

template <typename T, typename U>
bool operator == (const SlabAllocator<T> &a, const SlabAllocator<U> &b){
	return static_cast<void*>(a.blocks.front()) == static_cast<void*>(b.blocks.front());
}

#endif

