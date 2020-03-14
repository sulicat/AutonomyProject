;; Auto-generated. Do not edit!


(when (boundp 'simple_car_model::VehicleMoveCommand)
  (if (not (find-package "SIMPLE_CAR_MODEL"))
    (make-package "SIMPLE_CAR_MODEL"))
  (shadow 'VehicleMoveCommand (find-package "SIMPLE_CAR_MODEL")))
(unless (find-package "SIMPLE_CAR_MODEL::VEHICLEMOVECOMMAND")
  (make-package "SIMPLE_CAR_MODEL::VEHICLEMOVECOMMAND"))

(in-package "ROS")
;;//! \htmlinclude VehicleMoveCommand.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass simple_car_model::VehicleMoveCommand
  :super ros::object
  :slots (_header _linear_vel _steering_angle_vel ))

(defmethod simple_car_model::VehicleMoveCommand
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:linear_vel __linear_vel) 0.0)
    ((:steering_angle_vel __steering_angle_vel) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _linear_vel (float __linear_vel))
   (setq _steering_angle_vel (float __steering_angle_vel))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:linear_vel
   (&optional __linear_vel)
   (if __linear_vel (setq _linear_vel __linear_vel)) _linear_vel)
  (:steering_angle_vel
   (&optional __steering_angle_vel)
   (if __steering_angle_vel (setq _steering_angle_vel __steering_angle_vel)) _steering_angle_vel)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float32 _linear_vel
    4
    ;; float32 _steering_angle_vel
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float32 _linear_vel
       (sys::poke _linear_vel (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _steering_angle_vel
       (sys::poke _steering_angle_vel (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float32 _linear_vel
     (setq _linear_vel (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _steering_angle_vel
     (setq _steering_angle_vel (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get simple_car_model::VehicleMoveCommand :md5sum-) "10971e0348cab38ff52d6137bdf2a0a6")
(setf (get simple_car_model::VehicleMoveCommand :datatype-) "simple_car_model/VehicleMoveCommand")
(setf (get simple_car_model::VehicleMoveCommand :definition-)
      "Header header
float32 linear_vel
float32 steering_angle_vel
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

")



(provide :simple_car_model/VehicleMoveCommand "10971e0348cab38ff52d6137bdf2a0a6")


