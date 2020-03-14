;; Auto-generated. Do not edit!


(when (boundp 'simple_car_model::VehicleState)
  (if (not (find-package "SIMPLE_CAR_MODEL"))
    (make-package "SIMPLE_CAR_MODEL"))
  (shadow 'VehicleState (find-package "SIMPLE_CAR_MODEL")))
(unless (find-package "SIMPLE_CAR_MODEL::VEHICLESTATE")
  (make-package "SIMPLE_CAR_MODEL::VEHICLESTATE"))

(in-package "ROS")
;;//! \htmlinclude VehicleState.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass simple_car_model::VehicleState
  :super ros::object
  :slots (_header _position _vel _accel _steering_angle _vehicle_angle _vehicle_width _vehicle_length ))

(defmethod simple_car_model::VehicleState
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:position __position) (instance geometry_msgs::Vector3 :init))
    ((:vel __vel) (instance geometry_msgs::Vector3 :init))
    ((:accel __accel) (instance geometry_msgs::Vector3 :init))
    ((:steering_angle __steering_angle) 0.0)
    ((:vehicle_angle __vehicle_angle) 0.0)
    ((:vehicle_width __vehicle_width) 0.0)
    ((:vehicle_length __vehicle_length) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _position __position)
   (setq _vel __vel)
   (setq _accel __accel)
   (setq _steering_angle (float __steering_angle))
   (setq _vehicle_angle (float __vehicle_angle))
   (setq _vehicle_width (float __vehicle_width))
   (setq _vehicle_length (float __vehicle_length))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:position
   (&rest __position)
   (if (keywordp (car __position))
       (send* _position __position)
     (progn
       (if __position (setq _position (car __position)))
       _position)))
  (:vel
   (&rest __vel)
   (if (keywordp (car __vel))
       (send* _vel __vel)
     (progn
       (if __vel (setq _vel (car __vel)))
       _vel)))
  (:accel
   (&rest __accel)
   (if (keywordp (car __accel))
       (send* _accel __accel)
     (progn
       (if __accel (setq _accel (car __accel)))
       _accel)))
  (:steering_angle
   (&optional __steering_angle)
   (if __steering_angle (setq _steering_angle __steering_angle)) _steering_angle)
  (:vehicle_angle
   (&optional __vehicle_angle)
   (if __vehicle_angle (setq _vehicle_angle __vehicle_angle)) _vehicle_angle)
  (:vehicle_width
   (&optional __vehicle_width)
   (if __vehicle_width (setq _vehicle_width __vehicle_width)) _vehicle_width)
  (:vehicle_length
   (&optional __vehicle_length)
   (if __vehicle_length (setq _vehicle_length __vehicle_length)) _vehicle_length)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; geometry_msgs/Vector3 _position
    (send _position :serialization-length)
    ;; geometry_msgs/Vector3 _vel
    (send _vel :serialization-length)
    ;; geometry_msgs/Vector3 _accel
    (send _accel :serialization-length)
    ;; float32 _steering_angle
    4
    ;; float32 _vehicle_angle
    4
    ;; float32 _vehicle_width
    4
    ;; float32 _vehicle_length
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; geometry_msgs/Vector3 _position
       (send _position :serialize s)
     ;; geometry_msgs/Vector3 _vel
       (send _vel :serialize s)
     ;; geometry_msgs/Vector3 _accel
       (send _accel :serialize s)
     ;; float32 _steering_angle
       (sys::poke _steering_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vehicle_angle
       (sys::poke _vehicle_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vehicle_width
       (sys::poke _vehicle_width (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vehicle_length
       (sys::poke _vehicle_length (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; geometry_msgs/Vector3 _position
     (send _position :deserialize buf ptr-) (incf ptr- (send _position :serialization-length))
   ;; geometry_msgs/Vector3 _vel
     (send _vel :deserialize buf ptr-) (incf ptr- (send _vel :serialization-length))
   ;; geometry_msgs/Vector3 _accel
     (send _accel :deserialize buf ptr-) (incf ptr- (send _accel :serialization-length))
   ;; float32 _steering_angle
     (setq _steering_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vehicle_angle
     (setq _vehicle_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vehicle_width
     (setq _vehicle_width (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vehicle_length
     (setq _vehicle_length (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get simple_car_model::VehicleState :md5sum-) "ee5f58c0c027a7069a3e20bf33a427ae")
(setf (get simple_car_model::VehicleState :datatype-) "simple_car_model/VehicleState")
(setf (get simple_car_model::VehicleState :definition-)
      "Header header
geometry_msgs/Vector3 position
geometry_msgs/Vector3 vel
geometry_msgs/Vector3 accel
float32 steering_angle
float32 vehicle_angle
float32 vehicle_width
float32 vehicle_length
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
")



(provide :simple_car_model/VehicleState "ee5f58c0c027a7069a3e20bf33a427ae")


