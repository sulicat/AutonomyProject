
(cl:in-package :asdf)

(defsystem "world_vis-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "VehicleMoveCommand" :depends-on ("_package_VehicleMoveCommand"))
    (:file "_package_VehicleMoveCommand" :depends-on ("_package"))
    (:file "VehicleState" :depends-on ("_package_VehicleState"))
    (:file "_package_VehicleState" :depends-on ("_package"))
  ))