;; Auto-generated. Do not edit!


(when (boundp 'follow_crop::angle)
  (if (not (find-package "FOLLOW_CROP"))
    (make-package "FOLLOW_CROP"))
  (shadow 'angle (find-package "FOLLOW_CROP")))
(unless (find-package "FOLLOW_CROP::ANGLE")
  (make-package "FOLLOW_CROP::ANGLE"))

(in-package "ROS")
;;//! \htmlinclude angle.msg.html


(defclass follow_crop::angle
  :super ros::object
  :slots (_angle ))

(defmethod follow_crop::angle
  (:init
   (&key
    ((:angle __angle) 0.0)
    )
   (send-super :init)
   (setq _angle (float __angle))
   self)
  (:angle
   (&optional __angle)
   (if __angle (setq _angle __angle)) _angle)
  (:serialization-length
   ()
   (+
    ;; float32 _angle
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _angle
       (sys::poke _angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _angle
     (setq _angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get follow_crop::angle :md5sum-) "2d11dcdbe5a6f73dd324353dc52315ab")
(setf (get follow_crop::angle :datatype-) "follow_crop/angle")
(setf (get follow_crop::angle :definition-)
      "float32 angle

")



(provide :follow_crop/angle "2d11dcdbe5a6f73dd324353dc52315ab")


