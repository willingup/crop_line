## *********************************************************
##
## File autogenerated for the opencv_apps package
## by the dynamic_reconfigure package.
## Please do not edit.
##
## ********************************************************/

from dynamic_reconfigure.encoding import extract_params

inf = float('inf')

config_description = {'upper': 'DEFAULT', 'lower': 'groups', 'srcline': 246, 'name': 'Default', 'parent': 0, 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'cstate': 'true', 'parentname': 'Default', 'class': 'DEFAULT', 'field': 'default', 'state': True, 'parentclass': '', 'groups': [], 'parameters': [{'srcline': 291, 'description': 'Method to recognize faces', 'max': '', 'cconsttype': 'const char * const', 'ctype': 'std::string', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'model_method', 'edit_method': "{'enum_description': 'Method to recognize faces', 'enum': [{'srcline': 41, 'description': 'eigen', 'srcfile': '/home/robot/crop_line/src/opencv_apps/cfg/FaceRecognition.cfg', 'cconsttype': 'const char * const', 'value': 'eigen', 'ctype': 'std::string', 'type': 'str', 'name': 'eigen'}, {'srcline': 42, 'description': 'fisher', 'srcfile': '/home/robot/crop_line/src/opencv_apps/cfg/FaceRecognition.cfg', 'cconsttype': 'const char * const', 'value': 'fisher', 'ctype': 'std::string', 'type': 'str', 'name': 'fisher'}, {'srcline': 43, 'description': 'LBPH', 'srcfile': '/home/robot/crop_line/src/opencv_apps/cfg/FaceRecognition.cfg', 'cconsttype': 'const char * const', 'value': 'LBPH', 'ctype': 'std::string', 'type': 'str', 'name': 'LBPH'}]}", 'default': 'eigen', 'level': 0, 'min': '', 'type': 'str'}, {'srcline': 291, 'description': 'Use saved data', 'max': True, 'cconsttype': 'const bool', 'ctype': 'bool', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'use_saved_data', 'edit_method': '', 'default': True, 'level': 0, 'min': False, 'type': 'bool'}, {'srcline': 291, 'description': 'Save train data', 'max': True, 'cconsttype': 'const bool', 'ctype': 'bool', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'save_train_data', 'edit_method': '', 'default': True, 'level': 0, 'min': False, 'type': 'bool'}, {'srcline': 291, 'description': 'Save directory for train data', 'max': '', 'cconsttype': 'const char * const', 'ctype': 'std::string', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'data_dir', 'edit_method': '', 'default': '~/.ros/opencv_apps/face_data', 'level': 0, 'min': '', 'type': 'str'}, {'srcline': 291, 'description': 'Width of training face image', 'max': 500, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'face_model_width', 'edit_method': '', 'default': 190, 'level': 0, 'min': 30, 'type': 'int'}, {'srcline': 291, 'description': 'Height of training face image', 'max': 500, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'face_model_height', 'edit_method': '', 'default': 90, 'level': 0, 'min': 30, 'type': 'int'}, {'srcline': 291, 'description': 'Padding ratio of each face', 'max': 2.0, 'cconsttype': 'const double', 'ctype': 'double', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'face_padding', 'edit_method': '', 'default': 0.1, 'level': 0, 'min': 0.0, 'type': 'double'}, {'srcline': 291, 'description': 'Number of components for face recognizer model', 'max': 100, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'model_num_components', 'edit_method': '', 'default': 0, 'level': 0, 'min': 0, 'type': 'int'}, {'srcline': 291, 'description': 'Threshold for face recognizer model', 'max': 10000.0, 'cconsttype': 'const double', 'ctype': 'double', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'model_threshold', 'edit_method': '', 'default': 8000.0, 'level': 0, 'min': 0.0, 'type': 'double'}, {'srcline': 291, 'description': 'Radius parameter used only for LBPH model', 'max': 10, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'lbph_radius', 'edit_method': '', 'default': 1, 'level': 0, 'min': 1, 'type': 'int'}, {'srcline': 291, 'description': 'Neighbors parameter used only for LBPH model', 'max': 30, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'lbph_neighbors', 'edit_method': '', 'default': 8, 'level': 0, 'min': 1, 'type': 'int'}, {'srcline': 291, 'description': 'grid_x parameter used only for LBPH model', 'max': 30, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'lbph_grid_x', 'edit_method': '', 'default': 8, 'level': 0, 'min': 1, 'type': 'int'}, {'srcline': 291, 'description': 'grid_y parameter used only for LBPH model', 'max': 30, 'cconsttype': 'const int', 'ctype': 'int', 'srcfile': '/opt/ros/melodic/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py', 'name': 'lbph_grid_y', 'edit_method': '', 'default': 8, 'level': 0, 'min': 1, 'type': 'int'}], 'type': '', 'id': 0}

min = {}
max = {}
defaults = {}
level = {}
type = {}
all_level = 0

#def extract_params(config):
#    params = []
#    params.extend(config['parameters'])
#    for group in config['groups']:
#        params.extend(extract_params(group))
#    return params

for param in extract_params(config_description):
    min[param['name']] = param['min']
    max[param['name']] = param['max']
    defaults[param['name']] = param['default']
    level[param['name']] = param['level']
    type[param['name']] = param['type']
    all_level = all_level | param['level']

FaceRecognition_eigen = 'eigen'
FaceRecognition_fisher = 'fisher'
FaceRecognition_LBPH = 'LBPH'
