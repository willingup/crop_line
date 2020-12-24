// Generated by gencpp from file line_follower/pos.msg
// DO NOT EDIT!


#ifndef LINE_FOLLOWER_MESSAGE_POS_H
#define LINE_FOLLOWER_MESSAGE_POS_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace line_follower
{
template <class ContainerAllocator>
struct pos_
{
  typedef pos_<ContainerAllocator> Type;

  pos_()
    : direction(0)  {
    }
  pos_(const ContainerAllocator& _alloc)
    : direction(0)  {
  (void)_alloc;
    }



   typedef int32_t _direction_type;
  _direction_type direction;





  typedef boost::shared_ptr< ::line_follower::pos_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::line_follower::pos_<ContainerAllocator> const> ConstPtr;

}; // struct pos_

typedef ::line_follower::pos_<std::allocator<void> > pos;

typedef boost::shared_ptr< ::line_follower::pos > posPtr;
typedef boost::shared_ptr< ::line_follower::pos const> posConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::line_follower::pos_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::line_follower::pos_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::line_follower::pos_<ContainerAllocator1> & lhs, const ::line_follower::pos_<ContainerAllocator2> & rhs)
{
  return lhs.direction == rhs.direction;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::line_follower::pos_<ContainerAllocator1> & lhs, const ::line_follower::pos_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace line_follower

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::line_follower::pos_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::line_follower::pos_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::line_follower::pos_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::line_follower::pos_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::line_follower::pos_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::line_follower::pos_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::line_follower::pos_<ContainerAllocator> >
{
  static const char* value()
  {
    return "3b685cbe3a2d37c79069d18fc947a4de";
  }

  static const char* value(const ::line_follower::pos_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x3b685cbe3a2d37c7ULL;
  static const uint64_t static_value2 = 0x9069d18fc947a4deULL;
};

template<class ContainerAllocator>
struct DataType< ::line_follower::pos_<ContainerAllocator> >
{
  static const char* value()
  {
    return "line_follower/pos";
  }

  static const char* value(const ::line_follower::pos_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::line_follower::pos_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int32 direction\n"
;
  }

  static const char* value(const ::line_follower::pos_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::line_follower::pos_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.direction);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct pos_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::line_follower::pos_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::line_follower::pos_<ContainerAllocator>& v)
  {
    s << indent << "direction: ";
    Printer<int32_t>::stream(s, indent + "  ", v.direction);
  }
};

} // namespace message_operations
} // namespace ros

#endif // LINE_FOLLOWER_MESSAGE_POS_H
