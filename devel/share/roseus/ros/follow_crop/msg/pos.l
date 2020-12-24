;; Auto-generated. Do not edit!


(when (boundp 'follow_crop::pos)
  (if (not (find-package "FOLLOW_CROP"))
    (make-package "FOLLOW_CROP"))
  (shadow 'pos (find-package "FOLLOW_CROP")))
(unless (find-package "FOLLOW_CROP::POS")
  (make-package "FOLLOW_CROP::POS"))

(in-package "ROS")
;;//! \htmlinclude pos.msg.html


(defclass follow_crop::pos
  :super ros::object
  :slots (_direction ))

(defmethod follow_crop::pos
  (:init
   (&key
    ((:direction __direction) 0)
    )
   (send-super :init)
   (setq _direction (round __direction))
   self)
  (:direction
   (&optional __direction)
   (if __direction (setq _direction __direction)) _direction)
  (:serialization-length
   ()
   (+
    ;; int32 _direction
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _direction
       (write-long _direction s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _direction
     (setq _direction (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get follow_crop::pos :md5sum-) "3b685cbe3a2d37c79069d18fc947a4de")
(setf (get follow_crop::pos :datatype-) "follow_crop/pos")
(setf (get follow_crop::pos :definition-)
      "int32 direction
")



(provide :follow_crop/pos "3b685cbe3a2d37c79069d18fc947a4de")


