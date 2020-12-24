
(cl:in-package :asdf)

(defsystem "follow_crop-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "angle" :depends-on ("_package_angle"))
    (:file "_package_angle" :depends-on ("_package"))
    (:file "pos" :depends-on ("_package_pos"))
    (:file "_package_pos" :depends-on ("_package"))
  ))