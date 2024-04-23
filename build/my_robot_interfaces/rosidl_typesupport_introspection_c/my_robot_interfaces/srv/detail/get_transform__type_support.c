// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from my_robot_interfaces:srv/GetTransform.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "my_robot_interfaces/srv/detail/get_transform__rosidl_typesupport_introspection_c.h"
#include "my_robot_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "my_robot_interfaces/srv/detail/get_transform__functions.h"
#include "my_robot_interfaces/srv/detail/get_transform__struct.h"


// Include directives for member types
// Member `frame_id`
// Member `child_frame_id`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void my_robot_interfaces__srv__GetTransform_Request__rosidl_typesupport_introspection_c__GetTransform_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  my_robot_interfaces__srv__GetTransform_Request__init(message_memory);
}

void my_robot_interfaces__srv__GetTransform_Request__rosidl_typesupport_introspection_c__GetTransform_Request_fini_function(void * message_memory)
{
  my_robot_interfaces__srv__GetTransform_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember my_robot_interfaces__srv__GetTransform_Request__rosidl_typesupport_introspection_c__GetTransform_Request_message_member_array[2] = {
  {
    "frame_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(my_robot_interfaces__srv__GetTransform_Request, frame_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "child_frame_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(my_robot_interfaces__srv__GetTransform_Request, child_frame_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers my_robot_interfaces__srv__GetTransform_Request__rosidl_typesupport_introspection_c__GetTransform_Request_message_members = {
  "my_robot_interfaces__srv",  // message namespace
  "GetTransform_Request",  // message name
  2,  // number of fields
  sizeof(my_robot_interfaces__srv__GetTransform_Request),
  my_robot_interfaces__srv__GetTransform_Request__rosidl_typesupport_introspection_c__GetTransform_Request_message_member_array,  // message members
  my_robot_interfaces__srv__GetTransform_Request__rosidl_typesupport_introspection_c__GetTransform_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  my_robot_interfaces__srv__GetTransform_Request__rosidl_typesupport_introspection_c__GetTransform_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t my_robot_interfaces__srv__GetTransform_Request__rosidl_typesupport_introspection_c__GetTransform_Request_message_type_support_handle = {
  0,
  &my_robot_interfaces__srv__GetTransform_Request__rosidl_typesupport_introspection_c__GetTransform_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_my_robot_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, my_robot_interfaces, srv, GetTransform_Request)() {
  if (!my_robot_interfaces__srv__GetTransform_Request__rosidl_typesupport_introspection_c__GetTransform_Request_message_type_support_handle.typesupport_identifier) {
    my_robot_interfaces__srv__GetTransform_Request__rosidl_typesupport_introspection_c__GetTransform_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &my_robot_interfaces__srv__GetTransform_Request__rosidl_typesupport_introspection_c__GetTransform_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "my_robot_interfaces/srv/detail/get_transform__rosidl_typesupport_introspection_c.h"
// already included above
// #include "my_robot_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "my_robot_interfaces/srv/detail/get_transform__functions.h"
// already included above
// #include "my_robot_interfaces/srv/detail/get_transform__struct.h"


// Include directives for member types
// Member `transform`
#include "geometry_msgs/msg/transform_stamped.h"
// Member `transform`
#include "geometry_msgs/msg/detail/transform_stamped__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void my_robot_interfaces__srv__GetTransform_Response__rosidl_typesupport_introspection_c__GetTransform_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  my_robot_interfaces__srv__GetTransform_Response__init(message_memory);
}

void my_robot_interfaces__srv__GetTransform_Response__rosidl_typesupport_introspection_c__GetTransform_Response_fini_function(void * message_memory)
{
  my_robot_interfaces__srv__GetTransform_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember my_robot_interfaces__srv__GetTransform_Response__rosidl_typesupport_introspection_c__GetTransform_Response_message_member_array[2] = {
  {
    "transform",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(my_robot_interfaces__srv__GetTransform_Response, transform),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(my_robot_interfaces__srv__GetTransform_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers my_robot_interfaces__srv__GetTransform_Response__rosidl_typesupport_introspection_c__GetTransform_Response_message_members = {
  "my_robot_interfaces__srv",  // message namespace
  "GetTransform_Response",  // message name
  2,  // number of fields
  sizeof(my_robot_interfaces__srv__GetTransform_Response),
  my_robot_interfaces__srv__GetTransform_Response__rosidl_typesupport_introspection_c__GetTransform_Response_message_member_array,  // message members
  my_robot_interfaces__srv__GetTransform_Response__rosidl_typesupport_introspection_c__GetTransform_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  my_robot_interfaces__srv__GetTransform_Response__rosidl_typesupport_introspection_c__GetTransform_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t my_robot_interfaces__srv__GetTransform_Response__rosidl_typesupport_introspection_c__GetTransform_Response_message_type_support_handle = {
  0,
  &my_robot_interfaces__srv__GetTransform_Response__rosidl_typesupport_introspection_c__GetTransform_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_my_robot_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, my_robot_interfaces, srv, GetTransform_Response)() {
  my_robot_interfaces__srv__GetTransform_Response__rosidl_typesupport_introspection_c__GetTransform_Response_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, TransformStamped)();
  if (!my_robot_interfaces__srv__GetTransform_Response__rosidl_typesupport_introspection_c__GetTransform_Response_message_type_support_handle.typesupport_identifier) {
    my_robot_interfaces__srv__GetTransform_Response__rosidl_typesupport_introspection_c__GetTransform_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &my_robot_interfaces__srv__GetTransform_Response__rosidl_typesupport_introspection_c__GetTransform_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "my_robot_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "my_robot_interfaces/srv/detail/get_transform__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers my_robot_interfaces__srv__detail__get_transform__rosidl_typesupport_introspection_c__GetTransform_service_members = {
  "my_robot_interfaces__srv",  // service namespace
  "GetTransform",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // my_robot_interfaces__srv__detail__get_transform__rosidl_typesupport_introspection_c__GetTransform_Request_message_type_support_handle,
  NULL  // response message
  // my_robot_interfaces__srv__detail__get_transform__rosidl_typesupport_introspection_c__GetTransform_Response_message_type_support_handle
};

static rosidl_service_type_support_t my_robot_interfaces__srv__detail__get_transform__rosidl_typesupport_introspection_c__GetTransform_service_type_support_handle = {
  0,
  &my_robot_interfaces__srv__detail__get_transform__rosidl_typesupport_introspection_c__GetTransform_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, my_robot_interfaces, srv, GetTransform_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, my_robot_interfaces, srv, GetTransform_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_my_robot_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, my_robot_interfaces, srv, GetTransform)() {
  if (!my_robot_interfaces__srv__detail__get_transform__rosidl_typesupport_introspection_c__GetTransform_service_type_support_handle.typesupport_identifier) {
    my_robot_interfaces__srv__detail__get_transform__rosidl_typesupport_introspection_c__GetTransform_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)my_robot_interfaces__srv__detail__get_transform__rosidl_typesupport_introspection_c__GetTransform_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, my_robot_interfaces, srv, GetTransform_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, my_robot_interfaces, srv, GetTransform_Response)()->data;
  }

  return &my_robot_interfaces__srv__detail__get_transform__rosidl_typesupport_introspection_c__GetTransform_service_type_support_handle;
}
