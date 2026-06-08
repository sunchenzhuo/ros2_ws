#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "base_demo_cpp__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__base_demo_cpp__msg__BaseStatus() -> *const std::ffi::c_void;
}

#[link(name = "base_demo_cpp__rosidl_generator_c")]
extern "C" {
    fn base_demo_cpp__msg__BaseStatus__init(msg: *mut BaseStatus) -> bool;
    fn base_demo_cpp__msg__BaseStatus__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<BaseStatus>, size: usize) -> bool;
    fn base_demo_cpp__msg__BaseStatus__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<BaseStatus>);
    fn base_demo_cpp__msg__BaseStatus__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<BaseStatus>, out_seq: *mut rosidl_runtime_rs::Sequence<BaseStatus>) -> bool;
}

// Corresponds to base_demo_cpp__msg__BaseStatus
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BaseStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub seq: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub vx: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub vy: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub wz: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub battery_voltage: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub err: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub cmd_timeout: bool,

}



impl Default for BaseStatus {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !base_demo_cpp__msg__BaseStatus__init(&mut msg as *mut _) {
        panic!("Call to base_demo_cpp__msg__BaseStatus__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for BaseStatus {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { base_demo_cpp__msg__BaseStatus__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { base_demo_cpp__msg__BaseStatus__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { base_demo_cpp__msg__BaseStatus__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for BaseStatus {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for BaseStatus where Self: Sized {
  const TYPE_NAME: &'static str = "base_demo_cpp/msg/BaseStatus";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__base_demo_cpp__msg__BaseStatus() }
  }
}


