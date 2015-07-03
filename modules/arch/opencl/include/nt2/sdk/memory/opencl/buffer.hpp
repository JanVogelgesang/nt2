#ifndef NT2_SDK_COPENCL_BUFFER_HPP_INCLUDED
#define NT2_SDK_COPENCL_BUFFER_HPP_INCLUDED

#include <boost/compute/core.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/buffer.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/include/functions/resize.hpp>

//#include <nt2/include/functions/copy.hpp>

namespace nt2 { namespace memory {

namespace compute = boost::compute;

template<class T>
class opencl_buffer
{
 public:
  typedef typename compute::buffer_allocator<T> Alloc;
  typedef T value_type;
  typedef Alloc allocator_type;
  typedef typename allocator_type::size_type size_type;
  typedef typename allocator_type::difference_type difference_type;
  typedef compute::detail::buffer_value<T> reference;
  typedef const compute::detail::buffer_value<T> const_reference;
  typedef typename compute::vector<T> pointer;
  typedef typename compute::vector<T> const_pointer;
  typedef compute::buffer_iterator<T> iterator;
  typedef compute::buffer_iterator<T> const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  //==========================================================================
  // Constructors (default, size, copy) 
  //==========================================================================
  opencl_buffer(
      const compute::context & context = compute::system::default_context(),
      const compute::command_queue & queue = compute::system::default_queue()):
    _context(context),
    _queue  (queue),
    _vec    (context)
  {}

  opencl_buffer(
      size_t n,
      const compute::context & context = compute::system::default_context(),
      const compute::command_queue & queue = compute::system::default_queue()):
    _context(context),
    _queue  (queue),
    _vec    (n, context)
  {} 

  opencl_buffer(
      const opencl_buffer & ref,
      const compute::context & context = compute::system::default_context(),
      const compute::command_queue & queue = compute::system::default_queue()):
    _context(context),
    _queue  (queue),
    _vec    (ref._vec)
  {} 

  //==========================================================================
  // Destructor (actual work handled by compute::vector) 
  //==========================================================================
  ~opencl_buffer()
  {}

  //==========================================================================
  // Assignment operator
  //==========================================================================
  opencl_buffer& operator=(const opencl_buffer & eq)
  {
    this->_vec = eq.data();
    return *this;
  }

  //==========================================================================
  // Size info
  //==========================================================================
   size_type size() {
    return _vec.size();
  }

  bool empty() {
    return _vec.empty();
  }

  void resize(size_type sz) {
    if ( sz > this->size() ) {
      _vec.resize(sz);
    }
  }


  //==========================================================================
  // Forbid direct accessors
  //==========================================================================
   BOOST_FORCEINLINE reference operator[](size_type )
  {
    static value_type x = 0;
    static_assert( x == 0 , "operator[] not available for cuda buffers");
    return x;
  }

  /// @overload
  BOOST_FORCEINLINE const_reference operator[](size_type ) const
  {
    static value_type x = 0 ;
    static_assert( x == 0 , "operator[] not available for cuda buffers");
    return x;
  }



  void swap(opencl_buffer<T> & swp)
  {
    this->_vec.swap(swp._vec);
  }

  // TODO: Does anyone else need data or iterators? if not, don't bother
  compute::vector<T> & data()
  {
    return _vec;
  }

  void data(std::vector<T> & copy_into) const
  {
    if(!this->size()) return;
    if ( copy_into.size() != this->size() ) copy_into.resize(this->size());

    compute::copy(_vec.begin(), _vec.end(), copy_into.data());

  }

  template<typename Container>
  void data(Container & copy_into) const
  {
    if(!this->size()) return;
    if ( copy_into.size() != this->size() ) copy_into.resize(nt2::of_size(this->size(),1));

    compute::copy(_vec.begin(), _vec.end(), copy_into.data());
  }

  size_t size() const
  {
    return _vec.size();
  }

// private:
  compute::context       _context;
  compute::command_queue _queue;
  compute::vector<T>     _vec;
};

} } // end namespaces nt2/memory

#endif//def opencl_buffer_hpp
