;; Auto-generated. Do not edit!


(when (boundp 'world_vis::VehicleState)
  (if (not (find-package "WORLD_VIS"))
    (make-package "WORLD_VIS"))
  (shadow 'VehicleState (find-package "WORLD_VIS")))
(unless (find-package "WORLD_VIS::VEHICLESTATE")
  (make-package "WORLD_VIS::VEHICLESTATE"))

(in-package "ROS")
;;//! \htmlinclude VehicleState.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass world_vis::VehicleState
  :super ros::object
  :slots (_header _pos _steering_angle _vehicle_angle _vehicle_width _vehicle_length _linear_vel _steering_angle_vel _linear_accel _steering_angle_acel ))

(defmethod world_vis::VehicleState
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:pos __pos) (instance geometry_msgs::Vector3 :init))
    ((:steering_angle __steering_angle) 0.0)
    ((:vehicle_angle __vehicle_angle) 0.0)
    ((:vehicle_width __vehicle_width) 0.0)
    ((:vehicle_length __vehicle_length) 0.0)
    ((:linear_vel __linear_vel) 0.0)
    ((:steering_angle_vel __steering_angle_vel) 0.0)
    ((:linear_accel __linear_accel) 0.0)
    ((:steering_angle_acel __steering_angle_acel) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _pos __pos)
   (setq _steering_angle (float __steering_angle))
   (setq _vehicle_angle (float __vehicle_angle))
   (setq _vehicle_width (float __vehicle_width))
   (setq _vehicle_length (float __vehicle_length))
   (setq _linear_vel (float __linear_vel))
   (setq _steering_angle_vel (float __steering_angle_vel))
   (setq _linear_accel (float __linear_accel))
   (setq _steering_angle_acel (float __steering_angle_acel))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:pos
   (&rest __pos)
   (if (keywordp (car __pos))
       (send* _pos __pos)
     (progn
       (if __pos (setq _pos (car __pos)))
       _pos)))
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
  (:linear_vel
   (&optional __linear_vel)
   (if __linear_vel (setq _linear_vel __linear_vel)) _linear_vel)
  (:steering_angle_vel
   (&optional __steering_angle_vel)
   (if __steering_angle_vel (setq _steering_angle_vel __steering_angle_vel)) _steering_angle_vel)
  (:linear_accel
   (&optional __linear_accel)
   (if __linear_accel (setq _linear_accel __linear_accel)) _linear_accel)
  (:steering_angle_acel
   (&optional __steering_angle_acel)
   (if __steering_angle_acel (setq _steering_angle_acel __steering_angle_acel)) _steering_angle_acel)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; geometry_msgs/Vector3 _pos
    (send _pos :serialization-length)
    ;; float32 _steering_angle
    4
    ;; float32 _vehicle_angle
    4
    ;; float32 _vehicle_width
    4
    ;; float32 _vehicle_length
    4
    ;; float32 _linear_vel
    4
    ;; float32 _steering_angle_vel
    4
    ;; float32 _linear_accel
    4
    ;; float32 _steering_angle_acel
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; geometry_msgs/Vector3 _pos
       (send _pos :serialize s)
     ;; float32 _steering_angle
       (sys::poke _steering_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vehicle_angle
       (sys::poke _vehicle_angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vehicle_width
       (sys::poke _vehicle_width (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vehicle_length
       (sys::poke _vehicle_length (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _linear_vel
       (sys::poke _linear_vel (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _steering_angle_vel
       (sys::poke _steering_angle_vel (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _linear_accel
       (sys::poke _linear_accel (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _steering_angle_acel
       (sys::poke _steering_angle_acel (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; geometry_msgs/Vector3 _pos
     (send _pos :deserialize buf ptr-) (incf ptr- (send _pos :serialization-length))
   ;; float32 _steering_angle
     (setq _steering_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vehicle_angle
     (setq _vehicle_angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vehicle_width
     (setq _vehicle_width (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vehicle_length
     (setq _vehicle_length (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _linear_vel
     (setq _linear_vel (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _steering_angle_vel
     (setq _steering_angle_vel (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _linear_accel
     (setq _linear_accel (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _steering_angle_acel
     (setq _steering_angle_acel (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get world_vis::VehicleState :md5sum-) "43281be11163876743cb99e5003e3502")
(setf (get world_vis::VehicleState :datatype-) "world_vis/VehicleState")
(setf (get world_vis::VehicleState :definition-)
      "Header header
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
")



(provide :world_vis/VehicleState "43281be11163876743cb99e5003e3502")


