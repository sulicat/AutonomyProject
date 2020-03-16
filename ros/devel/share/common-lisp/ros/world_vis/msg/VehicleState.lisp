; Auto-generated. Do not edit!


(cl:in-package world_vis-msg)


;//! \htmlinclude VehicleState.msg.html

(cl:defclass <VehicleState> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (pos
    :reader pos
    :initarg :pos
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (steering_angle
    :reader steering_angle
    :initarg :steering_angle
    :type cl:float
    :initform 0.0)
   (vehicle_angle
    :reader vehicle_angle
    :initarg :vehicle_angle
    :type cl:float
    :initform 0.0)
   (vehicle_width
    :reader vehicle_width
    :initarg :vehicle_width
    :type cl:float
    :initform 0.0)
   (vehicle_length
    :reader vehicle_length
    :initarg :vehicle_length
    :type cl:float
    :initform 0.0)
   (linear_vel
    :reader linear_vel
    :initarg :linear_vel
    :type cl:float
    :initform 0.0)
   (steering_angle_vel
    :reader steering_angle_vel
    :initarg :steering_angle_vel
    :type cl:float
    :initform 0.0)
   (linear_accel
    :reader linear_accel
    :initarg :linear_accel
    :type cl:float
    :initform 0.0)
   (steering_angle_acel
    :reader steering_angle_acel
    :initarg :steering_angle_acel
    :type cl:float
    :initform 0.0))
)

(cl:defclass VehicleState (<VehicleState>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <VehicleState>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'VehicleState)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name world_vis-msg:<VehicleState> is deprecated: use world_vis-msg:VehicleState instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <VehicleState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world_vis-msg:header-val is deprecated.  Use world_vis-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'pos-val :lambda-list '(m))
(cl:defmethod pos-val ((m <VehicleState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world_vis-msg:pos-val is deprecated.  Use world_vis-msg:pos instead.")
  (pos m))

(cl:ensure-generic-function 'steering_angle-val :lambda-list '(m))
(cl:defmethod steering_angle-val ((m <VehicleState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world_vis-msg:steering_angle-val is deprecated.  Use world_vis-msg:steering_angle instead.")
  (steering_angle m))

(cl:ensure-generic-function 'vehicle_angle-val :lambda-list '(m))
(cl:defmethod vehicle_angle-val ((m <VehicleState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world_vis-msg:vehicle_angle-val is deprecated.  Use world_vis-msg:vehicle_angle instead.")
  (vehicle_angle m))

(cl:ensure-generic-function 'vehicle_width-val :lambda-list '(m))
(cl:defmethod vehicle_width-val ((m <VehicleState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world_vis-msg:vehicle_width-val is deprecated.  Use world_vis-msg:vehicle_width instead.")
  (vehicle_width m))

(cl:ensure-generic-function 'vehicle_length-val :lambda-list '(m))
(cl:defmethod vehicle_length-val ((m <VehicleState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world_vis-msg:vehicle_length-val is deprecated.  Use world_vis-msg:vehicle_length instead.")
  (vehicle_length m))

(cl:ensure-generic-function 'linear_vel-val :lambda-list '(m))
(cl:defmethod linear_vel-val ((m <VehicleState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world_vis-msg:linear_vel-val is deprecated.  Use world_vis-msg:linear_vel instead.")
  (linear_vel m))

(cl:ensure-generic-function 'steering_angle_vel-val :lambda-list '(m))
(cl:defmethod steering_angle_vel-val ((m <VehicleState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world_vis-msg:steering_angle_vel-val is deprecated.  Use world_vis-msg:steering_angle_vel instead.")
  (steering_angle_vel m))

(cl:ensure-generic-function 'linear_accel-val :lambda-list '(m))
(cl:defmethod linear_accel-val ((m <VehicleState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world_vis-msg:linear_accel-val is deprecated.  Use world_vis-msg:linear_accel instead.")
  (linear_accel m))

(cl:ensure-generic-function 'steering_angle_acel-val :lambda-list '(m))
(cl:defmethod steering_angle_acel-val ((m <VehicleState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world_vis-msg:steering_angle_acel-val is deprecated.  Use world_vis-msg:steering_angle_acel instead.")
  (steering_angle_acel m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <VehicleState>) ostream)
  "Serializes a message object of type '<VehicleState>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pos) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'steering_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vehicle_angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vehicle_width))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vehicle_length))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
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
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'linear_accel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'steering_angle_acel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <VehicleState>) istream)
  "Deserializes a message object of type '<VehicleState>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pos) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'steering_angle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vehicle_angle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vehicle_width) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vehicle_length) (roslisp-utils:decode-single-float-bits bits)))
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
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'linear_accel) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'steering_angle_acel) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<VehicleState>)))
  "Returns string type for a message object of type '<VehicleState>"
  "world_vis/VehicleState")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'VehicleState)))
  "Returns string type for a message object of type 'VehicleState"
  "world_vis/VehicleState")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<VehicleState>)))
  "Returns md5sum for a message object of type '<VehicleState>"
  "43281be11163876743cb99e5003e3502")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'VehicleState)))
  "Returns md5sum for a message object of type 'VehicleState"
  "43281be11163876743cb99e5003e3502")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<VehicleState>)))
  "Returns full string definition for message of type '<VehicleState>"
  (cl:format cl:nil "Header header~%geometry_msgs/Vector3 pos~%float32 steering_angle~%float32 vehicle_angle~%float32 vehicle_width~%float32 vehicle_length~%float32 linear_vel~%float32 steering_angle_vel~%float32 linear_accel~%float32 steering_angle_acel~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'VehicleState)))
  "Returns full string definition for message of type 'VehicleState"
  (cl:format cl:nil "Header header~%geometry_msgs/Vector3 pos~%float32 steering_angle~%float32 vehicle_angle~%float32 vehicle_width~%float32 vehicle_length~%float32 linear_vel~%float32 steering_angle_vel~%float32 linear_accel~%float32 steering_angle_acel~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <VehicleState>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pos))
     4
     4
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <VehicleState>))
  "Converts a ROS message object to a list"
  (cl:list 'VehicleState
    (cl:cons ':header (header msg))
    (cl:cons ':pos (pos msg))
    (cl:cons ':steering_angle (steering_angle msg))
    (cl:cons ':vehicle_angle (vehicle_angle msg))
    (cl:cons ':vehicle_width (vehicle_width msg))
    (cl:cons ':vehicle_length (vehicle_length msg))
    (cl:cons ':linear_vel (linear_vel msg))
    (cl:cons ':steering_angle_vel (steering_angle_vel msg))
    (cl:cons ':linear_accel (linear_accel msg))
    (cl:cons ':steering_angle_acel (steering_angle_acel msg))
))
