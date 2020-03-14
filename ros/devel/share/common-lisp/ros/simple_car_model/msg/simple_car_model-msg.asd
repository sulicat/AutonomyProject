
(cl:in-package :asdf)

(defsystem "simple_car_model-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "VehicleState" :depends-on ("_package_VehicleState"))
    (:file "_package_VehicleState" :depends-on ("_package"))
  ))