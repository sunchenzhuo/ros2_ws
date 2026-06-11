#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to base_demo_cpp__msg__BaseStatus

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub err: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub cmd_timeout: bool,

}



impl Default for BaseStatus {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::BaseStatus::default())
  }
}

impl rosidl_runtime_rs::Message for BaseStatus {
  type RmwMsg = super::msg::rmw::BaseStatus;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        seq: msg.seq,
        vx: msg.vx,
        vy: msg.vy,
        wz: msg.wz,
        battery_voltage: msg.battery_voltage,
        err: msg.err.as_str().into(),
        cmd_timeout: msg.cmd_timeout,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      seq: msg.seq,
      vx: msg.vx,
      vy: msg.vy,
      wz: msg.wz,
      battery_voltage: msg.battery_voltage,
        err: msg.err.as_str().into(),
      cmd_timeout: msg.cmd_timeout,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      seq: msg.seq,
      vx: msg.vx,
      vy: msg.vy,
      wz: msg.wz,
      battery_voltage: msg.battery_voltage,
      err: msg.err.to_string(),
      cmd_timeout: msg.cmd_timeout,
    }
  }
}


