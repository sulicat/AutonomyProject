; Auto-generated. Do not edit!


(cl:in-package world_vis-msg)


;//! \htmlinclude VehicleMoveCommand.msg.html

(cl:defclass <VehicleMoveCommand> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (linear_vel
    :reader linear_vel
    :initarg :linear_vel
    :type cl:float
    :initform 0.0)
   (steering_angle_vel
    :reader steering_angle_vel
    :initarg :steering_angle_vel
    :type cl:float
    :initform 0.0))
)

(cl:defclass VehicleMoveCommand (<VehicleMoveCommand>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VehicleMoveCommand>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VehicleMoveCommand)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name world_vis-msg:<VehicleMoveCommand> is deprecated: use world_vis-msg:VehicleMoveCommand instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <VehicleMoveCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world_vis-msg:header-val is deprecated.  Use world_vis-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'linear_vel-val :lambda-list '(m))
(cl:defmethod linear_vel-val ((m <VehicleMoveCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world_vis-msg:linear_vel-val is deprecated.  Use world_vis-msg:linear_vel instead.")
  (linear_vel m))

(cl:ensure-generic-function 'steering_angle_vel-val :lambda-list '(m))
(cl:defmethod steering_angle_vel-val ((m <VehicleMoveCommand>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world_vis-msg:steering_angle_vel-val is deprecated.  Use world_vis-msg:steering_angle_vel instead.")
  (steering_angle_vel m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VehicleMoveCommand>) ostream)
  "Serializes a message object of type '<VehicleMoveCommand>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'linear_vel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'steering_angle_vel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VehicleMoveCommand>) istream)
  "Deserializes a message object of type '<VehicleMoveCommand>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'linear_vel) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'steering_angle_vel) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VehicleMoveCommand>)))
  "Returns string type for a message object of type '<VehicleMoveCommand>"
  "world_vis/VehicleMoveCommand")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VehicleMoveCommand)))
  "Returns string type for a message object of type 'VehicleMoveCommand"
  "world_vis/VehicleMoveCommand")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VehicleMoveCommand>)))
  "Returns md5sum for a message object of type '<VehicleMoveCommand>"
  "10971e0348cab38ff52d6137bdf2a0a6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VehicleMoveCommand)))
  "Returns md5sum for a message object of type 'VehicleMoveCommand"
  "10971e0348cab38ff52d6137bdf2a0a6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VehicleMoveCommand>)))
  "Returns full string definition for message of type '<VehicleMoveCommand>"
  (cl:format cl:nil "Header header~%float32 linear_vel~%float32 steering_angle_vel~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VehicleMoveCommand)))
  "Returns full string definition for message of type 'VehicleMoveCommand"
  (cl:format cl:nil "Header header~%float32 linear_vel~%float32 steering_angle_vel~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VehicleMoveCommand>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VehicleMoveCommand>))
  "Converts a ROS message object to a list"
  (cl:list 'VehicleMoveCommand
    (cl:cons ':header (header msg))
    (cl:cons ':linear_vel (linear_vel msg))
    (cl:cons ':steering_angle_vel (steering_angle_vel msg))
))
