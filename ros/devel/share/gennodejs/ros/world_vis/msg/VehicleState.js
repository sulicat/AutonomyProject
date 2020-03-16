// Auto-generated. Do not edit!

// (in-package world_vis.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class VehicleState {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.pos = null;
      this.steering_angle = null;
      this.vehicle_angle = null;
      this.vehicle_width = null;
      this.vehicle_length = null;
      this.linear_vel = null;
      this.steering_angle_vel = null;
      this.linear_accel = null;
      this.steering_angle_acel = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('pos')) {
        this.pos = initObj.pos
      }
      else {
        this.pos = new geometry_msgs.msg.Vector3();
      }
      if (initObj.hasOwnProperty('steering_angle')) {
        this.steering_angle = initObj.steering_angle
      }
      else {
        this.steering_angle = 0.0;
      }
      if (initObj.hasOwnProperty('vehicle_angle')) {
        this.vehicle_angle = initObj.vehicle_angle
      }
      else {
        this.vehicle_angle = 0.0;
      }
      if (initObj.hasOwnProperty('vehicle_width')) {
        this.vehicle_width = initObj.vehicle_width
      }
      else {
        this.vehicle_width = 0.0;
      }
      if (initObj.hasOwnProperty('vehicle_length')) {
        this.vehicle_length = initObj.vehicle_length
      }
      else {
        this.vehicle_length = 0.0;
      }
      if (initObj.hasOwnProperty('linear_vel')) {
        this.linear_vel = initObj.linear_vel
      }
      else {
        this.linear_vel = 0.0;
      }
      if (initObj.hasOwnProperty('steering_angle_vel')) {
        this.steering_angle_vel = initObj.steering_angle_vel
      }
      else {
        this.steering_angle_vel = 0.0;
      }
      if (initObj.hasOwnProperty('linear_accel')) {
        this.linear_accel = initObj.linear_accel
      }
      else {
        this.linear_accel = 0.0;
      }
      if (initObj.hasOwnProperty('steering_angle_acel')) {
        this.steering_angle_acel = initObj.steering_angle_acel
      }
      else {
        this.steering_angle_acel = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type VehicleState
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [pos]
    bufferOffset = geometry_msgs.msg.Vector3.serialize(obj.pos, buffer, bufferOffset);
    // Serialize message field [steering_angle]
    bufferOffset = _serializer.float32(obj.steering_angle, buffer, bufferOffset);
    // Serialize message field [vehicle_angle]
    bufferOffset = _serializer.float32(obj.vehicle_angle, buffer, bufferOffset);
    // Serialize message field [vehicle_width]
    bufferOffset = _serializer.float32(obj.vehicle_width, buffer, bufferOffset);
    // Serialize message field [vehicle_length]
    bufferOffset = _serializer.float32(obj.vehicle_length, buffer, bufferOffset);
    // Serialize message field [linear_vel]
    bufferOffset = _serializer.float32(obj.linear_vel, buffer, bufferOffset);
    // Serialize message field [steering_angle_vel]
    bufferOffset = _serializer.float32(obj.steering_angle_vel, buffer, bufferOffset);
    // Serialize message field [linear_accel]
    bufferOffset = _serializer.float32(obj.linear_accel, buffer, bufferOffset);
    // Serialize message field [steering_angle_acel]
    bufferOffset = _serializer.float32(obj.steering_angle_acel, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type VehicleState
    let len;
    let data = new VehicleState(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [pos]
    data.pos = geometry_msgs.msg.Vector3.deserialize(buffer, bufferOffset);
    // Deserialize message field [steering_angle]
    data.steering_angle = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [vehicle_angle]
    data.vehicle_angle = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [vehicle_width]
    data.vehicle_width = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [vehicle_length]
    data.vehicle_length = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [linear_vel]
    data.linear_vel = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [steering_angle_vel]
    data.steering_angle_vel = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [linear_accel]
    data.linear_accel = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [steering_angle_acel]
    data.steering_angle_acel = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 56;
  }

  static datatype() {
    // Returns string type for a message object
    return 'world_vis/VehicleState';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '43281be11163876743cb99e5003e3502';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    geometry_msgs/Vector3 pos
    float32 steering_angle
    float32 vehicle_angle
    float32 vehicle_width
    float32 vehicle_length
    float32 linear_vel
    float32 steering_angle_vel
    float32 linear_accel
    float32 steering_angle_acel
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    string frame_id
    
    ================================================================================
    MSG: geometry_msgs/Vector3
    # This represents a vector in free space. 
    # It is only meant to represent a direction. Therefore, it does not
    # make sense to apply a translation to it (e.g., when applying a 
    # generic rigid transformation to a Vector3, tf2 will only apply the
    # rotation). If you want your data to be translatable too, use the
    # geometry_msgs/Point message instead.
    
    float64 x
    float64 y
    float64 z
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new VehicleState(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.pos !== undefined) {
      resolved.pos = geometry_msgs.msg.Vector3.Resolve(msg.pos)
    }
    else {
      resolved.pos = new geometry_msgs.msg.Vector3()
    }

    if (msg.steering_angle !== undefined) {
      resolved.steering_angle = msg.steering_angle;
    }
    else {
      resolved.steering_angle = 0.0
    }

    if (msg.vehicle_angle !== undefined) {
      resolved.vehicle_angle = msg.vehicle_angle;
    }
    else {
      resolved.vehicle_angle = 0.0
    }

    if (msg.vehicle_width !== undefined) {
      resolved.vehicle_width = msg.vehicle_width;
    }
    else {
      resolved.vehicle_width = 0.0
    }

    if (msg.vehicle_length !== undefined) {
      resolved.vehicle_length = msg.vehicle_length;
    }
    else {
      resolved.vehicle_length = 0.0
    }

    if (msg.linear_vel !== undefined) {
      resolved.linear_vel = msg.linear_vel;
    }
    else {
      resolved.linear_vel = 0.0
    }

    if (msg.steering_angle_vel !== undefined) {
      resolved.steering_angle_vel = msg.steering_angle_vel;
    }
    else {
      resolved.steering_angle_vel = 0.0
    }

    if (msg.linear_accel !== undefined) {
      resolved.linear_accel = msg.linear_accel;
    }
    else {
      resolved.linear_accel = 0.0
    }

    if (msg.steering_angle_acel !== undefined) {
      resolved.steering_angle_acel = msg.steering_angle_acel;
    }
    else {
      resolved.steering_angle_acel = 0.0
    }

    return resolved;
    }
};

module.exports = VehicleState;
